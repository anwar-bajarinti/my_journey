#define DDRB  (*(volatile char*)0x24)
#define PORTB (*(volatile char*)0x25)

#define LOAD 0
#define CLK  1
#define DIN  2

// Digits column-wise (normal orientation)
unsigned char digit1[8] = {
  0b00010000,
  0b00011000,
  0b00010100,
  0b00010000,
  0b00010000,
  0b00010000,
  0b01111100,
  0b00000000
};
unsigned char digit2[8] = {
  0b01100000,
  0b10010000,
  0b10000000,
  0b01000000,
  0b00100000,
  0b00010000,
  0b11110000,
  0b00000000
};
unsigned char digit3[8] = {
  0b01100000,
  0b10010000,
  0b10000000,
  0b01000000,
  0b10000000,
  0b10010000,
  0b01100000,
  0b00000000
};
unsigned char digit4[8] = {
  0b00010000,
  0b00011000,
  0b00010100,
  0b00010010,
  0b01111110,
  0b00010000,
  0b00010000,
  0b00000000
};

void max7219_send_all(unsigned char addr, unsigned char d1, unsigned char d2, unsigned char d3, unsigned char d4) {
  PORTB &= ~(1 << LOAD);
  unsigned char data[4] = { d1, d2, d3, d4 };
  for (char dev = 0; dev < 4; dev++) {
    for (int i = 7; i >= 0; i--) {
      PORTB &= ~(1 << CLK);
      (addr & (1 << i)) ? (PORTB |= (1 << DIN)) : (PORTB &= ~(1 << DIN));
      PORTB |= (1 << CLK);
    }
    for (int i = 7; i >= 0; i--) {
      PORTB &= ~(1 << CLK);
      (data[dev] & (1 << i)) ? (PORTB |= (1 << DIN)) : (PORTB &= ~(1 << DIN));
      PORTB |= (1 << CLK);
    }
  }
  PORTB |= (1 << LOAD);
}

void max7219_init() {
  DDRB |= (1 << LOAD) | (1 << CLK) | (1 << DIN);
  for (int i = 0; i < 4; i++) {
    max7219_send_all(0x0F, 0, 0, 0, 0);
    max7219_send_all(0x0C, 1, 1, 1, 1);
    max7219_send_all(0x0B, 7, 7, 7, 7);
    max7219_send_all(0x0A, 8, 8, 8, 8);
    max7219_send_all(0x09, 0, 0, 0, 0);
  }
  for (int i = 1; i <= 8; i++) {
    max7219_send_all(i, 0, 0, 0, 0);
  }
}

void delay_custom(long t) {
  for (volatile long i = 0; i < t; i++);
}

void setup() {
  max7219_init();
}

void loop() {
  for (int step = 0; step < 4; step++) {
    for (int frame = 0; frame < 8; frame++) {
      for (int row = 0; row < 8; row++) {
        unsigned char r1 = 0, r2 = 0, r3 = 0, r4 = 0;

        if (row <= step) {
          r1 = digit1[7 - row];
          r2 = digit2[7 - row];
          r3 = digit3[7 - row];
          r4 = digit4[7 - row];
        }

        if (row >= 7 - step) {
          r1 = digit1[7 - row];
          r2 = digit2[7 - row];
          r3 = digit3[7 - row];
          r4 = digit4[7 - row];
        }

        max7219_send_all(8 - row, r1, r2, r3, r4);
      }
      delay_custom(30000);
    }
  }
  for (volatile long i = 0; i < 300000; i++);
}