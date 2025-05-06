#include <avr/io.h>

.data                     
  var1: .byte 0xAA       ; Variável tipo byte
  var2: .byte 0xBB       ; Variável tipo byte

.text                    ; A partir daqui é feita a execução do processador 
.global __asmFunc

start:
  ; Configura PD7 como saída
  LDI r18, (1 << PD7)     ; Carrega o bit mask para PD7
  OUT (DDRD - 0x20), r18  ; Define PD7 como saída (DDRD = PORTD - 0x20)
  
  ; Inicializa PD7 desligado (LOW)
  CBI (PORTD - 0x20), PD7 ; Clear Bit I/O - Desliga PD7
  RET

__asmFunc:
  ; Verifica se PD7 está configurado como saída
  IN r16, (DDRD - 0x20)   ; Lê o registrador DDRD
  SBRS r16, PD7           ; Skip if Bit in Register is Set (PD7)
  RCALL start             ; Se PD7 não está como saída, chama start para configurar
  
  ; Agora podemos manipular o pino com segurança
  SBI (PORTD - 0x20), PD7 ; Set Bit I/O - Liga PD7
  RCALL delay             ; Chama delay
  CBI (PORTD - 0x20), PD7 ; Clear Bit I/O - Desliga PD7
  RCALL delay             ; Chama delay
  RET

delay:
  LDS r18, var1           ; r18 recebe variável de um byte declarada na section data
  MOV r24, r18            ; Movendo r18 para r24
  LDS r19, var2           ; r19 recebe 0xBB 
  MOV r25, r19            ; Movendo r19 para r25
  ADD r20, r18            ; Soma r20 + r18 e guarda em r20
  MOV r26, r20            ; Movendo r20 para r26
  SUB r19, r19            ; Subtrai r19 - r19 e guarda em r19
  CLR r18                 ; Clear Register - limpeza eficaz
  CLR r20                 ; Limpar o registrador r20
  
  delay_loop:
    DEC r24               ; --r24
    BRNE delay_loop       ; Se r24 não for zero, continua no loop
    DEC r25               ; --r25
    BRNE delay_loop       ; Se r25 não for zero, continua no loop
    DEC r26               ; --r26
    BRNE delay_loop       ; Se r26 não for zero, continua no loop
    RET                   ; Retorno
