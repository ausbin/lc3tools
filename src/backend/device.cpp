/*
 * Copyright 2020 McGraw-Hill Education. All rights reserved. No reproduction or distribution without the prior written consent of McGraw-Hill Education.
 */
#include <cstring>
#include <unistd.h>
#include <fcntl.h>

#include "device.h"

using namespace lc3::core;

std::pair<uint16_t, PIMicroOp> RWReg::read(uint16_t addr)
{
    if(addr == data_addr) {
        return std::make_pair(data.getValue(), nullptr);
    }

    return std::make_pair(0x0000, nullptr);
}

PIMicroOp RWReg::write(uint16_t addr, uint16_t value)
{
    if(addr == data_addr) {
        data.setValue(value);
    }

    return nullptr;
}

std::vector<uint16_t> RWReg::getAddrMap(void) const
{
    return { data_addr };
}

KeyboardDevice::KeyboardDevice(lc3::utils::IInputter & inputter) : inputter(inputter)
{
    status.setValue(0x0000);
    data.setValue(0x0000);
}

void KeyboardDevice::startup(void)
{
    inputter.beginInput();
}

void KeyboardDevice::shutdown(void)
{
    inputter.endInput();
}

std::pair<uint16_t, PIMicroOp> KeyboardDevice::read(uint16_t addr)
{
    if(addr == KBSR) {
        PIMicroOp callback = std::make_shared<CallbackMicroOp>(CallbackType::INPUT_POLL);
        return std::make_pair(status.getValue(), callback);
    } else if(addr == KBDR) {
        uint16_t status_value = status.getValue();
        if(utils::getBit(status_value, 15) == 1) {
            PIMicroOp write_addr = std::make_shared<RegWriteImmMicroOp>(8, KBSR);
            PIMicroOp toggle_status = std::make_shared<MemWriteImmMicroOp>(8, status_value & 0x7FFF);
            PIMicroOp pop_from_buffer = std::make_shared<GenericPopMicroOp<std::queue<KeyInfo>>>(key_buffer, "kbbuf");
            write_addr->insert(toggle_status);
            toggle_status->insert(pop_from_buffer);
            return std::make_pair(data.getValue(), write_addr);
        } else {
            PIMicroOp callback = nullptr;

            if(! inputter.hasRemaining()) {
                callback = std::make_shared<CallbackMicroOp>(CallbackType::INPUT_REQUEST);
            }

            return std::make_pair(data.getValue(), callback);
        }
    }

    return std::make_pair(0x0000, nullptr);
}

PIMicroOp KeyboardDevice::write(uint16_t addr, uint16_t value)
{
    if(addr == KBSR) {
        status.setValue(value & 0x4000);
    }

    return nullptr;
}

std::vector<uint16_t> KeyboardDevice::getAddrMap(void) const
{
    return { KBSR, KBDR };
}

PIMicroOp KeyboardDevice::tick(void)
{
    // Set ready bit.
    char c;
    if(inputter.getChar(c)) {
        key_buffer.emplace(c);
    }

    if(! key_buffer.empty()) {
        status.setValue(status.getValue() | 0x8000);
        data.setValue(static_cast<uint16_t>(key_buffer.front().value));

        if(! key_buffer.front().triggered_interrupt && (status.getValue() & 0x4000) == 0x4000) {
            key_buffer.front().triggered_interrupt = true;
            return std::make_shared<PushInterruptTypeMicroOp>(InterruptType::KEYBOARD);
        }
    }

    return nullptr;
}

std::pair<uint16_t, PIMicroOp> DisplayDevice::read(uint16_t addr)
{
    if(addr == DSR) {
        return std::make_pair(status.getValue(), nullptr);
    }

    return std::make_pair(0x0000, nullptr);
}

DisplayDevice::DisplayDevice(lc3::utils::Logger & logger) : logger(logger)
{
    status.setValue(0x0000);
    data.setValue(0x0000);
}

