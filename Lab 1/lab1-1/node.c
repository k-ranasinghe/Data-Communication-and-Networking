// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // includes malloc(),free()
#include <string.h> // includes strlen(), memcpy()
#include <ctype.h> // includes toupper(), tolower()

// user-defined header files
#include "node.h" // do not modify this file

// put your function prototypes for additional helper functions below:


// implementation
void insert_node_before(list *lst, int index, char *word)
{
    node *new_node = (node *)malloc(sizeof(node));
    new_node->word = (char *)malloc(strlen(word)+1);
    strcpy(new_node->word, word);
    new_node->prev = NULL;
    new_node->next = NULL;
    if (lst->head == NULL || index == 0) {
        new_node->next = lst->head;
        if (lst->head != NULL) {
            lst->head->prev = new_node;
        }
        lst->head = new_node;
    } else if (index < 0){
        node *current = lst->head;
        while (current->next) {
            current = current->next;
        }
        for (int i = 0; i > index + 1; i--){
            current = current->prev;
        }
        new_node->next = current;
        new_node->prev = current->prev;
        current->prev->next = new_node;
        current->prev = new_node;
    } else {
        node *current = lst->head;
        for (int i = 0; i < index - 1 && current->next != NULL; ++i) {
            current = current->next;
        }
        new_node->next = current->next;
        if (current->next != NULL) {
            current->next->prev = new_node;
        }
        current->next = new_node;
        new_node->prev = current;
    }
}

void insert_node_after(list *lst, int index, char *word)
{
    node *new_node = (node *)malloc(sizeof(node));
    new_node->word = (char *)malloc(strlen(word)+1);
    strcpy(new_node->word, word);
    new_node->prev = NULL;
    new_node->next = NULL;

    if (lst->head == NULL) {
        lst->head = new_node;
    } else if (index < 0){
        node *current = lst->head;
        while (current->next) {
            current = current->next;
        }
        for (int i = 0; i > index + 1; i--){
            current = current->prev;
        }
        current->next = new_node;
        new_node->prev = current;
        new_node->next = NULL;
    } else {
        node *current = lst->head;
        for (int i = 0; i < index && current->next != NULL; ++i) {
            current = current->next;
        }
        if (current->next == NULL) {
            current->next = new_node;
            new_node->prev = current;
        } else {
            new_node->next = current->next;
            new_node->prev = current;
            current->next->prev = new_node;
            current->next = new_node;
        }
    }
}

char *list_to_sentence(list *lst)
{
    int total_length = 0;
    node *current = lst->head;
    while (current != NULL) {
        total_length += strlen(current->word) + 1; // +1 for space separator or null terminator
        current = current->next;
    }

    char *sentence = (char *)malloc(total_length);
    sentence[0] = '\0'; // Initialize as an empty string

    current = lst->head;
    while (current != NULL) {
        strcat(sentence, current->word);
        strcat(sentence, " ");
        current = current->next;
    }

    sentence[total_length - 1] = '\0';

    return sentence;
}

void delete_node(list *lst, int index)
{
    if (index == 0) {
        node *temp = lst->head;
        lst->head = lst->head->next;
        free(temp->word);
        free(temp);
    } else if (index > 0){
        node *current = lst->head;
        for (int i = 0; i < index - 1 && current->next != NULL; ++i) {
            current = current->next;
        }
        node *temp = current->next;
        current->next = temp->next;
        free(temp->word);
        free(temp);
    } else if (index == -1){
        node *current = lst->head;
        while (current->next) {
            current = current->next;
        }
        current->prev->next = NULL;
        free(current->word);
        free(current);
    } else {
        node *current = lst->head;
        while (current->next) {
            current = current->next;
        }
        for (int i = 0; i > index + 2; i--){
            current = current->prev;
        }
        node *temp = current->prev;
        current->prev = temp->prev;
        temp->prev->next = current;
        free(temp->word);
        free(temp);
    }
}

void delete_list(list *lst)
{
    node *current = lst->head;
    while (current != NULL) {
        node *temp = current;
        current = current->next;
        free(temp->word);
        free(temp);
    }
    lst->head = NULL;
}