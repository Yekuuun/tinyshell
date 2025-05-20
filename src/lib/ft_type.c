#include "tinyshell.h"

/**
 * Custom implementation of tolower function
 */
int ft_type_tolower(int c){
    if(c >= 'A' && c <= 'Z')
        return c + ('a' - 'A');

    return c;
}

/**
 * Custom implementation of isdigit function
 */
int ft_type_isdigit(char c){
    return (c >= '0' && c <= '9');
}