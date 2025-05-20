#pragma once
#include "utils.h"

//global vars
extern volatile int RUNNING;
extern token *g_token_head;
extern ast *g_ast_head;

//input.c
int start_shell();

//builtins
void clear();
void pwd();
void exit(const char **args);

//ft_str
size_t ft_str_len(const char *str);
char* ft_str_ncpy(char *dest, const char *src, size_t n);
int ft_str_cmp(const char *s1, const char *s2);
char *ft_str_dup(const char *s);
char *ft_extract_word(const char *input, int *index);

//ft_type
int ft_type_tolower(int c);
int ft_type_isdigit(char c);

//ft_atoi
int ft_atoi(const char *str);

//lexing
token *lexer(const char *input);
void print_tokens(token *head);
void free_tokens(token **head);

//parsing
void free_ast(ast **node);
ast* parse_pipe(token **current);
