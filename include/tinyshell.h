#pragma once
#include "utils.h"

//input.c
int start_shell();

//builtins
void clear();

//lib
size_t ft_str_len(const char *str);
char* ft_str_ncpy(char *dest, const char *src, size_t n);
int ft_str_cmp(const char *s1, const char *s2);
char *ft_extract_word(const char *line, int *i);
char *ft_str_dup(const char *s);

//lexing
token *lexer(const char *input);
void print_tokens(token *head);
void free_tokens(token **head);
