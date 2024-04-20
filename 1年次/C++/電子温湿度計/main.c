/*******************************************/
/*         TK210466 西原　葵                */
/*******************************************/
#include "common.h"
#include "lcd.h"                  /*LCD表示ヘッダーファイル*/
#include "dht11_read.h"


char bin2ASC( char data);			/*4bit16進データをASC11コード変換関数*/


int main()
{
    UCHR thbuff[5];					/*温湿度データ受信*/
	char dispBuff[16]="                ";
	int i;							/*ループ変数*/
	int digit;
	
	DDRD |= 0b00010000;
	PORTD = PIND & 0b11101111;		/*LED消灯*/
	lcd_init();						/*LED初期化*/
	sei();
	_delay_ms(2000);
	
    while (1)						/*無限Loop*/
    {
		if (dht11_read(&thbuff[0]) == 1)
		{
			PORTD = PIND | 0b00010000;
		}else{
			PORTD = PIND & 0b11101111;/*LEDを消灯*/
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
		_delay_ms(2000);			/*2秒毎表示*/
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

