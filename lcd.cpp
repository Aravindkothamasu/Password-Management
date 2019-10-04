#include"header.h"
				/*************************************************/
				/*						LCD			   	  		 */
				/*					P1.16 - P1.23				 */
				/*		RS - P1.26    EN - P1.27				 */

#define RS (1<<26)			
#define EN (1<<27)
void lcd_init()
{
	IODIR1 |=  (0xff<<16);					  			  //Setting as Output for D0-D7
	IODIR1 |=  ( 0x3<<26);										//Output for RS and EN
	
	lcd_cmd(0x38);
	lcd_cmd(0x2);
	lcd_cmd(0x6);
	lcd_cmd(0xe);
	lcd_cmd(0x1);	
}

void lcd_data(U8 data)
{
	IOCLR1 |= 0xff<<16;
 	IOSET1 |= data<<16;
	IOSET1 |= RS;
	IOSET1 |= EN;
	tdelay_ms(2);
	IOCLR1 |= EN;
}

void lcd_cmd(U8 cmd)
{	
	IOCLR1 |= 0xff<<16;
	IOSET1 |= cmd<<16;
	IOCLR1 |= RS;
	IOSET1 |= EN;
	tdelay_ms(2);
	IOCLR1 |= EN;
}

void lcd_string(CU8 *s)
{
	while(*s)
		lcd_data(*s++);
}
 	
