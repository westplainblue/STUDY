/***************************************************/
/*         TK210466Å@Å@êºå¥Å@à®                     */
/***************************************************/


#include "common.h"
#include "dht11.h"

int dht11_read(UCHR *ptr){
	int i;         
	int n;         
	int ret_flg = 0;
	UCHR tcn;
	UCHR add = 0;
	
	TCCR0A = 0b00000001;
	TCCR0B = 0b00000010;
	TIMSK0 = 0b00000000;
	
	
	SDA_H;
	SDA_OUT;
	_delay_ms(50);
	SDA_L;
	_delay_ms(19);
	SDA_H;

	
	SDA_IN;
	WAIT_SDA_L;
	WAIT_SDA_H;
	WAIT_SDA_L;

	
	for (n = 0; n < 5; n++){
		for (i = 0; i < 8; i++){
			cli();
			WAIT_SDA_H;
			TCNT0 = 0;       
			WAIT_SDA_L;
			tcn = TCNT0;
			sei();
			*(ptr + n) = *(ptr + n) << 1;    
			if (tcn > 97){
				*(ptr + n) |=0b00000001;
			}
		}
	}
	
	add = *(ptr + 0) + *(ptr + 1) + *(ptr + 2) + *(ptr + 3);
	if (add != *(ptr + 4)){
		ret_flg = 1;
	}
	
	WAIT_SDA_H;

	return ret_flg;
}