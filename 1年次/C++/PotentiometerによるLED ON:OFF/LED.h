
/************************************************************************/
/*   TK210466       ������                                               */
/************************************************************************/

#if
def LED_H_
#define LED_H_

class LED{
	
	UCHR ledLevel;						/*LED���x*/
	public:								
	LED( void);							/*�R���X�g���N�^*/
	void setLedLevel( UCHR level);		/*���x�ݒ胁�\�b�h*/
	UCHR getLedLevel( void);			/*���x�ǂݏo�����\�b�h*/
	
	};
	
	
	#endif