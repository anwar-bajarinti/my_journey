#define F_CPU 16000000UL
#include <avr/io.h>

// PORTA registers
volatile char *ddra  = (char *)0x21;
volatile char *porta = (char *)0x22;

// Timer1
volatile char *tccr1a = (char *)0x80;
volatile char *tccr1b = (char *)0x81;
volatile short *tcnt1 = (short *)0x84;
volatile char *tifr1  = (char *)0x36;

// Timer2
volatile char *tccr2a = (char *)0xB0;
volatile char *tccr2b = (char *)0xB1;
volatile char *tcnt2  = (char *)0xB2;
volatile char *tifr2  = (char *)0x37;

// Timer3
volatile char *tccr3a = (char *)0x90;
volatile char *tccr3b = (char *)0x91;
volatile short *tcnt3 = (short *)0x94;
volatile char *tifr3  = (char *)0x38;

// 1 second delay using Timer1
void delay_timer1_1sec() {
    *tccr1a = 0x00;
    *tccr1b = (1 << 2) | (1 << 0);  // Prescaler 1024
    *tcnt1  = 49911;                // preload for 1 sec
    while (((*tifr1) & (1 << 0)) == 0);
    *tifr1 |= (1 << 0);
}

// 2 second delay using Timer2 (8-bit)
void delay_timer2_2sec() {
    *tccr2a = 0x00;
    *tccr2b = (1 << 2) | (1 << 1) | (1 << 0);  // Prescaler 1024
    *tcnt2 = 0;
    unsigned char of_count = 0;
    while (of_count < 122) {
        while (((*tifr2) & (1 << 0)) == 0);
        *tifr2 |= (1 << 0);
        of_count++;
    }
}

// 4 second delay using Timer3
void delay_timer3_4sec() {
    *tccr3a = 0x00;
    *tccr3b = (1 << 2) | (1 << 0);  // Prescaler 1024
    *tcnt3  = 3036;                 // preload = 65536 - 62500
    while (((*tifr3) & (1 << 0)) == 0);
    *tifr3 |= (1 << 0);
}

int main() {
    *ddra |= (1 << 0) | (1 << 1) | (1 << 2);  // Set PORTA.0, .1, .2 as output

    while (1) {
        delay_timer1_1sec();
        *porta ^= (1 << 0);  // Toggle LED1 every 1s

        delay_timer2_2sec();
        *porta ^= (1 << 1);  // Toggle LED2 every 2s

        delay_timer3_4sec();
        *porta ^= (1 << 2);  // Toggle LED3 every 4s
    }
}
