#define DDRB  (*(volatile char*)0x24)
#define PORTB (*(volatile char*)0x25)

#define LOAD 0
#define CLK  1
#define DIN  2

// Parallel scroll buffer (24 = 8 top pad + 8 digit + 8 bottom pad)
unsigned char d1_scroll[24], d2_scroll[24], d3_scroll[24], d4_scroll[24];

// Digits for 1, 2, 3, 4 (column-wise format)
unsigned char digit1[8] = {0b00000000,
    0b01111110,
    0b00000010,
    0b00000010,
    0b01111110,
    0b00000010,
    0b00000010,
    0b01111110};
unsigned char digit2[8] = {0b00000000,
    0b00010000,
    0b00010000,
    0b00010000,
    0b00010000,
    0b00010000,
    0b00010000,
    0b01111100};
unsigned char digit3[8] = {0b00000000,
    0b01000010,
    0b01000010,
    0b01000010,
    0b01111110,
    0b01000010,
    0b01000010,
    0b00111100};
unsigned char digit4[8] = {0b00000000,
    0b01111110,
    0b00000010,
    0b00000010,
    0b00000010,
    0b00000010,
    0b00000010,
    0b00000010};

// Send address + data to all 4 cascaded MAX7219 chips
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

// Fill buffer = top pad + digit + bottom pad
void prepare_scroll_data() {
  for (int i = 0; i < 8; i++) {
    d1_scroll[i] = 0x00;
    d2_scroll[i] = 0x00;
    d3_scroll[i] = 0x00;
    d4_scroll[i] = 0x00;

    d1_scroll[i + 8] = digit1[i];
    d2_scroll[i + 8] = digit2[i];
    d3_scroll[i + 8] = digit3[i];
    d4_scroll[i + 8] = digit4[i];

    d1_scroll[i + 16] = 0x00;
    d2_scroll[i + 16] = 0x00;
    d3_scroll[i + 16] = 0x00;
    d4_scroll[i + 16] = 0x00;
  }
}

void delay_scroll() {
  for (volatile long i = 0; i < 40000; i++);
}

void setup() {
  max7219_init();
  prepare_scroll_data();
}

// Top to bottom scrolling animation
void loop() {
  for (int shift = 16; shift >=0; shift--) {
    for (int frame = 0; frame < 10; frame++) {
      for (int row = 0; row < 8; row++) {
        max7219_send_all( 8-row ,
          d1_scroll[shift + row],
          d2_scroll[shift + row],
          d3_scroll[shift + row],
          d4_scroll[shift + row]);
      }
      delay_scroll();
    }
  }
}
