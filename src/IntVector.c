#include <stdlib.h>
#include "IntVector.h"

IntVector *createIntVector(int x, int y) {
    IntVector *intVec;
    if ((intVec = (IntVector *) malloc(sizeof(IntVector))) == NULL) {
        return NULL;
    }

    intVec->x = x;
    intVec->y = y;

    return intVec;
}

void freeIntVector(IntVector *pIntVec) {
    free(pIntVec);
}

