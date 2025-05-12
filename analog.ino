#include <Arduino.h>
// Macros para manipulação de bits:
// - LOWST: Limpa o bit especificado no registrador - HIGST: Seta o bit especificado no registrador - OUTIN: Configura o pino como saída (equivalente a setar o bit no DDR)
#define LOWST(pim, bim, reg) (reg &= ~(bim << pim))
#define INOUT(pim, bim, reg) (reg &= ~(bim << pim))
#define HIGST(pim, bim, reg) (reg |=  (bim << pim))
#define OUTIN(pim, bim, reg) (reg |=  (bim << pim))
#define SWAPS(pim, bim, reg) (reg ^=  (bim << pim))
#define CLEARL(lef, bim, reg) (reg >>= (bim << lef))
#define CLEARR(rgh, int, reg) (reg <<= (int >> rgh))
#define ERRO(x, y, z) do { digitalWrite(x, y); pinMode(x, z); goto label; } while(0x00) 
extern              "C"  { void __asmFunc(void); };
static unsigned char pwm0 = 0xA1;  // Valor inicial do PWM (161 em decimal)
static bool state = 0x00;          // Estado atual do PWM (0 = baixo, 1 = alto)

// Rotina de Interrupção do Timer2 (Overflow)
ISR(  TIMER2_OVF_vect  )
{
  switch (state) 
  {
    #if defined(HIGST)
    case true: state = (false >> 0); 
      TCNT2 = pwm0; // Reinicia o timer com valor pwm0
      HIGST(PB4, 0x01, PORTB); /* Seta o pino PB4 (HIGH) */ 
      break;
    #endif
    #if defined(LOWST)
    case false: state = (true >> 0);
      TCNT2 = 0xFF -pwm0; // Reinicia o timer com valor complementar
      LOWST(PB4, 0x01, PORTB); /* Limpa o pino PB4 (LOW) */  
      break; 
    #endif
    #if !defined(LOWST) || defined(HIGST)
    default: ERRO(12, LOW, INPUT_PULLUP); break;
    #endif
  } while (0x00) {  __asmFunc();  }
}
#ifndef brain_Main
void setup(void) 
{
  #if defined(OUTIN) && defined(LOWST)
  OUTIN(PB4, 0x01, DDRB); LOWST(PB4, 0x01, PORTB);
  #else
    #pragma message "Erro: Macro não definida.\n"
  #endif
  // Configura o Timer2:
  TCCR2A = 0x00;  // Modo normal (sem comparação, sem PWM hardware)
  // Configura o prescaler (divisor de clock):
  // Opções comentadas (apenas uma deve estar ativa):
  // TCCR2B = 0x00; // Timer parado (no clock)
  // TCCR2B = 0x01; // Prescaler 1 (clock direto)
  // TCCR2B = 0x02; // Prescaler 8
  // TCCR2B = 0x03; // Prescaler 32
  TCCR2B = 0x04;   // Prescaler 64 (selecionado)
  // TCCR2B = 0x05; // Prescaler 128
  // TCCR2B = 0x06; // Prescaler 256
  // TCCR2B = 0x07; // Prescaler 1024
  // Habilita interrupção por overflow do Timer2
  TIMSK2 = 0x01;
}
#endif
/* Loop principal (vazio, toda a lógica é feita na interrupção) */ void loop(void) { label: }
