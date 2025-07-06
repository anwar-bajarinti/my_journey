void setup() {
  // put your setup code here, to run once:
  volatile char *ddr_a=(char*)0x21;
  *ddr_a=0xff;
  volatile char *ddr_b=(char*)0x24;
  *ddr_b=0xff;

}

void loop() {
  // put your main code here, to run repeatedly:
  volatile char *port_a=(char*)0x22;
  volatile char *port_b=(char*)0x25;
  while(1){
  *port_a=0xff;
  *port_b=0;
  delay_1_sec();
  *port_b=0xff;
  *port_a=0;
  delay_1_sec();
  }
}
void delay_1_sec() {
  for (unsigned int i = 0; i < 1000; i++) {
    for (unsigned int j = 0; j < 4000; j++) {
      asm volatile("nop");
    }
  }
}

