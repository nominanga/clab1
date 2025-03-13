#include "matrix.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>

    Matrix* create_matrix(int rows, int cols, DataType type) {

        if (rows <=0 || cols <= 0) {
            printf("Declaration failure: rows and columns amount must not equal to zero\n");
            return NULL;
        }

        Matrix* m = (Matrix*)malloc(sizeof(Matrix));
        if (m == NULL) {
            printf("Memory allocation failed\n");
            return NULL;
        }
        m->rows = rows;
        m->cols = cols;
        m->type = type;

        m->data = (void***)malloc(rows * sizeof(void**));
        if (m->data == NULL) {
            free(m);
            printf("Memory allocation failed\n");
            return NULL;
        }
        for (int i = 0; i < rows; i++) {
            m->data[i] = (void**)malloc(cols * sizeof(void*));
            if (m->data[i] == NULL) {
                for (int j = 0; j < m->rows; j++) { 
                    free(m->data[i]);
                }
                free(m->data);
                free(m);
                printf("Memory allocation failed\n");
                return NULL;
            }
        }

        return m;
    }

void free_matrix(Matrix* m) {
    if (m == NULL) {
        return;
    }

    for (int i = 0; i < m->rows; i++) { 
        free(m->data[i]);
    }
    free(m->data);
    free(m);
}

void set_matrix(const void* element, Matrix* m, DataType type) {
    if (m == NULL) {
        printf("Operations with null matrix due to failed allocation\n");
        return;
    }

    if (type != m->type) {
        printf("Types compatibilty error\n");
        free_matrix(m);
        m = NULL;
        return;
    }

    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            m->data[i][j] = copy(element, type);
        }
    }
    
}

void set_element(const void* element, Matrix* m, int i, int j, DataType type) {
    if (m == NULL) {
        printf("Operations with null matrix due to failed allocation\n");
        return;
    }

    if (type != m->type) {
        printf("Types compatibilty error\n");
        free_matrix(m);
        m = NULL;
        return;
    }

    if (i > m->rows-1 || j > m->cols-1 || i < 0 || j < 0) {
        printf("Index Error\n");
        return;
    }

    m->data[i][j] = copy(element, type);
    
}

void print_matrix(const Matrix* m) {
    if (m == NULL) {
        printf("Operations with null matrix due to failed allocation\n");
        return;
    }

    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            if (m->data[i][j])
            print(m->data[i][j], m->type);
        }
        printf("\n");
    }
}

Matrix* add_matrix(const Matrix* a, const Matrix* b) {
    if (a == NULL || b == NULL) {
        printf("Operations with null matrix due to failed allocation\n");
        return NULL;
    }

    if (a->rows != b->rows || a->cols != b->cols) {
        printf("Failed addition: matrix 1 and matrix 2 must be the same size\n");
        return NULL;
    }

    if (a->type != b->type) {
        printf("Failed addition: matrix 1 and matrix 2 must contain same data types\n");
        return NULL;
    }

    Matrix* result_matrix = create_matrix(a->rows, a->cols, a->type);

    if (result_matrix) {
        for (int i = 0; i < result_matrix->rows; i++) {
            for (int j = 0; j < result_matrix->cols; j++) {
                result_matrix->data[i][j] = sum(a->data[i][j], b->data[i][j], a->type);
            }
        }
    }

    return result_matrix;
}

Matrix* transpose_matrix(const Matrix* m) {
    if (m == NULL) {
        printf("Operations with null matrix due to failed allocation\n");
        return NULL;
    }

    Matrix* transposed_matrix = create_matrix(m->cols, m->rows, m->type);

    if (transposed_matrix) {
        for (int i = 0; i < transposed_matrix->rows; i++) {
            for (int j = 0; j < transposed_matrix->cols; j++) {
                transposed_matrix->data[i][j] = copy(m->data[j][i], m->type);
            }
        }
    }

    return transposed_matrix;
}

Matrix* multiply_matrix(const Matrix* a, const Matrix* b) {
    if (a == NULL || b == NULL) {
        printf("Operations with null matrix due to failed allocation\n");
        return NULL;
    }

    if (a->cols != b-> rows) {
        printf("Failed multiplication: matrix 1 columns amount must be equal to matrix 2 rows amount\n");
        return NULL;
    }

    if (a->type != b->type) {
        printf("Failed multiplication: matrix 1 and matrix 2 must contain same data types\n");
        return NULL;
    }

    Matrix* product_matrix = create_matrix(a->rows, b->cols, a->type);

    if (product_matrix) {
        for (int i = 0; i < product_matrix->rows; i++) {
            for (int j = 0; j < product_matrix->cols; j++) {
                product_matrix->data[i][j] = copy(product(a->data[i][0], b->data[0][j], a->type), a->type);
                for (int k = 1; k < a->cols; k++) {
                    product_matrix->data[i][j] = sum(product_matrix->data[i][j], product(a->data[i][k], b->data[k][j], a->type), a->type);
                }
            }
        }
    }

    return product_matrix;
}

Matrix* add_linear_combination(const void* scalar, const Matrix* m, int row, DataType type) {
    if (m == NULL) {
        printf("Operations with null matrix due to failed allocation\n");
        return NULL;
    }

    if (type != m->type) {
        printf("TypeError: Scalar must be the same type as matrix values\n");
        return NULL;
    }

    if (row > m->rows-1 || row < 0) {
        printf("Index Error\n");
        return NULL;
    }

    Matrix* result = create_matrix(m->rows, m->cols, m->type);

    for (int i = 0; i < m->cols; i++) {
        result->data[row][i] = copy(m->data[row][i], type);
    }

    for (int i = 0; i < m->rows; i++) {
        if (i == row) {
            continue;
        }
        for (int j = 0; j < m->cols; j++) {
            result->data[i][j] = copy(m->data[i][j], type);
            result->data[row][j] = sum(result->data[row][j], product(scalar, m->data[i][j], type), type);
        }
    }

    return result;
}

