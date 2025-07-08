void setup() {
  // put your setup code here, to run once:
  volatile char *ddr_a=(char*)0x21;
  *ddr_a=0xFF;

}

void loop() {
  // put your main code here, to run repeatedly:
volatile char *port_a=(char*)0x22;
char num[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

for(char i=0;i<10;i++)
 {
  *port_a=num[i];
  delay_();
 }
}
void delay_() {
  volatile long  dummy=0;
  for ( long i = 0; i < 1000; i++) {
    for (long  j = 0; j < 4000; j++) {
      dummy++; 
    }
  }
}
