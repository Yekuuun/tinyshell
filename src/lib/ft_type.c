#include "tinyshell.h"

/**
 * Custom implementation of tolower function
 */
int ft_type_tolower(int c){
    if(c >= 'A' && c <= 'Z')
        return c + ('a' - 'A');

    return c;
}