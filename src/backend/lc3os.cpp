/*
 * Copyright 2020 McGraw-Hill Education. All rights reserved. No reproduction or distribution without the prior written consent of McGraw-Hill Education.
 */
#include "lc3os.h"

namespace lc3
{
namespace core
{
    std::string getOSSrc(void)
    {
        char const * lc3os_src_1 = R"LC3OS1(
    .ORIG x0000

; the TRAP vector table
    .FILL BAD_TRAP     ; x00
    .FILL BAD_TRAP     ; x01
    .FILL BAD_TRAP     ; x02
    .FILL BAD_TRAP     ; x03
    .FILL BAD_TRAP     ; x04
    .FILL BAD_TRAP     ; x05
    .FILL BAD_TRAP     ; x06
    .FILL BAD_TRAP     ; x07
    .FILL BAD_TRAP     ; x08
    .FILL BAD_TRAP     ; x09
    .FILL BAD_TRAP     ; x0A
    .FILL BAD_TRAP     ; x0B
    .FILL BAD_TRAP     ; x0C
    .FILL BAD_TRAP     ; x0D
    .FILL BAD_TRAP     ; x0E
    .FILL BAD_TRAP     ; x0F
    .FILL BAD_TRAP     ; x10
    .FILL BAD_TRAP     ; x11
    .FILL BAD_TRAP     ; x12
    .FILL BAD_TRAP     ; x13
    .FILL BAD_TRAP     ; x14
    .FILL BAD_TRAP     ; x15
    .FILL BAD_TRAP     ; x16
    .FILL BAD_TRAP     ; x17
    .FILL BAD_TRAP     ; x18
    .FILL BAD_TRAP     ; x19
    .FILL BAD_TRAP     ; x1A
    .FILL BAD_TRAP     ; x1B
    .FILL BAD_TRAP     ; x1C
    .FILL BAD_TRAP     ; x1D
    .FILL BAD_TRAP     ; x1E
    .FILL BAD_TRAP     ; x1F
    .FILL TRAP_GETC    ; x20
    .FILL TRAP_OUT     ; x21
    .FILL TRAP_PUTS    ; x22
    .FILL TRAP_IN      ; x23
    .FILL TRAP_PUTSP   ; x24
    .FILL TRAP_HALT    ; x25
    .FILL BAD_TRAP     ; x26
    .FILL BAD_TRAP     ; x27
    .FILL BAD_TRAP     ; x28
    .FILL BAD_TRAP     ; x29
    .FILL BAD_TRAP     ; x2A
    .FILL BAD_TRAP     ; x2B
    .FILL BAD_TRAP     ; x2C
    .FILL BAD_TRAP     ; x2D
    .FILL BAD_TRAP     ; x2E
    .FILL BAD_TRAP     ; x2F
    .FILL TRAP_FOPEN   ; x30
    .FILL TRAP_FPUTC   ; x31
    .FILL TRAP_FGETC   ; x32
    .FILL TRAP_FTRUNC  ; x33
    .FILL TRAP_FREWIND ; x34
    .FILL TRAP_FCLOSE  ; x35
    .FILL BAD_TRAP     ; x36
    .FILL BAD_TRAP     ; x37
    .FILL BAD_TRAP     ; x38
    .FILL BAD_TRAP     ; x39
    .FILL BAD_TRAP     ; x3A
    .FILL BAD_TRAP     ; x3B
    .FILL BAD_TRAP     ; x3C
    .FILL BAD_TRAP     ; x3D
    .FILL BAD_TRAP     ; x3E
    .FILL BAD_TRAP     ; x3F
    .FILL BAD_TRAP     ; x40
    .FILL BAD_TRAP     ; x41
    .FILL BAD_TRAP     ; x42
    .FILL BAD_TRAP     ; x43
    .FILL BAD_TRAP     ; x44
    .FILL BAD_TRAP     ; x45
    .FILL BAD_TRAP     ; x46
    .FILL BAD_TRAP     ; x47
    .FILL BAD_TRAP     ; x48
    .FILL BAD_TRAP     ; x49
    .FILL BAD_TRAP     ; x4A
    .FILL BAD_TRAP     ; x4B
    .FILL BAD_TRAP     ; x4C
    .FILL BAD_TRAP     ; x4D
    .FILL BAD_TRAP     ; x4E
    .FILL BAD_TRAP     ; x4F
    .FILL BAD_TRAP     ; x50
    .FILL BAD_TRAP     ; x51
    .FILL BAD_TRAP     ; x52
    .FILL BAD_TRAP     ; x53
    .FILL BAD_TRAP     ; x54
    .FILL BAD_TRAP     ; x55
    .FILL BAD_TRAP     ; x56
    .FILL BAD_TRAP     ; x57
    .FILL BAD_TRAP     ; x58
    .FILL BAD_TRAP     ; x59
    .FILL BAD_TRAP     ; x5A
    .FILL BAD_TRAP     ; x5B
    .FILL BAD_TRAP     ; x5C
    .FILL BAD_TRAP     ; x5D
    .FILL BAD_TRAP     ; x5E
    .FILL BAD_TRAP     ; x5F
    .FILL BAD_TRAP     ; x60
    .FILL BAD_TRAP     ; x61
    .FILL BAD_TRAP     ; x62
    .FILL BAD_TRAP     ; x63
    .FILL BAD_TRAP     ; x64
    .FILL BAD_TRAP     ; x65
    .FILL BAD_TRAP     ; x66
    .FILL BAD_TRAP     ; x67
    .FILL BAD_TRAP     ; x68
    .FILL BAD_TRAP     ; x69
    .FILL BAD_TRAP     ; x6A
    .FILL BAD_TRAP     ; x6B
    .FILL BAD_TRAP     ; x6C
    .FILL BAD_TRAP     ; x6D
    .FILL BAD_TRAP     ; x6E
    .FILL BAD_TRAP     ; x6F
    .FILL BAD_TRAP     ; x70
    .FILL BAD_TRAP     ; x71
    .FILL BAD_TRAP     ; x72
    .FILL BAD_TRAP     ; x73
    .FILL BAD_TRAP     ; x74
    .FILL BAD_TRAP     ; x75
    .FILL BAD_TRAP     ; x76
    .FILL BAD_TRAP     ; x77
    .FILL BAD_TRAP     ; x78
    .FILL BAD_TRAP     ; x79
    .FILL BAD_TRAP     ; x7A
    .FILL BAD_TRAP     ; x7B
    .FILL BAD_TRAP     ; x7C
    .FILL BAD_TRAP     ; x7D
    .FILL BAD_TRAP     ; x7E
    .FILL BAD_TRAP     ; x7F
    .FILL BAD_TRAP     ; x80
    .FILL BAD_TRAP     ; x81
    .FILL BAD_TRAP     ; x82
    .FILL BAD_TRAP     ; x83
    .FILL BAD_TRAP     ; x84
    .FILL BAD_TRAP     ; x85
    .FILL BAD_TRAP     ; x86
    .FILL BAD_TRAP     ; x87
    .FILL BAD_TRAP     ; x88
    .FILL BAD_TRAP     ; x89
    .FILL BAD_TRAP     ; x8A
    .FILL BAD_TRAP     ; x8B
    .FILL BAD_TRAP     ; x8C
    .FILL BAD_TRAP     ; x8D
    .FILL BAD_TRAP     ; x8E
    .FILL BAD_TRAP     ; x8F
    .FILL BAD_TRAP     ; x90
    .FILL BAD_TRAP     ; x91
    .FILL BAD_TRAP     ; x92
    .FILL BAD_TRAP     ; x93
    .FILL BAD_TRAP     ; x94
    .FILL BAD_TRAP     ; x95
    .FILL BAD_TRAP     ; x96
    .FILL BAD_TRAP     ; x97
    .FILL BAD_TRAP     ; x98
    .FILL BAD_TRAP     ; x99
    .FILL BAD_TRAP     ; x9A
    .FILL BAD_TRAP     ; x9B
    .FILL BAD_TRAP     ; x9C
    .FILL BAD_TRAP     ; x9D
    .FILL BAD_TRAP     ; x9E
    .FILL BAD_TRAP     ; x9F
    .FILL BAD_TRAP     ; xA0
    .FILL BAD_TRAP     ; xA1
    .FILL BAD_TRAP     ; xA2
    .FILL BAD_TRAP     ; xA3
    .FILL BAD_TRAP     ; xA4
    .FILL BAD_TRAP     ; xA5
    .FILL BAD_TRAP     ; xA6
    .FILL BAD_TRAP     ; xA7
    .FILL BAD_TRAP     ; xA8
    .FILL BAD_TRAP     ; xA9
    .FILL BAD_TRAP     ; xAA
    .FILL BAD_TRAP     ; xAB
    .FILL BAD_TRAP     ; xAC
    .FILL BAD_TRAP     ; xAD
    .FILL BAD_TRAP     ; xAE
    .FILL BAD_TRAP     ; xAF
    .FILL BAD_TRAP     ; xB0
    .FILL BAD_TRAP     ; xB1
    .FILL BAD_TRAP     ; xB2
    .FILL BAD_TRAP     ; xB3
    .FILL BAD_TRAP     ; xB4
    .FILL BAD_TRAP     ; xB5
    .FILL BAD_TRAP     ; xB6
    .FILL BAD_TRAP     ; xB7
    .FILL BAD_TRAP     ; xB8
    .FILL BAD_TRAP     ; xB9
    .FILL BAD_TRAP     ; xBA
    .FILL BAD_TRAP     ; xBB
    .FILL BAD_TRAP     ; xBC
    .FILL BAD_TRAP     ; xBD
    .FILL BAD_TRAP     ; xBE
    .FILL BAD_TRAP     ; xBF
    .FILL BAD_TRAP     ; xC0
    .FILL BAD_TRAP     ; xC1
    .FILL BAD_TRAP     ; xC2
    .FILL BAD_TRAP     ; xC3
    .FILL BAD_TRAP     ; xC4
    .FILL BAD_TRAP     ; xC5
    .FILL BAD_TRAP     ; xC6
    .FILL BAD_TRAP     ; xC7
    .FILL BAD_TRAP     ; xC8
    .FILL BAD_TRAP     ; xC9
    .FILL BAD_TRAP     ; xCA
    .FILL BAD_TRAP     ; xCB
    .FILL BAD_TRAP     ; xCC
    .FILL BAD_TRAP     ; xCD
    .FILL BAD_TRAP     ; xCE
    .FILL BAD_TRAP     ; xCF
    .FILL BAD_TRAP     ; xD0
    .FILL BAD_TRAP     ; xD1
    .FILL BAD_TRAP     ; xD2
    .FILL BAD_TRAP     ; xD3
    .FILL BAD_TRAP     ; xD4
    .FILL BAD_TRAP     ; xD5
    .FILL BAD_TRAP     ; xD6
    .FILL BAD_TRAP     ; xD7
    .FILL BAD_TRAP     ; xD8
    .FILL BAD_TRAP     ; xD9
    .FILL BAD_TRAP     ; xDA
    .FILL BAD_TRAP     ; xDB
    .FILL BAD_TRAP     ; xDC
    .FILL BAD_TRAP     ; xDD
    .FILL BAD_TRAP     ; xDE
    .FILL BAD_TRAP     ; xDF
    .FILL BAD_TRAP     ; xE0
    .FILL BAD_TRAP     ; xE1
    .FILL BAD_TRAP     ; xE2
    .FILL BAD_TRAP     ; xE3
    .FILL BAD_TRAP     ; xE4
    .FILL BAD_TRAP     ; xE5
    .FILL BAD_TRAP     ; xE6
    .FILL BAD_TRAP     ; xE7
    .FILL BAD_TRAP     ; xE8
    .FILL BAD_TRAP     ; xE9
    .FILL BAD_TRAP     ; xEA
    .FILL BAD_TRAP     ; xEB
    .FILL BAD_TRAP     ; xEC
    .FILL BAD_TRAP     ; xED
    .FILL BAD_TRAP     ; xEE
    .FILL BAD_TRAP     ; xEF
    .FILL BAD_TRAP     ; xF0
    .FILL BAD_TRAP     ; xF1
    .FILL BAD_TRAP     ; xF2
    .FILL BAD_TRAP     ; xF3
    .FILL BAD_TRAP     ; xF4
    .FILL BAD_TRAP     ; xF5
    .FILL BAD_TRAP     ; xF6
    .FILL BAD_TRAP     ; xF7
    .FILL BAD_TRAP     ; xF8
    .FILL BAD_TRAP     ; xF9
    .FILL BAD_TRAP     ; xFA
    .FILL BAD_TRAP     ; xFB
    .FILL BAD_TRAP     ; xFC
    .FILL BAD_TRAP     ; xFD
    .FILL BAD_TRAP     ; xFE
    .FILL BAD_TRAP     ; xFF

; the interrupt vector table
    .FILL EX_PRIV    ; x00
    .FILL EX_ILL     ; x01
    .FILL EX_ACV     ; x02
    .FILL BAD_INT    ; x03
    .FILL BAD_INT    ; x04
    .FILL BAD_INT    ; x05
    .FILL BAD_INT    ; x06
    .FILL BAD_INT    ; x07
    .FILL BAD_INT    ; x08
    .FILL BAD_INT    ; x09
    .FILL BAD_INT    ; x0A
    .FILL BAD_INT    ; x0B
    .FILL BAD_INT    ; x0C
    .FILL BAD_INT    ; x0D
    .FILL BAD_INT    ; x0E
    .FILL BAD_INT    ; x0F
    .FILL BAD_INT    ; x10
    .FILL BAD_INT    ; x11
    .FILL BAD_INT    ; x12
    .FILL BAD_INT    ; x13
    .FILL BAD_INT    ; x14
    .FILL BAD_INT    ; x15
    .FILL BAD_INT    ; x16
    .FILL BAD_INT    ; x17
    .FILL BAD_INT    ; x18
    .FILL BAD_INT    ; x19
    .FILL BAD_INT    ; x1A
    .FILL BAD_INT    ; x1B
    .FILL BAD_INT    ; x1C
    .FILL BAD_INT    ; x1D
    .FILL BAD_INT    ; x1E
    .FILL BAD_INT    ; x1F
    .FILL BAD_INT    ; x20
    .FILL BAD_INT    ; x21
    .FILL BAD_INT    ; x22
    .FILL BAD_INT    ; x23
    .FILL BAD_INT    ; x24
    .FILL BAD_INT    ; x25
    .FILL BAD_INT    ; x26
    .FILL BAD_INT    ; x27
    .FILL BAD_INT    ; x28
    .FILL BAD_INT    ; x29
    .FILL BAD_INT    ; x2A
    .FILL BAD_INT    ; x2B
    .FILL BAD_INT    ; x2C
    .FILL BAD_INT    ; x2D
    .FILL BAD_INT    ; x2E
    .FILL BAD_INT    ; x2F
    .FILL BAD_INT    ; x30
    .FILL BAD_INT    ; x31
    .FILL BAD_INT    ; x32
    .FILL BAD_INT    ; x33
    .FILL BAD_INT    ; x34
    .FILL BAD_INT    ; x35
    .FILL BAD_INT    ; x36
    .FILL BAD_INT    ; x37
    .FILL BAD_INT    ; x38
    .FILL BAD_INT    ; x39
    .FILL BAD_INT    ; x3A
    .FILL BAD_INT    ; x3B
    .FILL BAD_INT    ; x3C
    .FILL BAD_INT    ; x3D
    .FILL BAD_INT    ; x3E
    .FILL BAD_INT    ; x3F
    .FILL BAD_INT    ; x40
    .FILL BAD_INT    ; x41
    .FILL BAD_INT    ; x42
    .FILL BAD_INT    ; x43
    .FILL BAD_INT    ; x44
    .FILL BAD_INT    ; x45
    .FILL BAD_INT    ; x46
    .FILL BAD_INT    ; x47
    .FILL BAD_INT    ; x48
    .FILL BAD_INT    ; x49
    .FILL BAD_INT    ; x4A
    .FILL BAD_INT    ; x4B
    .FILL BAD_INT    ; x4C
    .FILL BAD_INT    ; x4D
    .FILL BAD_INT    ; x4E
    .FILL BAD_INT    ; x4F
    .FILL BAD_INT    ; x50
    .FILL BAD_INT    ; x51
    .FILL BAD_INT    ; x52
    .FILL BAD_INT    ; x53
    .FILL BAD_INT    ; x54
    .FILL BAD_INT    ; x55
    .FILL BAD_INT    ; x56
    .FILL BAD_INT    ; x57
    .FILL BAD_INT    ; x58
    .FILL BAD_INT    ; x59
    .FILL BAD_INT    ; x5A
    .FILL BAD_INT    ; x5B
    .FILL BAD_INT    ; x5C
    .FILL BAD_INT    ; x5D
    .FILL BAD_INT    ; x5E
    .FILL BAD_INT    ; x5F
    .FILL BAD_INT    ; x60
    .FILL BAD_INT    ; x61
    .FILL BAD_INT    ; x62
    .FILL BAD_INT    ; x63
    .FILL BAD_INT    ; x64
    .FILL BAD_INT    ; x65
    .FILL BAD_INT    ; x66
    .FILL BAD_INT    ; x67
    .FILL BAD_INT    ; x68
    .FILL BAD_INT    ; x69
    .FILL BAD_INT    ; x6A
    .FILL BAD_INT    ; x6B
    .FILL BAD_INT    ; x6C
    .FILL BAD_INT    ; x6D
    .FILL BAD_INT    ; x6E
    .FILL BAD_INT    ; x6F
    .FILL BAD_INT    ; x70
    .FILL BAD_INT    ; x71
    .FILL BAD_INT    ; x72
    .FILL BAD_INT    ; x73
    .FILL BAD_INT    ; x74
    .FILL BAD_INT    ; x75
    .FILL BAD_INT    ; x76
    .FILL BAD_INT    ; x77
    .FILL BAD_INT    ; x78
    .FILL BAD_INT    ; x79
    .FILL BAD_INT    ; x7A
    .FILL BAD_INT    ; x7B
    .FILL BAD_INT    ; x7C
    .FILL BAD_INT    ; x7D
    .FILL BAD_INT    ; x7E
    .FILL BAD_INT    ; x7F
    .FILL BAD_INT    ; x80
    .FILL BAD_INT    ; x81
    .FILL BAD_INT    ; x82
    .FILL BAD_INT    ; x83
    .FILL BAD_INT    ; x84
    .FILL BAD_INT    ; x85
    .FILL BAD_INT    ; x86
    .FILL BAD_INT    ; x87
    .FILL BAD_INT    ; x88
    .FILL BAD_INT    ; x89
    .FILL BAD_INT    ; x8A
    .FILL BAD_INT    ; x8B
    .FILL BAD_INT    ; x8C
    .FILL BAD_INT    ; x8D
    .FILL BAD_INT    ; x8E
    .FILL BAD_INT    ; x8F
    .FILL BAD_INT    ; x90
    .FILL BAD_INT    ; x91
    .FILL BAD_INT    ; x92
    .FILL BAD_INT    ; x93
    .FILL BAD_INT    ; x94
    .FILL BAD_INT    ; x95
    .FILL BAD_INT    ; x96
    .FILL BAD_INT    ; x97
    .FILL BAD_INT    ; x98
    .FILL BAD_INT    ; x99
    .FILL BAD_INT    ; x9A
    .FILL BAD_INT    ; x9B
    .FILL BAD_INT    ; x9C
    .FILL BAD_INT    ; x9D
    .FILL BAD_INT    ; x9E
    .FILL BAD_INT    ; x9F
    .FILL BAD_INT    ; xA0
    .FILL BAD_INT    ; xA1
    .FILL BAD_INT    ; xA2
    .FILL BAD_INT    ; xA3
    .FILL BAD_INT    ; xA4
    .FILL BAD_INT    ; xA5
    .FILL BAD_INT    ; xA6
    .FILL BAD_INT    ; xA7
    .FILL BAD_INT    ; xA8
    .FILL BAD_INT    ; xA9
    .FILL BAD_INT    ; xAA
    .FILL BAD_INT    ; xAB
    .FILL BAD_INT    ; xAC
    .FILL BAD_INT    ; xAD
    .FILL BAD_INT    ; xAE
    .FILL BAD_INT    ; xAF
    .FILL BAD_INT    ; xB0
    .FILL BAD_INT    ; xB1
    .FILL BAD_INT    ; xB2
    .FILL BAD_INT    ; xB3
    .FILL BAD_INT    ; xB4
    .FILL BAD_INT    ; xB5
    .FILL BAD_INT    ; xB6
    .FILL BAD_INT    ; xB7
    .FILL BAD_INT    ; xB8
    .FILL BAD_INT    ; xB9
    .FILL BAD_INT    ; xBA
    .FILL BAD_INT    ; xBB
    .FILL BAD_INT    ; xBC
    .FILL BAD_INT    ; xBD
    .FILL BAD_INT    ; xBE
    .FILL BAD_INT    ; xBF
    .FILL BAD_INT    ; xC0
    .FILL BAD_INT    ; xC1
    .FILL BAD_INT    ; xC2
    .FILL BAD_INT    ; xC3
    .FILL BAD_INT    ; xC4
    .FILL BAD_INT    ; xC5
    .FILL BAD_INT    ; xC6
    .FILL BAD_INT    ; xC7
    .FILL BAD_INT    ; xC8
    .FILL BAD_INT    ; xC9
    .FILL BAD_INT    ; xCA
    .FILL BAD_INT    ; xCB
    .FILL BAD_INT    ; xCC
    .FILL BAD_INT    ; xCD
    .FILL BAD_INT    ; xCE
    .FILL BAD_INT    ; xCF
    .FILL BAD_INT    ; xD0
    .FILL BAD_INT    ; xD1
    .FILL BAD_INT    ; xD2
    .FILL BAD_INT    ; xD3
    .FILL BAD_INT    ; xD4
    .FILL BAD_INT    ; xD5
    .FILL BAD_INT    ; xD6
    .FILL BAD_INT    ; xD7
    .FILL BAD_INT    ; xD8
    .FILL BAD_INT    ; xD9
    .FILL BAD_INT    ; xDA
    .FILL BAD_INT    ; xDB
    .FILL BAD_INT    ; xDC
    .FILL BAD_INT    ; xDD
    .FILL BAD_INT    ; xDE
    .FILL BAD_INT    ; xDF
    .FILL BAD_INT    ; xE0
    .FILL BAD_INT    ; xE1
    .FILL BAD_INT    ; xE2
    .FILL BAD_INT    ; xE3
    .FILL BAD_INT    ; xE4
    .FILL BAD_INT    ; xE5
    .FILL BAD_INT    ; xE6
    .FILL BAD_INT    ; xE7
    .FILL BAD_INT    ; xE8
    .FILL BAD_INT    ; xE9
    .FILL BAD_INT    ; xEA
    .FILL BAD_INT    ; xEB
    .FILL BAD_INT    ; xEC
    .FILL BAD_INT    ; xED
    .FILL BAD_INT    ; xEE
    .FILL BAD_INT    ; xEF
    .FILL BAD_INT    ; xF0
    .FILL BAD_INT    ; xF1
    .FILL BAD_INT    ; xF2
    .FILL BAD_INT    ; xF3
    .FILL BAD_INT    ; xF4
    .FILL BAD_INT    ; xF5
    .FILL BAD_INT    ; xF6
    .FILL BAD_INT    ; xF7
    .FILL BAD_INT    ; xF8
    .FILL BAD_INT    ; xF9
    .FILL BAD_INT    ; xFA
    .FILL BAD_INT    ; xFB
    .FILL BAD_INT    ; xFC
    .FILL BAD_INT    ; xFD
    .FILL BAD_INT    ; xFE
    .FILL BAD_INT    ; xFF)LC3OS1";

