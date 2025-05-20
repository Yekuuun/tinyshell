#include "tinyshell.h"

/**
 * Base echo function.
 */
int echo(const char **args){
    int new_line = 1;
    int i = 0;

    if(!args[0])
        return 1;

    if(args[1] && ft_str_cmp(args[1], "-n") == 0){
        new_line = 0;
        i++;
    }

    while(args[i]){
        printf("%s", args[i]);

        //handling space.
        if (args[i + 1])
            printf(" ");

        i++;
    }

    if(new_line)
        printf("\n");

    return 0;
}