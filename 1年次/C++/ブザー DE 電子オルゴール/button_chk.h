#ifndef BUTTON_CHK_H_
#define BUTTON_CHK_H_

#include "common.h"

/*マクロ定義*/
#define SW_OFF	0
#define SW_ON	1
#define SW_UNKNOWN	2



char button_chk(void){
	char ret = SW_UNKNOWN;
	char btn_old;
	btn_old = PIND;
	_delay_ms(10);
	if (((btn_old ^ PIND) & 0b01000000) == 0)
	{
		ret = (btn_old & 0b01000000) >> 6;
	}
	return ret;
}

#endif /* BUTTON_CHK_H_ */

/********************************************/
/*          TK210466 西原　葵　              */
/********************************************/