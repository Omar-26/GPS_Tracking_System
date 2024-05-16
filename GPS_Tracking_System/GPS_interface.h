#include "STD_TYPES.h"
#ifndef __HAL_GPS_INTERFACE_H__
#define __HAL_GPS_INTERFACE_H__

f32 calcDistance(volatile f32 latitude_1, volatile f32 longitude_1, volatile f32 latitude_2, volatile f32 longitude_2);

void GPS_Read();

void GPS_format();

double todegree(double angle);

f32 Value_to_Degree(f32 value);

#define DEG_TO_RAD(DEG) ((DEG * PI / 180))
#define M_PI            3.14159265358979323846264338327950
		 
#define EARTH_RADIUS  6371000
#define PI  3.14159265358979323846264338327950
		 
#endif