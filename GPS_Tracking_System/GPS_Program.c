/*****<tft *******************/
#include "mcal/nvic/nvic.h"
#include "mcal/SysCtr/SysCtr.h"
#include "mcal/dio/dio_types.h"
#include "mcal/PortDriver/port.h"
#include "mcal/dio/dio.h"
#include "mcal/mcu_hw.h"
#include "Service/Delay_ms/Delay_ms.h"
#include "mcal/ssi/ssi.h"
#include "TFT/ST7735.h"
#include "Sys_Tick.h"
/*****<tft *******************/
#include "UART_Interface.h"
#include "GPS_interface.h"

#include <string.h>
#include <stdlib.h>

#include <math.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "tm4c123gh6pm.h"
#define DEG_TO_RAD(DEG) ((DEG * PI / 180))

u8 GPS_Counter = 0;

f32 currentLatitude, currentLongitude;

void GPS_Read()
{
	u8 GPS_Log_Check[] = "$GPRMC,";
  char GPS[80];
  char GPS_Tokens[12][20];
	char *token;
    u8 Local_u8ReceivedChar;
    u8 i , flag = 1;
     do
    { 
			  flag = 1 ;
        for (i = 0; i < 7 ; i++)
        {
					
           if (UART_u8ReceiveByte(UART1) != GPS_Log_Check[i])
					 {
						 flag = 0;
             break;
					 }
        }
    } while (flag == 0);
		
		ST7735_drawString("after do while 1",4, 4,0X0000,0Xffff,1);
    strcpy(GPS, "");
    do
    {
        Local_u8ReceivedChar = UART_u8ReceiveByte(UART1);
        GPS[GPS_Counter++] = Local_u8ReceivedChar;
    } while (Local_u8ReceivedChar != '*');
		ST7735_drawString("before format",4, 4,0X0000,0Xffff,1);
    
		token = strtok(GPS, ",");
    u8 No_Of_Token_Strings = 0;
    
		while ((token != NULL) && (No_Of_Token_Strings < 7) )
		{
        strcpy(GPS_Tokens[No_Of_Token_Strings++], token);
        token = strtok(NULL, ",");
    } 

    if (strcmp(GPS_Tokens[1], "A") == 0)
    { 
        if (strcmp(GPS_Tokens[3], "N") == 0)
            currentLatitude = atof(GPS_Tokens[2]);
						
        else
            currentLatitude = -atof(GPS_Tokens[2]);

        if (strcmp(GPS_Tokens[5], "E") == 0)
            currentLongitude = atof(GPS_Tokens[4]);
        else
            currentLongitude = -atof(GPS_Tokens[4]);
    }
}

/*
f32 calcDistance(volatile f32 latitude_1, volatile f32 longitude_1, volatile f32 latitude_2, volatile f32 longitude_2)
{
    volatile f32 phi1, phi2, delta_phi, delta_lmbda, a, c, d;

    phi1 = DEG_TO_RAD(Value_to_Degree(latitude_1));
    phi2 = DEG_TO_RAD(Value_to_Degree(latitude_2));
    delta_phi = phi2 - phi1;
    delta_lmbda = longitude_2 - longitude_1;
    delta_lmbda = DEG_TO_RAD(Value_to_Degree(delta_lmbda));
    // harvsine law for calculating distance on sphere
    a = (sin(delta_phi / 2) * sin(delta_phi / 2)) +
        (cos(phi1) * cos(phi2)) *
            (sin(delta_lmbda / 2) * sin(delta_lmbda / 2));
    c = 2 * atan2(sqrt(a), sqrt(1 - a));
    d = EARTH_RADIUS * c;
    return d;
}*/

double distance;
double todegree(double angle) {
int    degree = angle / 100;                    // Extracting the degree part
double minutes = angle - (double)degree * 100; // Extracting the minutes part
 return (degree + minutes / 60);              // Converting minutes to degrees;
}
double torad(double angle) {
 return angle * M_PI / 180.0;
}

f32 calcDistance(volatile f32 long1 ,volatile f32 lat1 ,volatile f32 long2 ,volatile f32 lat2){
double long_diff;
double lat_diff;
double a;
double c;
long1 = torad (todegree( long1));
long2 = torad (todegree( long2));
lat2  = torad (todegree( lat2 ));
lat1  = torad (todegree( lat1 ));
long_diff=long1-long2;
lat_diff= lat1-lat2;
a= pow(sin(lat_diff/2),2) + cos(lat1) * cos(lat2) * pow(sin(long_diff/2),2);
c = 2*atan2(sqrt(a), sqrt(1.0 - a));
distance = EARTH_RADIUS*c;
return (distance);
}