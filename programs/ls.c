/**
 * A basic implementation of the ls command.
 * Author : Yekuuun
 * Github : https://github.com/Yekuuun
*/
#include "shared.h"

typedef struct ls_flags {
    int show_hidden;
    int long_format;
    int sort_time;
} ls_flags;

typedef struct file_info {
    char name[256];
    time_t mtime;
    struct stat statbuf;
} file_info;

/**
 * Check if a const char * is a valid path.
 */
static int is_valid_path(const char *path){
    struct stat path_stat;

    if(stat(path, &path_stat) != 0)
        return 1;

    return S_ISREG(path_stat.st_mode);
}

/**
 * Print helping menu
 */
static void print_help(const char *prog_name) {
    printf("Usage: %s [-a] [-l] [-h] [-t] [files...]\n", prog_name);
    printf("Options:\n");
    printf("  -a        Show hidden files\n");
    printf("  -l        Use long listing format\n");
    printf("  -h        Display this help message\n");
    printf("  -t        Sort by modification time\n");
}


/**
 * Sorting by time.
 */
static int compare_time(const void *a, const void *b) {
    const file_info *fa = (const file_info *)a;
    const file_info *fb = (const file_info *)b;
    return (fb->mtime - fa->mtime);
}

/**
 * Main ls function displaying files.
 * @param flags => a base structure containing flags
 * @param path => given path to dir.
 */
static int main_ls(ls_flags *flags, const char *path){
    int count = 0;

    DIR *dir = opendir(path);
    if(!dir){
        printf("[!] Error opening folder.\n");
        return 1;
    }

    struct dirent *entry;
    file_info *files = NULL;

    while((entry = readdir(dir)) != NULL){
        if(!flags->show_hidden && entry->d_name[0] == '.')
            continue;

        file_info *tmp = realloc(files, (count + 1) * sizeof(file_info));
        if(!tmp){
            free(files);
            return 1;
        }

        files = tmp;
        file_info *current = &files[count];

        snprintf(current->name, sizeof(current->name), "%s", entry->d_name);

        char fullpath[512];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        if (stat(fullpath, &current->statbuf) == 0)
            current->mtime = current->statbuf.st_mtime;
        else
            current->mtime = 0;

        count++;
    }   

    if(flags->sort_time)
        qsort(files, count, sizeof(file_info), compare_time);

    for(int i = 0; i < count; i++){
        file_info *f = &files[i];

        if(flags->long_format){
            char timebuf[64];
            struct tm *tm_info = localtime(&f->mtime);
            strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", tm_info);

            printf("%ld %s %s\n", (long)f->statbuf.st_size, timebuf, f->name);
        }
        else {
            printf("%s\n", f->name);
        }
    }

    free(files);
    return 0;
}

//entry
int main(int argc, char **argv){
    int opt;
    char *c_path = NULL;

    //struct
    ls_flags *flags = (ls_flags*)calloc(1, sizeof(ls_flags));
    if(!flags)
        return 1;

    //check help function.
    if(argc > 1 && (strcmp(argv[1], "--help") == 0)){
        print_help(argv[0]);
        return 0;
    }

    //parsing flags.
    while((opt = getopt(argc, argv, "alht")) != -1){
        switch(opt){
            case 'a':
                flags->show_hidden = 1; break;
            case 'l':
                flags->long_format = 1; break;
            case 'h':
                print_help(argv[0]);
                return 0;
            case 't':
                flags->show_hidden = 1; break;
            case '?':
                fprintf(stderr, "[!] Usage: %s [-a] [-l] [-t] [-h] [files...]\n", argv[0]);
                return 1;
            default:
                return 1;
        }
    }

    //assigning path.
    c_path = optind == argc ? "." : argv[optind];

    //base checks.
    if(is_valid_path(c_path) != 0){
        printf("[!] Invalid path.\n");
        return 1;
    }

    if(access(c_path, R_OK | X_OK) != 0){
        printf("[!] No access to %s \n", c_path);
        return 1;
    }

    return main_ls(flags, c_path);
}