#include <stdio.h>
#include <stdlib.h> // includes malloc(), free(), realloc()
#include <string.h> // includes memcpy()

#include "chain.h" // do not modify this file

// put your function prototypes for additional helper functions below:


// implementation
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


/*
    DO NOT MODIFY BELOW
*/
// print out matrix in row-major order
// elements in the same row are space-separated
// each row starts in a new line
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

//Add the rest of the functions needed for the chain below
