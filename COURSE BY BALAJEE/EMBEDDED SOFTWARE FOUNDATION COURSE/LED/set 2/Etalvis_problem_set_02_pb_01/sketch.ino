void setup() {
  // put your setup code here, to run once:
  volatile char *ddr_j=(char*)0x104;
  *ddr_j=0xff;

}

void loop() {
  // put your main code here, to run repeatedly:
  volatile char *port_j=(char*)0x105;
  
 volatile long i;
  while(1)
  { *port_j=1; 
  for(i=0;i<100000;i++);
  *port_j=0;
    for(i=0;i<100000;i++);
 
  }
  

}