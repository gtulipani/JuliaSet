#include <stdlib.h>
#include "Resolution.h"

Resolution *createResolution(int wPixels, int hPixels) {
    Resolution *res;
    if ((res = (Resolution *) malloc(sizeof(Resolution))) == NULL) {
        return NULL;
    }

    res->width = wPixels;
    res->height = hPixels;

    return res;
}

void freeResolution(Resolution *pRes) {
    free(pRes);
}