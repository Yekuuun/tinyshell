#include "tinyshell.h"

/**
 * print current working directory.
 */
int pwd(){
    char cwd[MAX_PATH] = {0};

    if(getcwd(cwd, MAX_PATH) != NULL){
        printf("%s", cwd);
    }

    return 0;
}