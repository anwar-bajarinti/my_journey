#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL

// GPIO registers
volatile char *ddra   = (char *)0x21;
volatile char *porta  = (char *)0x22;

// Timer1 registers (16-bit)
volatile char *tccr1a = (char *)0x80;
volatile char *tccr1b = (char *)0x81;
volatile short *tcnt1 = (short *)0x84;
volatile char *timsk1 = (char *)0x6F;

// Timer2 registers (8-bit)
volatile char *tccr2a = (char *)0xB0;
volatile char *tccr2b = (char *)0xB1;
volatile char *tcnt2  = (char *)0xB2;
volatile char *timsk2 = (char *)0x70;

// --- Timer1: 1 sec toggle on PA0 ---
// Prescaler = 1024 --> 16MHz / 1024 = 15625 ticks/sec
// For 1 second delay, we need 65536 - 15625 = 49911 preload
ISR(TIMER1_OVF_vect) {
    *porta ^= (1 << 1);       // Toggle PA0
    *tcnt1 = 49911;           // Reload for 1 sec
}

// --- Timer2: 2 sec toggle on PA1 ---
// Timer2 is 8-bit, so we count overflows
volatile uint16_t overflow2_count = 0;

ISR(TIMER2_OVF_vect) {
    overflow2_count++;
    if (overflow2_count >= 122) {  // 122 overflows × 16.384ms ≈ 2 seconds
        *porta ^= (1 << 0);        // Toggle PA1
        overflow2_count = 0;
    }
}

int main(void) {
    *ddra = 0x03;     // PA0 and PA1 as output
    *porta = 0x00;

    // Timer1 setup (for 1 second)
    *tccr1a = 0x00;
    *tccr1b = (1 << 2) | (1 << 0);   // CTC off, prescaler = 1024
    *tcnt1 = 49911;                  // Preload for 1 sec

    *timsk1 = (1 << 0);              // Enable Timer1 overflow interrupt

    // Timer2 setup (for 2 seconds)
    *tccr2a = 0x00;
    *tccr2b = (1 << 2) | (1 << 0);   // Normal mode, prescaler = 1024
    *tcnt2 = 0x00;                   // Start from 0

    *timsk2 = (1 << 0);              // Enable Timer2 overflow interrupt

    sei(); // Enable global interrupts

    while (1); // Infinite loop
}
