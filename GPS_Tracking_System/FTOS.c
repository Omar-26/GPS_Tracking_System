#include <stdio.h>
#include <string.h>

int s=0;
char temp [50]; // Temporary buffer to hold each float as a string

void ftos(float latitude[] , float longitude[], char Co_final[], int size)
{
	//char lat_final[2100] = ""; // Assuming a maximum length for the character array

		//Co_final="";
	for ( s = 0; s < size; s++) {
		
        sprintf(temp, "%.6f", latitude[s]); // Convert float to string with 7 decimal places
        strcat(Co_final, temp); // Concatenate the string representation
        if (s < size ) {
        strcat(Co_final, ","); // Add comma and space if not the last element
        }
    }
	
    for ( s = 0; s < size; s++) {
			
        sprintf(temp, "%.6f", longitude[s]); // Convert float to string with 7 decimal places
        strcat(Co_final, temp); // Concatenate the string representation
        if (s < size - 1) {
        strcat(Co_final, ","); // Add comma and space if not the last element
        }
    }
		
		strcat(Co_final, "\n");
		//Co_final = lat_final;
		
}


