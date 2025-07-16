#define DDRB  (*(volatile byte*)0x24)
#define PORTB (*(volatile byte*)0x25)

#define LOAD 0
#define CLK  1
#define DIN  2

void max7219send4(unsigned char addr, unsigned char d4, unsigned char d3, unsigned char d2, unsigned char d1) {
  PORTB &= ~(1 << LOAD);

  unsigned char data[4] = {d4, d3, d2, d1};
  for (int chip = 0; chip < 4; chip++) {
    for (int i = 7; i >= 0; i--) {
      PORTB &= ~(1 << CLK);
      if (addr & (1 << i))
        PORTB |= (1 << DIN);
      else
        PORTB &= ~(1 << DIN);
      PORTB |= (1 << CLK);
    }

    for (int i = 7; i >= 0; i--) {
      PORTB &= ~(1 << CLK);
      if (data[chip] & (1 << i))
        PORTB |= (1 << DIN);
      else
        PORTB &= ~(1 << DIN);
      PORTB |= (1 << CLK);
    }
  }

  PORTB |= (1 << LOAD);
}

void max7219setup4() {
  DDRB |= (1 << LOAD) | (1 << CLK) | (1 << DIN);

  for (int i = 0; i < 4; i++) {
    max7219send4(0x0F, 0, 0, 0, 0);  // Test off
    max7219send4(0x0C, 1, 1, 1, 1);  // Shutdown off
    max7219send4(0x0B, 7, 7, 7, 7);  // Scan all digits
    max7219send4(0x0A, 8, 8, 8, 8);  // Medium brightness
    max7219send4(0x09, 0, 0, 0, 0);  // No decode mode
  }

  for (int i = 1; i <= 8; i++) {
    max7219send4(i, 0, 0, 0, 0);  // Clear all
  }
}

void setup() {
  max7219setup4();

  // Example: row 1 has 0xFF on each matrix
  max7219send4(1, 0x01, 0x00, 0x00, 0x00);  // Only MAX4 ON
  delay(500);
 
}

void loop() {
  // scrolling animation goes here
}
