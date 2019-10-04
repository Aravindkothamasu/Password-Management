								/********************************************/
								/*		USE TIMER Delay for accurate		*/	

#include"header.h"
#define CLKEN  0    /* RTC Clock Enable*/
#define CLKSRC 4 	/* RTC Clock Source Select Bit */

void rtc_init()
{
	CCR = ((1<<CLKEN ) | (1<<CLKSRC));
}

  
void set_time(void)
{
	SEC = 32; 	// a.sec;
	MIN = 32; 	//a.min;
	HOUR =12; 	//a.hr;
	DOM =  3; 	//a.day_of_mnth;
	DOW =  4; 	//a.day_of_week;
	DOY = 150;	//a.day_of_year;
	MONTH = 10;	//a.mnth;
	YEAR = 2019;//a.yr;		
}


ti get_time()
{
	ti a;
	a.sec =  CTIME0 & 0x3F;
	a.min = (CTIME0>> 8) & 0x3F;
	a.hr  = (CTIME0>>16) & 0x1F;
	a.day_of_week = (CTIME0 >> 24) & 7;
	a.day_of_mnth = (CTIME1) & 0x1F;
	a.day_of_year =  CTIME2 & 0x7FF;
	a.mnth = (CTIME1 >> 8) & 0xF;
	a.yr = (CTIME1 >>16) & 0xFFF;
	return a;
}

void pf_time_uart(ti a)
{
	CU8 d[7][10] = {"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
	  dec_print(a.hr,1);	 		//For hour printing
	  uart0_tx(':');
	
	  dec_print(a.min,1);		   //for minute printing
	  uart0_tx(':');
	
	dec_print(a.sec,1);
	uart0_tx('\t');
	uart0_tx_string(d[a.day_of_week]);							  //Day of week

	uart0_tx('\t');

	dec_print(a.day_of_mnth,1);
	uart0_tx('/');
	
	dec_print(a.mnth,1);
    uart0_tx('/');
	dec_print(a.yr,1);
	uart0_tx_string("\r\n");
}


void pf_time_lcd(ti a)
{
	CU8 d[7][10] = {"Sunday","Monday","Tuesday","Wednesday","Thrusday","Friday","Saturday"};
  dec_print(a.hr,2);	 		//For hour printing
  lcd_data(':');
	
	dec_print(a.min,2);		   //for minute printing
	lcd_data(':');
	

	dec_print(a.sec,2);
	lcd_string("   ");
	lcd_string(d[a.day_of_week]);							  //Day of week

	lcd_cmd(0xc0);
	dec_print(a.day_of_mnth,2);
	lcd_data('/');
	
	dec_print(a.mnth,2);
  	lcd_string("/");
	dec_print(a.yr,2);
}
