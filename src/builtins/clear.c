#include "tinyshell.h"

int clear(char **args){
    printf("\x1B%c", 'c');
    return 0;
}