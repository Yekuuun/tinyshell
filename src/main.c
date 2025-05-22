/**
 * Main entry point for the tinyshell project.
 * Author : Yekuuun
 * Github : https://github.com/Yekuuun
 */

#include "tinyshell.h"

//init builtin.
builtin builtins[] = {
    { "clear", clear },
    { "echo", echo },
    { "pwd", pwd },
    { NULL, NULL }
};

/**
 * Main entry point.
 */
int main(int argc, char **argv){
    if(argc > 1){
        printf("[!] %s no arguments needed for tinyshell. \n", argv[0]);
        return -1;
    }


    //add exec folder to env.
    int path = set_exec_env(ENV_PATH);
    if(path != 0)
        return 1;

    return start_shell();
}