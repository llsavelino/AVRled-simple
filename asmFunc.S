#include <avr/io.h>

.data                     
  var1: .byte 0xAA       ; Declarando var1

.text                    ; Apartir daqui é feito a execução do processador 
.global __asmFunc    
__asmFunc:
  sbi (PORTD -0x20), PD7; Set Bit
  rcall delay           ;       
  cbi (PORTD -0x20), PD7; Clear Bit
  rcall delay           ; Chama função delay 
  
  rjmp __asmFunc        ; Chamada recursiva
delay:
    
    lds r18, var1        ; r18 recebe Variavel de um byte declarada na { section data }
    mov r24, r18         ; Movendo r18 para r24
    ldi r19, 0xBB        ; r19 recebe 204 
    mov r25, r19         ; Movendo r19 para r25
    add r20, r18         ; Soma r20 + r18 e guarda em r20
    mov r26, r20         ; Movendo r20 para r26
    eor r18, r18         ; Aplica a lógica xor para limpar o registrador r18
    sub r19, r19         ; Subtrai r19 - r19 e guarda em r19
    clr r19              ; Clear Register limpeza efiecaz
    eor r20, r20         ; Aplica a lógica xor para limpar o registrador r20
  
  delay_loop:
    
    dec r24              ; --r24
    brne  delay_loop     ; Se r24 não for zero, continua no loop
    dec r25              ; -- r25
    brne delay_loop      ; Se r25 não for zero, continua no loop
    dec r26              ; -- r26
    brne delay_loop      ; Se r26 não for zero, continua no loop

  ret                   ; Retorno
