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
    
    *port_a=check;
  }

}
