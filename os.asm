.orig x3000
jsr INIT_TABLES
jsr OPEN_STDIN
jsr OPEN_STDOUT

lea r0, DRIVE_0
and r1, r1, 0
fopen
halt
DRIVE_0 .stringz "/dev/st0"

INIT_TABLES
    ; for (i = 0; i < 16; i++) {
    and r0, r0, 0 ; i = 0
    FD_TABLE_INIT_LOOP
    and r1, r1, 0
    add r1, r1, -1 ; r1 <- -1

    add r2, r0, r0 ; r2 <- 2*i
    add r2, r2, r2 ; r2 <- 4*i
    add r2, r2, r0 ; r2 <- 5*i
    add r2, r2, r0 ; r2 <- 6*i
    add r2, r2, r0 ; r2 <- 7*i
    ld r3, INIT_TABLES__FD_TABLE__ADDR
    ; fd_ent *ent = fd_table + i;
    add r3, r3, r2

    ; ent->state = -1; // invalid
    str r1, r3, 0

    add r0, r0, 1 ; i++
    ldi r1, INIT_TABLES__FD_TABLE_LEN__ADDR
    not r1, r1
    add r1, r1, 1
    add r1, r0, r1
    brn FD_TABLE_INIT_LOOP
    ; }

    ; for (i = 0; i < 64; i++) {
    and r0, r0, 0 ; i = 0
    TAPENUM_TABLE_INIT_LOOP
    and r1, r1, 0
    add r1, r1, -1 ; r1 <- -1
    ld r3, INIT_TABLES__TAPENUM_TABLE__ADDR
    ; tapenum_ent *ent = tapenum_table + i;
    add r3, r3, r0
    ; *ent = -1;
    str r1, r3, 0
    add r0, r0, 1 ; i++
    ; if i < 64, continue
    ldi r1, INIT_TABLES__TAPENUM_TABLE_LEN__ADDR
    not r1, r1
    add r1, r1, 1
    add r1, r1, r0
    brn TAPENUM_TABLE_INIT_LOOP
    ; }

    ret

    INIT_TABLES__FD_TABLE__ADDR .fill FD_TABLE
    INIT_TABLES__FD_TABLE_LEN__ADDR .fill FD_TABLE_LEN
    INIT_TABLES__TAPENUM_TABLE__ADDR .fill TAPENUM_TABLE
    INIT_TABLES__TAPENUM_TABLE_LEN__ADDR .fill TAPENUM_TABLE_LEN

OPEN_STDIN
    ; fd_ent *fd0 = &fd_table[0];
    ld r1, OPEN_STDIN__FD_TABLE__ADDR
    ; fd0->state = 0; // R
    and r0, r0, 0
    str r0, r1, 0
    ; fd0->data = 0; // don't care
    str r0, r1, 1
    ; fd0->putc = &keyboard_invalid
    lea r0, KEYBOARD_INVALID
    str r0, r1, 2
    ; fd0->getc = &keyboard_getc
    lea r0, KEYBOARD_GETC
    str r0, r1, 3
    ; fd0->trunc = &keyboard_invalid
    lea r0, KEYBOARD_INVALID
    str r0, r1, 4
    ; fd0->rewind = &keyboard_invalid
    lea r0, KEYBOARD_INVALID
    str r0, r1, 5
    ; fd0->close = &keyboard_close
    lea r0, KEYBOARD_CLOSE
    str r0, r1, 6
    ret

    OPEN_STDIN__FD_TABLE__ADDR .fill FD_TABLE

KEYBOARD_INVALID
    lea r0, KEYBOARD_INVALID_ERR
    puts
    halt
    KEYBOARD_INVALID_ERR .stringz "ERROR: Invalid operation for stdin\n"

; Output: byte from keyboard (r0)
KEYBOARD_GETC
    getc
    ret

; Currently a no-op
KEYBOARD_CLOSE
    ret

OPEN_STDOUT
    ; fd_ent *fd1 = &fd_table[1];
    ld r1, OPEN_STDOUT__FD_TABLE__ADDR
    add r1, r1, 7
    ; fd1->state = 1; // W
    and r0, r0, 0
    add r0, r0, 1
    str r0, r1, 0
    ; fd1->data = 1; // don't care
    str r0, r1, 1
    ; fd1->putc = &console_putc
    lea r0, CONSOLE_PUTC
    str r0, r1, 2
    ; fd1->getc = &console_getc
    lea r0, CONSOLE_INVALID
    str r0, r1, 3
    ; fd1->trunc = &console_trunc
    lea r0, CONSOLE_INVALID
    str r0, r1, 4
    ; fd1->rewind = &console_rewind
    lea r0, CONSOLE_INVALID
    str r0, r1, 5
    ; fd1->close = &console_close
    lea r0, CONSOLE_CLOSE
    str r0, r1, 6
    ret

    OPEN_STDOUT__FD_TABLE__ADDR .fill FD_TABLE

