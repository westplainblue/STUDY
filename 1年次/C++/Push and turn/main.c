#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

typedef unsigned char UCHR;

/*Button 状態*/
#define SW_OFF	0						/*Button OFF状態*/
#define SW_ON	1						/*Button ON状態*/
#define SW_UNKNOWN	2					/*Button 状態不明*/

/*LEDの光の移動間隔*/
#define  DELAY	500						/*LED光の移動までの待ち時間*/

/*関数プロトタイプ宣言*/
char button_chk(void);					/*ボタン状態のチェック関数*/
int dir = -1;
int main(void)
   {
   						
	DDRB |= 0x0F;						/*PB0-PB3を出力に設定する*/
	PORTB = ( PINB & 0xF0) | 0x01;		/*PB0-PB3を初期化する*/
	DDRD &= 0xBF;
	EICRA = 0b00000011;
	EIMSK = 0b00000001;
	sei();						
	
	
    while (1)						    
    {									
		_delay_ms(DELAY);
		cli();
		
		
		if ((PINB & 0b00001001) != 0)	/*点灯しているLEDが端であれば*/
		{
			dir *= -1;					/*方向を反転する*/
		}
		if (dir == 1)					/*方向が正ならPB0-3を左シフトする*/
		{
			PORTB = ((PINB << 1) & 0x0F) | (PINB & 0xF0);	
		}
		else{							/*方向が正でなければPB0-3を右シフトする*/			
			PORTB = ((PINB >> 1) & 0x07) | (PINB & 0xF0);
        }
            sei();
	    }
	}


char button_chk(void){					/*Button 状態取得関数*/
	char ret = SW_UNKNOWN;				/*戻り値に初期値(不明)を入れる*/
	char btn_old;						/*Button 状態保持関数*/
	btn_old = PIND;						/*PORTDのbit6以外をマスクして保持する*/
	_delay_ms(10);						/*10ms待つ*/
	if (((btn_old ^ PIND) & 0b01000000) == 0) /*前回と今回でButtonに変化がない時*/
	{
		ret = (btn_old & 0b01000000) >> 6; /*ButtonのBitをBit0に移動し、戻り値に設定する*/
	}
	return ret;
	}
ISR(INT0_vect){
	if (button_chk() == SW_ON) 
	{
		if ((PINB & 0b00001001) == 0)
		{
			dir *= -1;
		}
	}
	
    }
	
	
/***********************************************************/
/*    TK210466 西原　葵                                     */
/***********************************************************/