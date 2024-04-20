/*****************************************/
/* TK210466 　　西原　葵　　　　　　　      */
/*****************************************/







/****************************************************************************************************/
/*		アプリケーション用共通ヘッダファイル	：	common.h											*/
/*																									*/
/*　本ヘッダファイルはAtmega328 CPUのプログラム作成時の標準ヘッダファイルである．							*/
/*  自身のよく使うincludeやtypedefなどはここに追加定義すること．											*/
/*　ただし，アプリケーション固有の構造体宣言などは，別のヘッダファイルを作成することを推奨する．				*/
/*																									*/
/*	変更履歴																							*/
/*　識別子	日付			氏名					変更内容													*/
/*　#000		2021.07.26	荒金 匡徳			初版リリース												*/
/****************************************************************************************************/

#ifndef COMMON_H_
#define COMMON_H_

#define 	F_CPU 16000000UL  // 16 MHz
#include 	<avr/io.h>
#include	<avr/interrupt.h>
#include	<util/delay.h>
#include	<stdio.h>
typedef		unsigned char	UCHR;
typedef		unsigned short	USHRT;
typedef		unsigned short	ULONG;

#endif /* COMMON_H_ */