/*********************************************/
/*   TK210466   êºå¥Å@à®                      */
/*********************************************/


#define SDA_H PORTD = PIND | 0x08
#define SDA_L PORTD = PIND & 0xF7
#define WAIT_SDA_L while(( PIND & 0x08) != 0)
#define WAIT_SDA_H while(( PIND & 0x08) == 0)
#define SDA_OUT DDRD |= 0x08
#define SDA_IN DDRD &= 0xF7
