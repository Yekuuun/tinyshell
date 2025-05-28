/**
 * Contains a base implementation of (in memory) history command.
 * Notes : changes are not saved to a dedicated file.
 */

#include "tinyshell.h"

/**
 * Create a new history node.
 * @param cmd => command typed by user to archive
 */
static history* create_history_node(const char *cmd){
    history *new_node = (history*)malloc(sizeof(history));
    if(!new_node)
        return NULL;
    
    current_history_index = current_history_index + 1;

    new_node->cmd   = ft_str_dup(cmd);
    new_node->next  = NULL;
    new_node->prev  = NULL;
    new_node->index = current_history_index;

    return new_node;
}

/**
 * Freeing memory for history list.
 */
void free_history(history **ref){
    if(ref && *ref){
        history *temp = *ref;
        while(temp) {
            history *next = temp->next;
            free(temp->cmd);
            free(temp);
            temp = next;
        }
        
        *ref = NULL;
    }
}

/**
 * Display all history commands.
 */
int display_history(char **args){
    if(current_history_index == 0)
        return 0;

    history *head = g_history_head;
    if(!head)
        return 1;

    printf("History :\n");
    while(head) {
        printf("- %s\n", head->cmd);
        head = head->next;
    }

    return 0;
}

/**
 * Add a dedicated command to history double linked list.
 * @param head => ref to head of the list
 * @param cmd  => command typed by user.
 */
void add_to_history(history **head,const char *cmd){
    if(cmd == NULL)
        return;

    if(strcmp(cmd, "history") == 0)
        return;

    history *new_node = create_history_node(cmd);
    if(!new_node)
        return;

    if(*head == NULL){
        *head = new_node;
    }
    else{
        history *temp = *head;
        while(temp->next)
            temp = temp->next;

        if(strcmp(temp->cmd, cmd) == 0){
            free(new_node);
        }
        else {
            temp->next = new_node;
            new_node->prev = temp;
        }
    }
}