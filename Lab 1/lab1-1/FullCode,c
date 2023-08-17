#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Node {
    struct Node *prev;
    struct Node *next;
    char *word;
} node;

typedef struct {
    node *head;
} list;

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

//Print the list contents
void print_list(list * lst)
{
    node *current = lst->head;
    while (current != NULL) {
        printf("%s ", current->word);
        current = current->next;
    }
    printf("\n");
}

// parse the input
void run(list *lst) 
{
    char input[100];
    fgets(input, sizeof(input), stdin);
    input[strlen(input) - 1] = '\0'; // Removing the newline character

    char* token = strtok(input, ",");
    while (token) {
        //insert(&list, token);
        insert_node_after(lst, -1, token);
        token = strtok(NULL, ",");
    }

    char inp[100];
    int num1=1, num2;
    char str[100];

    while (1) {
        fgets(inp, sizeof(inp), stdin);
        sscanf(inp,"%d %d %99s", &num1, &num2, str);

        if (num1 == 0) {
            break; // Exit loop on encountering 0
        }

        switch (num1) {
            case 1: // insert_node_before
                insert_node_before(lst, num2, str);
                break;
            case 2: // insert_node_after
                insert_node_after(lst, num2, str);
                break;
            case 3: // delete_node
                delete_node(lst, num2);
                break;
            case 4: // delete_list
                delete_list(lst);
                break;
            default:
                printf("Invalid choice! Please choose again.\n");
        }
    }
}

int main()
{
    list * lst = (list *) malloc(sizeof(list));
    lst->head = NULL;
	run(lst);
    print_list(lst);
    free(lst);
	return 0;
}