PIMicroOp DisplayDevice::write(uint16_t addr, uint16_t value)
{
    if(addr == DSR) {
        status.setValue(value & 0x4000);
    } else if(addr == DDR) {
        // Clear ready bit.
        status.setValue(status.getValue() & 0x7FFF);

        // Write to DDR and output to screen.
        data.setValue(value & 0x00FF);
        char char_value = static_cast<char>(value & 0x00FF);
        if(char_value == 10 || char_value == 13) {
            logger.newline(utils::PrintType::P_NONE);
        } else {
            logger.print(std::string(1, char_value));
        }
    }

    return nullptr;
}

std::vector<uint16_t> DisplayDevice::getAddrMap(void) const
{
    return { DSR, DDR };
}

PIMicroOp DisplayDevice::tick(void)
{
    // Set ready bit.
    status.setValue(status.getValue() | 0x8000);

    return nullptr;
}

void Tape::openFileIfNeeded(void)
{
    if (!fp) {
        // TODO: use this hack on Windows
        //FILE *hack;
        //if (!(hack = fopen(path.c_str(), "a"))) {
        //    throw lc3::utils::exception("Could not try to create tape `" + path + "': "
        //                                + std::strerror(errno));
        //}
        //if (fclose(hack)) {
        //    throw lc3::utils::exception("Could not try to close tape `" + path + "': "
        //                                + std::strerror(errno));
        //}

        //if (!(fp = fopen(path.c_str(), "r+"))) {
        //    throw lc3::utils::exception("Could not open tape `" + path + "': "
        //                                + std::strerror(errno));
        //}
        int fd;
        if ((fd = open(path.c_str(), O_CREAT | O_RDWR, 0644)) < 0) {
            throw lc3::utils::exception("Could not open() tape `" + path + "': "
                                        + std::strerror(errno));
        }
        if (!(fp = fdopen(fd, "r+"))) {
            close(fd);
            throw lc3::utils::exception("Could not fdopen() tape `" + path + "': "
                                        + std::strerror(errno));
        }

        int ret;
        if ((ret = fseek(fp, 0, SEEK_END)) < 0) {
            throw lc3::utils::exception("Could not seek in tape `" + path + "': "
                                        + std::strerror(errno));
        }
        file_size = ret;
        if (fseek(fp, 0, SEEK_SET) < 0) {
            throw lc3::utils::exception("Could not rewind tape `" + path + "': "
                                        + std::strerror(errno));
        }
        file_pos = 0;
    }
}

void Tape::resizeTo(size_t size)
{
    file_size = size;

    // Need to resize yolo
    if (fflush(fp) == EOF) {
        throw lc3::utils::exception("Could not flush tape `" + path + "': "
                                    + std::strerror(errno));
    }
    // Drop down to lower unix level
    // TODO: support windows
    int fd;
    if ((fd = fileno(fp)) < 0) {
        throw lc3::utils::exception("Could not get fd for tape `" + path + "': "
                                    + std::strerror(errno));
    }
    if (ftruncate(fd, size) < 0) {
        throw lc3::utils::exception("Could not grow tape `" + path + "': "
                                    + std::strerror(errno));
    }
}

void Tape::growIfNeeded(size_t pos)
{
    if (pos >= file_size) {
        resizeTo(file_size + 1024);
    }
}

void Tape::seek(size_t pos)
{
    openFileIfNeeded();
    growIfNeeded(pos);

    if (fseek(fp, 0, SEEK_SET) < 0) {
        throw lc3::utils::exception("Could not rewind tape `" + path + "': "
                                    + std::strerror(errno));
    }
}

int Tape::getc(void) {
    openFileIfNeeded();

    int ret;
    if ((ret = fgetc(fp)) == EOF) {
        return -1;
    } else {
        file_pos++;
        return ret;
    }
}

void Tape::putc(uint8_t c)
{
    openFileIfNeeded();
    growIfNeeded(file_pos);

    // In case the last thing we did was a read
    // (required by ANSI C)
    if (fseek(fp, file_pos, SEEK_SET) < 0) {
        throw lc3::utils::exception("Could not fseek(0) tape `" + path + "': "
                                    + std::strerror(errno));
    }

    int ret;
    if ((ret = fputc(c, fp)) == EOF) {
        throw lc3::utils::exception("Could not fputc to tape `" + path
                                    + "': " + std::strerror(errno));
    } else {
        file_pos++;
    }
}

