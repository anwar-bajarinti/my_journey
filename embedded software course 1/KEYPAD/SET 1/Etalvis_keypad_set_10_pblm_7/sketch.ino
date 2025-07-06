void setup() {
  // put your setup code here, to run once:
volatile char *ddr_f=(char*)0x30;
*ddr_f=0xFF;
volatile char *ddr_k=(char*)0x107;
*ddr_k=0x00;
volatile char *ddr_a=(char*)0x21;
*ddr_a=0xFF;
volatile char *ddr_b=(char*)0x24;
*ddr_b=0xFF;
volatile char *ddr_c=(char*)0x27;
*ddr_c=0xFF;
volatile char *ddr_l=(char*)0x10A;
*ddr_l=0xFF;
}

void loop() {
  // put your main code here, to run repeatedly:
  volatile char *port_f=(char*)0x31;
  volatile char *port_k=(char*)0x106;
  volatile char *port_a=(char*)0x22;
  volatile char *port_l=(char*)0x10B;
  volatile char *port_c=(char*)0x28;
  volatile char *port_b=(char*)0x25;
  char num[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
      
  long  digit1[4];
  long  digit2[4];
  for(signed char i=3;i>=0;i--)
  {
    digit1[i]=scan();
    for(volatile long i=0;i<100000;i++);
  }
  for(signed char i=3;i>=0;i--)
  {
    digit2[i]=scan();
    for(volatile long i=0;i<100000;i++);
  }
  long  sum1=(1000*digit1[3])+(100*digit1[2])+(10*digit1[1])+digit1[0];
  long  sum2=(1000*digit2[3])+(100*digit2[2])+(10*digit2[1])+digit2[0];
  long signed sum=sum1-sum2;
  

  char ones=sum%10;
        sum=sum/10;
  char tens=sum%10;
        sum=sum/10;
 char hun=sum%10;
         sum=sum/10;
  char thous=sum;
   if((sum<0)&&(sum>-999))
  {
      *port_a=0x40;
      *port_l=num[hun];   
      *port_c=num[tens];
      *port_b=num[ones];

  } 
  else{
   
      *port_a=num[thous];
      *port_l=num[hun];   
      *port_c=num[tens];
      *port_b=num[ones];
  }

}
char scan()
{ volatile char *port_f=(char*)0x31;
volatile char *port_k=(char*)0x106;
  while(1)
  {
    for(char row=0;row<4;row++)
    {
      *port_f=1<<row;
      char status=*port_k;
      if(status!=0)
      {
        if((row==0)&&status==1)
           return 1;
        if((row==0)&&status==2)
           return 2;
        if((row==0)&&status==4)
           return 3;
        if((row==1)&&status==1)
           return 4;
        if((row==1)&&status==2)
           return 5;
        if((row==1)&&status==4)
           return 6;
        if((row==2)&&status==1)
           return 7;
          if((row==2)&&status==2)
           return 8;
        if((row==2)&&status==4)
           return 9;
        if((row==3)&&status==2)
           return 0;
        
      }
    }
  }
}