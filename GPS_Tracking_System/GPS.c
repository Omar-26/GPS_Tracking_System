#include "GPS_interface.h"
#include "UART_Interface.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "stdlib.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "tm4c123gh6pm.h"

u8 GPS_Log_Check[] = "$GPRMC,";
u8 GPS_Formatted[12][20];
u8 GPS_Counter = 0;
u8 flag = 0;

u8 *token;
u8 GPS[80];

f64 currentLatitude, currentLongitude;

u16 length (u8* arr)
{return sizeof(*arr)/sizeof(arr[0]);
}

void GPS_Read()
{

    u8 Received_Char;
    u8 Local_u8ReceivedChar;

    
    do
    {
        flag = 0;
        for (u8 i = 0; i < length(GPS_Log_Check); i++)
        {
            Local_u8ReceivedChar = UART_u8RecieveByte(UART0);
            if (Local_u8ReceivedChar != GPS_Log_Check[i])
                flag = 1;
            break;
        }
    } while (flag);

    strcpy(GPS, "");

    do
    {
        Local_u8ReceivedChar = UART_u8RecieveByte(UART0);
        Received_Char = Local_u8ReceivedChar;
        GPS[GPS_Counter++] = Received_Char;
    } while (Received_Char != '*');

    GPS_format();
}

void GPS_format()
{

    u8 No_Of_Token_Strings = 0;

    token = strtok(GPS, ",");

    do
    {
        strcpy(GPS_Formatted[No_Of_Token_Strings++], token);
        token = strtok(NULL, ",");
    } while (token != NULL);

    if (strcmp(GPS_Formatted[1], "A") == 0)
    { // Valid Case

        if (strcmp(GPS_Formatted[3], "N") == 0)
            currentLat = atof(GPS_Formatted[2]);
        else
            currentLat = -atof(GPS_Formatted[2]);

        if (strcmp(GPS_Formatted[5], "E") == 0)
            currentLong = atof(GPS_Formatted[4]);
        else
            currentLong = -atof(GPS_Formatted[4]);
    }
}
f64 Value_to_Degree(double value) { return value; }
// double degree = (int)value/100 ;
// double minutes = value - 	(double)degree*100;
// return (degree + (minutes/60));
// }

f64 Calc_Distance(volatile f64 latitude_1, volatile f64 longitude_1, volatile f64 latitude_2, volatile f64 longitude_2)
{

    volatile f64 phi1, phi2, delta_phi, delta_lmbda, a, c, d;

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
}
