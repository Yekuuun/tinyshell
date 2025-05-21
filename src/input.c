/**
 * Handling main routine for shell command handling
 */

#include "tinyshell.h"

int RUNNING = 1;
history *g_history_head;
token *g_token_head;
ast *g_ast_head;


/**
 * print current user username.
 */
static void get_current_user(){
    char *username = getenv("USER");
    if(username != NULL)
        printf("%s", username);
}

/**
 * Print current working dir.
 */
static void print_working_dir(){
    char cwd[MAX_PATH] = {0};

    if(getcwd(cwd, MAX_PATH) != NULL){
        printf("%s", cwd);
    }
}

/**
 * print shell banner.
 */
static void print_shell_banner(){
    printf(ANSI_COLOR_BLUE);

    //user
    get_current_user();
    printf("@");
    get_current_user();

    //path.
    printf(":");

    printf(ANSI_COLOR_GREEN);
    printf("~");
    print_working_dir();
    printf("$ ");

    printf(ANSI_COLOR_RESET);
}

/**
 * Handling CTRL-C events => proper exit.
 */
static void crtrl_c_handler(int sig){
    (void)sig;

    printf("[*] Catched CTRL-C event. Ending tinyshell.\n");
    free_tokens(&g_token_head);

    RUNNING = 0;
    exit(130);
}

/**
 * Main function for handling shell functions.
 */
int start_shell(){
    signal(SIGINT, crtrl_c_handler);
    char buffer[BUFFER_MAX] = {0};
    clear();

    //declaring ptr to global structs
    g_token_head   = NULL;
    g_ast_head     = NULL;
    g_history_head = NULL;

    //handling commands.
    while(RUNNING > 0){
        print_shell_banner();
        if(fgets(buffer, BUFFER_MAX, stdin) == NULL){
            printf("[!] Internal error reading user commands. \n");
            return 1;
        }

        //handling fgets.
        size_t len = ft_str_len(buffer);
        if((len < BUFFER_MAX) && buffer[len - 1] == '\n'){
            buffer[len - 1] = '\0';
        }
        else{
            int ch;
            while ((ch = fgetc(stdin)) != '\n' && ch != EOF)
            fputs("[!] Command too large.", stderr);

            return 1;
        }

        //lex
        g_token_head = lexer(buffer);
        if(!g_token_head){
            printf("[!] Error lexing commands.\n");
            return 1;
        }

        //parse
        g_ast_head = parse_pipe(&g_token_head);
        if(!g_ast_head){
            printf("[!] Error parsing commands\n");
            free_tokens(&g_token_head);
            return 1;
        }

        //exec.
        int exec = execute_ast(g_ast_head);
        if(exec != 0)
            RUNNING = 0;

        add_to_history(&g_history_head, buffer);
        free_tokens(&g_token_head);
        free_ast(&g_ast_head);
    }

    return 0;
}