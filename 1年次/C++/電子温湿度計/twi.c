/****************************************************************************************************/
/*		I2C通信用ライブラリ	：	twi.c																*/
/*																									*/
/*　本ファイルはAtmega328PにてI2C通信ライブラリを使用する際に使用すること．								*/
/*  その際に，twi.hファイルを同時にBuildする必要がある．												*/
/*　本I2C通信ライブラリは，Atmega328 CPUのSCL及びSDA端子にI2Cデバイスが接続されている事を想定している．	*/
/*　デバイスにコマンド送信後にI2Cの状態が想定通りにならない場合は，エラー関数を定義しているが，エラー発生時	*/
/*　の処理は定義していない．（その場で無限Loop）														*/
/*　twi_error関数にエラーコードを渡せるようになっているため，適宜必要な処理を記述すること．					*/
/*																									*/
/*	変更履歴																							*/
/*　識別子	日付			氏名					変更内容													*/
/*　#000		2021.07.26	荒金 匡徳			初版リリース												*/
/****************************************************************************************************/
#define 	F_CPU 16000000UL							/* CPU Clock 定義（16 MHz）					*/
#include 	<avr/io.h>									/* Atmega328P I/O 定義ヘッダファイル			*/
#include	<util/delay.h>								/* Delay 関連ライブラリヘッダファイル			*/
#include	<stdio.h>									/* 標準I/O ライブラリヘッダファイル			*/
typedef		unsigned char UCHR;							/* UCHR 型定義								*/

/* 状態値定義																						*/
#define	START		0x08								/* スタート状態値								*/
#define	MT_SLA_ACK	0x18								/* アドレス:SLA_Wを正常送信チェック値			*/
#define	MT_DATA_ACK	0x28								/* データを正常送信チェック値					*/

/* プロトタイプ宣言																					*/
void	twi_init(void);									/* TWI 初期化関数							*/
void	twi_start(UCHR slave_address);					/* TWI 通信開始								*/
void	twi_send(UCHR twi_data);						/* TWI データ送信							*/
void	twi_stop(void);									/* TWI データ送信終了							*/
UCHR twi_rcv(UCHR *data, UCHR length);					/* TWI データ受信							*/

void twi_error(int cd){
	while(1){
	/*	twiエラーの時の処理（例えばLEDの点滅等）の処理を入れる											*/
	}
}

void twi_init(){
	/* 転送周波数設定					　						分周比：1/1分周
														転送周波数：16MHz/(16 + 2*12/1) = 400KHz		*/
	TWBR = 12;											/* カウント値：12								*/
	TWSR = 0x00;										/* 分周比：1/1分周							*/
	TWCR = 1<< TWEN;
}

void twi_start(UCHR slave_address){						/* I2C通信開始(start 状態/スレーブアドレス/RW)	*/
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);			/* start 状態送信							*/
	while( !( TWCR & (1<<TWINT) ) );					/* Start 状態送信完了待ち						*/
	if( (TWSR & 0xF8 ) != START ){						/* Start 状態にならない時						*/
		twi_error(2);									/* エラー処理								*/
	}
	TWDR=slave_address;									/* TWDRにslave address + Write を書き込み		*/
	TWCR = ( 1<<TWINT )| ( 1<<TWEN ) | ( 1<<TWEA);					/* TWINTを解除								*/
	while(  ! ( TWCR & ( 1<<TWINT ) ) );				/* TWINTが1になるまで待機						*/
	if((TWSR & 0xF8 ) != MT_SLA_ACK){					/* ACKが来ない時								*/
		twi_error(3);									/* エラー処理								*/
	}
}

void twi_send(UCHR twi_data){							/* データ1バイト送信							*/
	TWDR = twi_data;									/* TWDRに送信データを書き込み					*/
	TWCR = ( 1<<TWINT )| ( 1<<TWEN ) | ( 1<<TWEA);		/* TWINTを解除								*/
	while(  ! ( TWCR & ( 1<<TWINT ) ) );				/* TWINTが1になるまで待機						*/
	if(  ( TWSR & 0xF8 ) != MT_DATA_ACK ){				/* ACKが来ないとき							*/
		twi_error(1);									/* エラー処理								*/
	}
}

void twi_stop(void){									/* I2C通信終了								*/
	TWCR = ( 1<<TWINT )| ( 1<<TWSTO )| ( 1<<TWEN );		/* I2C停止条件許可設定						*/
}
/****************************************************/
/*          TK210466  西原　葵　　　　　　　　　　　　*/
/***************************************************/



/****************************************************************/
/*I2C通信データ受信												*/
/*戻り値：データ受信が成功したかどうか								*/
/* 0：送信失敗													*/
/* 1：送信成功													*/
/*                                                              */
/*引数：															*/
/* data：受信したデータを格納する変数の先頭アドレス					*/
/* dataSize：受信するデータの数									*/
/****************************************************************/

UCHR twi_rcv(UCHR *data, UCHR length){
	UCHR state[2] = {0x50, 0x58};						/* I2C slave のリターンコード					*/
	UCHR ack_cd[2] = {(1 << TWINT) | (1 << TWEA) | (1 << TWEN),(1 << TWINT) | (1 << TWEN)};/* ACK有無*/
	UCHR	ret = 1;									/* 戻り値（0:失敗/1:成功）					*/
	for(; length > 0; length--, data++){				/* 指定のバイト数だけ繰り返す					*/
		TWCR = ack_cd[length==1];						/* データ受信開始(最後のデータかどうかで値変更	*/
		while( !(TWCR & (1 << TWINT)) );				/* データの受信待ち							*/
		if((TWSR & 0xF8) != state[length==1]) {			/* 受信成功かチェック							*/
			ret = 0;									/* 失敗なら戻り値を失敗に設定し処理を抜ける		*/
			break;
		}
		*data = TWDR;									/* 受信データの保存							*/
	}
	return ret;
}
