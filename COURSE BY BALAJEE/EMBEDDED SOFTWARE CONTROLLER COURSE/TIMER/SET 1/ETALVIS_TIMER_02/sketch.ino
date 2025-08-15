#define F_CPU 16000000UL
#include <avr/io.h>

// Define register addresses
volatile char *ddra  = (char *)0x21;
volatile char *porta = (char *)0x22;

volatile char *tccr1a = (char *)0x80;
volatile char *tccr1b = (char *)0x81;
volatile short *tcnt1 = (short *)0x84;
volatile char *tifr1  = (char *)0x36;

volatile char *tccr2a = (char *)0xB0;
volatile char *tccr2b = (char *)0xB1;
volatile char *tcnt2  = (char *)0xB2;
volatile char *tifr2  = (char *)0x37;

void delay_timer1_1sec() {
    *tccr1a = 0x00;
    *tccr1b = (1 << 2) | (1 << 0);  // Prescaler 1024

    *tcnt1 = 49911; // preload = 65536 - 15625 for 1 sec

    while (((*tifr1) & (1 << 0)) == 0);  // Wait for TOV1
    *tifr1 |= (1 << 0);                 // Clear TOV1
}

void delay_timer2_2sec() {
    *tccr2a = 0x00;
    *tccr2b = (1 << 2) | (1 << 1) | (1 << 0);  // Prescaler 1024

    *tcnt2 = 0;  // Start from 0
    unsigned char overflows = 0;

    while (overflows < 122) {
        while (((*tifr2) & (1 << 0)) == 0);  // Wait for TOV2
        *tifr2 |= (1 << 0);  // Clear TOV2
        overflows++;
    }
}

int main() {
    *ddra |= (1 << 0) | (1 << 1);  // Set PORTA.0 and PORTA.1 as output

    while (1) {
        delay_timer1_1sec();
        *porta ^= (1 << 0);  // Toggle LED1

        delay_timer2_2sec();
        *porta ^= (1 << 1);  // Toggle LED2
    }
}
