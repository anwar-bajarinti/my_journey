void setup() {
  // put your setup code here, to run once:
  volatile char *ddr_a=(char*)0x21;
  *ddr_a=0xFF;

}

void loop() {
  // put your main code here, to run repeatedly:
volatile char *port_a=(char*)0x22;
char num[]={0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10};

for(char i=1;i<10;i+=2)
 {
  *port_a=(num[i]);
  delay_();
 }
 
}
void delay_() {
  volatile long  dummy=0;
  for ( long i = 0; i < 150; i++) {
    for (long  j = 0; j < 4000; j++) {
      dummy++; 
    }
  }
}
