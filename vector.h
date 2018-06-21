#ifndef VECTOR_H
#define VECTOR_H

typedef struct vec *Vector;

#include <stdlib.h>

struct vec {
    unsigned long* elements;
    int length, sizeUsed;
};

/* Allocates the necessary space for a vector, starting with
a given size. */
Vector initVector(int size);

/* Frees the allocated space by vector. */
void freeVector(Vector vector);

/* Returns wheter element is in the vector or not. */
int hasElementVec(Vector vector, unsigned long element);

/* Adds a new element to the vector. */
void addElementVec(Vector vector, unsigned long element);

#endif

