/**
 * Main entry point for the tinyshell project.
 * Author : Yekuuun
 * Github : https://github.com/Yekuuun
 */

#include "tinyshell.h"

/**
 * Main entry point.
 */
int main(int argc, char **argv, char **envp){
    if(argc > 1){
        printf("[!] no arguments needed for tinyshell. \n");
        return -1;
    }

    return start_shell();
}