void setup() {
  // put your setup code here, to run once:
  volatile char *ddr_c=(char*)0x27;
  *ddr_c=0xff;
}

void loop() {
  // put your main code here, to run repeatedly:
  volatile char *port_c=(char*)0x28;
  *port_c=192;
}
