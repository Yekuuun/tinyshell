#include "tinyshell.h"

static volatile int RUNNING = 1;
token *g_token_head;

/**
 * print current working dir.
 */
static void get_current_working_dir(){
    char cwd[MAX_PATH] = {0};

    if(getcwd(cwd, MAX_PATH) != NULL){
        printf("%s", cwd);
    }
}

/**
 * print current user username.
 */
static void get_current_user(){
    char *username = getenv("USER");
    if(username != NULL)
        printf("%s", username);
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
    get_current_working_dir();
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

    //declaring ptr to token list.
    g_token_head = NULL;

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

        g_token_head = lexer(buffer);
        if(!g_token_head){
            printf("[!] Error lexing commands.\n");
            return 1;
        }

        print_tokens(g_token_head);
        free_tokens(&g_token_head);
    }

    return 0;
}