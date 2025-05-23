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
 * Execute pipe command.
 */
int execute_pipeline(ast *node) {
    int pipefd[2];
    pid_t pid1, pid2;

    if (pipe(pipefd) == -1)
        return 1;

    pid1 = fork();
    if (pid1 == 0) {
        // Child 1: execute left
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        exit(execute_ast(node->left));
    }

    pid2 = fork();
    if (pid2 == 0) {
        // Child 2: execute right
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        exit(execute_ast(node->right));
    }

    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}

/**
 * Execute command with redirection
 */
int execute_redirection(ast *node) {
    int fd;
    int saved_fd;
    int result;

    switch (node->type) {
        case AST_REDIR_IN:
            fd = open(node->filename, O_RDONLY);
            if (fd == -1)
                return 1;

            saved_fd = dup(STDIN_FILENO);
            dup2(fd, STDIN_FILENO);
            close(fd);
            result = execute_ast(node->left);
            dup2(saved_fd, STDIN_FILENO);
            close(saved_fd);
            return result;

        case AST_REDIR_OUT:
            fd = open(node->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1)
                return 1;

            saved_fd = dup(STDOUT_FILENO);
            dup2(fd, STDOUT_FILENO);
            close(fd);
            result = execute_ast(node->left);
            dup2(saved_fd, STDOUT_FILENO);
            close(saved_fd);
            return result;

        case AST_REDIR_APPEND:
            fd = open(node->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd == -1) 
                return 1;

            saved_fd = dup(STDOUT_FILENO);
            dup2(fd, STDOUT_FILENO);
            close(fd);
            result = execute_ast(node->left);
            dup2(saved_fd, STDOUT_FILENO);
            close(saved_fd);
            return result;

        case AST_HEREDOC:
            fprintf(stderr, "Heredoc execution not implemented\n");
            return 1;

        default:
            fprintf(stderr, "Unknown redirection type\n");
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
        case AST_PIPELINE:
            return execute_pipeline(node);
        case AST_REDIR_IN:
        case AST_REDIR_OUT:
        case AST_REDIR_APPEND:
        case AST_HEREDOC:
            return execute_redirection(node);
        default:
            return 1;
    }

    return 0;
}