        char const * lc3os_src_2 = R"LC3OS2(
OS_START
    ; set system stack pointer
    LD R6, OS_SP
    ; push synthesized PSR onto system stack
    LD R0, USER_PSR
    ADD R6, R6, #-1
    STR R0, R6, #0
    ; push synthesized (x3000) PSR onto system stack
    LD R0, USER_PC
    ADD R6, R6, #-1
    STR R0, R6, #0
    ; initialize fd layer
    JSR INIT_TABLES
    JSR OPEN_STDIN
    JSR OPEN_STDOUT
    ; enter user mode
    RTI

    OS_SP       .FILL x3000
    USER_PSR    .FILL x8002
    USER_PC     .FILL x3000

INIT_TABLES
    ; save return address
    ADD R6, R6, -1
    STR R7, R6, 0

    ; for (i = 0; i < 16; i++) {
    AND R0, R0, 0 ; i = 0
    FD_TABLE_INIT_LOOP
    AND R1, R1, 0
    ADD R1, R1, -1 ; r1 <- -1

    ADD R2, R0, R0 ; r2 <- 2*i
    ADD R2, R2, R2 ; r2 <- 4*i
    ADD R2, R2, R0 ; r2 <- 5*i
    ADD R2, R2, R0 ; r2 <- 6*i
    ADD R2, R2, R0 ; r2 <- 7*i
    LD R3, INIT_TABLES__FD_TABLE__ADDR
    ; fd_ent *ent = fd_table + i;
    ADD R3, R3, R2

    ; ent->state = -1; // invalid
    STR R1, R3, 0

    ADD R0, R0, 1 ; i++
    LDI R1, INIT_TABLES__FD_TABLE_LEN__ADDR
    NOT R1, R1
    ADD R1, R1, 1
    ADD R1, R0, R1
    BRn FD_TABLE_INIT_LOOP
    ; }

