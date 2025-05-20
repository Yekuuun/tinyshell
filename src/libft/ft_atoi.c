#include "tinyshell.h"

/**
 * Custom implementation of the atoi function.
 */
int ft_atoi(const char *str){
    int sign = 1;
    long result = 0;

    while(*str == ' ' || (*str >= 9 && *str <= 13)){
        if(str == '\0')
            return sign < 0 ? INT_MIN : INT_MAX;

        str++;
    }

    if(*str == '-' || *str == '+'){
        if(*str == '-')
            sign = -1;
        
        str++;
    }

    while(ft_type_isdigit(*str)){
        result = result * 10 + (*str - '0');

        if (sign == 1 && result > INT_MAX)
            return INT_MAX;
        if (sign == -1 && -result < INT_MIN)
            return INT_MIN;

        str++;
    }

    return (int)(sign * result);
}