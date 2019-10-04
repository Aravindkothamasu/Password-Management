#include"header.h"


				/*************************************************/
				/*					Keypad				   		 */
				/*					P0.8 - P0.15				 */


#define R0	 (1<< 8)						/*************For input***********/
#define R1	 (1<< 9)
#define R2	 (1<<10)
#define R3	 (1<<11)
#define C0	 (1<<12)
#define C1	 (1<<13)
#define C2	 (1<<14)
#define C3	 (1<<15)


U8 kpd[4][4] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

																									   
U8 keyscan(void)
{
 	U8 row=0,col=0;	
	IODIR0 |= (0xf<<8);								  		  //Rows should be output.
	IOCLR0 |= (R0|R1|R2|R3|C0|C1|C2|C3);					  //Setting all to zero
	IOSET0 |= (C0 | C1 | C2 | C3);							  //setting coloumn to 1
	while( col_scan() == 1 );								  //Checking (waiting for switch press)
	tdelay_ms(50);

	IOCLR0 |=  R0;												  
	IOSET0 |= (R1|R2|R3);
	if( col_scan() == 0 )
	{	
			row = 0;
			goto colcheck;	
	}


	IOCLR0 |=  R1;
	IOSET0 |= (R0|R2|R3);
	if( col_scan() == 0 )
	{	
			row = 1;
			goto colcheck;	
	}


	IOCLR0 |=  R2;
	IOSET0 |= (R0|R1|R3);
	if( col_scan() == 0 )
	{	
			row = 2;
			goto colcheck;	
	}



	IOCLR0 |= R3;
	IOSET0 |= (R0|R1|R2);
	if( col_scan() == 0 )
	{	
			row = 3;
			goto colcheck;	
	}


	colcheck:
		if(  ( (IOPIN0>>12)&1)==0)
			 col=0;
		else if(  ( (IOPIN0>>13)&1)==0)
			col=1;
		else if(  ( (IOPIN0>>14)&1)==0)
			col=2;
		else if(  ( (IOPIN0>>15)&1)==0)
			col=3; 

	   while( col_scan()==0);
	   tdelay_ms(50);
	   return (kpd[row][col]);
}

U8 col_scan(void)
{
 	U8 temp=0;
	temp = 	(IOPIN0>>12)&1;
	temp &= (IOPIN0>>13)&1;
	temp &= (IOPIN0>>14)&1;
 	temp &= (IOPIN0>>15)&1;
	return temp;
}
