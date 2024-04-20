#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

typedef unsigned char UCHR;

/*Button ���*/
#define SW_OFF	0						/*Button OFF���*/
#define SW_ON	1						/*Button ON���*/
#define SW_UNKNOWN	2					/*Button ��ԕs��*/

/*LED�̌��̈ړ��Ԋu*/
#define  DELAY	500						/*LED���̈ړ��܂ł̑҂�����*/

/*�֐��v���g�^�C�v�錾*/
char button_chk(void);					/*�{�^����Ԃ̃`�F�b�N�֐�*/
int dir = -1;
int main(void)
   {
   						
	DDRB |= 0x0F;						/*PB0-PB3���o�͂ɐݒ肷��*/
	PORTB = ( PINB & 0xF0) | 0x01;		/*PB0-PB3������������*/
	DDRD &= 0xBF;
	EICRA = 0b00000011;
	EIMSK = 0b00000001;
	sei();						
	
	
    while (1)						    
    {									
		_delay_ms(DELAY);
		cli();
		
		
		if ((PINB & 0b00001001) != 0)	/*�_�����Ă���LED���[�ł����*/
		{
			dir *= -1;					/*�����𔽓]����*/
		}
		if (dir == 1)					/*���������Ȃ�PB0-3�����V�t�g����*/
		{
			PORTB = ((PINB << 1) & 0x0F) | (PINB & 0xF0);	
		}
		else{							/*���������łȂ����PB0-3���E�V�t�g����*/			
			PORTB = ((PINB >> 1) & 0x07) | (PINB & 0xF0);
        }
            sei();
	    }
	}


char button_chk(void){					/*Button ��Ԏ擾�֐�*/
	char ret = SW_UNKNOWN;				/*�߂�l�ɏ����l(�s��)������*/
	char btn_old;						/*Button ��ԕێ��֐�*/
	btn_old = PIND;						/*PORTD��bit6�ȊO���}�X�N���ĕێ�����*/
	_delay_ms(10);						/*10ms�҂�*/
	if (((btn_old ^ PIND) & 0b01000000) == 0) /*�O��ƍ����Button�ɕω����Ȃ���*/
	{
		ret = (btn_old & 0b01000000) >> 6; /*Button��Bit��Bit0�Ɉړ����A�߂�l�ɐݒ肷��*/
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
/*    TK210466 �����@��                                     */
/***********************************************************/