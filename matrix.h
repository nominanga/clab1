#ifndef MATRIX_H
#define MATRIX_H

#include "complex.h"
#include "types.h"

typedef struct {
    int rows;
    int cols;
    DataType type;
    void*** data;
} Matrix;

Matrix* create_matrix(int rows, int cols, DataType type);
void set_matrix(const void* element, Matrix* m, DataType type);
void set_element(const void* element, Matrix* m, int i, int j, DataType type);
void free_matrix(Matrix* m);
void print_matrix(const Matrix* m);
Matrix* add_matrix(const Matrix* a, const Matrix* b);
Matrix* multiply_matrix(const Matrix* a, const Matrix* b);
Matrix* transpose_matrix(const Matrix* m);
Matrix* add_linear_combination(const void* scalar, const Matrix* m, int row_number, DataType type);


#endif