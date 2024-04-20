

/************************************************************************/
/*   TK210466       ¼Œ´ˆ¨                                               */
/************************************************************************/

#include "common.h"
#include "Potentiometer.h"

class Potentiometer{
	UCHR potAd;
	UCHR threshold;
	public:
	Potentiometer( void);
	Potentiometer( UCHR threshold);
	UCHR getPotAd( void);
	UCHR getHL( void);
	UCHR getHL( UCHR threshold);
	};

Potentiometer::Potentiometer( void){
	DDRC &= 0b11111110;
	ADCSRA = 0b10000100;
	ADMUX = 0b01100000;
	this->potAd = 0;
	this->threshold = 0x80;
}

Potentiometer::Potentiometer( UCHR threshold){
	DDRC &= 0b11111110;
	ADCSRA = 0b10000100;
	ADMUX = 0b01100000;
	this->potAd = 0;
	this->threshold = threshold;
}


UCHR Potentiometer::getPotAd( void){
	ADCSRA |= 0b01000000;
	while(( ADCSRA & 0b01000000) != 0);
	this->potAd = ADCH;
	return this->potAd;
	
}

UCHR Potentiometer::getHL( void){
	UCHR ret = POT_HIGH;
	if (getPotAd() < this->threshold)
	{
		ret = POT_LOW;
	}
	return ret;
}