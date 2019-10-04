#include"header.h"

void delay_ms(U32 ms)
{
	unsigned int i;
	for( ;ms>0;ms--)
		for(i=12000 ; i>0 ; i-- );
}

void tdelay_ms(U32 ms)
{
 	T0PR = 15000-1;
	T0PC = T0TC = 0x0;
	T0TCR = 0x1;
	while(T0TC < ms);
	T0TCR = 0x0;
}
