#ifndef TP0_VECTOR_H
#define TP0_VECTOR_H

typedef struct IntVector {
    int x;
    int y;
} IntVector;

IntVector *createIntVector(int x, int y);

void freeIntVector(IntVector *pIntVec);

#endif