CONSOLE_INVALID
    lea r0, CONSOLE_INVALID_ERR
    puts
    halt
    CONSOLE_INVALID_ERR .stringz "ERROR: Invalid operation for stdout\n"

; Input: byte to display (r0)
CONSOLE_PUTC
    putc
    ret

; Currently a no-op
CONSOLE_CLOSE
    ret

; Input: Byte to write (r0, written below as c), Drive number (r1)
TAPE_PUTC
    ; Wait to send
    TAPE_PUTC_POLL1
        ldi r2, TSSR_ADDR
        brzp TAPE_PUTC_POLL1

    jsr SHIFT_DRIVENUM ; r1 <- drivenum << 8
    ; Build PUTC message (format below)
    ld r2, PUTC_MSG
    ; PUTC_MSG | c | (drivenum << 8) // Except DeMorgan's'd
    not r2, r2
    not r0, r0
    not r1, r1
    and r2, r0, r2
    and r2, r1, r2
    not r2, r2
    ; Send PUTC(drivenum, c)
    sti r2, TSDR_ADDR

    ; Wait to recv an ACK
    TAPE_PUTC_POLL2
        ldi r2, TRSR_ADDR
        brzp TAPE_PUTC_POLL2

    ldi r1, TRDR_ADDR
    jsr DECODE_TAPE_MSG ; r1 <- data, r2 <- opcode

    ; Jump table for opcode
    lea r3, TAPE_PUTC_JMP_OPCODE
    add r3, r3, r2
    ldr r3, r3, 0
    jmp r3
    TAPE_PUTC_JMP_OPCODE
        .fill TAPE_PUTC_HANDLE_ERR
        .fill TAPE_PUTC_HANDLE_DATA
        .fill TAPE_PUTC_HANDLE_ACK
        .fill TAPE_PUTC_HANDLE_UNKNOWN

    TAPE_PUTC_HANDLE_ERR
        lea r0, TAPE_PUTC_WHOAMI
        puts
        jsr TAPE_PRINT_ERR ; Will not return
        TAPE_PUTC_WHOAMI .stringz "fputc: "

    TAPE_PUTC_HANDLE_DATA
        lea r0, TAPE_PUTC_DATA_ERR_MSG
        puts
        halt
        TAPE_PUTC_DATA_ERR_MSG .stringz "fputc: ERROR: Unexpected DATA response from tape drive\n"

    TAPE_PUTC_HANDLE_UNKNOWN
        lea r0, TAPE_PUTC_UNKNOWN_ERR_MSG
        puts
        halt
        TAPE_PUTC_UNKNOWN_ERR_MSG .stringz "fputc: ERROR: Unknown message id sent by tape drive\n"

    TAPE_PUTC_HANDLE_ACK
    ; We're good, return
    ret

    ; Message format:
    ; 15     14 13       8 7         0
    ; .-------------------------------.
    ; | opcode | tape num |   data    |
    ; '-------------------------------'
    PUTC_MSG  .fill x8000 ; message with tapenum=0 and opcode=0b10
    TRSR_ADDR .fill xFE08 ; Tape recv status register
    TRDR_ADDR .fill xFE0A ; Tape recv data register
    TSSR_ADDR .fill xFE0C ; Tape send status register
    TSDR_ADDR .fill xFE0E ; Tape send data register

; Input: Drive number (r1)
; Output: Byte from tape (r0)
TAPE_GETC
    ; Wait to send
    TAPE_GETC_POLL1
        ldi r2, TSSR_ADDR
        brzp TAPE_GETC_POLL1

    jsr SHIFT_DRIVENUM ; r1 <- drivenum << 8
    ; Build GETC message (format above in TAPE_PUTC)
    ld r2, GETC_MSG
    ; PUTC_MSG | (drivenum << 8) // Except DeMorgan's'd
    not r2, r2
    not r1, r1
    and r2, r1, r2
    not r2, r2
    ; Send GETC(drivenum)
    sti r2, TSDR_ADDR

    ; Wait to recv an ACK
    TAPE_GETC_POLL2
        ldi r2, TRSR_ADDR
        brzp TAPE_GETC_POLL2

    ldi r1, TRDR_ADDR
    jsr DECODE_TAPE_MSG ; r1 <- data, r2 <- opcode

    ; Jump table for opcode
    lea r3, TAPE_GETC_JMP_OPCODE
    add r3, r3, r2
    ldr r3, r3, 0
    jmp r3
    TAPE_GETC_JMP_OPCODE
        .fill TAPE_GETC_HANDLE_ERR
        .fill TAPE_GETC_HANDLE_DATA
        .fill TAPE_GETC_HANDLE_ACK
        .fill TAPE_GETC_HANDLE_UNKNOWN

    TAPE_GETC_HANDLE_ERR
        lea r0, TAPE_GETC_WHOAMI
        puts
        jsr TAPE_PRINT_ERR ; Will not return
        TAPE_GETC_WHOAMI .stringz "fgetc: "

    TAPE_GETC_HANDLE_DATA
        ; Set return value that TRAP_FGETC expects
        add r0, r1, 0
        br TAPE_GETC_DONE

    TAPE_GETC_HANDLE_ACK
        lea r0, TAPE_GETC_ACK_ERR_MSG
        puts
        halt
        TAPE_GETC_ACK_ERR_MSG .stringz "fgetc: ERROR: Unexpected ACK response from tape drive\n"

    TAPE_GETC_HANDLE_UNKNOWN
        lea r0, TAPE_GETC_UNKNOWN_ERR_MSG
        puts
        halt
        TAPE_GETC_UNKNOWN_ERR_MSG .stringz "fgetc: ERROR: Unknown message id sent by tape drive\n"

    TAPE_GETC_DONE
    ret
    GETC_MSG  .fill x4000 ; message with tapenum=0 and opcode=0b01

