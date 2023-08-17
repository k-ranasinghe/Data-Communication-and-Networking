// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // stdlib includes malloc() and free()
#include <string.h> // includes strlen(), memcpy()
#include <ctype.h> // includes toupper(), tolower()

// user-defined header files
#include "node.h"

// macros

#define INSERT_BEFORE 1
#define INSERT_AFTER 2
#define DELETE_NODE 3
#define DELETE_LIST 4

// function prototypes
void print_list(list * lst); 
void run(list * lst);


int main()
{
    list * lst = (list *) malloc(sizeof(list));
    lst->head = NULL;
	run(lst);
    print_list(lst);
    free(lst);
	return 0;
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