void Tape::setEof(void) {
    openFileIfNeeded();

    resizeTo(file_pos);
}

Tape::~Tape(void)
{
    if (fp) {
        if (fclose(fp)) {
            // TODO: fix warning about this
            throw lc3::utils::exception("Could not close tape `" + path + "': " + std::strerror(errno));
        }
    }
}

TapeDriveDevice::TapeDriveDevice(std::vector<Tape> tapes) : tapes(tapes)
{
    recv_status.setValue(0x0000);
    recv_data.setValue(0x0000);
    send_status.setValue(0x0000);
    send_data.setValue(0x0000);
}

void TapeDriveDevice::startup(void)
{
    // TODO: remove this?
}

void TapeDriveDevice::shutdown(void)
{
    // TODO: remove this?
}

std::pair<uint16_t, PIMicroOp> TapeDriveDevice::read(uint16_t addr)
{
    uint16_t value;
    switch (addr) {
        case TRSR:
            value = recv_status.getValue();
            break;
        case TSSR:
            value = send_status.getValue();
            break;
        case TRDR:
            // Clear ready bit. Don't bother with micro-op nonsense
            recv_status.setValue(recv_status.getValue() & 0x7FFF);
            value = recv_data.getValue();
            break;
        default:
            value = 0x0000;
    }
    return std::make_pair(value, nullptr);
}

void TapeDriveDevice::reply(RecvOpcode opcode, unsigned int tape_num, uint8_t data)
{
    recv_status.setValue(recv_status.getValue() | 0x8000);
    // Message format:
    // 15     14 13       8 7         0
    // .-------------------------------.
    // | opcode | tape num |   data    |
    // '-------------------------------'
    recv_data.setValue(static_cast<unsigned int>(opcode) << 14 | tape_num << 8 | data);
}

void TapeDriveDevice::replyError(unsigned int tape_num, RecvError err) {
    reply(RecvOpcode::ERROR, tape_num, static_cast<uint8_t>(err));
}

PIMicroOp TapeDriveDevice::write(uint16_t addr, uint16_t value)
{
    if (addr == TSDR && (send_status.getValue() & 0x8000)) {
        // Clear ready bit. Don't bother with micro-op nonsense
        send_status.setValue(send_status.getValue() & 0x7FFF);
        // TODO: get rid of this?
        send_data.setValue(value);

        // Message format:
        // 15     14 13       8 7         0
        // .-------------------------------.
        // | opcode | tape num |   data    |
        // '-------------------------------'
        SendOpcode opcode = static_cast<SendOpcode>(value >> 14);
        unsigned int tape_num = (value >> 8) & 0x3FU;
        uint8_t data = value & 0xFFU;

        if (tape_num >= tapes.size()) {
            // TODO: reply with ERROR
        }

        Tape &tape = tapes[tape_num];

        int c;
        switch (opcode) {
            case SendOpcode::SEEK:
                tape.seek(data);
                reply(RecvOpcode::ACK, tape_num, 0);
                break;
            case SendOpcode::GETC:
                if (data) {
                    replyError(tape_num, RecvError::BAD_ARG);
                } else {
                    c = tape.getc();
                    if (c < 0) { // EOF
                        replyError(tape_num, RecvError::END_OF_TAPE);
                    } else {
                        reply(RecvOpcode::DATA, tape_num, c);
                    }
                }
                break;
            case SendOpcode::PUTC:
                tape.putc(data);
                reply(RecvOpcode::ACK, tape_num, 0);
                break;
            case SendOpcode::SET_EOF:
                if (data) {
                    replyError(tape_num, RecvError::BAD_ARG);
                } else {
                    tape.setEof();
                    reply(RecvOpcode::ACK, tape_num, 0);
                }
                break;
            default:
                // Should be unreachable, but just in case
                replyError(tape_num, RecvError::BAD_OPCODE);
                break;
        }
    }

    return nullptr;
}

std::vector<uint16_t> TapeDriveDevice::getAddrMap(void) const
{
    return { TRSR, TRDR, TSSR, TSDR };
}

PIMicroOp TapeDriveDevice::tick(void)
{
    // Set ready bit.
    send_status.setValue(send_status.getValue() | 0x8000);

    return nullptr;
}
