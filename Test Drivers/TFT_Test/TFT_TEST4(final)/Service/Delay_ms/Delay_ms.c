#include "../../utils/STD_Types.h"

/*****delay function******/
void delay_ms(float time_delay_ms)
{
  uint32 delay_int=0;
  float  freq_uc=(80000000),ms_float=(1.0/1000),cycles_float=freq_uc*time_delay_ms*ms_float,delay_float=0;//MISSING ORDER OF 10
 //A problem face me with debugger in calculation
  /*the equation of of cycles with respect to the coefient of delay
  that we consider it as the input of for is cycles_float=6(delay_flaot)+23 and this
  is calculated according to cycles that the delay call and delay function take in
  zero optimization level and the type of compiler is(********) */
  delay_float=(cycles_float-23)/6 ;
  for(delay_int=(int)delay_float;delay_int>=1;delay_int--);
}
/********NOTE******/
/*That time will not be accurate but it raally accepted
as the cylces that will make the delay function and call
of it in main will  39999995 that wiil make 499.9999375ms
that will make aproxiamtly 500ms but we should know that
the accurate value that the function and call should make
40000000 but this happen as value of delay _float will be
 from this equation delay_float=(cycles_float-23)/6
6666662.8333333333333333333333333 where cycles_float=
40000000 and this value will be approximated to
6666662 substitute it in this equation
cycles_float=6*(delay_flaot)+23 that cykces_float
will be 39999995 but this is thimer could be acceptable if
we will be in need for it to solve it i will multiply with 10 or 100*/
