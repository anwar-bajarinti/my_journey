void setup() {
  // put your setup code here, to run once:
  volatile char *ddr_l=(char*)0x10A;
  *ddr_l=0xff;
}

void loop() {
  // put your main code here, to run repeatedly:
  volatile char *port_l=(char*)0x10B;
  *port_l=0b0101010101;
}
