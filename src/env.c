#include "tinyshell.h"

/**
 * Adding a custom path to ENV var
 */
int set_exec_env(const char *path){
    if(!path)
        return 1;
    
    char *new_path = NULL;

    const char *old_path = getenv("PATH");
    if(!old_path)
        return 1;

    
    size_t s_path = ft_str_len(path);
    size_t s_oldp = ft_str_len(old_path);
    size_t s_flen = (s_path + s_oldp + 2);

    new_path = malloc(s_flen * sizeof(char)); // +2 (: + '\0')
    if(!new_path)
        return 1;

    snprintf(new_path, (s_flen), "%s:%s", path, old_path);
    if (setenv("PATH", new_path, 1) != 0)
        return 1;

    free(new_path);
    return 0;
}