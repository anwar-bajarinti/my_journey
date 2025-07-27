void setup() {
  // put your setup code here, to run once:
  volatile char *ddr_a=(char*)0x21;
  *ddr_a=0xff;

}

void loop() {
  // put your main code here, to run repeatedly:
  volatile char *port_a=(char*)0x22;\
  *port_a=0;
  
 volatile long  x;
 while(1){
  *port_a=0;
 for(volatile char i=0;i<8;i++)
 { *port_a|=(1<<i);
  for(x=0;x<100000;x++);
 }
 }
}
