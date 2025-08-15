void setup() {
  // put your setup code here, to run once:
  volatile char *ddr_a=(char*)0x21;
  volatile char *ddr_b=(char*)0x24;
  *ddr_a=0xFF;
  *ddr_b=0x00;
}

void loop() {
  // put your main code here, to run repeatedly:
  volatile char *port_a=(char*)0x22;
  volatile char *port_b=(char*)0x23;
  volatile char check;
  while(1)
  { check=*port_b;
    
    if(check&1)
    {
      *port_a=128;
      for(long i=0;i<10000;i++);
      *port_a=0x00;
    }
    if(check&2)
    {
      *port_a=64;
      for(long i=0;i<10000;i++);
      *port_a=0x00;
    }
    if(check&4)
    {
      *port_a=32;
      for(long i=0;i<10000;i++);
      *port_a=0x00;
    }
    if(check&8)
    {
      *port_a=16;
      for(long i=0;i<10000;i++);
      *port_a=0x00;
    }
    if(check&16)
    {
      *port_a=8;
      for(long i=0;i<10000;i++);
      *port_a=0x00;
    }
    if(check&32)
    {
      *port_a=4;
      for(long i=0;i<10000;i++);
      *port_a=0x00;
    }
    if(check&64)
    {
      *port_a=2;
      for(long i=0;i<10000;i++);
      *port_a=0x00;
    }
    if(check&128)
    {
      *port_a=1;
      for(long i=0;i<10000;i++);
      *port_a=0x00;
    }
    if(check&1)
    {
      *port_a=128;
      for(long i=0;i<10000;i++);
      *port_a=0x00;
    }
  }

}
