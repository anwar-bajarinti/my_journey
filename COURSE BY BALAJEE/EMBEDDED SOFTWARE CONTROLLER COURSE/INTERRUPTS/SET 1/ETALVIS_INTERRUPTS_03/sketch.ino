#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL

// GPIO registers
volatile char *ddra   = (char *)0x21;
volatile char *porta  = (char *)0x22;

// Timer1 registers
volatile char *tccr1a = (char *)0x80;
volatile char *tccr1b = (char *)0x81;
volatile short *tcnt1 = (short *)0x84;
volatile char *timsk1 = (char *)0x6F;

// Timer2 registers (8-bit)
volatile char *tccr2a = (char *)0xB0;
volatile char *tccr2b = (char *)0xB1;
volatile char *tcnt2  = (char *)0xB2;
volatile char *timsk2 = (char *)0x70;

// Timer3 registers (same as Timer1 offsets + 0x10)
volatile char *tccr3a = (char *)0x90;
volatile char *tccr3b = (char *)0x91;
volatile short *tcnt3 = (short *)0x94;
volatile char *timsk3 = (char *)0x71;

// Timer2 overflow count for 2 sec
volatile uint16_t overflow2_count = 0;
// Timer3 overflow count for 4 sec
volatile uint8_t overflow3_count = 0;

// --- Timer1 ISR: 1 second toggle on PA0 ---
ISR(TIMER1_OVF_vect) {
    *porta ^= (1 << 1);        // Toggle PA1
    *tcnt1 = 49911;            // Reload for 1 sec
}

// --- Timer2 ISR: 2 second toggle on PA1 ---
ISR(TIMER2_OVF_vect) {
    overflow2_count++;
    if (overflow2_count >= 122) {  // ~2 sec (122 × 16.384ms)
        *porta ^= (1 << 0);       
        overflow2_count = 0;
    }
}

// --- Timer3 ISR: 4 second toggle on PA2 ---
ISR(TIMER3_OVF_vect) {
    overflow3_count++;
    if (overflow3_count >= 4) {     // 4 × 1 sec = 4 sec
        *porta ^= (1 << 2);         // Toggle PA2
        overflow3_count = 0;
    }
    *tcnt3 = 49911;                 // Reload for 1 sec per overflow
}

int main(void) {
    *ddra = 0x07;       // PA0, PA1, PA2 as output
    *porta = 0x00;

    // --- Timer1 setup ---
    *tccr1a = 0x00;
    *tccr1b = (1 << 2) | (1 << 0);   // Normal mode, prescaler = 1024
    *tcnt1 = 49911;                  // 1 sec
    *timsk1 = (1 << 0);              // Enable Timer1 overflow

    // --- Timer2 setup ---
    *tccr2a = 0x00;
    *tccr2b = (1 << 2) | (1 << 0);   // Normal mode, prescaler = 1024
    *tcnt2 = 0x00;
    *timsk2 = (1 << 0);              // Enable Timer2 overflow

    // --- Timer3 setup ---
    *tccr3a = 0x00;
    *tccr3b = (1 << 2) | (1 << 0);   // Normal mode, prescaler = 1024
    *tcnt3 = 49911;                  // 1 sec preload
    *timsk3 = (1 << 0);              // Enable Timer3 overflow

    sei(); // Enable global interrupts

    while (1); // Infinite loop
}
