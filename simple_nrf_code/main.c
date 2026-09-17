#define P0_OUT               (*(volatile unsigned int *)0x50000504)
#define P0_DIRSET            (*(volatile unsigned int *)0x50000518)

#define TIMER0_TASKS_START   (*(volatile unsigned int *)0x40008000)
#define TIMER0_TASKS_STOP    (*(volatile unsigned int *)0x40008004)
#define TIMER0_TASKS_CLEAR   (*(volatile unsigned int *)0x4000800C)
#define TIMER0_EVENTS_COMP0  (*(volatile unsigned int *)0x40008140)
#define TIMER0_BITMODE       (*(volatile unsigned int *)0x40008508)
#define TIMER0_PRESCALER     (*(volatile unsigned int *)0x40008510)
#define TIMER0_CC0           (*(volatile unsigned int *)0x40008540)

#define PIN_13               (1 << 13)

static void delay_half_sec(void) {
    TIMER0_TASKS_STOP = 1;
    TIMER0_BITMODE = 3;          // 32-bit counter mode
    TIMER0_PRESCALER = 4;        // 16 MHz / 2^4 = 1 MHz (1 us per tick)
    TIMER0_CC0 = 500000;         // 500,000 us = 0.5 seconds
    TIMER0_EVENTS_COMP0 = 0;     // Clear previous event flag
    TIMER0_TASKS_CLEAR = 1;      // Reset counter to 0
    TIMER0_TASKS_START = 1;      // Start counting

    // Spin until TIMER0 matches CC0
    while (TIMER0_EVENTS_COMP0 == 0);

    TIMER0_TASKS_STOP = 1;
}

int main(void) {
    P0_DIRSET = PIN_13;

    while (1) {
        P0_OUT ^= PIN_13;
        delay_half_sec();
    }
}