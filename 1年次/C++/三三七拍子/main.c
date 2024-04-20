#define		F_CPU	16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	PORTD = 0b00000000;
	DDRD |= 0b00010000;
	while (1)
	{
		/*3*/
		PORTD = PIND ^ 0b00010000;/*1*/
		_delay_ms(200);
		PORTD = PIND ^ 0b00010000;
		_delay_ms(200);
		PORTD = PIND ^ 0b00010000;/*2*/
		_delay_ms(200);
		PORTD = PIND ^ 0b00010000;
		_delay_ms(200);
		PORTD = PIND ^ 0b00010000;/*3*/
		_delay_ms(200);
		PORTD = PIND ^ 0b00010000;
		_delay_ms(600);
		/*3*/
		PORTD = PIND ^ 0b00010000;/*1*/
		_delay_ms(200);
		PORTD = PIND ^ 0b00010000;
		_delay_ms(200);
		PORTD = PIND ^ 0b00010000;/*2*/
		_delay_ms(200);
		PORTD = PIND ^ 0b00010000;
		_delay_ms(200);
		PORTD = PIND ^ 0b00010000;/*3*/
		_delay_ms(200);
		PORTD = PIND ^ 0b00010000;
		_delay_ms(600);
		/*7*/
		PORTD = PIND ^ 0b00010000;/*1*/
		_delay_ms(200);
		PORTD = PIND ^ 0b00010000;
		_delay_ms(200);
		PORTD = PIND ^ 0b00010000;/*2*/
		_delay_ms(200);
		PORTD = PIND ^ 0b00010000;
		_delay_ms(200);
		PORTD = PIND ^ 0b00010000;/*3*/
		_delay_ms(200);
		PORTD = PIND ^ 0b00010000;
		_delay_ms(200);
		PORTD = PIND ^ 0b00010000;/*4*/
		_delay_ms(200);
		PORTD = PIND ^ 0b00010000;
		_delay_ms(200);
		PORTD = PIND ^ 0b00010000;/*5*/
		_delay_ms(200);
		PORTD = PIND ^ 0b00010000;
		_delay_ms(200);
		PORTD = PIND ^ 0b00010000;/*6*/
		_delay_ms(200);
		PORTD = PIND ^ 0b00010000;
		_delay_ms(200);
		PORTD = PIND ^ 0b00010000;/*7*/
		_delay_ms(200);
		PORTD = PIND ^ 0b00010000;
		_delay_ms(600);
	}
	return 0;
}

