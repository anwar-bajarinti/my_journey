#define DDRB  (*(volatile char*)0x24)
#define PORTB (*(volatile char*)0x25)

#define LOAD 0
#define CLK  1
#define DIN  2

// Send to 4 cascaded MAX7219 chips
void max7219_send_all(unsigned char addr, unsigned char d1, unsigned char d2, unsigned char d3, unsigned char d4) {
  PORTB &= ~(1 << LOAD);  // Begin transmission

  unsigned char data[4] = { d1,d2,d3,d4 };  

  for (char dev = 0; dev < 4; dev++) {
    // Send address
    for (int i = 7; i >= 0; i--) {
      PORTB &= ~(1 << CLK);
      if (addr & (1 << i)) PORTB |= (1 << DIN);
      else PORTB &= ~(1 << DIN);
      PORTB |= (1 << CLK);
    }

    // Send data
    for (int i = 7; i >= 0; i--) {
      PORTB &= ~(1 << CLK);
      if (data[dev] & (1 << i)) PORTB |= (1 << DIN);
      else PORTB &= ~(1 << DIN);
      PORTB |= (1 << CLK);
    }
  }

  PORTB |= (1 << LOAD);  // Latch all data
}

void max7219_init() {
  DDRB |= (1 << LOAD) | (1 << CLK) | (1 << DIN);  // Set as output

  for (int i = 0; i < 4; i++) {
    max7219_send_all(0x0F, 0x00, 0x00, 0x00, 0x00); // test mode off
    max7219_send_all(0x0C, 0x01, 0x01, 0x01, 0x01); // shutdown mode off
    max7219_send_all(0x0B, 0x07, 0x07, 0x07, 0x07); // scan all digits
    max7219_send_all(0x0A, 0x08, 0x08, 0x08, 0x08); // medium brightness
    max7219_send_all(0x09, 0x00, 0x00, 0x00, 0x00); // no decode
  }

  for (int i = 1; i <= 8; i++) {
    max7219_send_all(i, 0x00, 0x00, 0x00, 0x00);  // Clear all
  }
}

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

void setup() {
  max7219_init();

  // for (int row = 0; row < 8; row++) {
    
  //   max7219_send_all(row + 1,  digit1[row], digit2[row], digit3[row],digit4[row]);
  // }
  // for(volatile long long  i=0;i<1000000;i++);
  
  
  
   for (int row = 0; row < 8; row++) {
    
    max7219_send_all(row + 1, digit1[row], 0x00, 0x00, 0x00);
  }
  for(volatile long long  i=0;i<100000;i++);
  for (int row = 0; row < 8; row++) {
    
    max7219_send_all(row + 1, digit1[row],digit2[row], 0x00, 0x00);
  }
  for(volatile long long  i=0;i<100000;i++);
  for (int row = 0; row < 8; row++) {
    
    max7219_send_all(row + 1, digit1[row],digit2[row],digit3[row] ,0x00 );
  }
  for(volatile long long  i=0;i<100000;i++);
  for (int row = 0; row < 8; row++) {
    
    max7219_send_all(row + 1, digit1[row],digit2[row],digit3[row],digit4[row]);
  } ;
}


void loop() {
  // Do nothing
}
