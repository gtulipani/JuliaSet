#include <stdlib.h>
#include <memory.h>
#include <printf.h>
#include "../lib/Resolution.h"
#include "../lib/TypeConverter.h"

char *delim = "x";

Resolution *createResolution(int wPixels, int hPixels) {
    Resolution *res;
    if ((res = (Resolution *) malloc(sizeof(Resolution))) == NULL) {
        return NULL;
    }

    res->width = wPixels;
    res->height = hPixels;

    return res;
}

void parseResolution(CustomString *pStr, Resolution *res, int *success, CustomString *errorMessage) {
    CustomString *aux = initializeString(STRING_MAX);
    stringCopy(aux, pStr);
    CustomString *wPixels = stringToken(aux, delim);
    CustomString *hPixels = stringToken(NULL, delim);
    if (hPixels != NULL) {
        int wPixelsQuantity, hPixelsQuantity;
        str2int(&wPixelsQuantity, wPixels->characters, 10);
        str2int(&hPixelsQuantity, hPixels->characters, 10);
        res->width = wPixelsQuantity;
        res->height = hPixelsQuantity;
        *success = 1;
        freeString(hPixels);
    } else {
        *success = 0;
        sprintf(aux->characters, "The value %s couldn't be parsed", pStr->characters);
        stringCopy(errorMessage, aux);
    }
    freeString(wPixels);
    freeString(aux);
}

void freeResolution(Resolution *pRes) {
    free(pRes);
}