#include "matrix.h"
#include "complex.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>

void print_menu() {
    printf("\n=== Matrix Operations Menu ===\n");
    printf("1. Create Matrix\n");
    printf("2. Set Matrix Element\n");
    printf("3. Print Matrix\n");
    printf("4. Add Matrices\n");
    printf("5. Multiply Matrices\n");
    printf("6. Transpose Matrix\n");
    printf("7. Add Linear Combination\n");
    printf("8. Exit\n");
    printf("Choose operation: ");
}

DataType choose_type() {
    printf("\nChoose data type:\n");
    printf("1. Integer\n");
    printf("2. Double\n");
    printf("3. Complex\n");
    printf("Enter choice: ");
    
    int choice;
    scanf("%d", &choice);
    while(getchar() != '\n');
    
    switch(choice) {
        case 1: return INT;
        case 2: return DOUBLE;
        case 3: return COMPLEX;
        default: printf("Invalid choice, using integer\n"); return INT;
    }
}

void input_element(DataType type, void** element) {
    switch(type) {
        case INT: {
            int val;
            printf("Enter integer value: ");
            scanf("%d", &val);
            *element = malloc(sizeof(int));
            *(int*)*element = val;
            break;
        }
        case DOUBLE: {
            double val;
            printf("Enter double value: ");
            scanf("%lf", &val);
            *element = malloc(sizeof(double));
            *(double*)*element = val;
            break;
        }
        case COMPLEX: {
            double real, img;
            printf("Enter complex (real imaginary): ");
            scanf("%lf %lf", &real, &img);
            *element = malloc(sizeof(Complex));
            ((Complex*)*element)->real = real;
            ((Complex*)*element)->img = img;
            break;
        }
    }
    while(getchar() != '\n');
}

Matrix* create_matrix_ui() {
    int rows, cols;
    printf("Enter matrix dimensions (rows cols): ");
    scanf("%d %d", &rows, &cols);
    DataType type = choose_type();
    
    Matrix* m = create_matrix(rows, cols, type);
    if(!m) return NULL;

    printf("Fill matrix:\n");
    void* element;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            printf("Element [%d][%d]: ", i, j);
            input_element(type, &element);
            set_element(element, m, i, j, type);
            free(element);
        }
    }
    return m;
}

void matrix_operations() {
    Matrix *m1 = NULL, *m2 = NULL, *result = NULL;
    int choice;
    
    do {
        print_menu();
        scanf("%d", &choice);
        while(getchar() != '\n');

        switch(choice) {
            case 1: {
                free_matrix(m1);
                m1 = create_matrix_ui();
                break;
            }
            case 2: {
                if(!m1) {
                    printf("Create matrix first!\n");
                    break;
                }
                int i, j;
                printf("Enter position (i j): ");
                scanf("%d %d", &i, &j);
                void* element;
                input_element(m1->type, &element);
                set_element(element, m1, i, j, m1->type);
                free(element);
                break;
            }
            case 3: {
                if(!m1) {
                    printf("Matrix not created!\n");
                    break;
                }
                printf("\nMatrix:\n");
                print_matrix(m1);
                break;
            }
            case 4: {
                free_matrix(m2);
                printf("Create second matrix:\n");
                m2 = create_matrix_ui();
                result = add_matrix(m1, m2);
                if(result) {
                    printf("\nResult:\n");
                    print_matrix(result);
                    free_matrix(result);
                }
                break;
            }
            case 5: {
                free_matrix(m2);
                printf("Create second matrix:\n");
                m2 = create_matrix_ui();
                result = multiply_matrix(m1, m2);
                if(result) {
                    printf("\nResult:\n");
                    print_matrix(result);
                    free_matrix(result);
                }
                break;
            }
            case 6: {
                result = transpose_matrix(m1);
                if(result) {
                    printf("\nTransposed:\n");
                    print_matrix(result);
                    free_matrix(result);
                }
                break;
            }
            case 7: {
                int row;
                printf("Enter row to modify: ");
                scanf("%d", &row);
                void* scalar;
                input_element(m1->type, &scalar);
                result = add_linear_combination(scalar, m1, row, m1->type);
                if(result) {
                    printf("\nResult:\n");
                    print_matrix(result);
                    free_matrix(result);
                }
                free(scalar);
                break;
            }
            case 8: {
                printf("Exiting...\n");
                break;
            }
            default: printf("Invalid choice!\n");
        }
    } while(choice != 8);

    free_matrix(m1);
    free_matrix(m2);
}

int main() {
    matrix_operations();
    return 0;
}