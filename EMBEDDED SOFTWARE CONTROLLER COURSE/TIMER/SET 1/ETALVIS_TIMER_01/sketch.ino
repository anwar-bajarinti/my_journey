#define F_CPU 16000000UL
#include <avr/io.h>

// GPIO Registers
volatile char *ddra  = (char *)0x21;
volatile char *porta = (char *)0x22;
volatile char *ddrb  = (char *)0x24;
volatile char *pinb  = (char *)0x23;

// Timer0 Registers (8-bit)
volatile char *tccr0a = (char *)0x44;
volatile char *tccr0b = (char *)0x45;
volatile char *tcnt0  = (char *)0x46;
volatile char *tifr0  = (char *)0x35;

// Timer2 Registers (8-bit)
volatile char *tccr2a = (char *)0xB0;
volatile char *tccr2b = (char *)0xB1;
volatile char *tcnt2  = (char *)0xB2;
volatile char *tifr2  = (char *)0x37;

// Timer3 Registers (16-bit)
volatile char  *tccr3a = (char *)0x90;
volatile char  *tccr3b = (char *)0x91;
volatile short *tcnt3  = (short *)0x94;
volatile char  *tifr3  = (char *)0x38;

void timer0_init() {
    *tccr0a = 0x00;
    *tccr0b = (1 << 2) | (1 << 0); // Prescaler 1024
    *tcnt0  = 0x00;
}

void wait_n_overflows_timer0(unsigned char n) {
    for (unsigned char i = 0; i < n; i++) {
        while (!(*tifr0 & (1 << 0)));
        *tifr0 |= (1 << 0);
    }
}

void timer2_init() {
    *tccr2a = 0x00;
    *tccr2b = (1 << 2) | (1 << 0); // Prescaler 1024
    *tcnt2  = 0x00;
}

void wait_n_overflows_timer2(unsigned char n) {
    for (unsigned char i = 0; i < n; i++) {
        while (!(*tifr2 & (1 << 0)));
        *tifr2 |= (1 << 0);
    }
}

void timer3_init() {
    *tccr3a = 0x00;
    *tccr3b = (1 << 2) | (1 << 0); // Prescaler 1024
    *tcnt3  = 0x0000;
}

void wait_n_overflows_timer3(unsigned char n) {
    for (unsigned char i = 0; i < n; i++) {
        while (!(*tifr3 & (1 << 1)));  // TOV3 is bit 1
        *tifr3 |= (1 << 1);
    }
}

int main(void) {
    *ddra |= 0x07;       // PA0–PA2 output
    *ddrb &= ~(1 << 0);  // PB0 input

    // Uncomment one of the following:
    // timer0_init();
    // timer2_init();
     timer3_init();

    while (!(*pinb & (1 << 0)));  // Wait for PB0 press

    while (1) {
        // Choose matching delay:
        // wait_n_overflows_timer0(60);
        // wait_n_overflows_timer2(60);
         wait_n_overflows_timer3(1);  // Only 1 needed (16-bit)

        *porta ^= 0x07;  // Toggle PA0–PA2
    }
}
