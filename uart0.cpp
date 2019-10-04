#include"header.h"

#define THRE (U0LSR&(1<<5))
#define RDR  (U0LSR&0x1)

void uart0_init(U32 baud)
{
	PINSEL0 |= 0x5;//P0.0=TXD0, P0.2=RXD0
	U0LCR=0x83;//DLAB=1, WORD LENGTH=8bits, PARITY=Disabled,No of Stop Bits=1  ( Unlocking  )
	switch(baud)	//setting baudrate
	{		 
		case 4800:		U0DLL=195;	break;		//4800bps
		case 7200:		U0DLL=130;	break;		//7200bps
		case 9600:		U0DLL=97;	break;		//9600bps
		case 57600:		U0DLL=16;	break;		//9600bps
		case 115200:	U0DLL=8;	break;		//9600bps
		default: 		U0DLL=97;
	}	
	U0LCR=0x3;			////DLAB=0, WORD LENGTH=8bits, PARITY=Disabled,No of Stop Bits=1   
}



void uart0_tx(U8 data)
{
	U0THR=data; 
	while (THRE == 0);
}

void uart0_tx_string(CU8 *s)
{
	while(*s)
		uart0_tx(*s++);
}


U8 uart0_rx ()
{
	while (RDR == 0);
	return U0RBR;	
} 



void uart0_rx_string(U8 *buf,U32 count)
{
	U32 i;
	for(i=0;i<count-1;i++)
	{
			buf[i]=  uart0_rx();
			uart0_tx(buf[i]);
			if(buf[i] == '\r')
					break;
	}
	buf[i] = 0;
}



void dec_print(U32 a,U32 var)   //For printing integer
{
		U32 k=1,b=0;		
		(a>=10000) ? k = 10000 : ( (a>=1000) ? k=1000 : ( (a>=100) ? k = 100 : ( (a>=10) ? k = 10 :(k=1) )));
		//////////////////// **********************  -----------------------
	/*	if(k==1)
			(var==1)?  uart0_tx(a+48) : lcd_data(a+48);	*/
		while(k)
		{
			(var==1) ? uart0_tx((a/k -(b*10))+48) : lcd_data((a/k -(b*10))+48);
			b = a/k;
			k /= 10;				
		}
}
                        
