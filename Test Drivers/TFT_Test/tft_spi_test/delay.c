#include "delay.h"


// delay function in mili seconds.
void delayMsec(U32_t miliSec){
	U32_t i, j;
	for(i = 0 ; i < miliSec; i++)
		for(j = 0; j < 3180; j++){} /* do nothing for 1 ms */
}//End of function.


// delay function in micro seconds.
void delayUs(U32_t n)
{
	U32_t i, j;
	for(i = 0 ; i < n; i++)
		for(j = 0; j < 3; j++){} /* do nothing for 1 us */
}//End of function.
