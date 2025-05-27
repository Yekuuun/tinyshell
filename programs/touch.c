/**
 * Base touche function creating a new file. 
 * Author : Yekuuun
 * Github : https://github.com/Yekuuun
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <utime.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

typedef struct touch_flags {
    int a_flag; //change access time
    int c_flag; //no create
    int m_flag; //change the modification time
    int h_flag; //show help
} touch_flags;

int optopt, optind;
char *optarg;

/**
 * Base function for showing command informations.
 */
static void show_help(const char *prog_name){
    printf("Usage: %s [-a] [-c] [-m] [files...]\n", prog_name);
    printf("Options:\n");
    printf("  -a        Change only access time\n");
    printf("  -c        Do not create any files\n");
    printf("  -m        Change only the modification time\n");
    printf("  -h        Display this help message\n");
}

/**
 * Main touch function.
 */
static int main_touch(const char *path, touch_flags *flags){
    if(!path || !flags)
        return 1;

    struct stat st;
    if(stat(path, &st) != 0) { //exist.
        if(flags->c_flag){
            printf("[!] File not exist.\n");
            return 1;
        }

        int fd = open(path, O_CREAT | O_WRONLY, 0644);
        if(fd == -1)
            return 1;

        close(fd);
        stat(path, &st);
    }

    //updating informations.
    struct utimbuf times;
    times.actime = flags->a_flag ? time(NULL) : st.st_atime;
    times.modtime = flags->m_flag ? time(NULL) : st.st_mtime;

    if(utime(path, &times) != 0)
        return -1;

    return 0;
}

//entry
int main(int argc, char **argv){
    int opt;
    int state = 0;

    touch_flags *flags = (touch_flags*)calloc(1, sizeof(touch_flags));
    if(!flags)
        return EXIT_FAILURE;

    if(argc < 2){
        printf("[!] touch missing file operand. Use --help for more informations.\n");
        state = 1; goto __CLEANUP;
    }

    if(argc == 2 && (strcmp(argv[1], "--help") == 0)){
        show_help(argv[0]);
        goto __CLEANUP;
    }

    //parsing flags.
    while((opt = getopt(argc, argv, "acmh")) != -1){
        switch(opt){
            case 'a':
                flags->a_flag = 1; break;
            case 'c':
                flags->c_flag = 1; break;
            case 'm':
                flags->m_flag = 1; break;
            case 'h':
                show_help(argv[0]);
                goto __CLEANUP;
            case '?':
                printf("Usage: %s [-a] [-c] [-m] [files...]\n", argv[0]);
                state = 1; goto __CLEANUP;
            default:
                state = 1; goto __CLEANUP;
        }
    }

    const char *path = argv[optind];
    state = main_touch(path, flags);

__CLEANUP:
    if(flags)
        free(flags);

    return state;
}