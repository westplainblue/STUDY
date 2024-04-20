
/************************************************************************/
/*   TK210466       西原葵                                               */
/************************************************************************/

#if
def LED_H_
#define LED_H_

class LED{
	
	UCHR ledLevel;						/*LED明度*/
	public:								
	LED( void);							/*コンストラクタ*/
	void setLedLevel( UCHR level);		/*明度設定メソッド*/
	UCHR getLedLevel( void);			/*明度読み出しメソッド*/
	
	};
	
	
	#endif