#include"header.h"


/************************************************************/
/*												   			*/
/*						login function						*/
/*															*/

void login(void)
{
	U32 i;
	lcd_cmd(1);
	lcd_string("Successfully Login");																	//Temp value
	tdelay_ms(1500);
	lcd_cmd(1);
	for(i=0;i<7;i++)
	{
		pf_time_lcd(get_time());
		tdelay_ms(1000);
		lcd_cmd(1);
	}
	lcd_cmd(1);
	tdelay_ms(1500);
	lcd_string("logging out");
	tdelay_ms(1000);
	lcd_cmd(1);
}
