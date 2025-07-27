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
  unsigned char w[] = {0x7E,0x7E,0x7E,0x7E,0x67,0x5B,0x3D,0x7E};
  unsigned char e[] = {0xC1,0xAD,0x61,0x7F,0x7F,0x7F,0xBF,0xC1};
  unsigned char l[] = {0xEF,0xEF,0xEF,0xEF,0xEF,0xEF,0xEF,0xEF};
  unsigned char c[] = {0xCD,0xBF,0x7F,0x7F,0x7F,0x7F,0xBF,0xC0};
  unsigned char o[] = {0x00,0x7E,0x7E,0x7E,0x7E,0x7E,0x7E,0x00};
  unsigned char m[] = {0xDB,0xA5,0x7E,0x7E,0x7E,0x7E,0x7E,0x7E,};
  

  // Display each character one by one
  display_char(w);
  delay_();

  display_char(e);
  delay_();

  display_char(l);
  delay_();

  display_char(c);
  delay_();

  display_char(o);
  delay_();
  display_char(m);
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
      *porta = 0x00;
      *portb = 0xFF;
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