; Input: Drive number (r1)
TAPE_TRUNC
    ld r2, SET_EOF_MSG
    lea r3, TAPE_TRUNC_WHOAMI
    jsr TAPE_SEND_COMMAND
    ret
    SET_EOF_MSG .fill xC000 ; message with tapenum=0 and opcode=0b11 (set eof)
    TAPE_TRUNC_WHOAMI .stringz "ftrunc: "

; Input: Drive number (r1)
TAPE_REWIND
    ld r2, SET_EOF_MSG
    lea r3, TAPE_REWIND_WHOAMI
    jsr TAPE_SEND_COMMAND
    ret
    SEEK_MSG .fill x0000 ; message with tapenum=0, opcode=0b00 (seek), and seekpos=0x00
    TAPE_REWIND_WHOAMI .stringz "frewind: "

; Input: Drive number (r1)
TAPE_CLOSE
    ; Be kind, rewind!
    frewind

    ; Free up entry in tapenum table
    ; tapenum_ent *ent = tapenum_table + drivenum;
    ldi r2, TAPE_CLOSE__TAPENUM_TABLE_LEN__ADDR
    add r2, r2, r1
    ; *ent = -1;
    and r0, r0, 0
    add r0, r0, -1
    str r0, r2, 0
    ret
    TAPE_CLOSE__TAPENUM_TABLE_LEN__ADDR .fill TAPENUM_TABLE_LEN

; Inputs: Command message template (r2), string of calling syscall (r3)
; Warning: this will clobber the daylights out of all registers
TAPE_SEND_COMMAND
    ; Wait to send
    TAPE_CMD_POLL1
        ldi r4, TSSR_ADDR
        brzp TAPE_CMD_POLL1

    jsr SHIFT_DRIVENUM ; r1 <- drivenum << 8
    ; Build CMD message (format below)
    ; r2 already holds message template
    ; message_template | (drivenum << 8) // Except DeMorgan's'd
    not r2, r2
    not r1, r1
    and r2, r1, r2
    not r2, r2
    ; Send <command>(drivenum)
    sti r2, TSDR_ADDR

    ; Wait to recv an ACK
    TAPE_CMD_POLL2
        ldi r2, TRSR_ADDR
        brzp TAPE_CMD_POLL2

    ldi r1, TRDR_ADDR
    jsr DECODE_TAPE_MSG ; r1 <- data, r2 <- opcode

    ; Jump table for opcode
    lea r3, TAPE_CMD_JMP_OPCODE
    add r3, r3, r2
    ldr r3, r3, 0
    jmp r3
    TAPE_CMD_JMP_OPCODE
        .fill TAPE_CMD_HANDLE_ERR
        .fill TAPE_CMD_HANDLE_DATA
        .fill TAPE_CMD_HANDLE_ACK
        .fill TAPE_CMD_HANDLE_UNKNOWN

    TAPE_CMD_HANDLE_ERR
        add r0, r3, 0 ; r0 <- whoami string address
        puts
        jsr TAPE_PRINT_ERR ; Will not return

    TAPE_CMD_HANDLE_DATA
        add r0, r3, 0 ; r0 <- whoami string address
        puts
        lea r0, TAPE_CMD_DATA_ERR_MSG
        puts
        halt
        TAPE_CMD_DATA_ERR_MSG .stringz "ERROR: Unexpected DATA response from tape drive\n"

    TAPE_CMD_HANDLE_UNKNOWN
        add r0, r3, 0 ; r0 <- whoami string address
        puts
        lea r0, TAPE_CMD_UNKNOWN_ERR_MSG
        puts
        halt
        TAPE_CMD_UNKNOWN_ERR_MSG .stringz "ERROR: Unknown message id sent by tape drive\n"

    TAPE_CMD_HANDLE_ACK
    ; We're good, return
    ret

