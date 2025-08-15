void setup() {
  // put your setup code here, to run once:
  volatile char *ddr_a=(char*)0x21;
  *ddr_a=0xFF;

}

void loop() {
  // put your main code here, to run repeatedly:
volatile char *port_a=(char*)0x22;
char letters[] = {0xF9,0xB0,0x92,0xF8};

 for(char i=0;i<4;i++)
 {
  *port_a=(letters[i]);
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
