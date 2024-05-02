#include "..\COTS\01_MCAL\03_UART\UART_Interface.h"
#include "..\COTS\02_HAL\02_GPS\GPS_params.h"
#include "..\COTS\02_HAL\02_GPS\GPS_interface.h"

#include <string.h>
#include <stdio.h>
#include <math.h>

#include "..\COTS\04_LIB\STD_TYPES.h"
#include "..\COTS\04_LIB\BIT_MATH.h"

#include "TM4C123GH6PM.h"
#define DEG_TO_RAD(DEG)((DEG*PI/180))


u8 GPS_Log_Check[] = "$GPRMC,";
u8 GPS_Formated[12][20];

u8 *token;
u8 GPS[80];

f64 currentLat, currentLong;

void GPS_Read(){
    
    u8 Recieved_Char;
    u8 Local_u8ReceivedChar;

    u8 flag = 0;
    do{
        flag = 0;
        for(u8 i = 0; i < length(GPS_Log_Check); i++){
            UART_voidReceiveByte(UART0, &Local_u8ReceivedChar);
            if (Local_u8ReceivedChar !=  GPS_Log_Check[i])
                flag = 1;
                break;
        }
    } while(flag);
    
    strcpy(GPS,"");

    do{
        u8 GPS_Counter = 0;
        UART_voidReceiveByte(UART0, &Local_u8ReceivedChar);
        Recieved_Char = Local_u8ReceivedChar;
        GPS[GPS_Counter++] = Recieved_Char;
    } while(Recieved_Char != '*');

}

void GPS_format(){
    
    u8 No_Of_Token_Strings = 0;

    token = strtok(GPS, ",");

    do{
        strcpy(GPS_Formated[No_Of_Token_Strings++], token);
        token = strtok(NULL, ",");
    } while(token != NULL);

    if(strcmp(GPS_Formated[1], "A") == 0){ // Valid Case
        
        if(strcmp(GPS_Formated[3], "N") == 0)
            currentLat = atof(GPS_Formated[2]);
        else
            currentLat = -atof(GPS_Formated[2]);

        if(strcmp(GPS_Formated[5], "E") == 0)
            currentLong = atof(GPS_Formated[4]);
        else
            currentLong = -atof(GPS_Formated[4]);
    }
}
const double EARTH_RADIUS = 6371000;
double Value_to_Degree(double value){return value}
// double degree = (int)value/100 ;
// double minutes = value - 	(double)degree*100;
// return (degree + (minutes/60));
// }

double calcDistance(volatile double latitude_1, volatile double longitude_1, volatile double latitude_2, volatile double longitude_2){
	
  volatile double phi1, phi2, delta_phi, delta_lmbda, a, c, d;
	
	phi1 = DEG_TO_RAD(Value_to_Degree(latitude_1));
	phi2 = DEG_TO_RAD(Value_to_Degree(latitude_2));
  delta_phi = phi2-phi1;
  delta_lmbda = longitude_2-longitude_1;
  delta_lmbda = DEG_TO_RAD(Value_to_Degree(delta_lmbda));
// harvsine law for calculating distance on sphere
   a = (sin(delta_phi/2) * sin(delta_phi/2)) + 
       (cos(phi1) * cos(phi2)) *            
       (sin(delta_lmbda/2) * sin(delta_lmbda/2)) ;
   c = 2 * atan2(sqrt(a),sqrt(1-a));
   d = EARTH_RADIUS * c;
	return d;
}