    ; for (i = 0; i < 64; i++) {
    AND R0, R0, 0 ; i = 0
    TAPENUM_TABLE_INIT_LOOP
    AND R1, R1, 0
    ADD R1, R1, -1 ; r1 <- -1
    LD R3, INIT_TABLES__TAPENUM_TABLE__ADDR
    ; tapenum_ent *ent = tapenum_table + i;
    ADD R3, R3, R0
    ; *ent = -1;
    STR R1, R3, 0
    ADD R0, R0, 1 ; i++
    ; if i < 64, continue
    LDI R1, INIT_TABLES__TAPENUM_TABLE_LEN__ADDR
    NOT R1, R1
    ADD R1, R1, 1
    ADD R1, R1, R0
    BRn TAPENUM_TABLE_INIT_LOOP
    ; }

    ; restore return address
    LDR R7, R6, 0
    ADD R6, R6, 1
    RET

    INIT_TABLES__FD_TABLE__ADDR .FILL FD_TABLE
    INIT_TABLES__FD_TABLE_LEN__ADDR .FILL FD_TABLE_LEN
    INIT_TABLES__TAPENUM_TABLE__ADDR .FILL TAPENUM_TABLE
    INIT_TABLES__TAPENUM_TABLE_LEN__ADDR .FILL TAPENUM_TABLE_LEN

OPEN_STDIN
    ; save return address
    ADD R6, R6, -1
    STR R7, R6, 0

    ; fd_ent *fd0 = &fd_table[0];
    LD R1, OPEN_STDIN__FD_TABLE__ADDR
    ; fd0->state = 0; // R
    AND R0, R0, 0
    STR R0, R1, 0
    ; fd0->data = 0; // don't care
    STR R0, R1, 1
    ; fd0->putc = &keyboard_invalid
    LEA R0, KEYBOARD_INVALID
    STR R0, R1, 2
    ; fd0->getc = &keyboard_getc
    LEA R0, KEYBOARD_GETC
    STR R0, R1, 3
    ; fd0->trunc = &keyboard_invalid
    LEA R0, KEYBOARD_INVALID
    STR R0, R1, 4
    ; fd0->rewind = &keyboard_invalid
    LEA R0, KEYBOARD_INVALID
    STR R0, R1, 5
    ; fd0->close = &keyboard_close
    LEA R0, KEYBOARD_CLOSE
    STR R0, R1, 6

    ; restore return address
    LDR R7, R6, 0
    ADD R6, R6, 1
    RET

