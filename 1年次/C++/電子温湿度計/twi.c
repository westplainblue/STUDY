/****************************************************************************************************/
/*		I2C�ʐM�p���C�u����	�F	twi.c																*/
/*																									*/
/*�@�{�t�@�C����Atmega328P�ɂ�I2C�ʐM���C�u�������g�p����ۂɎg�p���邱�ƁD								*/
/*  ���̍ۂɁCtwi.h�t�@�C���𓯎���Build����K�v������D												*/
/*�@�{I2C�ʐM���C�u�����́CAtmega328 CPU��SCL�y��SDA�[�q��I2C�f�o�C�X���ڑ�����Ă��鎖��z�肵�Ă���D	*/
/*�@�f�o�C�X�ɃR�}���h���M���I2C�̏�Ԃ��z��ʂ�ɂȂ�Ȃ��ꍇ�́C�G���[�֐����`���Ă��邪�C�G���[������	*/
/*�@�̏����͒�`���Ă��Ȃ��D�i���̏�Ŗ���Loop�j														*/
/*�@twi_error�֐��ɃG���[�R�[�h��n����悤�ɂȂ��Ă��邽�߁C�K�X�K�v�ȏ������L�q���邱�ƁD					*/
/*																									*/
/*	�ύX����																							*/
/*�@���ʎq	���t			����					�ύX���e													*/
/*�@#000		2021.07.26	�r�� ����			���Ń����[�X												*/
/****************************************************************************************************/
#define 	F_CPU 16000000UL							/* CPU Clock ��`�i16 MHz�j					*/
#include 	<avr/io.h>									/* Atmega328P I/O ��`�w�b�_�t�@�C��			*/
#include	<util/delay.h>								/* Delay �֘A���C�u�����w�b�_�t�@�C��			*/
#include	<stdio.h>									/* �W��I/O ���C�u�����w�b�_�t�@�C��			*/
typedef		unsigned char UCHR;							/* UCHR �^��`								*/

/* ��Ԓl��`																						*/
#define	START		0x08								/* �X�^�[�g��Ԓl								*/
#define	MT_SLA_ACK	0x18								/* �A�h���X:SLA_W�𐳏푗�M�`�F�b�N�l			*/
#define	MT_DATA_ACK	0x28								/* �f�[�^�𐳏푗�M�`�F�b�N�l					*/

/* �v���g�^�C�v�錾																					*/
void	twi_init(void);									/* TWI �������֐�							*/
void	twi_start(UCHR slave_address);					/* TWI �ʐM�J�n								*/
void	twi_send(UCHR twi_data);						/* TWI �f�[�^���M							*/
void	twi_stop(void);									/* TWI �f�[�^���M�I��							*/
UCHR twi_rcv(UCHR *data, UCHR length);					/* TWI �f�[�^��M							*/

void twi_error(int cd){
	while(1){
	/*	twi�G���[�̎��̏����i�Ⴆ��LED�̓_�œ��j�̏���������											*/
	}
}

void twi_init(){
	/* �]�����g���ݒ�					�@						������F1/1����
														�]�����g���F16MHz/(16 + 2*12/1) = 400KHz		*/
	TWBR = 12;											/* �J�E���g�l�F12								*/
	TWSR = 0x00;										/* ������F1/1����							*/
	TWCR = 1<< TWEN;
}

void twi_start(UCHR slave_address){						/* I2C�ʐM�J�n(start ���/�X���[�u�A�h���X/RW)	*/
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);			/* start ��ԑ��M							*/
	while( !( TWCR & (1<<TWINT) ) );					/* Start ��ԑ��M�����҂�						*/
	if( (TWSR & 0xF8 ) != START ){						/* Start ��ԂɂȂ�Ȃ���						*/
		twi_error(2);									/* �G���[����								*/
	}
	TWDR=slave_address;									/* TWDR��slave address + Write ����������		*/
	TWCR = ( 1<<TWINT )| ( 1<<TWEN ) | ( 1<<TWEA);					/* TWINT������								*/
	while(  ! ( TWCR & ( 1<<TWINT ) ) );				/* TWINT��1�ɂȂ�܂őҋ@						*/
	if((TWSR & 0xF8 ) != MT_SLA_ACK){					/* ACK�����Ȃ���								*/
		twi_error(3);									/* �G���[����								*/
	}
}

void twi_send(UCHR twi_data){							/* �f�[�^1�o�C�g���M							*/
	TWDR = twi_data;									/* TWDR�ɑ��M�f�[�^����������					*/
	TWCR = ( 1<<TWINT )| ( 1<<TWEN ) | ( 1<<TWEA);		/* TWINT������								*/
	while(  ! ( TWCR & ( 1<<TWINT ) ) );				/* TWINT��1�ɂȂ�܂őҋ@						*/
	if(  ( TWSR & 0xF8 ) != MT_DATA_ACK ){				/* ACK�����Ȃ��Ƃ�							*/
		twi_error(1);									/* �G���[����								*/
	}
}

void twi_stop(void){									/* I2C�ʐM�I��								*/
	TWCR = ( 1<<TWINT )| ( 1<<TWSTO )| ( 1<<TWEN );		/* I2C��~�������ݒ�						*/
}
/****************************************************/
/*          TK210466  �����@���@�@�@�@�@�@�@�@�@�@�@�@*/
/***************************************************/



/****************************************************************/
/*I2C�ʐM�f�[�^��M												*/
/*�߂�l�F�f�[�^��M�������������ǂ���								*/
/* 0�F���M���s													*/
/* 1�F���M����													*/
/*                                                              */
/*�����F															*/
/* data�F��M�����f�[�^���i�[����ϐ��̐擪�A�h���X					*/
/* dataSize�F��M����f�[�^�̐�									*/
/****************************************************************/

UCHR twi_rcv(UCHR *data, UCHR length){
	UCHR state[2] = {0x50, 0x58};						/* I2C slave �̃��^�[���R�[�h					*/
	UCHR ack_cd[2] = {(1 << TWINT) | (1 << TWEA) | (1 << TWEN),(1 << TWINT) | (1 << TWEN)};/* ACK�L��*/
	UCHR	ret = 1;									/* �߂�l�i0:���s/1:�����j					*/
	for(; length > 0; length--, data++){				/* �w��̃o�C�g�������J��Ԃ�					*/
		TWCR = ack_cd[length==1];						/* �f�[�^��M�J�n(�Ō�̃f�[�^���ǂ����Œl�ύX	*/
		while( !(TWCR & (1 << TWINT)) );				/* �f�[�^�̎�M�҂�							*/
		if((TWSR & 0xF8) != state[length==1]) {			/* ��M�������`�F�b�N							*/
			ret = 0;									/* ���s�Ȃ�߂�l�����s�ɐݒ肵�����𔲂���		*/
			break;
		}
		*data = TWDR;									/* ��M�f�[�^�̕ۑ�							*/
	}
	return ret;
}
