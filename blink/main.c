// main.c
// 
// A simple blinky program for ATtiny85 (Digispark clone)
// Led connected on PB1
//

#include <avr/io.h>
#include <util/delay.h>
 
int main (void)
{
    // set PB1 to be output
    DDRB |= (1 << PB1);
    while (1) {
      
      // flash #1
      // set PB1 high
      PORTB |= (1 << PB1);
      _delay_ms(200);
      // set PB1 low
      PORTB = 0b00000000;
      PORTB &= ~(1 << PB1);
      _delay_ms(200);
  
      // flash #2
      // set PB1 high
      PORTB |= (1 << PB1);
      _delay_ms(1000);
      // set PB1 low
      PORTB &= ~(1 << PB1);
      _delay_ms(1000);
    }
 
  return 1; // Never reach under normal execution
}
