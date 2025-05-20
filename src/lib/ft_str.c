#include "tinyshell.h"

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
    int i;

    for(i = 0; *s1 && *s2; i++){
        if (s1[i] == s2[i] || (s1[i] ^ 32) == s2[i])
           continue;
        else
           break;
    }

    if(s1[i] == s2[i])
        return 0;

    if ((s1[i] | 32) < (s2[i] | 32)) 
        return -1;
    
    return 1;
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
    return dup;
}

/**
 * Extract a word from an str.
 */
char *ft_extract_word(const char *line, int *i){
    int start = *i;
    while (line[*i] && line[*i] != ' ' && line[*i] != '\t')
        (*i)++;

    int len = *i - start;
    char *word = malloc(len + 1);
    if (!word)
        return NULL;

    strncpy(word, line + start, len);
    word[len] = '\0';
    return word;
}