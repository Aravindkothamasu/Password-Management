#include"header.h"
extern U32 s1[12],s2[12];
int main()
{
	
	//U32 t; 
	inits(); 							//Initization of H/w's
	lcd_string("Set the data");
	tdelay_ms(1500);
	set(s1,s2);							//Set the data
	dob();								//Feed the Date of Birth
	tdelay_ms(1500);
	lcd_cmd(0xc4);
	lcd_string("Setting Done");
	tdelay_ms(2999);
	lcd_cmd(1);
	while(7)
 		Menu();
	
}