    OPEN_STDIN__FD_TABLE__ADDR .FILL FD_TABLE

KEYBOARD_INVALID
    LEA R0, KEYBOARD_INVALID_ERR
    PUTS
    HALT
    KEYBOARD_INVALID_ERR .STRINGZ "ERROR: Invalid operation for stdin\n"

; Output: byte from keyboard (r0)
KEYBOARD_GETC
    GETC
    RET

; Currently a no-op
KEYBOARD_CLOSE
    RET

OPEN_STDOUT
    ; save return address
    ADD R6, R6, -1
    STR R7, R6, 0

    ; fd_ent *fd1 = &fd_table[1];
    LD R1, OPEN_STDOUT__FD_TABLE__ADDR
    ADD R1, R1, 7
    ; fd1->state = 1; // W
    AND R0, R0, 0
    ADD R0, R0, 1
    STR R0, R1, 0
    ; fd1->data = 1; // don't care
    STR R0, R1, 1
    ; fd1->putc = &console_putc
    LEA R0, CONSOLE_PUTC
    STR R0, R1, 2
    ; fd1->getc = &console_getc
    LEA R0, CONSOLE_INVALID
    STR R0, R1, 3
    ; fd1->trunc = &console_trunc
    LEA R0, CONSOLE_INVALID
    STR R0, R1, 4
    ; fd1->rewind = &console_rewind
    LEA R0, CONSOLE_INVALID
    STR R0, R1, 5
    ; fd1->close = &console_close
    LEA R0, CONSOLE_CLOSE
    STR R0, R1, 6

    ; restore return address
    LDR R7, R6, 0
    ADD R6, R6, 1
    RET

    OPEN_STDOUT__FD_TABLE__ADDR .FILL FD_TABLE

CONSOLE_INVALID
    LEA R0, CONSOLE_INVALID_ERR
    PUTS
    HALT
    CONSOLE_INVALID_ERR .STRINGZ "ERROR: Invalid operation for stdout\n"

; Input: byte to display (r0)
CONSOLE_PUTC
    PUTC
    RET

; Currently a no-op
CONSOLE_CLOSE
    RET
    .END

    .ORIG x300
TRAP_GETC
    LDI R0, OS_KBSR        ; wait for a keystroke
    BRzp TRAP_GETC
    LDI R0, OS_KBDR        ; read it and return
    RTI

OS_KBSR    .FILL xFE00
OS_KBDR    .FILL xFE02


TRAP_OUT
    ADD R6, R6, #-1
    STR R1, R6, #0        ; save R1
TRAP_OUT_WAIT
    LDI R1, OS_DSR        ; wait for the display to be ready
    BRzp TRAP_OUT_WAIT
    STI R0, OS_DDR        ; write the character and return
    LDR R1, R6, #0        ; restore R1
    ADD R6, R6, #1
    RTI

OS_DSR     .FILL xFE04
OS_DDR     .FILL xFE06


TRAP_PUTS
    ADD R6, R6, #-1       ; save R0 and R1
    STR R0, R6, #0
    ADD R6, R6, #-1
    STR R1, R6, #0
    ADD R1, R0, #0        ; move string pointer (R0) into R1
TRAP_PUTS_LOOP
    LDR R0, R1, #0        ; write characters in string using OUT
    BRz TRAP_PUTS_DONE
    OUT
    ADD R1, R1, #1
    BRnzp TRAP_PUTS_LOOP
TRAP_PUTS_DONE
    LDR R1, R6, #0         ; restore R0 and R1
    ADD R6, R6, #1
    LDR R0, R6, #0
    ADD R6, R6, #1
    RTI

TRAP_IN
    LEA R0, TRAP_IN_MSG    ; prompt for input
    PUTS
    GETC                   ; read a character
    OUT                    ; echo back to monitor
    ADD R6, R6, #-1
    STR R0, R6, #0         ; save the character
    AND R0, R0, #0         ; write a linefeed, too
    ADD R0, R0, #10
    OUT
    LDR R0, R6, #0         ; restore the character
    ADD R6, R6, #1
    RTI

TRAP_IN_MSG    .STRINGZ "\nInput a character> "



    ; NOTE: This trap will end when it sees any NUL, even in
    ; packed form, despite the P&P second edition's requirement
    ; of a double NUL.
TRAP_PUTSP 
    ADD R6, R6, #-1        ; save R0, R1, R2, and R3
    STR R0, R6, #0
    ADD R6, R6, #-1
    STR R1, R6, #0
    ADD R6, R6, #-1
    STR R2, R6, #0
    ADD R6, R6, #-1
    STR R3, R6, #0
    ADD R1, R0, #0         ; move string pointer (R0) into R1
TRAP_PUTSP_LOOP
    LDR R2, R1, #0         ; read the next two characters
    LD R0, LOW_8_BITS      ; use mask to get low byte
    AND R0, R0, R2         ; if low byte is NUL, quit printing
    BRz TRAP_PUTSP_DONE
    OUT                    ; otherwise print the low byte
    AND R0, R0, #0         ; shift high byte into R0
    ADD R3, R0, #8
TRAP_PUTSP_S_LOOP
    ADD R0, R0, R0         ; shift R0 left
    ADD R2, R2, #0         ; move MSB from R2 into R0
    BRzp TRAP_PUTSP_MSB_0
    ADD R0, R0, #1
TRAP_PUTSP_MSB_0
    ADD R2, R2, R2         ; shift R2 left
    ADD R3, R3, #-1
    BRp TRAP_PUTSP_S_LOOP
    ADD R0, R0, #0         ; if high byte is NUL, quit printing
    BRz TRAP_PUTSP_DONE
    OUT                    ; otherwise print the low byte
    ADD R1, R1, #1         ; and keep going
    BRnzp TRAP_PUTSP_LOOP
TRAP_PUTSP_DONE
    LDR R3, R6, #0         ; restore R0, R1, R2, and R3
    ADD R6, R6, #1
    LDR R2, R6, #0
    ADD R6, R6, #1
    LDR R1, R6, #0
    ADD R6, R6, #1
    LDR R0, R6, #0
    ADD R6, R6, #1
    RTI

LOW_8_BITS  .FILL x00FF


    ; clear power-on bit in MCR
TRAP_HALT
    LDI R0, OS_MCR         ; halt the machine
    LD R1, MASK_HI
    AND R0, R0, R1
    STI R0, OS_MCR
    BRnzp TRAP_HALT        ; HALT again if need be...

OS_MCR          .FILL xFFFE
MASK_HI         .FILL x7FFF


    ; print an error message and offending PC, then HALT
BAD_TRAP
    LEA R0, BAD_TRAP_MSG   ; give an error message
    PUTS
    AND R1, R1, #0
    ADD R1, R1, #-1        ; decrement PC before printing
    BR EX_PRINT_PC         ; print offending PC

BAD_TRAP_MSG   .STRINGZ "\n\n--- Undefined trap executed ---\n\n"


    ; print an error message and offending PC, then HALT
EX_PRIV
    LEA R0, EX_PRIV_MSG    ; give an error message
    PUTS
    AND R1, R1, #0         ; do not decrement PC before printing
    BR EX_PRINT_PC         ; print offending PC

EX_PRIV_MSG    .STRINGZ "\n\n--- Privilege violation ---\n\n"


    ; print an error message and offending PC, then HALT
EX_ILL
    LEA R0, EX_ILL_MSG     ; give an error message
    PUTS
    AND R1, R1, #0         ; do not decrement PC before printing
    BR EX_PRINT_PC         ; print offending PC

EX_ILL_MSG     .STRINGZ "\n\n--- Illegal opcode ---\n\n"

    ; print an error message and offending PC, then HALT
EX_ACV
    LEA R0, EX_ACV_MSG     ; give an error message
    PUTS
    AND R1, R1, #0         ; do not decrement PC before printing
    BR EX_PRINT_PC         ; print offending PC

EX_ACV_MSG     .STRINGZ "\n\n--- Access violation---\n\n"

; For BAD_TRAP, the top of the stack will be PC+1, but for the exceptions, the
; top of the stack is just PC. So R1 is expected to hold the offset (-1 or 0,
; realistically)
EX_PRINT_PC
    LEA R0, PC_MESSAGE
    PUTS

    ; Grab the offending PC from the top of
    ; the supervisor stack and print it
    LDR R0, R6, #0
    ; Add the offset required to the PC to get the PC
    ; that actually caused this error
    ADD R0, R0, R1
    JSR PRINTHEX

    ; Print a newline to make the cursor not
    ; annoyingly right after the PC
    AND R0, R0, #0
    ADD R0, R0, #10 ; '\n'
    PUTC
    HALT
    PC_MESSAGE .STRINGZ "Offending PC: "

; Input: Word to print as hex (R0)
; Output: To the console
PRINTHEX
       ADD R6, R6, #-5
       STR R0, R6, #0 ; push r0 onto the stack
       STR R1, R6, #1 ; push r1 onto the stack
       STR R2, R6, #2 ; push r2 onto the stack
       STR R3, R6, #3 ; push r3 onto the stack
       STR R4, R6, #4 ; push r4 onto the stack

       ADD R1, R0, #0 ; r1 <- r0
       LD R0, ASCII_X
       PUTC           ; print 'x'

