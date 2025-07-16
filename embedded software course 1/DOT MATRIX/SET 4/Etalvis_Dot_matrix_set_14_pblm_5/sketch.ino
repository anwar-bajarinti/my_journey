// max7219.ino

#define DDRB  (*(volatile byte*)0x24)
#define PORTB (*(volatile byte*)0x25)

#define LOAD 0
#define CLK  1
#define DIN  2

void max7219send(unsigned char addr, unsigned char data) {
  PORTB &= ~(1 << LOAD);

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
    if (data & (1 << i))
      PORTB |= (1 << DIN);
    else
      PORTB &= ~(1 << DIN);
    PORTB |= (1 << CLK);
  }

  PORTB |= (1 << LOAD);
}

void max7219setup() {
  DDRB |= (1 << LOAD) | (1 << CLK) | (1 << DIN);  // Set as output

  max7219send(0x0F, 0x00);  // Display test off
  max7219send(0x0C, 0x01);  // Shutdown off
  max7219send(0x0B, 0x07);  // Scan limit = 8 digits
  max7219send(0x0A, 0x08);  // Brightness
  max7219send(0x09, 0x00);  // No decode

  for (int i = 1; i <= 8; i++)
    max7219send(i, 0x00);  // Clear all digits
}

void setup() {
  max7219setup();
  max7219send(1, 0xFF);  // Turn ON all segments on digit 1
}

void loop() {
  // Optional scroll, animate, or update here
}
