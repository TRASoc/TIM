#include <efi.h>

#include "util.h"


static void reverse(char *str, int str_size) {
    char *start = str, *end = (str + str_size - 1);
    while(start < end) {
        char temp = *end;
        *end = *start;
        *start = temp;
        start++; end--;
    }
}

void itoa(char* str, int str_size, int num) {
    int i = 0;
    int neg = num < 0;
    if(neg)
        num = -num;

    if(num == 0)
        str[i++] = '0';
    else {
        for(; i < str_size && num != 0; i++) {
            str[i] = (num % 10) + 48;
            num /= 10;
        }
    }

    if(i >= str_size)
        return; //This should throw an error but won't be possible
                //in the final implimentation so I am not too worried.
    if(neg)
        str[i++] = '-';
    if(i > str_size)
        i = str_size;
    str[i] = '\0';
    reverse(str, i);
}

void itox(char* str, int str_size, int num) {
    //Turn num into unsigned so we don't shift 1's right.
    unsigned int unum = (unsigned int) num;
    int i = 0;
    if(unum == 0)
        str[i++] = '0';
    else {
        for(; i < str_size && unum != 0; i++) {
            int hex_num = unum & 0x0000000F;
            if(hex_num <= 9)
                str[i] = hex_num + 48; //0 - 9
            else
                str[i] = hex_num + 55; //A - F
            unum = unum >> 4;
        }
    }
    str[i] = '\0';
    reverse(str, i);
}