       AND R2, R2, #0  ; i <- 0 (outer/nibble loop counter)
NIBBLE AND R0, R0, #0  ; r0 <- 0
       AND R3, R3, #0  ; j <- 0 (inner/bit loop counter)
   BIT ADD R1, R1, #0  ; cc for r1
       BRzp ZERO
       ADD R0, R0, R0  ; r0 <<= 1
       ADD R0, R0, #1  ; r0 += 1
       BR #1
  ZERO ADD R0, R0, R0  ; r0 <<= 1
       ADD R1, R1, R1  ; r1 <<= 1
       ADD R3, R3, #1   ; j++
       ADD R4, R3, #-4  ; cc <- j-4
       BRn BIT        ; loop while j < 4
       ADD R4, R0, #-10 ; r0-10
       BRzp AF
       LD R4, ASCII_ZERO
       ADD R0, R0, R4  ; r0 += '0'
       BR PRINT
    AF LD R4, ASCII_A
       ADD R0, R0, #-10 ; r0 -= 10
       ADD R0, R0, R4  ; r0 += 'A'
 PRINT PUTC
       ADD R2, R2, #1   ; i++
       ADD R4, R2, #-4  ; i-4
       BRn NIBBLE

       LDR R0, R6, #0 ; pop r0 off the stack
       LDR R1, R6, #1 ; pop r1 off the stack
       LDR R2, R6, #2 ; pop r2 off the stack
       LDR R3, R6, #3 ; pop r3 off the stack
       LDR R4, R6, #4 ; pop r4 off the stack
       ADD R6, R6, #5
       RET

ASCII_X    .FILL x78 ; 'x'
ASCII_ZERO .FILL x30 ; '0'
ASCII_A    .FILL x41 ; 'A'

BAD_INT
    RTI

;;; File descriptors / Tape I/O ;;;

; Input: Byte to write (r0, written below as c), Drive number (r1)
TAPE_PUTC
    ; save return address
    ADD R6, R6, #-1
    STR R7, R6, #0

    ; Wait to send
    TAPE_PUTC_POLL1
        LDI R2, TSSR_ADDR
        BRzp TAPE_PUTC_POLL1

    JSR SHIFT_DRIVENUM ; r1 <- drivenum << 8
    ; Build PUTC message (format below)
    LD R2, PUTC_MSG
    ; PUTC_MSG | c | (drivenum << 8) // Except DeMorgan's'd
    NOT R2, R2
    NOT R0, R0
    NOT R1, R1
    AND R2, R0, R2
    AND R2, R1, R2
    NOT R2, R2
    ; Send PUTC(drivenum, c)
    STI R2, TSDR_ADDR

    ; Wait to recv an ACK
    TAPE_PUTC_POLL2
        LDI R2, TRSR_ADDR
        BRzp TAPE_PUTC_POLL2

    LDI R1, TRDR_ADDR
    JSR DECODE_TAPE_MSG ; r1 <- data, r2 <- opcode

    ; Jump table for opcode
    LEA R3, TAPE_PUTC_JMP_OPCODE
    ADD R3, R3, R2
    LDR R3, R3, #0
    JMP R3
    TAPE_PUTC_JMP_OPCODE
        .FILL TAPE_PUTC_HANDLE_ERR
        .FILL TAPE_PUTC_HANDLE_DATA
        .FILL TAPE_PUTC_HANDLE_ACK
        .FILL TAPE_PUTC_HANDLE_UNKNOWN

    TAPE_PUTC_HANDLE_ERR
        LEA R0, TAPE_PUTC_WHOAMI
        PUTS
        JSR TAPE_PRINT_ERR ; Will not return
        TAPE_PUTC_WHOAMI .STRINGZ "fputc: "

    TAPE_PUTC_HANDLE_DATA
        LEA R0, TAPE_PUTC_DATA_ERR_MSG
        PUTS
        HALT
        TAPE_PUTC_DATA_ERR_MSG .STRINGZ "fputc: ERROR: Unexpected DATA response from tape drive\n"

    TAPE_PUTC_HANDLE_UNKNOWN
        LEA R0, TAPE_PUTC_UNKNOWN_ERR_MSG
        PUTS
        HALT
        TAPE_PUTC_UNKNOWN_ERR_MSG .STRINGZ "fputc: ERROR: Unknown message id sent by tape drive\n"

    TAPE_PUTC_HANDLE_ACK
    ; We're good, return
    ; restore return address
    LDR R7, R6, #0
    ADD R6, R6, #1
    RET

    ; Message format:
    ; 15     14 13       8 7         0
    ; .-------------------------------.
    ; | opcode | tape num |   data    |
    ; '-------------------------------'
    PUTC_MSG  .FILL x8000 ; message with tapenum=0 and opcode=0b10
    TRSR_ADDR .FILL xFE08 ; Tape recv status register
    TRDR_ADDR .FILL xFE0A ; Tape recv data register
    TSSR_ADDR .FILL xFE0C ; Tape send status register
    TSDR_ADDR .FILL xFE0E ; Tape send data register

; Input: Drive number (r1)
; Output: Byte from tape (r0)
TAPE_GETC
    ; save return address
    ADD R6, R6, #-1
    STR R7, R6, #0

    ; Wait to send
    TAPE_GETC_POLL1
        LDI R2, TSSR_ADDR
        BRzp TAPE_GETC_POLL1

    JSR SHIFT_DRIVENUM ; r1 <- drivenum << 8
    ; Build GETC message (format above in TAPE_PUTC)
    LD R2, GETC_MSG
    ; PUTC_MSG | (drivenum << 8) // Except DeMorgan's'd
    NOT R2, R2
    NOT R1, R1
    AND R2, R1, R2
    NOT R2, R2
    ; Send GETC(drivenum)
    STI R2, TSDR_ADDR

    ; Wait to recv an ACK
    TAPE_GETC_POLL2
        LDI R2, TRSR_ADDR
        BRzp TAPE_GETC_POLL2

    LDI R1, TRDR_ADDR
    JSR DECODE_TAPE_MSG ; r1 <- data, r2 <- opcode

    ; Jump table for opcode
    LEA R3, TAPE_GETC_JMP_OPCODE
    ADD R3, R3, R2
    LDR R3, R3, #0
    JMP R3
    TAPE_GETC_JMP_OPCODE
        .FILL TAPE_GETC_HANDLE_ERR
        .FILL TAPE_GETC_HANDLE_DATA
        .FILL TAPE_GETC_HANDLE_ACK
        .FILL TAPE_GETC_HANDLE_UNKNOWN

    TAPE_GETC_HANDLE_ERR
        ; 0x02 is the error code for EOF. It's returned as an "error" but we
        ; won't treat it as one. Instead, we'll just return -1.
        ADD R0, R1, #-2
        BRnp TAPE_GETC_SERIOUS_ERROR
        ; Return -1 to signal EOF
        AND R0, R0, #0
        ADD R0, R0, #-1
        BR TAPE_GETC_DONE

        TAPE_GETC_SERIOUS_ERROR
        LEA R0, TAPE_GETC_WHOAMI
        PUTS
        JSR TAPE_PRINT_ERR ; Will not return
        TAPE_GETC_WHOAMI .STRINGZ "fgetc: "

    TAPE_GETC_HANDLE_DATA
        ; Set return value that TRAP_FGETC expects
        ADD R0, R1, #0
        BR TAPE_GETC_DONE

    TAPE_GETC_HANDLE_ACK
        LEA R0, TAPE_GETC_ACK_ERR_MSG
        PUTS
        HALT
        TAPE_GETC_ACK_ERR_MSG .STRINGZ "fgetc: ERROR: Unexpected ACK response from tape drive\n"

    TAPE_GETC_HANDLE_UNKNOWN
        LEA R0, TAPE_GETC_UNKNOWN_ERR_MSG
        PUTS
        HALT
        TAPE_GETC_UNKNOWN_ERR_MSG .STRINGZ "fgetc: ERROR: Unknown message id sent by tape drive\n"

    TAPE_GETC_DONE
    ; restore return address
    LDR R7, R6, #0
    ADD R6, R6, #1
    RET
    GETC_MSG  .FILL x4000 ; message with tapenum=0 and opcode=0b01

; Input: Drive number (r1)
TAPE_TRUNC
    ; save return address
    ADD R6, R6, #-1
    STR R7, R6, #0
    LD R2, SET_EOF_MSG
    LEA R3, TAPE_TRUNC_WHOAMI
    JSR TAPE_SEND_COMMAND
    ; restore return address
    LDR R7, R6, #0
    ADD R6, R6, #1
    RET
    SET_EOF_MSG .FILL xC000 ; message with tapenum=0 and opcode=0b11 (set eof)
    TAPE_TRUNC_WHOAMI .STRINGZ "ftrunc: "

; Input: Drive number (r1)
TAPE_REWIND
    ; save return address
    ADD R6, R6, #-1
    STR R7, R6, #0
    LD R2, SEEK0_MSG
    LEA R3, TAPE_REWIND_WHOAMI
    JSR TAPE_SEND_COMMAND
    ; restore return address
    LDR R7, R6, #0
    ADD R6, R6, #1
    RET
    SEEK0_MSG .FILL x0000 ; message with tapenum=0, opcode=0b00 (seek), and seekpos=0x00
    TAPE_REWIND_WHOAMI .STRINGZ "frewind: "

; Input: Drive number (r1)
TAPE_CLOSE
    ; save return address
    ADD R6, R6, #-1
    STR R7, R6, #0
    ; Be kind, rewind!
    FREWIND

    ; Free up entry in tapenum table
    ; tapenum_ent *ent = tapenum_table + drivenum;
    LDI R2, TAPE_CLOSE__TAPENUM_TABLE_LEN__ADDR
    ADD R2, R2, R1
    ; *ent = -1;
    AND R0, R0, #0
    ADD R0, R0, #-1
    STR R0, R2, #0
    ; restore return address
    LDR R7, R6, #0
    ADD R6, R6, #1
    RET
    TAPE_CLOSE__TAPENUM_TABLE_LEN__ADDR .FILL TAPENUM_TABLE_LEN

; Inputs: Command message template (r2), string of calling syscall (r3)
; Warning: this will clobber the daylights out of all registers
TAPE_SEND_COMMAND
    ; save return address
    ADD R6, R6, #-1
    STR R7, R6, #0

