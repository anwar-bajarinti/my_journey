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
  char name2[] = "ETALVIS";
  int len1 = 7;
  int len2 = 7;

  for (char k = 0; k<=9; k++)  // Scroll WELCOME left
  {
    command(0x01);            // Clear screen
    command(0xC4);
  for (int i = 0; i < len1; i++) {
      data(name2[i]);
  }
    // Print WELCOME on Line 1 (0x80)
    command(0x80 + k);
    for (int i = 0; i < len1; i++) {
      data(name[i]);
    }

    delay_(2000);
  }

  

}