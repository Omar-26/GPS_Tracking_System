#include "../../03_UART/UART_Interface.h"
#include "../../02_GPS/GPS_params.h"
#include "../../02_GPS/GPS_interface.h"

#include <string.h>
#include <stdio.h>
#include <math.h>

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "TM4C123GH6PM.h"


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