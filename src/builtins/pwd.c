#include "tinyshell.h"

/**
 * print current working directory.
 */
int pwd(char **args){
    char cwd[MAX_PATH] = {0};

    if(getcwd(cwd, MAX_PATH) != NULL){
        printf("%s\n", cwd);
    }

    return 0;
}