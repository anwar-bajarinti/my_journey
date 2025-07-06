

void setup() {
  // put your setup code here, to run once:
volatile char *DDR_j;
DDR_j=(volatile char*)0x104;
*DDR_j=0xFF;
}

void loop() {
  // put your main code here, to run repeatedly:
volatile char *PORT_J;
PORT_J=(volatile char*)0x105;
*PORT_J=1;
}
