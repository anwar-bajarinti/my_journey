#define F_CPU 16000000UL
#include <avr/io.h>

// PORTA and PORTB
volatile char *ddra  = (char *)0x21;
volatile char *porta = (char *)0x22;
volatile char *ddrb  = (char *)0x24;
volatile char *pinb  = (char *)0x23;
volatile char *portb = (char *)0x25;  // For pull-up

// Timer1 (1 second)
volatile char *tccr1a = (char *)0x80;
volatile char *tccr1b = (char *)0x81;
volatile short *tcnt1 = (short *)0x84;
volatile char *tifr1  = (char *)0x36;

// Timer2 (2 second)
volatile char *tccr2a = (char *)0xB0;
volatile char *tccr2b = (char *)0xB1;
volatile char *tcnt2  = (char *)0xB2;
volatile char *tifr2  = (char *)0x37;

// Timer3 (4 second)
volatile char *tccr3a = (char *)0x90;
volatile char *tccr3b = (char *)0x91;
volatile short *tcnt3 = (short *)0x94;
volatile char *tifr3  = (char *)0x38;

// 1 sec delay using Timer1
void delay_timer1_1sec() {
    *tccr1a = 0x00;
    *tccr1b = (1 << 2) | (1 << 0);  // prescaler = 1024
    *tcnt1 = 49911;                // preload for 1 sec (65536 - 15625)
    while (((*tifr1) & (1 << 0)) == 0);
    *tifr1 |= (1 << 0);
}

// 2 sec delay using Timer2 (8-bit)
void delay_timer2_2sec() {
    *tccr2a = 0x00;
    *tccr2b = (1 << 2) | (1 << 1) | (1 << 0);  // prescaler = 1024
    *tcnt2 = 0;
    unsigned char of_count = 0;
    while (of_count < 122) {
        while (((*tifr2) & (1 << 0)) == 0);
        *tifr2 |= (1 << 0);
        of_count++;
    }
}

// 4 sec delay using Timer3
void delay_timer3_4sec() {
    *tccr3a = 0x00;
    *tccr3b = (1 << 2) | (1 << 0);  // prescaler = 1024
    *tcnt3 = 3036;                 // preload = 65536 - 62500 (4 sec)
    while (((*tifr3) & (1 << 0)) == 0);
    *tifr3 |= (1 << 0);
}

int main() {
    *ddra = 0x07;           // PORTA.0, .1, .2 as output
    *ddrb &= ~(1 << 0);     // PINB0 as input (switch input)
    // No pull-up — you're using external pull-down

    while (1) {
        if (*pinb & (1 << 0)) {
            // Switch Pressed
            delay_timer1_1sec();
            *porta ^= (1 << 0);  // Toggle LED on PA0

            delay_timer2_2sec();
            *porta ^= (1 << 1);  // Toggle LED on PA1

            delay_timer3_4sec();
            *porta ^= (1 << 2);  // Toggle LED on PA2
        } else {
            // Switch Not Pressed
            delay_timer1_1sec();
            *porta ^= (1 << 1);  // Toggle LED on PA1

            delay_timer2_2sec();
            *porta ^= (1 << 0);  // Toggle LED on PA0

            delay_timer3_4sec();
            *porta ^= (1 << 2);  // Toggle LED on PA2
        }
    }
}
