void setup() {
  // Set ports
  volatile char *ddr_f = (char*)0x30;  *ddr_f = 0xFF;   // Keypad rows output
  volatile char *ddr_k = (char*)0x107; *ddr_k = 0x00;   // Keypad cols input

  volatile char *ddr_a = (char*)0x21;  *ddr_a = 0xFF;   // 7-segment digit 1 (thousands)
  volatile char *ddr_l = (char*)0x10A; *ddr_l = 0xFF;   // digit 2 (hundreds)
  volatile char *ddr_c = (char*)0x27;  *ddr_c = 0xFF;   // digit 3 (tens)
  volatile char *ddr_b = (char*)0x24;  *ddr_b = 0xFF;   // digit 4 (ones)
}

void loop() {
  volatile char *port_a = (char*)0x22;
  volatile char *port_l = (char*)0x10B;
  volatile char *port_c = (char*)0x28;
  volatile char *port_b = (char*)0x25;

  char num[] = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F  // 9
  };

  char digit1[4], digit2[4];

  // Input 1st 4-digit number (numerator)
  for (char i = 0; i < 4; i++) {
    digit1[i] = scan();
    delay_ms(300);
  }

  // Input 2nd 4-digit number (denominator)
  for (char i = 0; i < 4; i++) {
    digit2[i] = scan();
    delay_ms(300);
  }

  long num1 = 1000 * digit1[0] + 100 * digit1[1] + 10 * digit1[2] + digit1[3];
  long num2 = 1000 * digit2[0] + 100 * digit2[1] + 10 * digit2[2] + digit2[3];

  // Check for division by zero
  if (num2 == 0) {
    *port_a = 0x79;  // E
    *port_l = 0x50;  // r
    *port_c = 0x50;  // r
    *port_b = 0x00;  // blank
  } else {
    long rem = num1 % num2;

    if (rem > 9999) {
      *port_a = 0x79;  // E
      *port_l = 0x79;  // E
      *port_c = 0x40;  // -
      *port_b = 0x40;  // -
    } else {
      char ones     = rem % 10;    rem /= 10;
      char tens     = rem % 10;    rem /= 10;
      char hundreds = rem % 10;    rem /= 10;
      char thousands = rem;

      *port_a = num[thousands];
      *port_l = num[hundreds];
      *port_c = num[tens];
      *port_b = num[ones];
    }
  }

  while (1); // freeze after result
}

void delay_ms(int ms) {
  for (volatile long i = 0; i < ms * 1000L; i++);
}

char scan() {
  volatile char *port_f = (char*)0x31;
  volatile char *port_k = (char*)0x106;

  while (1) {
    for (char row = 0; row < 4; row++) {
      *port_f = (1 << row);
      char status = *port_k;

      if (status != 0) {
        if (row == 0 && status == 1) return 1;
        if (row == 0 && status == 2) return 2;
        if (row == 0 && status == 4) return 3;
        if (row == 1 && status == 1) return 4;
        if (row == 1 && status == 2) return 5;
        if (row == 1 && status == 4) return 6;
        if (row == 2 && status == 1) return 7;
        if (row == 2 && status == 2) return 8;
        if (row == 2 && status == 4) return 9;
        if (row == 3 && status == 2) return 0;
      }
    }
  }
}