    ; Wait to send
    TAPE_CMD_POLL1
        LDI R4, TSSR_ADDR
        BRzp TAPE_CMD_POLL1

    JSR SHIFT_DRIVENUM ; r1 <- drivenum << 8
    ; Build CMD message (format below)
    ; r2 already holds message template
    ; message_template | (drivenum << 8) // Except DeMorgan's'd
    NOT R2, R2
    NOT R1, R1
    AND R2, R1, R2
    NOT R2, R2
    ; Send <command>(drivenum)
    STI R2, TSDR_ADDR

    ; Wait to recv an ACK
    TAPE_CMD_POLL2
        LDI R2, TRSR_ADDR
        BRzp TAPE_CMD_POLL2

    LDI R1, TRDR_ADDR
    JSR DECODE_TAPE_MSG ; r1 <- data, r2 <- opcode

    ; Jump table for opcode
    LEA R3, TAPE_CMD_JMP_OPCODE
    ADD R3, R3, R2
    LDR R3, R3, #0
    JMP R3
    TAPE_CMD_JMP_OPCODE
        .FILL TAPE_CMD_HANDLE_ERR
        .FILL TAPE_CMD_HANDLE_DATA
        .FILL TAPE_CMD_HANDLE_ACK
        .FILL TAPE_CMD_HANDLE_UNKNOWN

    TAPE_CMD_HANDLE_ERR
        ADD R0, R3, #0 ; r0 <- whoami string address
        PUTS
        JSR TAPE_PRINT_ERR ; Will not return

    TAPE_CMD_HANDLE_DATA
        ADD R0, R3, #0 ; r0 <- whoami string address
        PUTS
        LEA R0, TAPE_CMD_DATA_ERR_MSG
        PUTS
        HALT
        TAPE_CMD_DATA_ERR_MSG .STRINGZ "ERROR: Unexpected DATA response from tape drive\n"

    TAPE_CMD_HANDLE_UNKNOWN
        ADD R0, R3, #0 ; r0 <- whoami string address
        PUTS
        LEA R0, TAPE_CMD_UNKNOWN_ERR_MSG
        PUTS
        HALT
        TAPE_CMD_UNKNOWN_ERR_MSG .STRINGZ "ERROR: Unknown message id sent by tape drive\n"

    TAPE_CMD_HANDLE_ACK
    ; We're good, return
    ; restore return address
    LDR R7, R6, #0
    ADD R6, R6, #1
    RET

; Inputs: message (r1)
; Outputs: data (r1), opcode (r2)
; Uses stack
DECODE_TAPE_MSG
    ; save return address
    ADD R6, R6, #-1
    STR R7, R6, #0
    ; Mask out upper 8 bits to get data (the lower 8 bits)
    LD R2, TAPE_DATA_MASK
    AND R2, R1, R2
    ; Spill the 8-bit data to the stack so we can clobber r1 and r2
    ADD R6, R6, #-1
    STR R2, R6, #0
    ; Mask out the lower 14 bits
    LD R2, TAPE_OPCODE_MASK
    AND R1, R1, R2
    ; trick to right shift
    AND R2, R2, #0
    ADD R1, R1, #0 ; update cc for packet
    BRzp MSB_CLEAR
    ADD R2, R2, #2 ; r2 | (0x1 << 1)
    MSB_CLEAR ADD R1, R1, R1 ; r1 = r1 << 1
    BRzp NMSB_CLEAR
    ADD R2, R2, #1
    NMSB_CLEAR
    ; Recover the 8 bits of data we saved earlier
    LDR R1, R6, #0
    ADD R6, R6, #1
    ; restore return address
    LDR R7, R6, #0
    ADD R6, R6, #1
    RET
    TAPE_OPCODE_MASK .FILL xC000
    TAPE_DATA_MASK   .FILL x00FF

; Input: drivenum (r1)
; Output: drivenum << 8 (r1)
SHIFT_DRIVENUM
    ; save return address
    ADD R6, R6, #-1
    STR R7, R6, #0
    ; Shift over r1, i.e., r1 << 8
    ADD R1, R1, R1 ; r1 <- 2*drivenum
    ADD R1, R1, R1 ; r1 <- 4*drivenum
    ADD R1, R1, R1 ; r1 <- 8*drivenum
    ADD R1, R1, R1 ; r1 <- 16*drivenum
    ADD R1, R1, R1 ; r1 <- 32*drivenum
    ADD R1, R1, R1 ; r1 <- 64*drivenum
    ADD R1, R1, R1 ; r1 <- 128*drivenum
    ADD R1, R1, R1 ; r1 <- 256*drivenum == r1 <- drivenum << 8
    ; restore return address
    LDR R7, R6, #0
    ADD R6, R6, #1
    RET

; Input: Message data (r1)
; Does not return (it HALTs)
TAPE_PRINT_ERR
    LEA R0, TAPE_ERR_MSG
    PUTS
    AND R1, R1, #3 ; mask out everything except lower 2 bits
    ; look up error message in table
    LEA R0, TAPE_ERR_TABLE
    ADD R0, R0, R1
    LDR R0, R0, #0
    PUTS
    HALT
    TAPE_ERR_MSG .STRINGZ "ERROR: Tape drive returned: "
    TAPE_ERR_TABLE
        .FILL TAPE_GETC_ERR_TABLE_00
        .FILL TAPE_GETC_ERR_TABLE_01
        .FILL TAPE_GETC_ERR_TABLE_10
        .FILL TAPE_GETC_ERR_TABLE_11
    TAPE_GETC_ERR_TABLE_00 .STRINGZ "Bad argument\n"    ; 0b00
    TAPE_GETC_ERR_TABLE_01 .STRINGZ "Bad message id\n"  ; 0b01
    TAPE_GETC_ERR_TABLE_10 .STRINGZ "Hit end of tape\n" ; 0b10
    TAPE_GETC_ERR_TABLE_11 .STRINGZ "Unknown error\n"   ; 0b11. Currently never sent by hardware

; Inputs: Path to open (r0), r/w (r1)
; Output: new fd (r1)
TRAP_FOPEN
    ; save regs
    ADD R6, R6, #-1
    STR R0, R6, #0
    ADD R6, R6, #-1
    STR R2, R6, #0
    ADD R6, R6, #-1
    STR R3, R6, #0
    ADD R6, R6, #-1
    STR R4, R6, #0
    ADD R6, R6, #-1
    STR R5, R6, #0
    ADD R6, R6, #-1
    STR R7, R6, #0

    ADD R1, R1, #0
    BRz RW_OK
    ADD R2, R1, #-1
    BRz RW_OK
    BR RW_BOGUS

    RW_OK
    ; char *prefix = "/dev/st"
    LEA R2, TAPE_DEV_PATH
    ; while (*path && *prefix) {
    PATH_PREFIX_LOOP
        LDR R3, R0, #0 ; *path
        BRz BAD_PATH
        LDR R4, R2, #0 ; *prefix
        BRz GOOD_PATH

        ; if (*path != *prefix) {
        ;     crash
        ; }
        NOT R4, R4
        ADD R4, R4, #1
        ADD R4, R3, R4 ; *path - *prefix
        BRnp BAD_PATH

        ; path++;
        ADD R0, R0, #1
        ; prefix++;
        ADD R2, R2, #1
        BR PATH_PREFIX_LOOP
    ; }

    GOOD_PATH
    ; int sum = 0;
    AND R2, R2, #0
    TAPE_IDX_LOOP
        LDR R3, R0, #0 ; *path
        BRz TAPE_IDX_LOOP_BREAK

