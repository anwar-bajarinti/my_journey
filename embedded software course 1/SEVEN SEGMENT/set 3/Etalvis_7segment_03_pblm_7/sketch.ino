void setup() {
  // put your setup code here, to run once:
  volatile char *ddr_a=(char*)0x21;
  volatile char *ddr_b=(char*)0x24;
  volatile char *ddr_f=(char*)0x30;
   volatile char *ddr_k=(char*)0x107;
  *ddr_a=0xFF;
  *ddr_b=0xFF;
  *ddr_f=0xFF;
  *ddr_k=0xFF;
}
void loop() {
  // put your main code here, to run repeatedly:
  char num[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0xF,0x6F};
  volatile char *port_a=(char*)0x22;
  volatile char *port_b=(char*)0x25;
   volatile char *port_f=(char*)0x31;
    volatile char *port_k=(char*)0x108;
    for(char i=0;i<10;i++)
    {
      for(char j=0;j<10;j++)
      {
        for(char k=0;k<10;k++)
        {
          for(char l=0;l<10;l++)
          {
            *port_a=num[i];
            *port_b=num[j];
             *port_f=num[k];
             *port_k=num[l];
             delay_();
  

          }
        }
      }
    }
    
}

void delay_(void)
{ 
  char temp=0;
  for(volatile long i=0;i<100;i++)
  {
    for(volatile long j=0;j<4000;j++)
    {
      temp++;
    }
  }
}
