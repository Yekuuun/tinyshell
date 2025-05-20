#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>

#define BUFFER_MAX 4096
#define MAX_PATH 4096
#define MAX_TOKEN_LEN 64

#define ANSI_COLOR_RED     "\x1b[91m"  // bright red
#define ANSI_COLOR_GREEN   "\x1b[92m"  // bright green
#define ANSI_COLOR_YELLOW  "\x1b[93m"  // bright yellow
#define ANSI_COLOR_BLUE    "\x1b[94m"  // bright blue
#define ANSI_COLOR_MAGENTA "\x1b[95m"  // bright magenta
#define ANSI_COLOR_CYAN    "\x1b[96m"  // bright cyan
#define ANSI_COLOR_RESET   "\x1b[0m"

//tokens.
typedef enum e_token_type {
    TOKEN_WORD,       // commande ou argument
    TOKEN_PIPE,       // |
    TOKEN_REDIR_IN,   // <
    TOKEN_REDIR_OUT,  // >
    TOKEN_HEREDOC,    // <<
    TOKEN_APPEND,     // >>
    TOKEN_END  
} e_token_type;

typedef struct token {
    e_token_type type;
    char *value;
    struct token *prev;
    struct token *next;
} token;

//quoting handling.
typedef enum e_quote_state {
    DEFAULT,
    SINGLE,
    DOUBLE
} e_quote_state;