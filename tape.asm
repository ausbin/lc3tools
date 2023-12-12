.orig x3000
POLL1 ldi r0, TSSR_ADDR
      brzp POLL1
      ld r0, GETC0_MSG
      sti r0, TSDR_ADDR

POLL2 ldi r0, TRSR_ADDR
      brzp POLL2
      ldi r0, TRDR_ADDR
      ld r1, OPCODE_MASK
      and r1, r0, r1

      jsr GET_OPCODE
      ; r2 now contains the opcode

      ld r1, DATA_MASK
      and r1, r0, r1
      ; r1 now contains data

      ; switch (opcode) {
      lea r3, JMP_OPCODE
      add r3, r3, r2
      ldr r3, r3, 0
      jmp r3
      JMP_OPCODE
      .fill HANDLE_ERR
      .fill HANDLE_DATA
      .fill HANDLE_ACK
      .fill HANDLE_WTF

      HANDLE_ERR
          ; Handle EOF specially
          add r0, r1, -2 
          brz HANDLE_EOF

          lea r0, ERR_MSG
          puts
          ld r0, ASCII_ZERO
          add r0, r0, r1
          putc
          ld r0, ASCII_LF
          putc
          br BAIL

      HANDLE_DATA
          lea r0, DATA_MSG
          puts
          add r0, r1, 0
          putc
          ld r0, ASCII_LF
          putc
          ;br POLL1
          br DO_PUTC

      HANDLE_ACK
          lea r0, ACK_MSG
          puts
          br BAIL

      HANDLE_WTF
          lea r0, WTF_MSG
          puts
          br BAIL

      HANDLE_EOF
          lea r0, EOF_MSG
          puts
          br BAIL

DO_PUTC ldi r0, TSSR_ADDR
        brzp DO_PUTC
        ld r0, PUTC1_MSG
        ; OR PUTC1_MSG with the byte read from the last message
        not r0, r0
        not r1, r1
        and r0, r0, r1
        not r0, r0
        sti r0, TSDR_ADDR

POLL3 ldi r0, TRSR_ADDR
      brzp POLL3
      ldi r0, TRDR_ADDR
      ld r1, OPCODE_MASK
      and r1, r0, r1
      jsr GET_OPCODE
      ; r2 now contains the opcode
      ld r1, DATA_MASK
      and r1, r0, r1
      ; r1 now contains data

      ; switch (opcode) {
      lea r3, JMP_PUTC_OPCODE
      add r3, r3, r2
      ldr r3, r3, 0
      jmp r3
      JMP_PUTC_OPCODE
      .fill HANDLE_PUTC_ERR
      .fill HANDLE_PUTC_DATA
      .fill HANDLE_PUTC_ACK
      .fill HANDLE_PUTC_WTF

      HANDLE_PUTC_ERR
          lea r0, PUTC_ERR_MSG
          puts
          ld r0, ASCII_ZERO
          add r0, r0, r1
          putc
          ld r0, ASCII_LF
          putc
          br BAIL

      HANDLE_PUTC_DATA
          lea r0, PUTC_DATA_MSG
          puts
          br BAIL

      HANDLE_PUTC_ACK
          ;lea r0, ACK_MSG
          ;puts
          br POLL1

      HANDLE_PUTC_WTF
          lea r0, PUTC_WTF_MSG
          puts
          br BAIL

BAIL halt

; Inputs: message (r1, clobbered)
; Outputs: opcode (r2)
GET_OPCODE
      ; trick to right shift
      and r2, r2, 0
      add r1, r1, 0 ; update cc for response
      brzp MSB_CLEAR
      add r2, r2, 2 ; r2 | (0x1 << 1)
      MSB_CLEAR add r1, r1, r1 ; r1 = r1 << 1
      brzp NMSB_CLEAR
      add r2, r2, 1
      NMSB_CLEAR
      ret

EOF_MSG .stringz "Hit eof\n"
WTF_MSG .stringz "getc: Bogus opcode\n"
PUTC_WTF_MSG .stringz "putc: Bogus opcode\n"
DATA_MSG .stringz "Got data: "
PUTC_DATA_MSG .stringz "Got data, wtf?\n"
ACK_MSG .stringz "Got ack, wtf?\n"
ERR_MSG .stringz "getc error: "
PUTC_ERR_MSG .stringz "putc error: "
ASCII_ZERO .fill x30
ASCII_LF .fill x0a
OPCODE_MASK .fill xC000
DATA_MASK .fill x00FF
GETC0_MSG .fill x4000
PUTC1_MSG .fill x8100
TRSR_ADDR .fill xFE08
TRDR_ADDR .fill xFE0A
TSSR_ADDR .fill xFE0C
TSDR_ADDR .fill xFE0E
.end
