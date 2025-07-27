void setup() {
  // put your setup code here, to run once:
  volatile char *DDR_D=(char*)0x2A;
  *DDR_D=0xff;
}

void loop() {
  // put your main code here, to run repeatedly: 
volatile char *port_d=(char*)0x2B;
*port_d=128;
}
