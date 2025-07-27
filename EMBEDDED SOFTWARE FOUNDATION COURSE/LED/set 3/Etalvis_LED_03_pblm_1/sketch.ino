void setup() {
  // put your setup code here, to run once:
  volatile char *ddr_a=(char*)0x21;
  *ddr_a=0xff;

}

void loop() {
  // put your main code here, to run repeatedly:
  volatile char *port_a=(char*)0x22;
  
 volatile long  x;
 while(1)
 {
 *port_a=0b10001000;
  for(x=0;x<100000;x++);
  *port_a=0b01000100;
  for(x=0;x<100000;x++);
  *port_a=0b00100010;
  for(x=0;x<100000;x++);
  *port_a=0b00010001;
  for(x=0;x<100000;x++);
}
}