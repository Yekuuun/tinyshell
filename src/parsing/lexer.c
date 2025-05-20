#include "tinyshell.h"

/**
 * Define type of a token
 * @param str => ptr to the given str to define type. (ex : |, >, "echo")
 */
static e_token_type define_token_type(const char *str){
    if(!str)
        return TOKEN_END;

    if(ft_str_cmp(str, "|") == 0)
        return TOKEN_PIPE;
    
    if(ft_str_cmp(str, "<") == 0)
        return TOKEN_REDIR_IN;
    
    if(ft_str_cmp(str, ">") == 0)
        return TOKEN_REDIR_OUT;
    
    if(ft_str_cmp(str, ">>") == 0)
        return TOKEN_APPEND;
    
    if(ft_str_cmp(str, "<<") == 0)
        return TOKEN_HEREDOC;
    
    return TOKEN_WORD;
}

/**
 * Creating a new token.
 * @param value => value to insert in to new token. (ex : "echo")
 */
static token* create_token(const char *value){
    token* new_token = (token*)malloc(sizeof(token));

    if(new_token == NULL)
        return NULL;

    new_token->value = ft_str_dup(value);
    if(new_token->value == NULL){
        free(new_token);
        return NULL;
    }

    new_token->type  = define_token_type(value);
    new_token->next  = NULL;
    new_token->prev  = NULL;

    return new_token;
}

/**
 * Create a new token
 * @param value => a base input str.
 * @param head  => head of the double linked list handling tokens.
 */
static int insert_at_end(token **head, const char *value){
    token *new_token = create_token(value);
    if(new_token == NULL)
        return 1;

    if(*head == NULL){ //start
        *head = new_token;
    }
    else {
        token *temp = *head;
        while(temp->next != NULL)
            temp = temp->next;
        
        temp->next = new_token;
        new_token->prev = temp;
    }

    return 0;
}

/**
 * Print every single tokens from the list.
 */
void print_tokens(token *head){
    token *current = head;
    while(current){
        printf("Token: \"%s\", Type: %d\n", current->value, current->type);
        current = current->next;
    }
}

/**
 * Free memory for allocated tokens.
 */
void free_tokens(token **head){
    if (head && *head) {
        token *current = *head;
        while (current) {
            token *next = current->next;
            free(current->value);
            free(current);
            current = next;
        }
        *head = NULL;
    }
}

/**
 * Main function for lexing phase.
 * @param input => brut input string from fgets.
 */
token *lexer(const char *input){
    int i = 0;
    token *head = NULL;

    while(input[i]){
        if(input[i] == ' ' || input[i] == '\t'){
            i++;
            continue;
        }

        if(input[i] == '\0')
            break;

        //extract & create token.
        char *word = ft_extract_word(input, &i);
        if(word == NULL)
            return NULL;

        if(insert_at_end(&head, word) != 0)
        {
            free(word);
            return NULL;
        }

        free(word);
    }
    
    return head;
}