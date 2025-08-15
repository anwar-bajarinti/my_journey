void setup() {
  // put your setup code here, to run once:
  volatile char *ddr_h=(char*)0x101;
  *ddr_h=0xff;
}

void loop() {
  // put your main code here, to run repeatedly:
  volatile char *port_h=(char*)0x102;
  *port_h=3;
}


