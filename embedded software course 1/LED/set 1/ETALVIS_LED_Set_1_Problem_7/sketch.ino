void setup() {
  // put your setup code here, to run once:
  volatile char *ddr_f=(char*)0x30;
  *ddr_f=0xff;
}

void loop() {
  // put your main code here, to run repeatedly:
  volatile char *port_f=(char*)0x31;
  *port_f=255; 
}
