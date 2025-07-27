void setup() {
  // put your setup code here, to run once:
  volatile char *ddr_k=(char*)0x107;
  *ddr_k=0xff;
}

void loop() {
  // put your main code here, to run repeatedly:
  volatile char *port_k=(char*)0x108;
  *port_k=0b1010101010 ;
}
