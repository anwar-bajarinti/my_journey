#define PORTB_REG (*(volatile char*)0x25)
#define DDRB_REG  (*(volatile char*)0x24)

#define DIN_BIT 2  // Arduino Mega Pin 51
#define CLK_BIT 1  // Arduino Mega Pin 52
#define CS_BIT  0  // Arduino Mega Pin 53

// Delay (software-based)
void delay_ms(unsigned int ms) {
  for (unsigned int i = 0; i < ms; i++)
    for (volatile int j = 0; j < 1000; j++);
}

// Reverse bits (for correct orientation)
unsigned char reverse_bits(unsigned char b) {
  b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
  b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
  b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
  return b;
}

// Send a row to all 4 displays
void max7219_send_row4(unsigned char row, unsigned char d1, unsigned char d2,
                       unsigned char d3, unsigned char d4) {
  unsigned char data[4] = {d1, d2, d3, d4};
  PORTB_REG &= ~(1 << CS_BIT);

  for (char m = 3; m >= 0; m--) {
    unsigned int packet = (row << 8) | data[m];
    for (char i = 0; i < 16; i++) {
      if (packet & 0x8000)
        PORTB_REG |= (1 << DIN_BIT);
      else
        PORTB_REG &= ~(1 << DIN_BIT);

      PORTB_REG &= ~(1 << CLK_BIT);
      for (volatile int d = 0; d < 10; d++);
      PORTB_REG |= (1 << CLK_BIT);
      packet <<= 1;
    }
  }

  PORTB_REG |= (1 << CS_BIT);
}

// MAX7219 Initialization
void max7219_init(void) {
  DDRB_REG = 0xFF;
  PORTB_REG = (1 << CS_BIT);

  max7219_send_row4(0x0C, 0x01, 0x01, 0x01, 0x01); // Normal mode
  max7219_send_row4(0x09, 0x00, 0x00, 0x00, 0x00); // No decode
  max7219_send_row4(0x0A, 0x08, 0x08, 0x08, 0x08); // Intensity
  max7219_send_row4(0x0B, 0x07, 0x07, 0x07, 0x07); // Scan limit = 8 rows
  max7219_send_row4(0x0F, 0x00, 0x00, 0x00, 0x00); // Test mode off

  for (unsigned char row = 1; row <= 8; row++)
    max7219_send_row4(row, 0x00, 0x00, 0x00, 0x00); // Clear
}

// Font for "WELCOME"
const unsigned char font_W[8] = {
  0b10000010, 0b10000010, 0b10000010, 0b10010010,
  0b10010010, 0b10010010, 0b01101100, 0b00000000
};
const unsigned char font_E[8] = {
  0b01111110, 0b01000000, 0b01000000, 0b01111100,
  0b01000000, 0b01000000, 0b01111110, 0b00000000
};
const unsigned char font_L[8] = {
  0b01000000, 0b01000000, 0b01000000, 0b01000000,
  0b01000000, 0b01000000, 0b01111110, 0b00000000
};
const unsigned char font_C[8] = {
  0b00111100, 0b01000010, 0b01000000, 0b01000000,
  0b01000000, 0b01000010, 0b00111100, 0b00000000
};
const unsigned char font_O[8] = {
  0b00111100, 0b01000010, 0b01000010, 0b01000010,
  0b01000010, 0b01000010, 0b00111100, 0b00000000
};
const unsigned char font_M[8] = {
  0b10000001, 0b11000011, 0b10100101, 0b10011001,
  0b10000001, 0b10000001, 0b10000001, 0b00000000
};

// Font sequence
const unsigned char* message[] = {
  font_W, font_E, font_L, font_C, font_O, font_M, font_E
};

#define LETTER_COUNT (sizeof(message) / sizeof(message[0]))

// Arduino setup()
void setup() {
  max7219_init();
}

// Arduino loop()
void loop() {
  for (unsigned int offset = 0; offset < LETTER_COUNT + 4; offset++) {
    for (unsigned char row = 1; row <= 8; row++) {
      unsigned char display[4] = {0};

      for (unsigned char d = 0; d < 4; d++) {
        int index = offset - d;
        if (index >= 0 && index < LETTER_COUNT) {
          display[d] = reverse_bits(message[index][row - 1]);
        }
      }

      max7219_send_row4(row, display[3], display[2], display[1], display[0]);
    }

    delay_ms(250);
  }
}
