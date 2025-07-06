void setup() {
  // put your setup code here, to run once:
  volatile char *ddr_a=(char*)0x21;
  *ddr_a=0xff;
  volatile char *ddr_b=(char*)0x24;
  *ddr_b=0xff;

}

void loop() {
  // put your main code here, to run repeatedly:
  volatile char *port_a=(char*)0x22;
  volatile char *port_b=(char*)0x25;
  *port_a=0xff;
  *port_b=0xff;
}
