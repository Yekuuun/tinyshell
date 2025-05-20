#include "tinyshell.h"

void clear(){
    printf("\x1B%c", 'c');
}