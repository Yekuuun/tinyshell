/**
 * A base implementation of the cat command.
 * Author : Yekuuun
 * Github : https://github.com/Yekuuun
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define EXIT_SUCCESS 0 
#define EXIT_FAILURE 1
#define MAX_READ_LEN 4056

//a base struct to handle cat command flags. => inspiration : https://man7.org/linux/man-pages/man1/cat.1.html
typedef struct cat_flags {
    int a_flag;
    int h_flag;
    int n_flag;
    int e_flag;
    int s_flag;
} cat_flags;

typedef cat_flags *pcat_flags;

int optopt, optind;
char *optarg;

/**
 * Helper man function.
 */
static void show_helper(){
    printf("Usage :\n");
}

/**
 * Main function checking if a path provided is valid. 
 * @param path => path to a given file.
 */
static int is_valid_path(const char *path){
    struct stat path_stat;

    if(stat(path, &path_stat) != 0)
        return 0;

    return S_ISREG(path_stat.st_mode);
}

/**
 * Main cat function implementation
 * @param path  => path to the file to display. 
 * @param flags => struct containing flags.
 */
static int cat_main(const char *path, pcat_flags flags){
    char ch;
    int lines  = 0;
    long count = 0;
    FILE *fileptr = NULL;

    fileptr = fopen(path, "r");
    if(!fileptr){
        printf("[!] Error opening file : %s\n", path);
        return 1;
    }

    //reading characters.
    while((ch = fgetc(fileptr)) != EOF){
        if(ch == '\n'){
            if(flags->e_flag)
                printf("$\n");

            if(flags->n_flag)
                lines++;
        }

        if(ch == ' ' && flags->n_flag)
            continue;

        if(!flags->a_flag && count == MAX_READ_LEN)
            break;

        
        printf("%c", ch);
        count++;
    }

    return 0;
}

//entry point.
int main(int argc, char **argv){
    int opt;
    int state = 0;

    if(argc < 2){
        show_helper();
        return EXIT_FAILURE;
    }

    if(strcmp(argv[1], "--help") == 0){
        show_helper();
        return EXIT_SUCCESS;
    }

    pcat_flags flags = (pcat_flags)calloc(1, sizeof(cat_flags));
    if(!flags)
        return EXIT_FAILURE;

    //building flags
    while((opt = getopt(argc, argv, "ahnes")) != -1){
        switch(opt){
            case 'a':
                flags->a_flag = 1; break;
            case 'h':
                show_helper();
                goto __CLEANUP;
            case 'n':
                flags->n_flag = 1; break;
            case 'e':
                flags->e_flag = 1; break;
            case 's':
                flags->s_flag = 1; break;
            case '?':
                fprintf(stderr, "[!] non valid option provided. Use --help for more informations.\n");
                state = 1; goto __CLEANUP;
            default:
                state = 1; goto __CLEANUP;
        }
    }

    if (optind >= argc) {
        printf("[!] No path provided.\n");
        state = 1; goto __CLEANUP;
    }

    const char *path = argv[optind];
    if(!is_valid_path(path)){
        printf("[!] Invalid file path.\n");
        state = 1; goto __CLEANUP;
    }

    //calling main process function.
    state = cat_main(path, flags);

__CLEANUP:
    if(flags)
        free(flags);

    return state;
}