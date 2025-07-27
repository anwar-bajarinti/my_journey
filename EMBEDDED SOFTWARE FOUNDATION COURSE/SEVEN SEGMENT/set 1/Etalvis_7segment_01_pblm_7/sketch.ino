void setup() {
  // put your setup code here, to run once:
  volatile char *ddr_a=(char*)0x21;
  *ddr_a=0xff;

}

void loop() {
  // put your main code here, to run repeatedly:
volatile char *port_a=(char*)0x22;
*port_a=0x7D;
}
