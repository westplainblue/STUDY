#define AD_MUX 758
#define DBG
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>						/*データ送信完了待ちでDelayを利用する*/
#include "UartLib.h"						/*シリアル通信用のヘッダファイル*/

int main(void)
{
	unsigned short brightness;			    /*明るさをいれる変数*/
	
	#ifdef DBG
	uartInit();								/*UARTの初期化*/
	sei();									/*割込み許可*/
	#endif
	
	DDRC &= 0b101111111;				    /*ANOを入力ポートに指定する*/
	PORTD = PIND & 0b11101111;			    /*PD4(LED出力)に'0'を設定する*/
	DDRD |= 0b00010000;					    /*PD0-PD7を出力ポートに指定する*/
	ADCSRA = 0b10000100;				    /*AD変換器をONにする*/
	ADMUX = 0b01000110;
	int i;
	
	while (1) {
		ADCSRA |= 0b01000000;			    /*ADの変換を開始する*/
		while((ADCSRA & 0b01000000) != 0);	/*AD開始フラグがクリアされるのを待つ*/
		brightness = ADC;
		PORTD = PIND | 0b00010000;          /*LEDを点灯させる*/
		for (i = 0;i<(AD_MUX-brightness);i++)
		{
			_delay_us(1);
		}
		PORTD = PIND & 0b11101111;			/*LEDを消灯させる*/
		for (i = 0;i<brightness;i++)
		{
			_delay_us(1);
		}
		#ifdef DBG
		printf("%d\n",(int)brightness);			/*PCにデータを送信させる*/
		#endif
		
	}
	return 0;
}

/************************************************/
/*     TK210466　西原　葵                        */
/************************************************/
