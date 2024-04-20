#define AD_MUX 758
#define DBG
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>						/*�f�[�^���M�����҂���Delay�𗘗p����*/
#include "UartLib.h"						/*�V���A���ʐM�p�̃w�b�_�t�@�C��*/

int main(void)
{
	unsigned short brightness;			    /*���邳�������ϐ�*/
	
	#ifdef DBG
	uartInit();								/*UART�̏�����*/
	sei();									/*�����݋���*/
	#endif
	
	DDRC &= 0b101111111;				    /*ANO����̓|�[�g�Ɏw�肷��*/
	PORTD = PIND & 0b11101111;			    /*PD4(LED�o��)��'0'��ݒ肷��*/
	DDRD |= 0b00010000;					    /*PD0-PD7���o�̓|�[�g�Ɏw�肷��*/
	ADCSRA = 0b10000100;				    /*AD�ϊ����ON�ɂ���*/
	ADMUX = 0b01000110;
	int i;
	
	while (1) {
		ADCSRA |= 0b01000000;			    /*AD�̕ϊ����J�n����*/
		while((ADCSRA & 0b01000000) != 0);	/*AD�J�n�t���O���N���A�����̂�҂�*/
		brightness = ADC;
		PORTD = PIND | 0b00010000;          /*LED��_��������*/
		for (i = 0;i<(AD_MUX-brightness);i++)
		{
			_delay_us(1);
		}
		PORTD = PIND & 0b11101111;			/*LED������������*/
		for (i = 0;i<brightness;i++)
		{
			_delay_us(1);
		}
		#ifdef DBG
		printf("%d\n",(int)brightness);			/*PC�Ƀf�[�^�𑗐M������*/
		#endif
		
	}
	return 0;
}

/************************************************/
/*     TK210466�@�����@��                        */
/************************************************/
