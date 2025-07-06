
void setup() {
  // put your setup code here, to run once:
  volatile char *ddra,*ddrb;//both port A and B as output
  ddra = 0x21;*ddra = 0xFF;
  ddrb = 0x24;*ddrb = 0xFF;
}

void loop() {
  // put your main code here, to run repeatedly:
  volatile char *porta,*portb;
  porta = 0x22;portb = 0x25;
  *porta = 0b10000000;
  *portb = 0b01111111;
}