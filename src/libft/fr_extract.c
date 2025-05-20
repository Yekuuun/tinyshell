#include "tinyshell.h"

/**
 * Check is character is a special meta character
 */
static bool is_shell_metacharacter(char c) {
    return (c == '|' || c == '<' || c == '>');
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