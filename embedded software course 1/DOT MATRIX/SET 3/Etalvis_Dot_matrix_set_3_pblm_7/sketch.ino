// Embedded Systems programming - GPIO
// Dot Matrix Control - Display revolving text "Welcome" Right to Left
// PORTA = Rows (Anodes), PORTB = Columns (Cathodes)

volatile char *porta = (char *)0x22;
volatile char *portb = (char *)0x25;

char rows[100];
char index = 0;

void delay1(void) {
  for (volatile long i = 0; i < 1000; i++);
}

// Add character to message array
void add(char *arr) {
  for (char i = 0; i < 8; i++) {
    rows[index++] = arr[i];
  }
  rows[index++] = 0x00;  // space between characters
}

void setup() {
  volatile char *ddra = (char *)0x21;
  volatile char *ddrb = (char *)0x24;
  *ddra = 0xFF;
  *ddrb = 0xFF;
  *porta = 0x00;
  *portb = 0xFF;

  // Letter bitmaps (row-wise)
  char W[8] = {0xFF, 0xBD, 0xBD, 0xBD, 0xA5, 0xA5, 0x81, 0xFF}; // 'W'
  char E[8] = {0xFF, 0xFF, 0xC7, 0xBB, 0x83, 0xBF, 0xC7, 0xFF}; // 'E'
  char L[8] = {0xCF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0x83, 0xFF}; // 'L'
  char C[8] = {0xFF, 0xC7, 0xBB, 0xBF, 0xBF, 0xBB, 0xC7, 0xFF}; // 'C'
  char O[8] = {0xFF, 0xFF, 0xCF, 0xB7, 0xB7, 0xCF, 0xFF, 0xFF}; // 'O'
  char M[8] = {0xFF, 0xD7, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xFF}; // 'M'

  add(W);
  add(E);
  add(L);
  add(C);
  add(O);
  add(M);
  add(E);  // Final E in "WELCOME"

  int totalrows = index;

  while (1) {
    for (int shift = 0; shift < totalrows; shift++) {
      for (int frame = 0; frame < 50; frame++) {
        for (int row = 0; row < 8; row++) {
          *porta = (1 << row);  // Activate one row at a time
          *portb = rows[(shift + row) % totalrows];  // Scroll across
          delay1();
          *porta = 0x00;
          *portb = 0xFF;
        }
      }
    }
  }
}

void loop() {
  // Nothing here because we do everything in setup()
}
