
/************************************************************************/
/*   TK210466       êºå¥à®                                               */
/************************************************************************/
#include <avr/io.h>

LED *led1;

int main(void)
{
	LED l1;
	led1 = &11;
	Potentiometer p1(0x40);
    while (1) 
    {
		if ( p1.getHL(0xC0))
		{
			l1.setLedLevel( 3);
		}else{
			l1.setLedLevel( 0);
		}
		_delay_ms(200);
    }
}

