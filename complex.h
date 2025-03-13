#ifndef COMPLEX_H
#define COMPLEX_H

typedef struct {
    double real;
    double img;
} Complex;

Complex* create_complex(const double x, const double y);
Complex* add_complex(const Complex* c1, const Complex* c2);
Complex* multiply_complex(const Complex* c1, const Complex* c2);

void print_complex(const Complex* c);

#endif


