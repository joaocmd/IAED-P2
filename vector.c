#include "vector.h"

/* Checks if the whole vector is occupied, if it is,
reallocates space for the vector. */
void checkVectorSize(Vector vector);

Vector initVector(int size)
{
    Vector vector = (Vector) malloc(sizeof(struct vec));
    vector->elements = (unsigned long*) malloc(sizeof(unsigned long) * size);
    vector->length = 0;
    vector->sizeUsed = size;

    return vector;
}

void freeVector(Vector vector)
{
    free(vector->elements);
    free(vector);
}

void addElementVec(Vector vector, unsigned long element)
{
    vector->elements[vector->length] = element;
    checkVectorSize(vector);
    vector->length++;
}

int hasElementVec(Vector vector, unsigned long element)
{
    int i;
    for (i = 0; i < vector->length; i++) {
        if (vector->elements[i] == element) {
            return 1;
        }
    }
    return 0;
}

void checkVectorSize(Vector vector)
{
    if (vector->length == vector->sizeUsed) {
        vector->sizeUsed *= 2;
        vector->elements = (unsigned long*) realloc(vector->elements, sizeof(unsigned long) * vector->sizeUsed);
    }
}
