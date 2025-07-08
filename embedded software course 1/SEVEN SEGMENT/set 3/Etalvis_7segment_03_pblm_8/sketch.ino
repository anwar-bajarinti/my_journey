void setup() {
  volatile char *ddr_a = (char*)0x21; // DDRA for segments
  volatile char *ddr_b = (char*)0x24; // DDRB for digit select
  *ddr_a = 0xFF;  // PORTA as output
  *ddr_b = 0x0F;  // Only lower 4 bits of PORTB as output
}

void loop() {
  char num[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F}; // 0–9

  volatile char *port_a = (char*)0x22; // PORTA
  volatile char *port_b = (char*)0x25; // PORTB

  for (volatile long i = 0; i < 200; i++) {
    // Digit 4 (thousands) = 2
    *port_b = 0b1110;  // PB0 LOW (digit 1 ON)
    *port_a = num[2];
    delay_();
    *port_a = 0x00;
    *port_b = 0x0F;

    // Digit 3 (hundreds) = 0
    *port_b = 0b1101;  // PB1 LOW (digit 2 ON)
    *port_a = num[0];
    delay_();
    *port_a = 0x00;
    *port_b = 0x0F;

    // Digit 2 (tens) = 2
    *port_b = 0b1011;  // PB2 LOW (digit 3 ON)
    *port_a = num[2];
    delay_();
    *port_a = 0x00;
    *port_b = 0x0F;

    // Digit 1 (ones) = 5
    *port_b = 0b0111;  // PB3 LOW (digit 4 ON)
    *port_a = num[5];
    delay_();
    *port_a = 0x00;
    *port_b = 0x0F;
  }
}

void delay_(void) {
  for (volatile long i = 0; i < 2000; i++);  // Short multiplexing delay
}
