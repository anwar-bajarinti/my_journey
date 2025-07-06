void setup() {
  // put your setup code here, to run once:
  volatile char *ddr_b=(char*)0x24;
  *ddr_b=0xff;

}

void loop() {
  // put your main code here, to run repeatedly:
  volatile char *port_b=(char*)0x25;
  
 volatile char i;
 volatile long x;
 for(i=0;i<7;i++)
 {
  *port_b=(1<<i);
  for(x=0;x<100000;x++);

 }
  

}