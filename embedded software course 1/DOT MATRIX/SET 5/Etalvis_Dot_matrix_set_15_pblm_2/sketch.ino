#define DDRB  (*(volatile char*)0x24)
#define PORTB (*(volatile char*)0x25)

// Pin definitions (connected to MAX7219)
#define LOAD 0   // CS
#define CLK  1   // Clock
#define DIN  2   // Data In

// Send 16 bits (address + data) to each MAX7219 (chained)
// First sent → last module (right), then left
void max7219_send_pair(unsigned char address, unsigned char left_data, unsigned char right_data) {
  PORTB &= ~(1 << LOAD);  // Begin communication

  // First send address to right module (2nd in chain)
  for (int i = 7; i >= 0; i--) {
    PORTB &= ~(1 << CLK);
    (address & (1 << i)) ? (PORTB |= (1 << DIN)) : (PORTB &= ~(1 << DIN));
    PORTB |= (1 << CLK);
  }

  // Then send data to right module
  for (int i = 7; i >= 0; i--) {
    PORTB &= ~(1 << CLK);
    (right_data & (1 << i)) ? (PORTB |= (1 << DIN)) : (PORTB &= ~(1 << DIN));
    PORTB |= (1 << CLK);
  }

  // Now send to left module
  for (int i = 7; i >= 0; i--) {
    PORTB &= ~(1 << CLK);
    (address & (1 << i)) ? (PORTB |= (1 << DIN)) : (PORTB &= ~(1 << DIN));
    PORTB |= (1 << CLK);
  }

  for (int i = 7; i >= 0; i--) {
    PORTB &= ~(1 << CLK);
    (left_data & (1 << i)) ? (PORTB |= (1 << DIN)) : (PORTB &= ~(1 << DIN));
    PORTB |= (1 << CLK);
  }

  PORTB |= (1 << LOAD);  // Latch all
}

// Initialize both MAX7219 chips
void max7219_init() {
  DDRB |= (1 << LOAD) | (1 << CLK) | (1 << DIN);  // Make pins output

  for (int i = 0; i < 2; i++) {
    max7219_send_pair(0x0F, 0x00, 0x00); // No display test
    max7219_send_pair(0x0C, 0x01, 0x01); // Normal operation
    max7219_send_pair(0x0B, 0x07, 0x07); // Display all 8 rows
    max7219_send_pair(0x0A, 0x08, 0x08); // Medium brightness
    max7219_send_pair(0x09, 0x00, 0x00); // No decode mode
  }

  // Clear all digits
  for (int row = 1; row <= 8; row++) {
    max7219_send_pair(row, 0x00, 0x00);
  }
}

// Character bitmaps for '1' and '2' (column-wise format)
unsigned char bitmap_1[8] = {
  0b00010000,
  0b00011000,
  0b00010100,
  0b00010000,
  0b00010000,
  0b00010000,
  0b01111100,
  0b00000000
};

unsigned char bitmap_2[8] = {
  0b01100000,
  0b10010000,
  0b10000000,
  0b01000000,
  0b00100000,
  0b00010000,
  0b11110000,
  0b00000000
};

void setup() {
  max7219_init();

  for (int row = 0; row < 8; row++) {
    // Left digit: '1', Right digit: '2'
    max7219_send_pair(row + 1, bitmap_2[row], bitmap_1[row]);
  }
}

void loop() {
  // No animation
}
