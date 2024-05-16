#include <stdio.h>
#include <stdlib.h>

void reverse(char str[], int length) {
    int start = 0;
    int end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

void itoa(int num, char* str, int base) {
    int i = 0;
    int isNegative = 0;

    /* A zero is same "0" string in any base */
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
    }

    /* Negative numbers are only handled if base is 10 
       otherwise assumed to be unsigned */
    if (num < 0 && base == 10) {
        isNegative = 1;
        num = -num;
    }

    /* Process individual digits */
    while (num != 0) {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }

    /* If number is negative, append '-' */
    if (isNegative)
        str[i++] = '-';

    str[i] = '\0'; // Null-terminate string

    /* Reverse the string */
    reverse(str, i);
}


