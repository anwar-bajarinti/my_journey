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
 { *port_a=0b00000011;
  for(x=0;x<100000;x++);
  *port_a=0b11000000;
  for(x=0;x<100000;x++);
  *port_a=0b00001100;
  for(x=0;x<100000;x++);
  *port_a=0b00110000;
  for(x=0;x<100000;x++);
  
  
 }
 
}
