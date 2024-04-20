#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
typedef unsigned char UCHR;
typedef unsigned char USHRT;

int main(void)
{
   PORTB = PINB & 0b11111100;  /*DIG1,2の共通アノードに０を出力する*/
   DDRD |= 0b00000011;         /*PB0,1(DIG2,DIG1の共通アノード)を出力ポートに設定する*/
   PORTD = 0xff;               /*各セグメントに1を出力する*/
   DDRD = 0b11111111;		   /*各セグメントのポートを出力に設定する。*/
   DDRD = 0b00000000;		   /*OC1タイマー割込みを１msに設定する。*/
   OCR1A = 16000;			   /*OC1/OC1Bを標準ポートに設定する。*/
   TCCR1A = 0b00000000;		  /*CTC動作,プリスケーラ分周比1/1を設定する。*/
   TCCR1B = 0b00001001;		  /*OCⅠ１A割込みのマスク解除する*/
   TIMSK1 = 0b00000010;		  /*割込み処理受け入れ開始をする*/	
   sei();
		
    while (1) ;
	return 0;
   
}

ISR(TIMER1_COMPA_vect){				/*7segLED標準パターン*/
	static UCHR ptn[11] = { 0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90, 0xff};
	static UCHR disp_cnt = 0;
	static UCHR cnt = 0;
	static UCHR lr_flg = 0;
	int sub;						/*標準添字*/


if ( lr_flg == 0){
	sub = disp_cnt / 10;
	if (sub == 0)
	{
		sub = 0;				/*表示添字に０をいれる*/
	}
	PORTB = ( PINB & 0b11111100) | 0b00000010;
	PORTD = ptn[sub];				
	cnt = (cnt+1) % 100;
    }else{
		sub == disp_cnt % 10;
		PORTB = (PINB & 0b11111100) | 0b00000010;
		PORTD = ptn[sub];
		cnt = ( cnt+1) % 100;
		if(cnt == 0){
			disp_cnt = (disp_cnt + 1) % 50; /*表示カウンター更新*/
		}
	}
	lr_flg ^=1;    /*左右フラグを更新*/
}


/*************************************/
/*  TK210466 西原葵                   */
/*************************************/