#include "tinyshell.h"

int clear(){
    printf("\x1B%c", 'c');
    return 0;
}