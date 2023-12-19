/*
 * Copyright 2020 McGraw-Hill Education. All rights reserved. No reproduction or distribution without the prior written consent of McGraw-Hill Education.
 */
#ifndef DEVICE_H
#define DEVICE_H

#include <memory>
#include <vector>
#include <queue>

#include "device_regs.h"
#include "inputter.h"
#include "intex.h"
#include "logger.h"
#include "mem.h"
#include "uop.h"

namespace lc3
{
namespace core
{
    class IDevice
    {
    public:
        IDevice(void) = default;
        virtual ~IDevice(void) {}

        virtual void startup(void) { }
        virtual void shutdown(void) { }
        virtual std::pair<uint16_t, PIMicroOp> read(uint16_t addr) = 0;
        virtual PIMicroOp write(uint16_t addr, uint16_t value) = 0;
        virtual std::vector<uint16_t> getAddrMap(void) const = 0;
        virtual std::string getName(void) const = 0;
        virtual PIMicroOp tick(void) { return nullptr; }
    };

    class RWReg : public IDevice
    {
    public:
        RWReg(uint16_t data_addr) : data_addr(data_addr) { data.setValue(0x0000); }
        virtual ~RWReg(void) override = default;

        virtual std::pair<uint16_t, PIMicroOp> read(uint16_t addr) override;
        virtual PIMicroOp write(uint16_t addr, uint16_t value) override;
        virtual std::vector<uint16_t> getAddrMap(void) const override;
        virtual std::string getName(void) const override { return "RWReg"; }

    private:
        MemLocation data;
        uint16_t data_addr;
    };

    class KeyboardDevice : public IDevice
    {
    public:
        KeyboardDevice(lc3::utils::IInputter & inputter);
        virtual ~KeyboardDevice(void) override = default;

        virtual void startup(void) override;
        virtual void shutdown(void) override;
        virtual std::pair<uint16_t, PIMicroOp> read(uint16_t addr) override;
        virtual PIMicroOp write(uint16_t addr, uint16_t value) override;
        virtual std::vector<uint16_t> getAddrMap(void) const override;
        virtual std::string getName(void) const override { return "Keyboard"; }
        virtual PIMicroOp tick(void) override;

    private:
        lc3::utils::IInputter & inputter;

        MemLocation status;
        MemLocation data;

        struct KeyInfo
        {
            char value;
            bool triggered_interrupt;

            KeyInfo(void) : KeyInfo(0) { }
            KeyInfo(char value) : value(value), triggered_interrupt(false) { }
        };

        std::queue<KeyInfo> key_buffer;
    };

    class DisplayDevice : public IDevice
    {
    public:
        DisplayDevice(lc3::utils::Logger & logger);
        virtual ~DisplayDevice(void) override = default;

        virtual std::pair<uint16_t, PIMicroOp> read(uint16_t addr) override;
        virtual PIMicroOp write(uint16_t addr, uint16_t value) override;
        virtual std::vector<uint16_t> getAddrMap(void) const override;
        virtual std::string getName(void) const override { return "Display"; }
        virtual PIMicroOp tick(void) override;

    private:
        lc3::utils::Logger & logger;

        MemLocation status;
        MemLocation data;
    };

    // TODO: move to tape.h
    class Tape
    {
    public:
        Tape(std::string path) : path(path), fp(nullptr), file_size(0), file_pos(0) {}
        ~Tape(void);

        void seek(size_t pos);
        int getc(void);
        void putc(uint8_t data);
        void setEof(void);
        void shutdown(void);
    private:
        std::string path;
        FILE *fp;
        size_t file_size;
        size_t file_pos;

        void openFileIfNeeded(void);
        void growIfNeeded(size_t pos);
        void resizeTo(size_t size);
    };

    class TapeDriveDevice : public IDevice
    {
    public:
        static constexpr size_t MAX_TAPES = 1 << 6;

        enum class SendOpcode {
            SEEK = 0x0,    // 0b00
            GETC = 0x1,    // 0b01
            PUTC = 0x2,    // 0b10
            SET_EOF = 0x3, // 0b11
        };

        enum class RecvOpcode {
            ERROR = 0x0, // 0b00
            DATA = 0x1,  // 0b01
            ACK = 0x2,   // 0b10
        };

        enum class RecvError {
            BAD_ARG = 0x0,
            BAD_OPCODE = 0x1,
            END_OF_TAPE = 0x2,
        };

        TapeDriveDevice(std::vector<std::string> &tape_names);
        virtual ~TapeDriveDevice(void) override = default;

        virtual void startup(void) override;
        virtual void shutdown(void) override;
        virtual std::pair<uint16_t, PIMicroOp> read(uint16_t addr) override;
        virtual PIMicroOp write(uint16_t addr, uint16_t value) override;
        virtual std::vector<uint16_t> getAddrMap(void) const override;
        virtual std::string getName(void) const override { return "Tape Drive"; }
        virtual PIMicroOp tick(void) override;

    private:
        void reply(RecvOpcode opcode, unsigned int tape_num, uint8_t data);
        void replyError(unsigned int tape_num, RecvError err);

        std::vector<Tape> tapes;
        MemLocation recv_status;
        MemLocation recv_data;
        MemLocation send_status;
        MemLocation send_data;
    };
};
};

#endif
