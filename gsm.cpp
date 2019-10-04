#include"header.h"
void gsm_init()
{
     uart0_tx_string("AT\r\n");
     tdelay_ms(5000);
     uart0_tx_string("AT+CMGF=1\r\n");
     tdelay_ms(1000);
}  


void send_msg(U8 *msg)
{
		CU8 *p=msg;
		lcd_cmd(1);
		tdelay_ms(500);
		lcd_string("Sending Message");
    uart0_tx_string("AT+CMGS=\"9247727161\"\r\n");
    tdelay_ms(2000);
    uart0_tx_string(p);							//send message to GSM
//    uart0_tx_string("\r\n");
		tdelay_ms(1000);
    uart0_tx(0x1A);										//ctrl+Z
    tdelay_ms(2000);
		lcd_cmd(0xc0);
		lcd_string("MSG sent");
		tdelay_ms(2500);
}   
