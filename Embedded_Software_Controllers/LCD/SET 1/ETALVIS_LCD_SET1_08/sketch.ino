volatile char *porta = (char *)0x22;
volatile char *portb = (char *)0x25;
volatile char *ddra  = (char *)0x21;
volatile char *ddrb  = (char *)0x24;

#define RS 1
#define E  0

void delay_(unsigned int t)
{
  for (volatile long i = 0; i < t * 1000; i++);
}

void pulseEnable()
{
  *portb |= (1 << E);
  delay_(1);
  *portb &= ~(1 << E);
}

void command(char cmd)
{
  *portb &= ~(1 << RS);   // RS = 0 for command
  *porta = cmd;
  pulseEnable();
  delay_(2);
}

void data(char d)
{
  *portb |= (1 << RS);    // RS = 1 for data
  *porta = d;
  pulseEnable();
  delay_(2);
}

void setup()
{
  *ddra = 0xFF;  // PORTA for data output
  *ddrb |= (1 << RS) | (1 << E); // RS and E as output

  command(0x38);  // Function set: 8-bit, 2-line
  command(0x0E);  // Display ON, cursor ON
  command(0x01);  // Clear display
  command(0x06);  // Entry mode set: increment
  
}

void loop()
{
  char name[] = "WELCOME";
  int len = 7;  // Length of "WELCOME"

  // Scroll from right (position 9) to left (position 0)
  for (char k = 9; k >= 0; k--)
  {
    command(0x01);          // Clear screen
    command(0x80 + k);      // Set cursor position on Line 1

    for (int i = 0; i < len; i++) {
      data(name[i]);        // Display each character
    }

    delay_(2000);            // Wait before shifting
  }

  while (1);  // Stay forever
}
