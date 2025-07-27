void setup() {
  volatile char *ddr_a = (char*)0x21; // DDRA – segment data lines
  volatile char *ddr_b = (char*)0x24; // DDRB – digit select lines
  *ddr_a = 0xFF; // PORTA as output
  *ddr_b = 0x0F; // Lower 4 bits of PORTB as output
}

void loop() {
  char num[] = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F  // 9
  };

  volatile char *port_a = (char*)0x22; // PORTA
  volatile char *port_b = (char*)0x25; // PORTB

  for (int count = 0; count <= 9999; count++) {
    int value = count;

    // Extract digits: X.YYY
    int d1 = (value / 1000);               // Thousands digit
    int d2 = (value / 100) % 10;           // Hundreds digit (DP here)
    int d3 = (value / 10) % 10;            // Tens
    int d4 = value % 10;                   // Ones

    // Show this number 100 times for 0.1 sec total
    for (int i = 0; i < 100; i++) {
      // Digit 1: d1
      *port_b = 0b1110;
      *port_a = num[d1];
      delay_();
      *port_a = 0x00;
      *port_b = 0x0F;

      // Digit 2: d2 (with decimal point)
      *port_b = 0b1101;
      *port_a = num[d2] | 0x80; // DP ON
      delay_();
      *port_a = 0x00;
      *port_b = 0x0F;

      // Digit 3: d3
      *port_b = 0b1011;
      *port_a = num[d3];
      delay_();
      *port_a = 0x00;
      *port_b = 0x0F;

      // Digit 4: d4
      *port_b = 0b0111;
      *port_a = num[d4];
      delay_();
      *port_a = 0x00;
      *port_b = 0x0F;
    }
  }
}

void delay_() {
  for (volatile long i = 0; i < 1000; i++);
}
