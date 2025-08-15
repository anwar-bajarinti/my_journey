// Embedded Systems - 8x8 LED Dot Matrix Scrolling Text: "WELCOME"
// PORTA → Rows (Anodes), PORTB → Columns (Cathodes)
// Author: Anwar Bajarinti

volatile char *rowPort = (char *)0x22;   // PORTA for rows
volatile char *colPort = (char *)0x25;   // PORTB for columns

char fontBuffer[100];   // Stores column/row values of characters
char bufferIndex = 0;   // Keeps track of the next position in buffer

// Simple delay for visible effect
void delay_scroll() {
  for (volatile long i = 0; i < 1000; i++);
}

// Add 1 character (8 rows) to fontBuffer with a blank column
void addCharacter(char *charRows) {
  for (char i = 0; i < 8; i++) {
    fontBuffer[bufferIndex++] = charRows[i];
  }
  fontBuffer[bufferIndex++] = 0x00;  // Spacer column
}

void setup() {
  volatile char *ddrRow = (char *)0x21;  // DDRA
  volatile char *ddrCol = (char *)0x24;  // DDRB
  *ddrRow = 0xFF;  // Set PORTA as output (rows)
  *ddrCol = 0xFF;  // Set PORTB as output (columns)
  *rowPort = 0x00;
  *colPort = 0xFF;

  // Letter bitmaps (row-wise, 8 rows per letter)
  char W[8] = {0xFF, 0xF7, 0xD7, 0xD7, 0xD7, 0xD7, 0x81, 0x81};
  char E[8] = {0xC7, 0xC7, 0xC3, 0xC3, 0xC3, 0xDF, 0xDF, 0xFF};
  char L[8] = {0x83, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xFF};
  char C[8] = {0xFF, 0xC7, 0xBB, 0xBF, 0xBF, 0xBB, 0xC7, 0xFF};
  char O[8] = {0xFF, 0xCF, 0xB7, 0xB7, 0xB7, 0xB7, 0xCF, 0xFF};
  char M[8] = {0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xD7, 0xFF};

  // Add letters of "WELCOME" into buffer
  addCharacter(W);
  addCharacter(E);
  addCharacter(L);
  addCharacter(C);
  addCharacter(O);
  addCharacter(M);
  addCharacter(E);

  int totalColumns = bufferIndex;  // Total number of columns to scroll
  int directionFlag = 0;           // Controls row scanning direction

  while (1) {
    for (int shift = 0; shift < totalColumns; shift++) {
      for (int repeat = 0; repeat < 50; repeat++) {
        for (int row = 0; row < 8; row++) {
          // Scan rows: top-to-bottom or bottom-to-top based on directionFlag
          *rowPort = (directionFlag % 2 == 0) ? (1 << row) : (1 << (7 - row));
          
          // Load the corresponding column value for current row
          *colPort = fontBuffer[(shift + row) % totalColumns];

          delay_scroll();

          // Clear both ports
          *rowPort = 0x00;
          *colPort = 0xFF;
        }
      }
      directionFlag++;  // Change direction after each character shift
    }
  }
}

void loop() {
  // Nothing here; execution handled in setup()
}