; Inputs: message (r1)
; Outputs: data (r1), opcode (r2)
; Uses stack
DECODE_TAPE_MSG
    ; Mask out upper 8 bits to get data (the lower 8 bits)
    ld r2, TAPE_DATA_MASK
    and r2, r1, r2
    ; Spill the 8-bit data to the stack so we can clobber r1 and r2
    add r6, r6, -1
    str r2, r6, 0
    ; Mask out the lower 14 bits
    ld r2, TAPE_OPCODE_MASK
    and r1, r1, r2
    ; trick to right shift
    and r2, r2, 0
    add r1, r1, 0 ; update cc for packet
    brzp MSB_CLEAR
    add r2, r2, 2 ; r2 | (0x1 << 1)
    MSB_CLEAR add r1, r1, r1 ; r1 = r1 << 1
    brzp NMSB_CLEAR
    add r2, r2, 1
    NMSB_CLEAR
    ; Recover the 8 bits of data we saved earlier
    ldr r1, r6, 0
    add r6, r6, 1
    ret
    TAPE_OPCODE_MASK .fill xC000
    TAPE_DATA_MASK   .fill x00FF

; Input: drivenum (r1)
; Output: drivenum << 8 (r1)
SHIFT_DRIVENUM
    ; Shift over r1, i.e., r1 << 8
    add r1, r1, r1 ; r1 <- 2*drivenum
    add r1, r1, r1 ; r1 <- 4*drivenum
    add r1, r1, r1 ; r1 <- 8*drivenum
    add r1, r1, r1 ; r1 <- 16*drivenum
    add r1, r1, r1 ; r1 <- 32*drivenum
    add r1, r1, r1 ; r1 <- 64*drivenum
    add r1, r1, r1 ; r1 <- 128*drivenum
    add r1, r1, r1 ; r1 <- 256*drivenum == r1 <- drivenum << 8
    ret

; Input: Message data (r1)
TAPE_PRINT_ERR
    lea r0, TAPE_ERR_MSG
    puts
    and r1, r1, 3 ; mask out everything except lower 2 bits
    ; look up error message in table
    lea r0, TAPE_ERR_TABLE
    add r0, r0, r1
    ldr r0, r0, 0
    puts
    halt
    TAPE_ERR_MSG .stringz "ERROR: Tape drive returned: "
    TAPE_ERR_TABLE
        .fill TAPE_GETC_ERR_TABLE_00
        .fill TAPE_GETC_ERR_TABLE_01
        .fill TAPE_GETC_ERR_TABLE_10
        .fill TAPE_GETC_ERR_TABLE_11
    TAPE_GETC_ERR_TABLE_00 .stringz "Bad argument\n"    ; 0b00
    TAPE_GETC_ERR_TABLE_01 .stringz "Bad message id\n"  ; 0b01
    TAPE_GETC_ERR_TABLE_10 .stringz "Hit end of tape\n" ; 0b10
    TAPE_GETC_ERR_TABLE_11 .stringz "Unknown error\n"   ; 0b11. Currently never sent by hardware

