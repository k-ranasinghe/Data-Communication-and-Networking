#include <stdio.h>
#include <stdlib.h> // includes malloc(), free(), realloc()
#include <string.h> // includes memcpy()

typedef struct {
    int **data;
    int num_rows;
    int num_cols;
} matrix;

typedef struct NODE {
    struct NODE *prev;
    struct NODE *next;
    matrix *mat;
} node;

typedef struct {
    node *head;
} chain;

// Function to create a matrix
matrix *create_matrix(int num_rows, int num_cols)
{   
    matrix *mat = (matrix *)malloc(sizeof(matrix));
    mat->num_rows = num_rows;
    mat->num_cols = num_cols;
    
    // Allocate memory for data in row-major order
    mat->data = (int **)malloc(num_rows * sizeof(int *));
    for (int i = 0; i < num_rows; ++i) {
        mat->data[i] = (int *)malloc(num_cols * sizeof(int));
        for (int j = 0; j < num_cols; ++j) {
            mat->data[i][j] = 0; // Initialize with zero
        }
    }
    
    return mat;
}

void add_row(matrix *mat, int *row)
{
    // Resize the matrix data array to accommodate the new row
    mat->data = (int **)realloc(mat->data, (mat->num_rows + 1) * sizeof(int *));
    mat->data[mat->num_rows] = (int *)malloc(mat->num_cols * sizeof(int));

    // Copy the elements from the provided row to the new matrix row
    for (int i = 0; i < mat->num_cols; ++i) {
        mat->data[mat->num_rows][i] = row[i];
    }

    // Increment the number of rows in the matrix
    mat->num_rows++;
}

void add_col(matrix *mat, int *col)
{
    // For each row in the matrix, realloc the row to include the new column
    for (int i = 0; i < mat->num_rows; ++i) {
        mat->data[i] = (int *)realloc(mat->data[i], (mat->num_cols + 1) * sizeof(int));
        mat->data[i][mat->num_cols] = col[i];
    }

    // Increment the number of columns in the matrix
    mat->num_cols++;
}

void increment(matrix *mat, int num)
{
    for (int i = 0; i < mat->num_rows; ++i) {
        for (int j = 0; j < mat->num_cols; ++j) {
            mat->data[i][j] += num;
        }
    }
}

void scalar_multiply(matrix *mat, int num)
{
    for (int i = 0; i < mat->num_rows; ++i) {
        for (int j = 0; j < mat->num_cols; ++j) {
            mat->data[i][j] *= num;
        }
    }
}

void scalar_divide(matrix *mat, int num)
{
    for (int i = 0; i < mat->num_rows; ++i) {
        for (int j = 0; j < mat->num_cols; ++j) {
            mat->data[i][j] /= num;
        }
    }
}

int power(int base, int exponent) {
    int result = 1;
    for (int i = 0; i < exponent; ++i) {
        result *= base;
    }
    return result;
}

void scalar_power(matrix *mat, int num)
{
    for (int i = 0; i < mat->num_rows; ++i) {
        for (int j = 0; j < mat->num_cols; ++j) {
            mat->data[i][j] = power(mat->data[i][j], num);
        }
    }
}

void delete_matrix(matrix *mat)
{
    for (int i = 0; i < mat->num_rows; ++i) {
        free(mat->data[i]);
    }
    free(mat->data);
    free(mat);
}

void print_matrix(matrix *mat) 
{
    int row_idx, col_idx;
    for(row_idx = 0; row_idx < mat->num_rows; ++row_idx) {
        for(col_idx = 0; col_idx < mat->num_cols; ++col_idx) {
            if (col_idx == mat->num_cols-1) {
                printf("%d\n", mat->data[row_idx][col_idx]);
            } else {
                printf("%d ", mat->data[row_idx][col_idx]);
            }
        }
    }
}

// Print the chain of matrices
void print_chain(chain * chn)
{
   node *current = chn->head;
    while (current->next != NULL) {
        current = current->next;
    }

    while (current != NULL) {
        for (int i = 0; i < current->mat->num_rows; ++i) {
            for (int j = 0; j < current->mat->num_cols; ++j) {
                printf("%d ", current->mat->data[i][j]);
            }
            printf("\n");
        }
        current = current->prev;
    }
}

