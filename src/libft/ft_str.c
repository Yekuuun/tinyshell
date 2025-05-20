#include "tinyshell.h"

/**
 * Check is character is a special meta character
 */
static bool is_shell_metacharacter(char c) {
    return (c == '|' || c == '<' || c == '>');
}

/**
 * Base str_len function.
 */
size_t ft_str_len(const char *str){
    int count = 0;
    while(*str != '\0'){
        count++;
        str++;
    }

    return count;
}


/**
 * A custom implementation of the strncpy function.
 */
char* ft_str_ncpy(char *dest, const char *src, size_t n){
    size_t i = 0;

    while(i < n && src[i] != '\0'){
        dest[i] = src[i];
        i++;
    }

    while(i < n){
        dest[i] = '\0';
        i++;
    }

    return dest;
}

/**
 * Custom non case sensitive strcmp function
 */
int ft_str_cmp(const char *s1, const char *s2){
    int i = 0;
    while(s1[i] && s2[i]){
        char c1 = ft_type_tolower((unsigned char)s1[i]);
        char c2 = ft_type_tolower((unsigned char)s2[i]);

        if(c1 != c2)
            return (c1 < c2) ? -1 : 1;
        
        i++;
    }

    char c1 = ft_type_tolower((unsigned char)s1[i]);
    char c2 = ft_type_tolower((unsigned char)s2[i]);

    if (c1 == c2)
        return 0;

    return (c1 < c2) ? -1 : 1;
}

/**
 * Custom implementation of strdup function.
 */
char *ft_str_dup(const char *s){
    size_t len = ft_str_len(s);
    if(len == 0)
        return NULL;

    char *dup  = malloc(len + 1);
    if(!dup)
        return NULL;

    ft_str_ncpy(dup, s, len);
    dup[len] = '\0';
    return dup;
}