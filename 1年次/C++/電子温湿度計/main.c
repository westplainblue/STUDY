/*******************************************/
/*         TK210466 �����@��                */
/*******************************************/
#include "common.h"
#include "lcd.h"                  /*LCD�\���w�b�_�[�t�@�C��*/
#include "dht11_read.h"


char bin2ASC( char data);			/*4bit16�i�f�[�^��ASC11�R�[�h�ϊ��֐�*/


int main()
{
    UCHR thbuff[5];					/*�����x�f�[�^��M*/
	char dispBuff[16]="                ";
	int i;							/*���[�v�ϐ�*/
	int digit;
	
	DDRD |= 0b00010000;
	PORTD = PIND & 0b11101111;		/*LED����*/
	lcd_init();						/*LED������*/
	sei();
	_delay_ms(2000);
	
    while (1)						/*����Loop*/
    {
		if (dht11_read(&thbuff[0]) == 1)
		{
			PORTD = PIND | 0b00010000;
		}else{
			PORTD = PIND & 0b11101111;/*LED������*/
		}
		digit = 0;
		for ( i=0; i< 5; i++)
		{
			dispBuff[digit]=bin2ASC(thbuff[i]>>4);
			digit++;
			dispBuff[digit]=bin2ASC(thbuff[i]&0x0f);
			digit += 2;
		}
		lcd_print(0,0,&dispBuff[0]);
		lcd_flip();
		_delay_ms(2000);			/*2�b���\��*/
    }
	return 0;
}


char bin2ASC( char data){
	char retData;
	if ( data < 0x0A)
	{
		retData = data | 0x30;
	}else{
		retData = data + 'A' - 0x0A;
	}
	return retData;
}