void run(chain *chn) {
    int num_rows;
    scanf("%d", &num_rows);
    getchar(); // Read the newline character after the integer

    int **rows = (int **)malloc(num_rows * sizeof(int *));
    int *row_lengths = (int *)malloc(num_rows * sizeof(int));

    for (int i = 0; i < num_rows; i++) {
        char input[100];
        fgets(input, sizeof(input), stdin);

        int count = 0;
        int size = 5; // Initial size of the array
        int *digits = (int *)malloc(size * sizeof(int));

        char *token = strtok(input, " ");
        while (token != NULL) {
            if (count >= size) {
                size *= 2; // Double the size if needed
                digits = (int *)realloc(digits, size * sizeof(int));
            }
            digits[count] = atoi(token);
            count++;
            token = strtok(NULL, " ");
        }

        rows[i] = digits;
        row_lengths[i] = count;
    }

    // Find the maximum number of columns
    int max_cols = 0;
    for (int i = 0; i < num_rows; i++) {
        if (row_lengths[i] > max_cols) {
            max_cols = row_lengths[i];
        }
    }

    // Create the matrix
    matrix *new_mat = create_matrix(num_rows, max_cols);
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < row_lengths[i]; j++) {
            new_mat->data[i][j] = rows[i][j];
        }
    }

    // Create a new node for the chain
    node *new_node = (node *)malloc(sizeof(node));
    new_node->mat = new_mat;
    new_node->prev = NULL;
    new_node->next = chn->head;
    if (chn->head != NULL) {
        chn->head->prev = new_node;
    }
    chn->head = new_node;

    // Free the dynamically allocated memory for rows and row_lengths
    for (int i = 0; i < num_rows; i++) {
        free(rows[i]);
    }
    free(rows);
    free(row_lengths);

    // Process the matrix operations
    int function_code;
    while (1) {
        char input[100];
        fgets(input, sizeof(input), stdin);

        // Process the input and count the number of digits
        int count = 0;
        int size = 5; // Initial size of the array
        int *func = (int *)malloc(size * sizeof(int));

        char *token = strtok(input, " ");
        while (token != NULL) {
            if (count >= size) {
                size *= 2; // Double the size if needed
                func = (int *)realloc(func, size * sizeof(int));
            }
            func[count] = atoi(token);
            count++;
            token = strtok(NULL, " ");
        }
        function_code = func[0];
        int *new_func = (int *)malloc((count - 1) * sizeof(int));

        for (int i = 1; i < count; i++) {
            new_func[i - 1] = func[i];
        }

        if (function_code == 0) {
            break;
        }
        
        print_chain(chn);
        printf("\n");

        // Apply the appropriate operation based on the function code
        switch (function_code) {
            case 2: {
                add_row(new_mat, new_func);
                free(new_func);
                break;
            }
            case 3: {
                add_col(new_mat, new_func);
                free(new_func);
                break;
            }
            case 4: {
                increment(new_mat, new_func[0]);
                free(new_func);
                break;
            }
            case 5: {
                scalar_multiply(chn->head->mat, new_func[0]);
                free(new_func);
                break;
            }
            case 6: {
                scalar_divide(chn->head->mat, new_func[0]);
                free(new_func);
                break;
            }
            case 7: {
                scalar_power(chn->head->mat, new_func[0]);
                free(new_func);
                break;
            }
            case 8: {
                delete_matrix(chn->head->mat);
                chn->head = chn->head->next;
                if (chn->head != NULL) {
                    free(chn->head->prev);
                    chn->head->prev = NULL;
                }
                break;
            }
            default: {
                printf("Invalid function code.\n");
                break;
            }
        }
    }
}

int main()
{
    chain * chn = (chain *) malloc(sizeof(chain));
    chn->head = NULL;
	run(chn);
    print_chain(chn);
    free(chn);
	return 0;
}
