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

volatile uint16_t overflow2_count = 0;
volatile char indicate = 0;

ISR(TIMER1_OVF_vect) {
    if (indicate == 0)
        *porta ^= (1 << 1);  // PA1
    else
        *porta ^= (1 << 0);  // PA0

    *tcnt1 = 49911;  // reload
}

ISR(TIMER2_OVF_vect) {
    overflow2_count++;
    if (overflow2_count >= 122) {
        if (indicate == 0)
            *porta ^= (1 << 0);
        else
            *porta ^= (1 << 1);

        overflow2_count = 0;
    }
}

void init_timers() {
    *tccr1a = 0x00;
    *tccr1b = (1 << 2) | (1 << 0);  // 1024 prescaler
    *tcnt1  = 49911;
    *timsk1 = (1 << 0);

    *tccr2a = 0x00;
    *tccr2b = (1 << 2) | (1 << 0);
    *tcnt2  = 0;
    *timsk2 = (1 << 0);
}

static char pressed_count = 0;
static char last_state = 0;

int main(void) {
    *ddra = 0x03;  // PA0, PA1 output
    *porta = 0x00;
    *ddrb = 0x00;  // PB0 input

    init_timers();
    sei();

    while (1) {
        char current_state = *pinb & 0x01;
        if (current_state && !last_state) {
            pressed_count++;
        }
        last_state = current_state;

        if (pressed_count >= 5) {
            indicate ^= 1;      // Toggle indicator
            pressed_count = 0;  // Reset press counter
        }

        for (volatile long i = 0; i < 5000; i++);  // Debounce
    }
}
