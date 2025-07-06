void setup() {
  // put your setup code here, to run once:
  volatile char *ddr_c=(char*)0x27;
  *ddr_c=0xff;

}

void loop() {
  // put your main code here, to run repeatedly:
  volatile char *port_c=(char*)0x28;
  
 volatile char i;
 volatile long x;
  *port_c=0;
 for(i=0;i<7;i++)
 {
  *port_c|=(1<<i);
  for(x=0;x<100000;x++);

 }
  

}