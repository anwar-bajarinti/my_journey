// Embedded Systems programming - GPIO
// Dot Matrix Control - Display Characters A to E one by one
// PORTA → Rows (Anodes), PORTB → Columns (Cathodes)

void setup() {
  volatile char *ddra = (char*)0x21;
  volatile char *ddrb = (char*)0x24;
  *ddra = 0xFF;  // Set PORTA (rows) as output
  *ddrb = 0xFF;  // Set PORTB (cols) as output
}

void loop() {
  // Each character pattern (A to E)
  unsigned char a[] = {0xC3,0xFD,0xFD,0xE3,0xDD,0xDD,0xE2,0xFF};
  unsigned char b[] = {0x7F,0x67,0x5B,0x3B,0x7B,0x3B,0xB7,0xFF};
  unsigned char c[] = {0xCD, 0xBF, 0x7F, 0x7F, 0x7F, 0x7F, 0xBF, 0xC0};
  unsigned char d[] = {0xFD,0xFD,0x8D,0x77,0x7B,0x72,0x7B,0x87};
  unsigned char e[] = {0xC1,0xAD,0x61,0x7F,0x7F,0x7F,0xBF,0xC1};

  // Display each character one by one
  display_char(a);
  delay_();

  display_char(b);
  delay_();

  display_char(c);
  delay_();

  display_char(d);
  delay_();

  display_char(e);
  delay_();
}

// Display a single 8×8 character pattern
void display_char(unsigned char pattern[]) {
  volatile char *porta = (char*)0x22;
  volatile char *portb = (char*)0x25;

  for (int repeat = 0; repeat < 200; repeat++) { // Refresh the full char multiple times
    for (volatile char row = 0; row < 8; row++) {
      *porta = 0x00;
      *portb = 0xFF;

      *porta = (1 << row);        // Enable one row (anode)
      *portb = pattern[row];      // Send column data (cathode pattern)

      for (volatile int i = 0; i < 1000; i++);  // Short row delay
    }
  }
}

// Delay between characters
void delay_() {
  volatile char dummy = 0;
  for (volatile long i = 0; i < 1000000; i++) {
    dummy++;
  }
}
