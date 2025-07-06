void setup() {
  // put your setup code here, to run once:
  volatile char *ddr_k=(char*)0x107;
  *ddr_k=0xff;

}

void loop() {
  // put your main code here, to run repeatedly:
  volatile char *port_k=(char*)0x108;
  
 volatile char i;
 volatile long x;
 *port_k=0;
 for(i=1;i<7;i=i+2)
 {
  *port_k|=(1<<i);
  for(x=0;x<100000;x++);

 }
  

}