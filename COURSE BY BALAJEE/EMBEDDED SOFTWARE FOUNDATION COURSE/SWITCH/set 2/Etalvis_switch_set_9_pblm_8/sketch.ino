void setup() {
  volatile char *ddr_a = (char*)0x21;  // DDRA
  volatile char *ddr_b = (char*)0x24;  // DDRB

  *ddr_a = 0xFF; // PORTA output
  *ddr_b = 0x00; // PORTB input
}

void loop() {
  volatile char *port_a = (char*)0x22; // PORTA
  volatile char *pin_b  = (char*)0x23; // PINB

  static char sw1_pressed = 0;
  static char sw2_pressed = 0;

  char input = *pin_b;

  if (input & (1 << 1)) sw1_pressed = 1;  // PB1
  if (input & (1 << 7)) sw2_pressed = 1;  // PB7

  if (sw1_pressed && sw2_pressed) {
    *port_a = 0x20;  // Light ON (PA5)
    sw1_pressed = 0; // Reset flags
    sw2_pressed = 0;
    delay_();        
    *port_a = 0x00;  // keep LED off until both pressed
  }
}

void delay_() {
  for (volatile long i = 0; i < 300000; i++);
}
