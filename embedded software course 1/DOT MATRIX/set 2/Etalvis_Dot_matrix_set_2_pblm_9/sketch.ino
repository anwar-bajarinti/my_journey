
void setup() {
  // put your setup code here, to run once:
  volatile char *ddra, *ddrb; //both port A and B as output
  ddra = 0x21; *ddra = 0xFF;
  ddrb = 0x24; *ddrb = 0xFF;

}

void loop() {
  // put your main code here, to run repeatedly:
  volatile char *porta, *portb, row;
  porta = 0x22; portb = 0x25;
  unsigned char value[]={ 0xFd,0xFB,0x97,0x67,0x67,0x9B,0xFD,0xFF};
  for (row = 0; row < 8; row++)
  {
   *porta = 0x00;
    *portb = 0xFF;
    *porta = (1 << row);             // Activate one row at a time
    *portb = value[row];      // Activate corresponding mirrored column
    *porta = 0x00;
    *portb = 0xFF;
  
  }

}