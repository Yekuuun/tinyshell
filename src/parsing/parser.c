#include "tinyshell.h"

/**
 * Creating a single ast node.
 */
static ast* create_ast_node(e_ast_type type){
    ast *new_node = (ast*)malloc(sizeof(ast));
    if(!new_node)
        return NULL;

    //setting default.
    new_node->type     = type;
    new_node->left     = NULL;
    new_node->right    = NULL;
    new_node->argv     = NULL;
    new_node->filename = NULL;

    return new_node;
}

/**
 * Parsing a base command.
 */
static ast* parse_command(token **current){
    int i = 0;

    char **args = malloc(sizeof(char*) * MAX_ARGS);
    if(!args)
        return NULL;

    ast *cmd = create_ast_node(AST_COMMAND);
    if(!cmd)
        return NULL;
    
    while(*current && (*current)->type == TOKEN_WORD){
        args[i++] = ft_str_dup((*current)->value);
        *current  = (*current)->next;
    }

    args[i] = NULL;
    cmd->argv = args;

    return cmd;
}

/**
 * Creating a redirection node.
 */
static ast* parse_redirection(token **current, ast *cmd){
    e_token_type redir_type = (*current)->type;
    *current = (*current)->next;

    if(!*current || (*current)->type != TOKEN_WORD)
        return NULL;
    
    ast *redir_node = create_ast_node(
        redir_type == TOKEN_REDIR_OUT ? AST_REDIR_OUT :
        redir_type == TOKEN_REDIR_IN ? AST_REDIR_IN :
        redir_type == TOKEN_APPEND ? AST_REDIR_APPEND :
        redir_type == TOKEN_HEREDOC ? AST_HEREDOC :
        AST_REDIR_OUT // fallback
    );

    redir_node->filename = ft_str_dup((*current)->value);
    redir_node->left = cmd;

    *current = (*current)->next;

    return redir_node;
}

/**
 * Pipe management.
 */
ast* parse_pipe(token **current){
    ast *left = parse_command(current);
    if(!left)
        return NULL;

    while (*current && (
        (*current)->type == TOKEN_REDIR_IN ||
        (*current)->type == TOKEN_REDIR_OUT ||
        (*current)->type == TOKEN_APPEND ||
        (*current)->type == TOKEN_HEREDOC)) {
        left = parse_redirection(current, left);
    }

    if(*current && (*current)->type == TOKEN_PIPE){
        *current = (*current)->next; //avoid | char.
        ast *pipe_node = create_ast_node(AST_PIPELINE);
        if(!pipe_node)
            return NULL;

        pipe_node->left  = left;
        pipe_node->right = parse_pipe(current);

        return pipe_node;
    }

    return left;
}

/**
 * Freeing nodes
 */
void free_ast(ast **node){
    if(!*node)
        return;

    if((*node)->argv){
        for(int i = 0; (*node)->argv[i] != NULL; i++)
            free((*node)->argv[i]);
        
        free((*node)->argv);
    }

    if((*node)->filename)
        free((*node)->filename);

    free_ast(&(*node)->left);
    free_ast(&(*node)->right);

    free((*node));
    *node = NULL;
}