; Inputs: Path to open (r0), r/w (r1)
; Output: new fd (r0)
TRAP_FOPEN
    ; save regs
    add r6, r6, -1
    str r1, r6, 0
    add r6, r6, -1
    str r2, r6, 0
    add r6, r6, -1
    str r3, r6, 0
    add r6, r6, -1
    str r4, r6, 0
    add r6, r6, -1
    str r5, r6, 0

    add r1, r1, 0
    brz RW_OK
    add r1, r1, -1
    brz RW_OK
    br RW_BOGUS

    RW_OK
    ; char *prefix = "/dev/st"
    lea r2, TAPE_DEV_PATH
    ; while (*path && *prefix) {
    PATH_PREFIX_LOOP
        ldr r3, r0, 0 ; *path
        brz BAD_PATH
        ldr r4, r2, 0 ; *prefix
        brz GOOD_PATH

        ; if (*path != *prefix) {
        ;     crash
        ; }
        not r4, r4
        add r4, r4, 1
        add r4, r3, r4 ; *path - *prefix
        brnp BAD_PATH

        ; path++;
        add r0, r0, 1
        ; prefix++;
        add r2, r2, 1
        br PATH_PREFIX_LOOP
    ; }

    GOOD_PATH
    ; int sum = 0;
    and r2, r2, 0
    TAPE_IDX_LOOP
        ldr r3, r0, 0 ; *path
        brz TAPE_IDX_LOOP_BREAK

        ; if (*path > '9') {
        ld r5, ASCII_NINE
        not r5, r5
        add r5, r5, 1
        add r5, r3, r5 ; *path - '9'
        brp BAD_PATH

        ; if (*path < '0') {
        ld r5, ASCII_ZERO
        not r5, r5
        add r5, r5, 1
        add r5, r3, r5 ; *path - '0'
        brn BAD_PATH

        ; sum = sum * 8 + sum * 2
        add r4, r2, r2 ; tmp = sum * 2
        add r4, r4, r4 ; tmp = sum * 4
        add r4, r4, r4 ; tmp = sum * 8
        add r2, r2, r2 ; sum * 2
        add r2, r4, r2 ; sum = sum * 8 + sum * 2

        ; sum += *path - '0'
        add r2, r2, r5 ; sum = sum + (*path - '0')
        add r0, r0, 1  ; path++
        br TAPE_IDX_LOOP
    TAPE_IDX_LOOP_BREAK

    ; if (sum < 0) {
    add r2, r2, 0
    brn BAD_PATH

    ; if (sum >= 64) {
    ldi r3, TRAP_FOPEN__TAPENUM_TABLE_LEN__ADDR
    not r3, r3
    add r3, r3, 1
    add r3, r3, r2 ; sum - 64
    brzp BAD_PATH

    ; tapenum_ent *ent = tapenum_table + sum
    ld r3, TRAP_FOPEN__TAPENUM_TABLE__ADDR
    add r3, r3, r2
    ldr r4, r3, 0 ; tapenum_table[sum]
    brzp DISK_IN_USE

    ; Find a free fd
    ; for (i = 0; i < FD_TABLE_LEN; i++) {
    and r4, r4, 0 ; i = 0
    FD_TABLE_SEARCH
        add r5, r4, r4 ; r5 <- 2*i
        add r5, r5, r5 ; r5 <- 4*i
        add r5, r5, r4 ; r5 <- 5*i
        add r5, r5, r4 ; r5 <- 6*i
        add r5, r5, r4 ; r5 <- 7*i
        ld r0, TRAP_FOPEN__FD_TABLE__ADDR
        add r5, r0, r5 ; fd_ent *ent = fd_table + i;

        ldr r0, r5, 0
        brn FOUND_FREE_FD
        add r4, r4, 1
        ldi r0, TRAP_FOPEN__FD_TABLE_LEN__ADDR
        not r0, r0
        add r0, r0, 1
        add r0, r0, r4 ; i - FD_TABLE_LEN
        brz FDS_EXHAUSTED
        br FD_TABLE_SEARCH

    FOUND_FREE_FD
    ; ent->state = rw;
    str r1, r5, 0
    ; ent->data = tape_idx;
    str r2, r5, 1
    ; ent->putc = &tape_putc
    ld r0, TRAP_FOPEN__TAPE_PUTC__ADDR
    str r0, r5, 2
    ; ent->getc = &tape_getc
    ld r0, TRAP_FOPEN__TAPE_GETC__ADDR
    str r0, r5, 3
    ; ent->trunc = &tape_trunc
    ld r0, TRAP_FOPEN__TAPE_TRUNC__ADDR
    str r0, r5, 4
    ; ent->rewind = &tape_rewind
    lea r0, TRAP_FOPEN__TAPE_REWIND__ADDR
    str r0, r5, 5
    ; ent->close = &tape_close
    lea r0, TRAP_FOPEN__TAPE_CLOSE__ADDR
    str r0, r5, 6

    ; *tapenum_ent = fd
    str r4, r3, 0
    ; return fd
    add r0, r4, 0

    ; Rewind, just in case LC3Tools has persisted some state unexpectedly
    frewind

    ; restore regs
    ldr r5, r6, 0
    add r6, r6, 1
    ldr r4, r6, 0
    add r6, r6, 1
    ldr r3, r6, 0
    add r6, r6, 1
    ldr r2, r6, 0
    add r6, r6, 1
    ldr r1, r6, 0
    add r6, r6, 1
    rti

    RW_BOGUS
    lea r0, RW_BOGUS_ERR
    puts
    halt

    BAD_PATH
    lea r0, BAD_PATH_ERR
    puts
    halt

    DISK_IN_USE
    lea r0, DISK_IN_USE_ERR
    puts
    halt

    FDS_EXHAUSTED
    lea r0, FDS_EXHAUSTED_ERR
    puts
    halt

    RW_BOGUS_ERR .stringz "ERROR: rw must be 0 or 1\n"
    DISK_IN_USE_ERR .stringz "ERROR: Disk in use\n"
    BAD_PATH_ERR .stringz "ERROR: Invalid path name\n"
    FDS_EXHAUSTED_ERR .stringz "ERROR: Out of file descriptors\n"
    TAPE_DEV_PATH .stringz "/dev/st"
    ASCII_ZERO .fill x30
    ASCII_NINE .fill x39
    TRAP_FOPEN__TAPENUM_TABLE_LEN__ADDR .fill TAPENUM_TABLE_LEN
    TRAP_FOPEN__TAPENUM_TABLE__ADDR .fill TAPENUM_TABLE
    TRAP_FOPEN__FD_TABLE_LEN__ADDR .fill FD_TABLE_LEN
    TRAP_FOPEN__FD_TABLE__ADDR .fill FD_TABLE
    TRAP_FOPEN__TAPE_PUTC__ADDR .fill TAPE_PUTC
    TRAP_FOPEN__TAPE_GETC__ADDR .fill TAPE_GETC
    TRAP_FOPEN__TAPE_TRUNC__ADDR .fill TAPE_TRUNC
    TRAP_FOPEN__TAPE_REWIND__ADDR .fill TAPE_REWIND
    TRAP_FOPEN__TAPE_CLOSE__ADDR .fill TAPE_CLOSE


; Inputs: c (R0), fd (R1)
TRAP_FPUTC
    ; save regs
    ; (Need to save pretty much everything here because who knows which
    ;  registers the driver uses)
    add r6, r6, -1
    str r0, r6, 0
    add r6, r6, -1
    str r1, r6, 0
    add r6, r6, -1
    str r2, r6, 0
    add r6, r6, -1
    str r3, r6, 0
    add r6, r6, -1
    str r4, r6, 0
    add r6, r6, -1
    str r5, r6, 0
    add r6, r6, -1
    str r7, r6, 0

    add r1, r1, 0
    brn FPUTC_BAD_FD
    ldi r2, TRAP_FPUTC__FD_TABLE_LEN__ADDR
    not r2, r2
    add r2, r2, 1
    add r2, r2, r1 ; fd - FD_TABLE_LEN
    brzp FPUTC_BAD_FD

    add r2, r1, r1 ; r2 <- 2*fd
    add r2, r2, r2 ; r2 <- 4*fd
    add r2, r2, r1 ; r2 <- 5*fd
    add r2, r2, r1 ; r2 <- 6*fd
    add r2, r2, r1 ; r2 <- 7*fd
    ld r3, TRAP_FPUTC__FD_TABLE__ADDR
    ; fd_ent *ent = fd_table + fd;
    add r2, r3, r2
    ldr r3, r2, 0 ; ent->status
    brn FPUTC_BAD_FD
    brz FPUTC_RDONLY

    ld r3, FPUTC_CHAR_MASK
    and r0, r0, r3 ; c = c & 0xff
    ldr r1, r2, 1 ; ent->arg
    ldr r3, r2, 2 ; ent->putc
    jsrr r3

    ; restore regs
    ldr r7, r6, 0
    add r6, r6, 1
    ldr r5, r6, 0
    add r6, r6, 1
    ldr r4, r6, 0
    add r6, r6, 1
    ldr r3, r6, 0
    add r6, r6, 1
    ldr r2, r6, 0
    add r6, r6, 1
    ldr r1, r6, 0
    add r6, r6, 1
    ldr r0, r6, 0
    add r6, r6, 1
    rti

    FPUTC_BAD_FD
    lea r0, FPUTC_BAD_FD_ERR
    puts
    halt

    FPUTC_RDONLY
    lea r0, FPUTC_RDONLY_ERR
    puts
    halt

    FPUTC_CHAR_MASK .fill xff
    FPUTC_BAD_FD_ERR .stringz "ERROR: fd is invalid\n"
    FPUTC_RDONLY_ERR .stringz "ERROR: cannot write to file opened for reading\n"
    TRAP_FPUTC__FD_TABLE__ADDR .fill FD_TABLE
    TRAP_FPUTC__FD_TABLE_LEN__ADDR .fill FD_TABLE_LEN

; Inputs: fd (R1)
; Outputs: c (R0)
TRAP_FGETC
    ; save regs
    ; (Need to save pretty much everything here because who knows which
    ;  registers the driver uses)
    add r6, r6, -1
    str r1, r6, 0
    add r6, r6, -1
    str r2, r6, 0
    add r6, r6, -1
    str r3, r6, 0
    add r6, r6, -1
    str r4, r6, 0
    add r6, r6, -1
    str r5, r6, 0
    add r6, r6, -1
    str r7, r6, 0

    add r1, r1, 0
    brn FGETC_BAD_FD
    ldi r2, TRAP_FGETC__FD_TABLE_LEN__ADDR
    not r2, r2
    add r2, r2, 1
    add r2, r2, r1 ; fd - FD_TABLE_LEN
    brzp FGETC_BAD_FD

    add r2, r1, r1 ; r2 <- 2*fd
    add r2, r2, r2 ; r2 <- 4*fd
    add r2, r2, r1 ; r2 <- 5*fd
    add r2, r2, r1 ; r2 <- 6*fd
    add r2, r2, r1 ; r2 <- 7*fd
    ld r3, TRAP_FGETC__FD_TABLE__ADDR
    ; fd_ent *ent = fd_table + fd;
    add r2, r3, r2
    ldr r3, r2, 0 ; ent->status
    brn FGETC_BAD_FD
    brp FGETC_WRONLY

    ldr r1, r2, 1 ; ent->arg
    ldr r3, r2, 3 ; ent->getc
    jsrr r3

    ; restore regs
    ldr r7, r6, 0
    add r6, r6, 1
    ldr r5, r6, 0
    add r6, r6, 1
    ldr r4, r6, 0
    add r6, r6, 1
    ldr r3, r6, 0
    add r6, r6, 1
    ldr r2, r6, 0
    add r6, r6, 1
    ldr r1, r6, 0
    add r6, r6, 1
    rti

    FGETC_BAD_FD
    lea r0, FGETC_BAD_FD_ERR
    puts
    halt

    FGETC_WRONLY
    lea r0, FGETC_WRONLY_ERR
    puts
    halt

    FGETC_BAD_FD_ERR .stringz "ERROR: fd is invalid\n"
    FGETC_WRONLY_ERR .stringz "ERROR: cannot read from file opened for writing\n"
    TRAP_FGETC__FD_TABLE__ADDR .fill FD_TABLE
    TRAP_FGETC__FD_TABLE_LEN__ADDR .fill FD_TABLE_LEN

; Inputs: fd (R1)
TRAP_FTRUNC
    ; save regs
    ; (Need to save pretty much everything here because who knows which
    ;  registers the driver uses)
    add r6, r6, -1
    str r0, r6, 0
    add r6, r6, -1
    str r1, r6, 0
    add r6, r6, -1
    str r2, r6, 0
    add r6, r6, -1
    str r3, r6, 0
    add r6, r6, -1
    str r4, r6, 0
    add r6, r6, -1
    str r5, r6, 0
    add r6, r6, -1
    str r7, r6, 0

    add r1, r1, 0
    brn FTRUNC_BAD_FD
    ldi r2, TRAP_FTRUNC__FD_TABLE_LEN__ADDR
    not r2, r2
    add r2, r2, 1
    add r2, r2, r1 ; fd - FD_TABLE_LEN
    brzp FTRUNC_BAD_FD

    add r2, r1, r1 ; r2 <- 2*fd
    add r2, r2, r2 ; r2 <- 4*fd
    add r2, r2, r1 ; r2 <- 5*fd
    add r2, r2, r1 ; r2 <- 6*fd
    add r2, r2, r1 ; r2 <- 7*fd
    ld r3, TRAP_FTRUNC__FD_TABLE__ADDR
    ; fd_ent *ent = fd_table + fd;
    add r2, r3, r2
    ldr r3, r2, 0 ; ent->status
    brn FTRUNC_BAD_FD
    brz FTRUNC_RDONLY

    ldr r1, r2, 1 ; ent->arg
    ldr r3, r2, 4 ; ent->trunc
    jsrr r3

    ; restore regs
    ldr r7, r6, 0
    add r6, r6, 1
    ldr r5, r6, 0
    add r6, r6, 1
    ldr r4, r6, 0
    add r6, r6, 1
    ldr r3, r6, 0
    add r6, r6, 1
    ldr r2, r6, 0
    add r6, r6, 1
    ldr r1, r6, 0
    add r6, r6, 1
    ldr r0, r6, 0
    add r6, r6, 1
    rti

    FTRUNC_BAD_FD
    lea r0, FTRUNC_BAD_FD_ERR
    puts
    halt

    FTRUNC_RDONLY
    lea r0, FTRUNC_RDONLY_ERR
    puts
    halt

    FTRUNC_BAD_FD_ERR .stringz "ERROR: fd is invalid\n"
    FTRUNC_RDONLY_ERR .stringz "ERROR: cannot read from file opened for writing\n"
    TRAP_FTRUNC__FD_TABLE__ADDR .fill FD_TABLE
    TRAP_FTRUNC__FD_TABLE_LEN__ADDR .fill FD_TABLE_LEN

; Inputs: fd (R1)
TRAP_FREWIND
    ; save regs
    ; (Need to save pretty much everything here because who knows which
    ;  registers the driver uses)
    add r6, r6, -1
    str r0, r6, 0
    add r6, r6, -1
    str r1, r6, 0
    add r6, r6, -1
    str r2, r6, 0
    add r6, r6, -1
    str r3, r6, 0
    add r6, r6, -1
    str r4, r6, 0
    add r6, r6, -1
    str r5, r6, 0
    add r6, r6, -1
    str r7, r6, 0

    add r1, r1, 0
    brn FREWIND_BAD_FD
    ld r2, FD_TABLE_LEN
    not r2, r2
    add r2, r2, 1
    add r2, r2, r1 ; fd - FD_TABLE_LEN
    brzp FREWIND_BAD_FD

    add r2, r1, r1 ; r2 <- 2*fd
    add r2, r2, r2 ; r2 <- 4*fd
    add r2, r2, r1 ; r2 <- 5*fd
    add r2, r2, r1 ; r2 <- 6*fd
    add r2, r2, r1 ; r2 <- 7*fd
    lea r3, FD_TABLE
    ; fd_ent *ent = fd_table + fd;
    add r2, r3, r2
    ldr r3, r2, 0 ; ent->status
    brn FREWIND_BAD_FD

    ldr r1, r2, 1 ; ent->arg
    ldr r3, r2, 5 ; ent->rewind
    jsrr r3

    ; restore regs
    ldr r7, r6, 0
    add r6, r6, 1
    ldr r5, r6, 0
    add r6, r6, 1
    ldr r4, r6, 0
    add r6, r6, 1
    ldr r3, r6, 0
    add r6, r6, 1
    ldr r2, r6, 0
    add r6, r6, 1
    ldr r1, r6, 0
    add r6, r6, 1
    ldr r0, r6, 0
    add r6, r6, 1
    rti

    FREWIND_BAD_FD
    lea r0, FREWIND_BAD_FD_ERR
    puts
    halt

    FREWIND_BAD_FD_ERR .stringz "ERROR: fd is invalid\n"

; Inputs: fd (R1)
TRAP_FCLOSE
    ; save regs
    ; (Need to save pretty much everything here because who knows which
    ;  registers the driver uses)
    add r6, r6, -1
    str r0, r6, 0
    add r6, r6, -1
    str r1, r6, 0
    add r6, r6, -1
    str r2, r6, 0
    add r6, r6, -1
    str r3, r6, 0
    add r6, r6, -1
    str r4, r6, 0
    add r6, r6, -1
    str r5, r6, 0
    add r6, r6, -1
    str r7, r6, 0

    add r1, r1, 0
    brn FCLOSE_BAD_FD
    ld r2, FD_TABLE_LEN
    not r2, r2
    add r2, r2, 1
    add r2, r2, r1 ; fd - FD_TABLE_LEN
    brzp FCLOSE_BAD_FD

    add r2, r1, r1 ; r2 <- 2*fd
    add r2, r2, r2 ; r2 <- 4*fd
    add r2, r2, r1 ; r2 <- 5*fd
    add r2, r2, r1 ; r2 <- 6*fd
    add r2, r2, r1 ; r2 <- 7*fd
    lea r3, FD_TABLE
    ; fd_ent *ent = fd_table + fd;
    add r2, r3, r2
    ldr r3, r2, 0 ; ent->status
    brn FCLOSE_BAD_FD

    ldr r1, r2, 1 ; ent->arg
    ldr r3, r2, 6 ; ent->close

    ; save ent (it's annoying to calculate)
    add r6, r6, -1
    str r2, r6, 0
    ; In the case of a tape, this will free up the location in the tape table
    jsrr r3
    ; restore ent
    ldr r2, r6, 0
    add r6, r6, 1

    ; Now free up this fd
    and r0, r0, 0
    add r0, r0, -1
    ; ent->state = -1 (free)
    str r0, r2, 0

    ; restore regs
    ldr r7, r6, 0
    add r6, r6, 1
    ldr r5, r6, 0
    add r6, r6, 1
    ldr r4, r6, 0
    add r6, r6, 1
    ldr r3, r6, 0
    add r6, r6, 1
    ldr r2, r6, 0
    add r6, r6, 1
    ldr r1, r6, 0
    add r6, r6, 1
    ldr r0, r6, 0
    add r6, r6, 1
    rti

    FCLOSE_BAD_FD
    lea r0, FCLOSE_BAD_FD_ERR
    puts
    halt

    FCLOSE_BAD_FD_ERR .stringz "ERROR: fd is invalid\n"

; #define TAPENUM_TABLE_LEN 64
; #define FD_TABLE_LEN 16
TAPENUM_TABLE_LEN .fill 64
FD_TABLE_LEN .fill 16
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
FD_TABLE .blkw 112 ; 7*16
; typedef int tapenum_ent;
; tapenum_ent tapenum_table[TAPENUM_TABLE_LEN];
TAPENUM_TABLE .blkw 64 ; 2^6
.end

.orig x30
.fill TRAP_FOPEN
.fill TRAP_FPUTC
.fill TRAP_FGETC
.fill TRAP_FTRUNC
.fill TRAP_FREWIND
.fill TRAP_FCLOSE
.end
