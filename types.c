#include "complex.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>

void* sum(const void* a, const void* b, DataType type) {
    void* result = NULL;

    switch (type) {
        case (INT):
            result = malloc(sizeof(int));
            if (result) *(int*)result = *(int*)a + *(int*)b; 
            break;
        case(DOUBLE):
            result = malloc(sizeof(double));
            if (result) *(double*)result = *(double*)a + *(double*)b; 
            break;
        case (COMPLEX):
            result = malloc(sizeof(Complex));
            Complex* tmp = add_complex((Complex*) a, (Complex*) b);
            if (result) *(Complex*)result = *tmp;
            free(tmp);
            break;
        default:
            printf("Unsupported type\n");
    }

    return result;
}

void* copy(const void* a, DataType type) {
    void* result = NULL;

    switch (type) {
        case (INT):
            result = malloc(sizeof(int));
            if (result) *(int*)result = *(int*)a; 
            break;
        case(DOUBLE):
            result = malloc(sizeof(double));
            if (result) *(double*)result = *(double*)a; 
            break;
        case (COMPLEX):
            result = malloc(sizeof(Complex));
            if (result) *(Complex*)result = *(Complex*)a;
            break;
        default:
            printf("Unsupported type\n");
    }

    return result;
}


void* product(const void* a, const void* b, DataType type) {
    void* result = NULL;

    switch (type) {
        case (INT):
            result = malloc(sizeof(int));
            if (result) *(int*)result = *(int*)a * *(int*)b; 
            break;
        case(DOUBLE):
            result = malloc(sizeof(double));
            if (result) *(double*)result = *(double*)a * *(double*)b; 
            break;
        case (COMPLEX):
            result = malloc(sizeof(Complex));
            Complex* tmp = multiply_complex((Complex*) a, (Complex*) b);
            if (result) *(Complex*)result = *tmp;
            free(tmp);
            break;
        default:
            printf("Unsupported type\n");
    }

    return result;
}

void print(const void* data, DataType type) {
    switch (type) {
        case (INT):
            printf("  %d  ", *(int*)data);
            break;
        case(DOUBLE):
            printf("  %g  ", *(double*)data);
            break;
        case (COMPLEX):
            print_complex((Complex*) data);
            break;
        default:
            printf("Unsupported type\n");
    }
}