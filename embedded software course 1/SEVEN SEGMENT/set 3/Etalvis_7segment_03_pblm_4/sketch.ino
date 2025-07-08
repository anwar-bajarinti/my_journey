void setup() {
  // put your setup code here, to run once:
  volatile char *ddr_a=(char*)0x21;
  volatile char *ddr_b=(char*)0x24;
  *ddr_a=0xFF;
  *ddr_b=0xFF;

}
void loop() {
  // put your main code here, to run repeatedly:
  char num[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
  volatile char *port_a=(char*)0x22;
  volatile char *port_b=(char*)0x25;
  while(1)
  {
      *port_b=2;
      *port_a=num[2];
      delay_();
       *port_b=3;
       *port_a=0;
      delay_();
      *port_b=1;
      *port_a=num[5];     
       delay_();
       *port_b=3;
       *port_a=0;
      delay_();

  } 
}
void delay_()
{ char temp=0;
  for(long i=0;i<1000;i++)
  {
    temp++;
  }
}