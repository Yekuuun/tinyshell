#include "tinyshell.h"

//show options.
static void print_exit_help(void) {
    printf("[?] exit: exit [n]\n");
    printf("  Exit the shell with a status of N.\n");
    printf("  If N is provided, it must be an integer between 0 and 255.\n");
    printf("  If N is omitted, the exit status is 0.\n");
    printf("  Examples:\n");
    printf("    exit        # exits with status 0\n");
    printf("    exit 42     # exits with status 42\n");
    printf("    exit 256    # exits with status 0 (256 modulo 256)\n");
    printf("  If N is not a valid integer, an error message is printed\n");
    printf("  and the shell exits with status 255.\n");
}

/**
 * exit function.
 */
void quit(char **args){
    int exit_code = 0;

    if(args && args[1]){
        if(ft_str_cmp(args[1], "--help")){
            print_exit_help();
            return;
        }

        //handling code.
        int code  = ft_atoi(args[1]);
        exit_code = code;

        if(args[2]){
            fprintf(stderr, "[*] Error, too many arguments. Exiting tinyshell.\n");
            return;
        }
    }

    //freeing ressources.
    free_ast(&g_ast_head);
    free_tokens(&g_token_head);
    free_history(&g_history_head);

    fprintf(stderr, "[*] exiting tinyshell.\n");
    _exit(exit_code);
}