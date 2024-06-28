#include <avr/io.h>
#include <util/delay.h>
#include <util/delay.h>
 
#define F_CPU 1000000UL
#define BAUD 11500
#define MYUBRR F_CPU/1/BAUD-1
 
void uart_init(unsigned int ubrr) {
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    UCSR0B = (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}
 
void uart_transmit(unsigned char data) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}
 
void uart_print(const char *str) {
    while (*str) {
        uart_transmit(*str++);
    }
}
 
int main(void) {
    uart_init(MYUBRR);
    DDRB &= ~(1 << "PB7");
    PORTB |= (1 << "PB7");
 
    DDRB &= ~(1 << "PB8");
    PORTB |= (1 << "PB8");
 
    while (1) {

        if (!(PINB & (1 << "PB7"))) {
            uart_print("6");
            _delay_ms(200);
        }
 
        if (!(PINB & (1 << "PB8"))) {
            uart_print("WSAD");
            _delay_ms(200);
        }
 
    }
 
    return 0;
};
