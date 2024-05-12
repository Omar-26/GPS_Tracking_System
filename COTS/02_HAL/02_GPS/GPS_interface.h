#ifndef __HAL_GPS_INTERFACE_H__
#define __HAL_GPS_INTERFACE_H__

double Calc_Distance(volatile double latitude_1, volatile double longitude_1, volatile double latitude_2, volatile double longitude_2);

void GPS_Read();

void GPS_format();

double Value_to_Degree(double value){return value};

#define DEG_TO_RAD(DEG)((DEG*PI/180))

const double EARTH_RADIUS = 6371000;
const double PI = 3.14159265358979323846264338327950;


#endif 