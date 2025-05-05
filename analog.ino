#define analogPim A0
unsigned  pwm0{0xA1};
bool     state{0x00};

ISR(TIMER2_OVF_vect) {

  if (state) 
  {
    TCNT2 = pwm0;
    PORTB |= (1 << PB4);
    state = false;
  }
  else 
  {
    TCNT2 = 0xff -pwm0;
    PORTB &= ~(1 << PB4);
    state = true;
  }

}


void setup() {
  
  DDRB |= (1 << PB4); PORTB &= ~(1 << PB4);

  TCCR2A = 0x00;

  // TCCR2B = 0x00;
  // TCCR2B = 0x01;
  // TCCR2B = 0x02;
  // TCCR2B = 0x03;
  TCCR2B = 0x04;
  // TCCR2B = 0x05;
  // TCCR2B = 0x06;
  // TCCR2B = 0x07;

  TIMSK2 = 0x01;

}

void loop() {
  
  // pwm0 = map(analogRead(analogPim), 0x00, 0x3FF, 0x00, 0xff);

}
