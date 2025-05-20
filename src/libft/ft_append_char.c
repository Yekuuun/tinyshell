#include "tinyshell.h"

/**
 * Add a character to dynamic buffer if necessary using realloc.
 */
int ft_append_char(char **buffer, int *len, int *cap, char c) {
    if (*len + 1 >= *cap) {
        *cap *= 2;
        char *new_buf = realloc(*buffer, *cap);
        if (!new_buf)
            return -1;
            
        *buffer = new_buf;
    }
    (*buffer)[(*len)++] = c;
    return 0;
}