        ; if (*path > '9') {
        LD R5, FOPEN_ASCII_NINE
        NOT R5, R5
        ADD R5, R5, #1
        ADD R5, R3, R5 ; *path - '9'
        BRp BAD_PATH

        ; if (*path < '0') {
        LD R5, FOPEN_ASCII_ZERO
        NOT R5, R5
        ADD R5, R5, #1
        ADD R5, R3, R5 ; *path - '0'
        BRn BAD_PATH

        ; sum = sum * 8 + sum * 2
        ADD R4, R2, R2 ; tmp = sum * 2
        ADD R4, R4, R4 ; tmp = sum * 4
        ADD R4, R4, R4 ; tmp = sum * 8
        ADD R2, R2, R2 ; sum * 2
        ADD R2, R4, R2 ; sum = sum * 8 + sum * 2

        ; sum += *path - '0'
        ADD R2, R2, R5 ; sum = sum + (*path - '0')
        ADD R0, R0, #1 ; path++
        BR TAPE_IDX_LOOP
    TAPE_IDX_LOOP_BREAK

    ; if (sum < 0) {
    ADD R2, R2, #0
    BRn BAD_PATH

    ; if (sum >= 64) {
    LDI R3, TRAP_FOPEN__TAPENUM_TABLE_LEN__ADDR
    NOT R3, R3
    ADD R3, R3, #1
    ADD R3, R3, R2 ; sum - 64
    BRzp BAD_PATH

    ; tapenum_ent *ent = tapenum_table + sum
    LD R3, TRAP_FOPEN__TAPENUM_TABLE__ADDR
    ADD R3, R3, R2
    LDR R4, R3, #0 ; tapenum_table[sum]
    BRzp DISK_IN_USE

    ; Find a free fd
    ; for (i = 0; i < FD_TABLE_LEN; i++) {
    AND R4, R4, #0 ; i = 0
    FD_TABLE_SEARCH
        ADD R5, R4, R4 ; r5 <- 2*i
        ADD R5, R5, R5 ; r5 <- 4*i
        ADD R5, R5, R4 ; r5 <- 5*i
        ADD R5, R5, R4 ; r5 <- 6*i
        ADD R5, R5, R4 ; r5 <- 7*i
        LD R0, TRAP_FOPEN__FD_TABLE__ADDR
        ADD R5, R0, R5 ; fd_ent *ent = fd_table + i;

        LDR R0, R5, #0
        BRn FOUND_FREE_FD
        ADD R4, R4, #1
        LDI R0, TRAP_FOPEN__FD_TABLE_LEN__ADDR
        NOT R0, R0
        ADD R0, R0, #1
        ADD R0, R0, R4 ; i - FD_TABLE_LEN
        BRz FDS_EXHAUSTED
        BR FD_TABLE_SEARCH

    FOUND_FREE_FD
    ; ent->state = rw;
    STR R1, R5, #0
    ; ent->data = tape_idx;
    STR R2, R5, #1
    ; ent->putc = &tape_putc
    LD R0, TRAP_FOPEN__TAPE_PUTC__ADDR
    STR R0, R5, #2
    ; ent->getc = &tape_getc
    LD R0, TRAP_FOPEN__TAPE_GETC__ADDR
    STR R0, R5, #3
    ; ent->trunc = &tape_trunc
    LD R0, TRAP_FOPEN__TAPE_TRUNC__ADDR
    STR R0, R5, #4
    ; ent->rewind = &tape_rewind
    LD R0, TRAP_FOPEN__TAPE_REWIND__ADDR
    STR R0, R5, #5
    ; ent->close = &tape_close
    LD R0, TRAP_FOPEN__TAPE_CLOSE__ADDR
    STR R0, R5, #6

    ; *tapenum_ent = fd
    STR R4, R3, #0
    ; return fd via r1
    ADD R1, R4, #0

    ; Rewind, just in case LC3Tools has persisted some state unexpectedly
    FREWIND

    ; restore regs
    LDR R7, R6, #0
    ADD R6, R6, #1
    LDR R5, R6, #0
    ADD R6, R6, #1
    LDR R4, R6, #0
    ADD R6, R6, #1
    LDR R3, R6, #0
    ADD R6, R6, #1
    LDR R2, R6, #0
    ADD R6, R6, #1
    LDR R0, R6, #0
    ADD R6, R6, #1
    RTI

    RW_BOGUS
    LEA R0, RW_BOGUS_ERR
    PUTS
    HALT

    BAD_PATH
    LEA R0, BAD_PATH_ERR
    PUTS
    HALT

    DISK_IN_USE
    LEA R0, DISK_IN_USE_ERR
    PUTS
    HALT

    FDS_EXHAUSTED
    LEA R0, FDS_EXHAUSTED_ERR
    PUTS
    HALT

    RW_BOGUS_ERR .STRINGZ "ERROR: rw must be #0 or #1\n"
    DISK_IN_USE_ERR .STRINGZ "ERROR: Disk in use\n"
    BAD_PATH_ERR .STRINGZ "ERROR: Invalid path name\n"
    FDS_EXHAUSTED_ERR .STRINGZ "ERROR: Out of file descriptors\n"
    TAPE_DEV_PATH .STRINGZ "/dev/st"
    FOPEN_ASCII_ZERO .FILL x30
    FOPEN_ASCII_NINE .FILL x39
    TRAP_FOPEN__TAPENUM_TABLE_LEN__ADDR .FILL TAPENUM_TABLE_LEN
    TRAP_FOPEN__TAPENUM_TABLE__ADDR .FILL TAPENUM_TABLE
    TRAP_FOPEN__FD_TABLE_LEN__ADDR .FILL FD_TABLE_LEN
    TRAP_FOPEN__FD_TABLE__ADDR .FILL FD_TABLE
    TRAP_FOPEN__TAPE_PUTC__ADDR .FILL TAPE_PUTC
    TRAP_FOPEN__TAPE_GETC__ADDR .FILL TAPE_GETC
    TRAP_FOPEN__TAPE_TRUNC__ADDR .FILL TAPE_TRUNC
    TRAP_FOPEN__TAPE_REWIND__ADDR .FILL TAPE_REWIND
    TRAP_FOPEN__TAPE_CLOSE__ADDR .FILL TAPE_CLOSE


; Inputs: c (R0), fd (R1)
TRAP_FPUTC
    ; save regs
    ; (Need to save pretty much everything here because who knows which
    ;  registers the driver uses)
    ADD R6, R6, #-1
    STR R0, R6, #0
    ADD R6, R6, #-1
    STR R1, R6, #0
    ADD R6, R6, #-1
    STR R2, R6, #0
    ADD R6, R6, #-1
    STR R3, R6, #0
    ADD R6, R6, #-1
    STR R4, R6, #0
    ADD R6, R6, #-1
    STR R5, R6, #0
    ADD R6, R6, #-1
    STR R7, R6, #0

    ADD R1, R1, #0
    BRn FPUTC_BAD_FD
    LDI R2, TRAP_FPUTC__FD_TABLE_LEN__ADDR
    NOT R2, R2
    ADD R2, R2, #1
    ADD R2, R2, R1 ; fd - FD_TABLE_LEN
    BRzP FPUTC_BAD_FD

    ADD R2, R1, R1 ; r2 <- 2*fd
    ADD R2, R2, R2 ; r2 <- 4*fd
    ADD R2, R2, R1 ; r2 <- 5*fd
    ADD R2, R2, R1 ; r2 <- 6*fd
    ADD R2, R2, R1 ; r2 <- 7*fd
    LD R3, TRAP_FPUTC__FD_TABLE__ADDR
    ; fd_ent *ent = fd_table + fd;
    ADD R2, R3, R2
    LDR R3, R2, #0 ; ent->status
    BRn FPUTC_BAD_FD
    BRz FPUTC_RDONLY

    LD R3, FPUTC_CHAR_MASK
    AND R0, R0, R3 ; c = c & 0xff
    LDR R1, R2, #1 ; ent->arg
    LDR R3, R2, #2 ; ent->putc
    JSRR R3

    ; restore regs
    LDR R7, R6, #0
    ADD R6, R6, #1
    LDR R5, R6, #0
    ADD R6, R6, #1
    LDR R4, R6, #0
    ADD R6, R6, #1
    LDR R3, R6, #0
    ADD R6, R6, #1
    LDR R2, R6, #0
    ADD R6, R6, #1
    LDR R1, R6, #0
    ADD R6, R6, #1
    LDR R0, R6, #0
    ADD R6, R6, #1
    RTI

    FPUTC_BAD_FD
    LEA R0, FPUTC_BAD_FD_ERR
    PUTS
    HALT

    FPUTC_RDONLY
    LEA R0, FPUTC_RDONLY_ERR
    PUTS
    HALT

    FPUTC_CHAR_MASK .FILL xff
    FPUTC_BAD_FD_ERR .STRINGZ "ERROR: fd is invalid\n"
    FPUTC_RDONLY_ERR .STRINGZ "ERROR: cannot write to file opened for reading\n"
    TRAP_FPUTC__FD_TABLE__ADDR .FILL FD_TABLE
    TRAP_FPUTC__FD_TABLE_LEN__ADDR .FILL FD_TABLE_LEN

; Inputs: fd (R1)
; Outputs: c (R0)
TRAP_FGETC
    ; save regs
    ; (Need to save pretty much everything here because who knows which
    ;  registers the driver uses)
    ADD R6, R6, #-1
    STR R1, R6, #0
    ADD R6, R6, #-1
    STR R2, R6, #0
    ADD R6, R6, #-1
    STR R3, R6, #0
    ADD R6, R6, #-1
    STR R4, R6, #0
    ADD R6, R6, #-1
    STR R5, R6, #0
    ADD R6, R6, #-1
    STR R7, R6, #0

    ADD R1, R1, #0
    BRn FGETC_BAD_FD
    LDI R2, TRAP_FGETC__FD_TABLE_LEN__ADDR
    NOT R2, R2
    ADD R2, R2, #1
    ADD R2, R2, R1 ; fd - FD_TABLE_LEN
    BRzP FGETC_BAD_FD

    ADD R2, R1, R1 ; r2 <- 2*fd
    ADD R2, R2, R2 ; r2 <- 4*fd
    ADD R2, R2, R1 ; r2 <- 5*fd
    ADD R2, R2, R1 ; r2 <- 6*fd
    ADD R2, R2, R1 ; r2 <- 7*fd
    LD R3, TRAP_FGETC__FD_TABLE__ADDR
    ; fd_ent *ent = fd_table + fd;
    ADD R2, R3, R2
    LDR R3, R2, #0 ; ent->status
    BRn FGETC_BAD_FD
    BRp FGETC_WRONLY

    LDR R1, R2, #1 ; ent->arg
    LDR R3, R2, #3 ; ent->getc
    JSRR R3

    ; restore regs
    LDR R7, R6, #0
    ADD R6, R6, #1
    LDR R5, R6, #0
    ADD R6, R6, #1
    LDR R4, R6, #0
    ADD R6, R6, #1
    LDR R3, R6, #0
    ADD R6, R6, #1
    LDR R2, R6, #0
    ADD R6, R6, #1
    LDR R1, R6, #0
    ADD R6, R6, #1
    RTI

    FGETC_BAD_FD
    LEA R0, FGETC_BAD_FD_ERR
    PUTS
    HALT

    FGETC_WRONLY
    LEA R0, FGETC_WRONLY_ERR
    PUTS
    HALT

    FGETC_BAD_FD_ERR .STRINGZ "ERROR: fd is invalid\n"
    FGETC_WRONLY_ERR .STRINGZ "ERROR: cannot read from file opened for writing\n"
    TRAP_FGETC__FD_TABLE__ADDR .FILL FD_TABLE
    TRAP_FGETC__FD_TABLE_LEN__ADDR .FILL FD_TABLE_LEN

; Inputs: fd (R1)
TRAP_FTRUNC
    ; save regs
    ; (Need to save pretty much everything here because who knows which
    ;  registers the driver uses)
    ADD R6, R6, #-1
    STR R0, R6, #0
    ADD R6, R6, #-1
    STR R1, R6, #0
    ADD R6, R6, #-1
    STR R2, R6, #0
    ADD R6, R6, #-1
    STR R3, R6, #0
    ADD R6, R6, #-1
    STR R4, R6, #0
    ADD R6, R6, #-1
    STR R5, R6, #0
    ADD R6, R6, #-1
    STR R7, R6, #0

    ADD R1, R1, #0
    BRn FTRUNC_BAD_FD
    LDI R2, TRAP_FTRUNC__FD_TABLE_LEN__ADDR
    NOT R2, R2
    ADD R2, R2, #1
    ADD R2, R2, R1 ; fd - FD_TABLE_LEN
    BRzP FTRUNC_BAD_FD

    ADD R2, R1, R1 ; r2 <- 2*fd
    ADD R2, R2, R2 ; r2 <- 4*fd
    ADD R2, R2, R1 ; r2 <- 5*fd
    ADD R2, R2, R1 ; r2 <- 6*fd
    ADD R2, R2, R1 ; r2 <- 7*fd
    LD R3, TRAP_FTRUNC__FD_TABLE__ADDR
    ; fd_ent *ent = fd_table + fd;
    ADD R2, R3, R2
    LDR R3, R2, #0 ; ent->status
    BRn FTRUNC_BAD_FD
    BRz FTRUNC_RDONLY

    LDR R1, R2, #1 ; ent->arg
    LDR R3, R2, #4 ; ent->trunc
    JSRR R3

    ; restore regs
    LDR R7, R6, #0
    ADD R6, R6, #1
    LDR R5, R6, #0
    ADD R6, R6, #1
    LDR R4, R6, #0
    ADD R6, R6, #1
    LDR R3, R6, #0
    ADD R6, R6, #1
    LDR R2, R6, #0
    ADD R6, R6, #1
    LDR R1, R6, #0
    ADD R6, R6, #1
    LDR R0, R6, #0
    ADD R6, R6, #1
    RTI

    FTRUNC_BAD_FD
    LEA R0, FTRUNC_BAD_FD_ERR
    PUTS
    HALT

    FTRUNC_RDONLY
    LEA R0, FTRUNC_RDONLY_ERR
    PUTS
    HALT

    FTRUNC_BAD_FD_ERR .STRINGZ "ERROR: fd is invalid\n"
    FTRUNC_RDONLY_ERR .STRINGZ "ERROR: cannot read from file opened for writing\n"
    TRAP_FTRUNC__FD_TABLE__ADDR .FILL FD_TABLE
    TRAP_FTRUNC__FD_TABLE_LEN__ADDR .FILL FD_TABLE_LEN

; Inputs: fd (R1)
TRAP_FREWIND
    ; save regs
    ; (Need to save pretty much everything here because who knows which
    ;  registers the driver uses)
    ADD R6, R6, #-1
    STR R0, R6, #0
    ADD R6, R6, #-1
    STR R1, R6, #0
    ADD R6, R6, #-1
    STR R2, R6, #0
    ADD R6, R6, #-1
    STR R3, R6, #0
    ADD R6, R6, #-1
    STR R4, R6, #0
    ADD R6, R6, #-1
    STR R5, R6, #0
    ADD R6, R6, #-1
    STR R7, R6, #0

    ADD R1, R1, #0
    BRn FREWIND_BAD_FD
    LD R2, FD_TABLE_LEN
    NOT R2, R2
    ADD R2, R2, #1
    ADD R2, R2, R1 ; fd - FD_TABLE_LEN
    BRzp FREWIND_BAD_FD

    ADD R2, R1, R1 ; r2 <- 2*fd
    ADD R2, R2, R2 ; r2 <- 4*fd
    ADD R2, R2, R1 ; r2 <- 5*fd
    ADD R2, R2, R1 ; r2 <- 6*fd
    ADD R2, R2, R1 ; r2 <- 7*fd
    LEA R3, FD_TABLE
    ; fd_ent *ent = fd_table + fd;
    ADD R2, R3, R2
    LDR R3, R2, #0 ; ent->status
    BRn FREWIND_BAD_FD

    LDR R1, R2, #1 ; ent->arg
    LDR R3, R2, #5 ; ent->rewind
    JSRR R3

    ; restore regs
    LDR R7, R6, #0
    ADD R6, R6, #1
    LDR R5, R6, #0
    ADD R6, R6, #1
    LDR R4, R6, #0
    ADD R6, R6, #1
    LDR R3, R6, #0
    ADD R6, R6, #1
    LDR R2, R6, #0
    ADD R6, R6, #1
    LDR R1, R6, #0
    ADD R6, R6, #1
    LDR R0, R6, #0
    ADD R6, R6, #1
    RTI

    FREWIND_BAD_FD
    LEA R0, FREWIND_BAD_FD_ERR
    PUTS
    HALT

    FREWIND_BAD_FD_ERR .STRINGZ "ERROR: fd is invalid\n"

; Inputs: fd (R1)
TRAP_FCLOSE
    ; save regs
    ; (Need to save pretty much everything here because who knows which
    ;  registers the driver uses)
    ADD R6, R6, #-1
    STR R0, R6, #0
    ADD R6, R6, #-1
    STR R1, R6, #0
    ADD R6, R6, #-1
    STR R2, R6, #0
    ADD R6, R6, #-1
    STR R3, R6, #0
    ADD R6, R6, #-1
    STR R4, R6, #0
    ADD R6, R6, #-1
    STR R5, R6, #0
    ADD R6, R6, #-1
    STR R7, R6, #0

    ADD R1, R1, #0
    BRn FCLOSE_BAD_FD
    LD R2, FD_TABLE_LEN
    NOT R2, R2
    ADD R2, R2, #1
    ADD R2, R2, R1 ; fd - FD_TABLE_LEN
    BRzp FCLOSE_BAD_FD

    ADD R2, R1, R1 ; r2 <- 2*fd
    ADD R2, R2, R2 ; r2 <- 4*fd
    ADD R2, R2, R1 ; r2 <- 5*fd
    ADD R2, R2, R1 ; r2 <- 6*fd
    ADD R2, R2, R1 ; r2 <- 7*fd
    LEA R3, FD_TABLE
    ; fd_ent *ent = fd_table + fd;
    ADD R2, R3, R2
    LDR R3, R2, #0 ; ent->status
    BRn FCLOSE_BAD_FD

    LDR R1, R2, #1 ; ent->arg
    LDR R3, R2, #6 ; ent->close

    ; save ent (it's annoying to calculate)
    ADD R6, R6, #-1
    STR R2, R6, #0
    ; In the case of a tape, this will free up the location in the tape table
    JSRR R3
    ; restore ent
    LDR R2, R6, #0
    ADD R6, R6, #1

    ; Now free up this fd
    AND R0, R0, #0
    ADD R0, R0, #-1
    ; ent->state = -1 (free)
    STR R0, R2, #0

    ; restore regs
    LDR R7, R6, #0
    ADD R6, R6, #1
    LDR R5, R6, #0
    ADD R6, R6, #1
    LDR R4, R6, #0
    ADD R6, R6, #1
    LDR R3, R6, #0
    ADD R6, R6, #1
    LDR R2, R6, #0
    ADD R6, R6, #1
    LDR R1, R6, #0
    ADD R6, R6, #1
    LDR R0, R6, #0
    ADD R6, R6, #1
    RTI

    FCLOSE_BAD_FD
    LEA R0, FCLOSE_BAD_FD_ERR
    PUTS
    HALT

    FCLOSE_BAD_FD_ERR .STRINGZ "ERROR: fd is invalid\n"

; #define TAPENUM_TABLE_LEN 64
; #define FD_TABLE_LEN 16
TAPENUM_TABLE_LEN .FILL #64
FD_TABLE_LEN .FILL #16
; enum fd_state {
;     STATE_FREE = -1,
;     STATE_R = 0,
;     STATE_W = 1,
; };
; typedef struct {
;     enum fd_state state;
;     int driver_data; // tape drive number for tape fds
;     void (*putc)(int driver_data /* r1 */, char c /* r0 */);
;     /* result in r0 */ char (*getc)(int driver_data /* r1 */);
;     void (*trunc)(int driver_data /* r1 */);
;     void (*rewind)(int driver_data /* r1 */);
;     void (*close)(int driver_data /* r1 */);
; } fd_ent;
; fd_ent fd_table[FD_TABLE_LEN];
FD_TABLE .BLKW #112 ; 7*16
; typedef int tapenum_ent;
; tapenum_ent tapenum_table[TAPENUM_TABLE_LEN];
TAPENUM_TABLE .BLKW #64 ; 2^6

    .END
)LC3OS2";
        return std::string(lc3os_src_1) + std::string(lc3os_src_2);
    }
};
};
