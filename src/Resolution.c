#include <stdlib.h>
#include <memory.h>
#include "../lib/Resolution.h"

char resolutionDelimiter[] = "x,";

Resolution *createResolution(int wPixels, int hPixels) {
    Resolution *res;
    if ((res = (Resolution *) malloc(sizeof(Resolution))) == NULL) {
        return NULL;
    }

    res->width = wPixels;
    res->height = hPixels;

    return res;
}

void validateResolutionParse(CustomString *pStr, str2int_errno wPixelsError, str2int_errno hPixelsError, int *success,
                             CustomString *errorMessage) {
    if (*success == TRUE) {
        *success = FALSE;
        if ((wPixelsError == STR2INT_INCONVERTIBLE) || (hPixelsError == STR2INT_INCONVERTIBLE)) {
            sprintf(errorMessage->characters, "The %s value can't be parsed as a resolution value.", pStr->characters);
        } else if ((wPixelsError == STR2INT_OVERFLOW) || (hPixelsError == STR2INT_OVERFLOW)) {
            sprintf(errorMessage->characters, "The %s value exceeds the maximum of %dx%d.", pStr->characters,
                    MAX_RESOLUTION_WIDTH, MAX_RESOLUTION_HEIGHT);
        } else if ((wPixelsError == STR2INT_UNDERFLOW) || (hPixelsError == STR2INT_UNDERFLOW)) {
            sprintf(errorMessage->characters, "The %s value falls behind the minimum of %dx%d.", pStr->characters,
                    MIN_RESOLUTION_WIDTH, MIN_RESOLUTION_HEIGHT);
        } else {
            *success = TRUE;
        }
    }
}

void validateResolutionValues(int wPixelsQuantity, int hPixelsQuantity, int *success, CustomString *errorMessage) {
    if (*success == TRUE) {
        *success = FALSE;
        if ((wPixelsQuantity > MAX_RESOLUTION_WIDTH) || (hPixelsQuantity > MAX_RESOLUTION_HEIGHT)) {
            sprintf(errorMessage->characters, "The %dx%d resolution exceeds the maximum of %dx%d.", wPixelsQuantity,
                    hPixelsQuantity, MAX_RESOLUTION_WIDTH, MAX_RESOLUTION_HEIGHT);
        } else if ((wPixelsQuantity < MIN_RESOLUTION_WIDTH) || (hPixelsQuantity < MIN_RESOLUTION_HEIGHT)) {
            sprintf(errorMessage->characters, "The  %dx%d value falls behind the minimum of %dx%d.", wPixelsQuantity,
                    hPixelsQuantity, MIN_RESOLUTION_WIDTH, MIN_RESOLUTION_HEIGHT);
        } else {
            *success = TRUE;
        }
    }
}

void parseResolution(CustomString *pStr, void *res, int *success, CustomString *errorMessage) {
    *success = TRUE;
    /* Divide the pStr in left and right parts */
    CustomString *wPixels = initializeString(STRING_MAX);
    CustomString *hPixels = initializeString(STRING_MAX);
    strdivide_errno result = stringDivide(pStr, wPixels, hPixels, resolutionDelimiter[0], resolutionDelimiter[1],
                                          FALSE);
    int wPixelsQuantity, hPixelsQuantity;

    switch (result) {
        case STR_DIVIDE_INVALID: {
            sprintf(errorMessage->characters, "The %s value can't be parsed as a resolution value.", pStr->characters);
            *success = FALSE;
            break;
        }
        case STR_DIVIDE_SUCCESS: {
            str2int_errno wPixelsError = str2int(&wPixelsQuantity, wPixels->characters, 10);
            str2int_errno hPixelsError = str2int(&hPixelsQuantity, hPixels->characters, 10);
            validateResolutionParse(pStr, wPixelsError, hPixelsError, success, errorMessage);
            validateResolutionValues(wPixelsQuantity, hPixelsQuantity, success, errorMessage);
            if (*success == TRUE) {
                ((Resolution *) res)->width = wPixelsQuantity;
                ((Resolution *) res)->height = hPixelsQuantity;
            }
            break;
        }
        case STR_DIVIDE_ONLY_LEFT: {
            sprintf(errorMessage->characters, "The %s value can't be parsed as a resolution value.", pStr->characters);
            *success = FALSE;
            break;
        }
    }

    freeString(wPixels);
    freeString(hPixels);
}

void freeResolution(Resolution *pRes) {
    free(pRes);
}

