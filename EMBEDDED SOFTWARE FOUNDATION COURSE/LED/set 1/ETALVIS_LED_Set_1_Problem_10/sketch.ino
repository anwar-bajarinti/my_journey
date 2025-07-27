void setup() {
  // put your setup code here, to run once:
  volatile char *ddr_e=(char*)0x2D;
  *ddr_e=0xff;
}

void loop() {
  // put your main code here, to run repeatedly:
volatile char *port_e=(char*)0x2E;
*port_e=0b00111010;
}
