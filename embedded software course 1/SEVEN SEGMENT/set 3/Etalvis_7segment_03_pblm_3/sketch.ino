void setup() {
  // put your setup code here, to run once:
  volatile char *ddr_a=(char*)0x21;
  volatile char *ddr_b=(char*)0x24;
  *ddr_a=0xFF;
  *ddr_b=0xFF;

}

void loop() {
  // put your main code here, to run repeatedly:
  char num2[]={0xBF,0x86,0xDB,0xCF,0xE6,0xED,0xFD,0x87,0xFF,0xEF};
  char num[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
  volatile char *port_a=(char*)0x22;
  volatile char *port_b=(char*)0x25;
  for(char i=0;i<10;i++)
  { 
    *port_a=num2[i];
    for(char j=0;j<10;j++)
    {
      *port_b=num[j];
      delay_();
     
    }
  }
  
  

}
void delay_()
{
  volatile char dummy=0;
  for(long i=0;i<150;i++)
  {
    for(long j=0;j<4000;j++)
    {
      dummy++;
    }
  }
}