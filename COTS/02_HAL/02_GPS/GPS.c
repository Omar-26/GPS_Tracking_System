#include "UART_Interface.h"
#include "GPS_params.h"
#include "GPS_interface.h"

#include <string.h>
#include <stdio.h>
#include <math.h>

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "tm4c123gh6pm.h"
#define DEG_TO_RAD(DEG) ((DEG * PI / 180))

u8 GPS_Log_Check[] = "$GPRMC,";
u8 GPS_Formatted[12][20];

u8 *token;
u8 GPS[80];

f32 currentLat, currentLong;

void GPS_Read()
{

    u8 Received_Char;
    u8 Local_u8ReceivedChar;

    u8 flag = 0;
    do
    {
        flag = 0;
        for (u8 i = 0; i < length(GPS_Log_Check); i++)
        {
            UART_u8ReceiveByte(UART0, &Local_u8ReceivedChar);
            if (Local_u8ReceivedChar != GPS_Log_Check[i])
                flag = 1;
            break;
        }
    } while (flag);

    strcpy(GPS, "");

    do
    {
        u8 GPS_Counter = 0;
        UART_u8ReceiveByte(UART0, &Local_u8ReceivedChar);
        Received_Char = Local_u8ReceivedChar;
        GPS[GPS_Counter++] = Received_Char;
    } while (Received_Char != '*');
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
double Value_to_Degree(double value) { return value; }
// double degree = (int)value/100 ;
// double minutes = value - 	(double)degree*100;
// return (degree + (minutes/60));
// }

double calcDistance(volatile double latitude_1, volatile double longitude_1, volatile double latitude_2, volatile double longitude_2)
{

    volatile double phi1, phi2, delta_phi, delta_lmbda, a, c, d;

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
