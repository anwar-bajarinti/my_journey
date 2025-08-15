#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL

volatile char *ddra   = (char *)0x21;
volatile char *porta  = (char *)0x22;

volatile char *tccr1a = (char *)0x80;
volatile char *tccr1b = (char *)0x81;
volatile short *tcnt1 = (short *)0x84;
volatile char *timsk1 = (char *)0x6F;

ISR(TIMER1_OVF_vect) {     // This will be automatically mapped to __vector_11
    *porta ^= (1 << 0);    // Toggle PA0
    *tcnt1 = 49911;        // Reload
}

int main(void) {
    *ddra = 0x01;
    *porta = 0x00;

    *tccr1a = 0x00;
    *tccr1b = (1 << 2) | (1 << 0);   // Prescaler 1024
    *tcnt1 = 49911;

    *timsk1 = (1 << 0);   // Enable Timer1 overflow interrupt

    sei();                // Enable global interrupts using standard macro

    while (1);
}
