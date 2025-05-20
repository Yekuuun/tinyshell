#include "tinyshell.h"

/**
 * Check is character is a special meta character
 */
static bool is_shell_metacharacter(char c) {
    return (c == '|' || c == '<' || c == '>');
}


/**
 * Add a character to dynamic buffer if necessary using realloc.
 */
static int ft_append_char(char **buffer, int *len, int *cap, char c) {
    if (*len + 1 >= *cap) {
        *cap *= 2;
        char *new_buf = realloc(*buffer, *cap);
        if (!new_buf)
            return -1;
            
        *buffer = new_buf;
    }
    (*buffer)[(*len)++] = c;
    return 0;
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

/**
 * Extract a word from an str.
 */
char *ft_extract_word(const char *input, int *index) {
    int i = *index;
    int len = 0, cap = MAX_TOKEN_LEN;
    e_quote_state state = DEFAULT;

    char *buffer = malloc(cap);
    if (!buffer)
        return NULL;

    while (input[i]) {
        char c = input[i];

        if (state == DEFAULT && is_shell_metacharacter(c)) {
            if (len == 0) {
                buffer[len++] = c;
                i++;
            }
            break;
        }

        if (state == DEFAULT && (c == ' ' || c == '\t'))
            break;

        if (c == '\'' && state == DEFAULT) {
            state = SINGLE;
            i++;
            continue;
        } 
        else if (c == '\'' && state == SINGLE) {
            state = DEFAULT;
            i++;
            continue;
        } 
        else if (c == '"' && state == DEFAULT) {
            state = DOUBLE;
            i++;
            continue;
        } 
        else if (c == '"' && state == DOUBLE) {
            state = DEFAULT;
            i++;
            continue;
        }

        if (c == '\\') {
            i++;
            if (input[i]) {
                if (state == SINGLE) {
                    if (ft_append_char(&buffer, &len, &cap, '\\') < 0)
                        return NULL;

                    continue;
                }

                if (ft_append_char(&buffer, &len, &cap, input[i]) < 0)
                    return NULL;

                i++;
                continue;
            } 
            else {
                break; 
            }
        }

        if (ft_append_char(&buffer, &len, &cap, c) < 0)
            return NULL;

        i++;
    }

    if (state != DEFAULT) {
        free(buffer);
        return NULL; // error in quotes
    }

    buffer[len] = '\0';
    *index = i;

    return buffer;
}