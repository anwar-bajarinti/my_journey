#define PORTB_REG (*(volatile char*)0x25)
#define DDRB_REG  (*(volatile char*)0x24)

#define DIN_BIT 2  // Mega pin 51
#define CLK_BIT 1  // Mega pin 52
#define CS_BIT  0  // Mega pin 53

void delay_ms(unsigned int ms) {
  for (unsigned int i = 0; i < ms; i++)
    for (volatile int j = 0; j < 1000; j++);
}

// Send one row to all 4 displays
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

void max7219_init(void) {
  DDRB_REG = 0xFF;
  PORTB_REG = (1 << CS_BIT);

  max7219_send_row4(0x0C, 0x01, 0x01, 0x01, 0x01);
  max7219_send_row4(0x09, 0x00, 0x00, 0x00, 0x00);
  max7219_send_row4(0x0A, 0x08, 0x08, 0x08, 0x08);
  max7219_send_row4(0x0B, 0x07, 0x07, 0x07, 0x07);
  max7219_send_row4(0x0F, 0x00, 0x00, 0x00, 0x00);

  for (unsigned char row = 1; row <= 8; row++)
    max7219_send_row4(row, 0x00, 0x00, 0x00, 0x00);
}

// Font for WELCOME (column-wise, each character 8 pixels tall)
const unsigned char FONT[][8] = {
  // W
  {0b10000001, 0b10000001, 0b10000001, 0b10010001, 0b10010001, 0b01101110, 0b00000000, 0b00000000},
  // E
  {0b11111111, 0b10010001, 0b10010001, 0b10010001, 0b00000000, 0b00000000, 0b00000000, 0b00000000},
  // L
  {0b11111111, 0b00000001, 0b00000001, 0b00000001, 0b00000000, 0b00000000, 0b00000000, 0b00000000},
  // C
  {0b01111110, 0b10000001, 0b10000001, 0b01000010, 0b00000000, 0b00000000, 0b00000000, 0b00000000},
  // O
  {0b01111110, 0b10000001, 0b10000001, 0b01111110, 0b00000000, 0b00000000, 0b00000000, 0b00000000},
  // M
  {0b11111111, 0b00100000, 0b00010000, 0b00100000, 0b11111111, 0b00000000, 0b00000000, 0b00000000},
  // E
  {0b11111111, 0b10010001, 0b10010001, 0b10010001, 0b00000000, 0b00000000, 0b00000000, 0b00000000}
};

#define NUM_LETTERS 7
#define CHAR_WIDTH  8
#define DISPLAY_WIDTH 32
#define SCROLL_SPACING 2

// Prepare scroll buffer (add spaces between characters)
unsigned char scroll_buffer[200];  // enough size
int total_cols = 0;

void prepare_scroll_buffer() {
  total_cols = 0;
  for (int i = 0; i < NUM_LETTERS; i++) {
    for (int col = 0; col < CHAR_WIDTH; col++) {
      scroll_buffer[total_cols++] = FONT[i][col];
    }
    // Add space after character
    for (int s = 0; s < SCROLL_SPACING; s++)
      scroll_buffer[total_cols++] = 0x00;
  }
  // Pad extra blanks for smooth loop
  for (int i = 0; i < DISPLAY_WIDTH; i++)
    scroll_buffer[total_cols++] = 0x00;
}

// Show one frame
void show_frame(int offset) {
  for (int row = 0; row < 8; row++) {
    unsigned char d1 = 0, d2 = 0, d3 = 0, d4 = 0;

    for (int col = 0; col < DISPLAY_WIDTH; col++) {
      int idx = offset + col;
      unsigned char pixel = 0;
      if (idx >= 0 && idx < total_cols)
        pixel = (scroll_buffer[idx] >> row) & 1;

      if (col < 8)      d4 |= (pixel << col);
      else if (col <16) d3 |= (pixel << (col - 8));
      else if (col <24) d2 |= (pixel << (col - 16));
      else              d1 |= (pixel << (col - 24));
    }

    max7219_send_row4(8 - row, d1, d2, d3, d4);
  }
}

// Show WELCOME rising from bottom
void scroll_up_intro() {
  for (int height = 1; height <= 8; height++) {
    for (int row = 0; row < 8; row++) {
      unsigned char d1 = 0, d2 = 0, d3 = 0, d4 = 0;
      for (int col = 0; col < DISPLAY_WIDTH; col++) {
        int idx = col;
        unsigned char pixel = 0;
        if (idx < total_cols) {
          if ((7 - row) < height)
            pixel = (scroll_buffer[idx] >> (7 - row)) & 1;
        }

        if (col < 8)      d4 |= (pixel << col);
        else if (col <16) d3 |= (pixel << (col - 8));
        else if (col <24) d2 |= (pixel << (col - 16));
        else              d1 |= (pixel << (col - 24));
      }
      max7219_send_row4(8 - row, d1, d2, d3, d4);
    }
    delay_ms(200);
  }
}

void setup() {
  max7219_init();
  prepare_scroll_buffer();
  scroll_up_intro();  // Show welcome from bottom
}

void loop() {
  static int scroll = 0;
  show_frame(scroll);
  scroll++;
  if (scroll >= total_cols)
    scroll = 0;
  delay_ms(150);
}
