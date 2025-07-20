#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL

// GPIO
volatile char *ddra   = (char *)0x21;
volatile char *porta  = (char *)0x22;
volatile char *ddrb   = (char *)0x24;
volatile char *pinb   = (char *)0x23;

// Timer1
volatile char *tccr1a = (char *)0x80;
volatile char *tccr1b = (char *)0x81;
volatile short *tcnt1 = (short *)0x84;
volatile char *timsk1 = (char *)0x6F;

// Timer2
volatile char *tccr2a = (char *)0xB0;
volatile char *tccr2b = (char *)0xB1;
volatile char *tcnt2  = (char *)0xB2;
volatile char *timsk2 = (char *)0x70;

// Overflow counters
volatile uint16_t overflow2_count = 0;
volatile char indicate = 0;

// Timer1 ISR – toggles PA0 or PA1 every 1 sec
ISR(TIMER1_OVF_vect) {
    if (indicate == 0)
        *porta ^= (1 << 1);  // Toggle PA1
    else
        *porta ^= (1 << 0);  // Toggle PA0

    *tcnt1 = 49911;  // Reload for 1s
}

// Timer2 ISR – toggles opposite of above every 2 sec
ISR(TIMER2_OVF_vect) {
    overflow2_count++;
    if (overflow2_count >= 122) {  // ~2 seconds
        if (indicate == 0)
            *porta ^= (1 << 0);  // Toggle PA0
        else
            *porta ^= (1 << 1);  // Toggle PA1

        overflow2_count = 0;
    }
}

void init_timers() {
    // Timer1 – 1s delay
    *tccr1a = 0x00;
    *tccr1b = (1 << 2) | (1 << 0);  // prescaler 1024
    *tcnt1  = 49911;
    *timsk1 = (1 << 0);             // enable overflow

    // Timer2 – 8-bit, 2s delay via overflow count
    *tccr2a = 0x00;
    *tccr2b = (1 << 2) | (1 << 0);
    *tcnt2  = 0;
    *timsk2 = (1 << 0);             // enable overflow
}

int main(void) {
    *ddra = 0x03;   // PA0, PA1 output
    *porta = 0x00;
    *ddrb = 0x00;   // PB0 as input

    init_timers();
    sei();          // Global interrupt enable

    while (1) {
        if (*pinb & (1 << 0)) {
            indicate = 1;  // Swap roles
        } else {
            indicate = 0;
        }
        // Small debounce delay (optional)
        for (volatile long i = 0; i < 10000; i++);
    }
}
