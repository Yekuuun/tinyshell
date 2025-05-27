/**
 * A base implementation of the tree command written from scratch.
 * Author : Yekuuun
 * Github : https://github.com/Yekuuun
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#define MAX_DEPTH 20
#define MAX_PATH  4096

//Main struct for tree handling.
typedef struct tree {
    bool is_last_child[MAX_DEPTH];
    int file_count;
    int dir_count;
} tree;

/**
 * Check if path is valid. 
 * @param path => a path to check
 */
static int path_exist(const char *path){
    struct stat path_stat;
    return path && stat(path, &path_stat) == 0;
}

/**
 * Print data properly
 */
static void print_prefix(tree *ctx, int level){
    for(int i = 0; i < level; i++){
        if(i == level - 1){
            printf(ctx->is_last_child[i] ? "└───" : "├───");
        }
        else {
            printf(ctx->is_last_child[i] ? "    " : "│   ");
        }
    }
}

/**
 * Counting entries
 */
static int count_entries(DIR *dir){
    int count = 0;
    struct dirent *entry;
    rewinddir(dir);
    while((entry = readdir(dir)) != NULL){
        if(strcmp(entry->d_name, ".") && strcmp(entry->d_name, ".."))
            count++;
    }
    rewinddir(dir);
    return count;
}

/**
 * Main tree command implementation. 
 * @param ctx => ctx to implement the base code.
 */
static void main_tree(tree *ctx, const char *path, int level){
    DIR *dir;
    struct dirent *entry;
    struct stat statbuf;
    char new_path[MAX_PATH];

    if((dir = opendir(path)) == NULL){
        perror("opendir");
        return;
    }

    int total = count_entries(dir);
    int index = 0;

    while((entry = readdir(dir)) != NULL){
        if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(new_path, MAX_PATH, "%s/%s", path, entry->d_name);
        stat(new_path, &statbuf);

        bool is_dir = S_ISDIR(statbuf.st_mode);
        ctx->is_last_child[level] = (++index == total);

        print_prefix(ctx, level);
        printf("%s\n", entry->d_name);

        if(is_dir){
            ctx->dir_count++;
            main_tree(ctx, new_path, level + 1);
        } 
        else {
            ctx->file_count++;
        }
    }

    closedir(dir);
}

//start.
int main(int argc, char **argv){
    if(argc > 2){
        printf("[!] tree only takes 1 argument.\n");
        return EXIT_FAILURE;
    }

    //main path to start tree
    const char *path = (argc > 1) ? argv[1] : ".";

    if(path != '.' && !path_exist(path))
        return EXIT_FAILURE;

    if(access(path, R_OK | X_OK) != 0){
        printf("[!] No access to %s \n", path);
        return EXIT_FAILURE;
    }

    tree ctx = {0};
    main_tree(&ctx, path, 0);
    printf("\n%d directories, %d files\n", ctx.dir_count, ctx.file_count);
    return EXIT_SUCCESS;
}