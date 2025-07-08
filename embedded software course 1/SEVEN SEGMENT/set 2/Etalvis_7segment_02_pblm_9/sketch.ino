void setup() {
  // put your setup code here, to run once:
  volatile char *ddr_a=(char*)0x21;
  *ddr_a=0xFF;

}

void loop() {
  // put your main code here, to run repeatedly:
volatile char *port_a=(char*)0x22;
char letters[] = {
  0x77, // A
  0x7C, // B
  0x39, // C
  0x5E, // D
  0x79, // E
  0x71, // F
  0x3D, // G
  0x76, // H
  0x06, // I
  0x1E, // J
  0x38, // L
  0x3F, // O
  0x73, // P
  0x67, // Q
  0x6D, // S
  0x3E, // U
  0x6E  // Y
};

 for(char i=0;i<17;i++)
 {
  *port_a=~(letters[i]);
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
