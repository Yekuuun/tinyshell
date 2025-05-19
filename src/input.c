#include "tinyshell.h"

#define BUFFER_MAX 4096
#define MAX_PATH 4096

static volatile int RUNNING = 1;

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
 * Main function for handling shell functions.
 */
int start_shell(){
    char buffer[BUFFER_MAX] = {0};
    printf("\x1B%c", 'c');

    //handling commands.
    while(RUNNING > 0){
        print_shell_banner();
        if(fgets(buffer, BUFFER_MAX, stdin) == NULL){
            printf("[!] Internal error reading user commands. \n");
            return 1;
        }

        //handling fgets.
        size_t len = strlen(buffer);
        if((len < BUFFER_MAX) && buffer[len - 1] == '\n'){
            buffer[len - 1] = '\0';
        }
        else{
            int ch;
            while ((ch = fgetc(stdin)) != '\n' && ch != EOF)
            fputs("[!] Command too large.", stderr);

            return 1;
        }

        puts(buffer);
    }

    return 0;
}