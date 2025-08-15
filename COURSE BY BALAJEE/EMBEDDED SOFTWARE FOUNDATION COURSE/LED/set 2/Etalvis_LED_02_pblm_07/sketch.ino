void setup() {
  // put your setup code here, to run once:
  volatile char *ddr_l=(char*)0x10A;
  *ddr_l=0xff;

}

void loop() {
  // put your main code here, to run repeatedly:
  volatile char *port_l=(char*)0x10B;
  
 volatile char i;
 volatile long x;

 for(i=0;i<4;i++)
 {
  *port_l=(1<<i);
  for(x=0;x<100000;x++);

 }
  

}