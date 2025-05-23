/**
 * Main file in charge of execution.
 */

#include "tinyshell.h"

/**
 * Check if a function is a builtin function. 
 * @param function_name => name of the given function
 */
static int is_builtin(const char *function_name){
    for(int i = 0; builtins[i].name != NULL; i++){
        if(ft_str_cmp(function_name, builtins[i].name) == 0)
            return 1;
    }
    return 0;
}

/**
 * Execute a builtin function
 */
static int exec_builtin(const char *function_name, char **args){
    for(int i = 0; builtins[i].name != NULL; i++){
        if(ft_str_cmp(function_name, builtins[i].name) == 0)
            return builtins[i].func(args);
    }
    return 1;
}

/**
 * handling error.
 */
static void handle_errno(int err, char **argv){
    if (err == ENOENT) {
        fprintf(stderr, "[!] %s: command not found\n", argv[0]);
        quit(NULL);
    } 
    else if (err == EACCES) {
        fprintf(stderr, "[!] %s: permission denied\n", argv[0]);
        quit(NULL);
    }
    else {
        fprintf(stderr, "[!] %s: execution error: %s\n", argv[0], strerror(err));
        quit(NULL);
    }
}

/**
 * Execute a basic command.
 */
static int execute_command(ast *node){
    if(!node || !node->argv)
        return 1;

    if(ft_str_cmp("exit", node->argv[0]) == 0){
        quit(NULL);
        return 0;
    }

    if(is_builtin(node->argv[0])){
        return exec_builtin(node->argv[0], node->argv);
    }
    else {
        pid_t pid = fork();  
        if(pid == 0){ //child
            execvp(node->argv[0], node->argv);
            
            int err = errno;
            handle_errno(err, node->argv);
            return 1;
        }
        else if(pid > 0){ //parent
            int status;
            waitpid(pid, &status, 0);
            return WEXITSTATUS(status);
        }
        else {
            return 1;
        }

        return 1;
    }
}

/**
 * Main function in charge of execution. 
 * @param node => a ptr to the head of the ast three
 */
int execute_ast(ast *node){
    if(!node)
        return 1;

    switch(node->type){
        case AST_COMMAND:
            return execute_command(node);
        default:
            return 1;
    }

    return 0;
}