#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

char button_chk(void)/*�`���^�����O�h�~�̃v���O���~���O*/
{
	char ret = 2;
	char btn_old = PIND;
	char a;
	_delay_ms(10);
	
	
	if (((btn_old ^ PIND) & 0b01000000) == 0 )/*btn_old��bit6��PIND��bit6�����������̏���*/
	{   a = btn_old & 0b01000000;
	 	ret = a >> 6;
	}
	return ret;
}

int main(void)/*LED�_���̃v���O���~���O*/
{
   PORTD = 0b00000000;
   DDRD = 0b00010000;
    while (1) 
    {
		while(button_chk() == 0);
		PORTD = PIND ^ 0b00010000;
		while(button_chk() != 0);
    }
	return 0;
}

/***********************************/
/*       TK210466 �����@���@�@�@�@�@*/
/***********************************/