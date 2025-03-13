#include "complex.h"
#include <stdlib.h>
#include <stdio.h>

Complex* create_complex(const double x, const double y) {
    Complex* c = (Complex*)malloc(sizeof(Complex));
    if (c == NULL){
        printf("Memory allocation failed\n");
        return NULL;
    }
    c->real = x;
    c->img = y;
    return c;
}

void print_complex(const Complex* c) {
    printf("  %g + %gi  ", c->real, c->img);
}

Complex* add_complex(const Complex* c1, const Complex* c2) {
    return create_complex(c1->real + c2->real, c1->img + c2-> img);
}

Complex* multiply_complex(const Complex* c1, const Complex* c2) {
    double real = c1->real * c2->real - c1->img * c2->img;
    double img = c1->real * c2->img + c1->img * c2->real;
    return create_complex(real, img);
}
