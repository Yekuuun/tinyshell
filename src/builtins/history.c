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

    new_node->cmd  = ft_str_dup(cmd);
    new_node->next = NULL;
    new_node->prev = NULL;

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
void display_history(){
    history *head = g_history_head;
    if(!head)
        return;

    printf("History :\n");
    while(head) {
        printf("\t%s\n", head->cmd);
        head = head->next;
    }
}

/**
 * Add a dedicated command to history double linked list.
 * @param head => ref to head of the list
 * @param cmd  => command typed by user.
 */
void add_to_history(history **head,const char *cmd){
    if(cmd == NULL)
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

        temp->next = new_node;
        new_node->prev = temp;
    }
}