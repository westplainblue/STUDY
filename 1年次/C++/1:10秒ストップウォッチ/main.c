#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
typedef unsigned char UCHR;
typedef unsigned char USHRT;

int main(void)
{
   PORTB = PINB & 0b11111100;  /*DIG1,2�̋��ʃA�m�[�h�ɂO���o�͂���*/
   DDRD |= 0b00000011;         /*PB0,1(DIG2,DIG1�̋��ʃA�m�[�h)���o�̓|�[�g�ɐݒ肷��*/
   PORTD = 0xff;               /*�e�Z�O�����g��1���o�͂���*/
   DDRD = 0b11111111;		   /*�e�Z�O�����g�̃|�[�g���o�͂ɐݒ肷��B*/
   DDRD = 0b00000000;		   /*OC1�^�C�}�[�����݂��Pms�ɐݒ肷��B*/
   OCR1A = 16000;			   /*OC1/OC1B��W���|�[�g�ɐݒ肷��B*/
   TCCR1A = 0b00000000;		  /*CTC����,�v���X�P�[��������1/1��ݒ肷��B*/
   TCCR1B = 0b00001001;		  /*OC�T�PA�����݂̃}�X�N��������*/
   TIMSK1 = 0b00000010;		  /*�����ݏ����󂯓���J�n������*/	
   sei();
		
    while (1) ;
	return 0;
   
}

ISR(TIMER1_COMPA_vect){				/*7segLED�W���p�^�[��*/
	static UCHR ptn[11] = { 0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90, 0xff};
	static UCHR disp_cnt = 0;
	static UCHR cnt = 0;
	static UCHR lr_flg = 0;
	int sub;						/*�W���Y��*/


if ( lr_flg == 0){
	sub = disp_cnt / 10;
	if (sub == 0)
	{
		sub = 0;				/*�\���Y���ɂO�������*/
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
			disp_cnt = (disp_cnt + 1) % 50; /*�\���J�E���^�[�X�V*/
		}
	}
	lr_flg ^=1;    /*���E�t���O���X�V*/
}


/*************************************/
/*  TK210466 ������                   */
/*************************************/