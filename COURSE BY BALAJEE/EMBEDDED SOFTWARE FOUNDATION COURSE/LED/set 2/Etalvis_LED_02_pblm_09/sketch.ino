void setup() {
  // put your setup code here, to run once:
  volatile char *ddr_f=(char*)0x30;
  *ddr_f=0xff;

}

void loop() {
  // put your main code here, to run repeatedly:
  volatile char *port_f=(char*)0x31;
  
 volatile char i;
 volatile long x;

 for(i=3;i>=0;i--)
 {
  *port_f=(1<<i);
  for(x=0;x<100000;x++);

 }
  

}