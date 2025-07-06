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
 { *port_a=1;
  for(x=0;x<100000;x++);
  *port_a=4;
  for(x=0;x<100000;x++);
  *port_a=2;
  for(x=0;x<100000;x++);
  *port_a=8;
  for(x=0;x<100000;x++);
  *port_a=16;
  for(x=0;x<100000;x++);
  *port_a=64;
  for(x=0;x<100000;x++);
  *port_a=32;
  for(x=0;x<100000;x++);
  *port_a=128;
  for(x=0;x<100000;x++);
 }
 
}
