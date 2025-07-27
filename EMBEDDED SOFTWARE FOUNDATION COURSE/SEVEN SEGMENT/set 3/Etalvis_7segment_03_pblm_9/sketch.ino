void setup() {
  volatile char *ddr_a = (char*)0x21; // DDRA for segments
  volatile char *ddr_b = (char*)0x24; // DDRB for digit select
  *ddr_a = 0xFF;  // PORTA as output
  *ddr_b = 0x0F;  // Only lower 4 bits of PORTB as output
}

void loop() {
  char num[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

  volatile char *port_a = (char*)0x22; // PORTA
  volatile char *port_b = (char*)0x25; // PORTB

  for (volatile char i = 0; i < 10; i++) {
    for (volatile char j = 0; j < 10; j++) {
      for (volatile char k = 0; k < 10; k++) {
        for (volatile char l = 0; l < 10; l++) {
          for (volatile long repeat = 0; repeat < 100; repeat++) {

            // Thousands
            *port_b = 0b1110;  // PB0 LOW
            *port_a = num[i];
            delay_();
            *port_a = 0x00;
            *port_b = 0x0F;

            // Hundreds
            *port_b = 0b1101;  // PB1 LOW
            *port_a = num[j];
            delay_();
            *port_a = 0x00;
            *port_b = 0x0F;

            // Tens
            *port_b = 0b1011;  // PB2 LOW
            *port_a = num[k];
            delay_();
            *port_a = 0x00;
            *port_b = 0x0F;

            // Ones
            *port_b = 0b0111;  // PB3 LOW
            *port_a = num[l];
            delay_();
            *port_a = 0x00;
            *port_b = 0x0F;
          }
        }
      }
    }
  }
}

void delay_(void) {
  for (volatile long i = 0; i < 1000; i++);  // Delay
}
