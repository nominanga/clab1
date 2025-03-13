#ifndef TYPES_H
#define TYPES_H

typedef enum {
    INT,
    DOUBLE,
    COMPLEX,
    FUCK
} DataType;

void* sum(const void* a, const void* b, DataType type);
void* copy(const void* a, DataType type);
void* product(const void* a, const void* b, DataType type);
void print(const void* data, DataType type);

#endif