#ifndef TP0_RESOLUTION_H
#define TP0_RESOLUTION_H

#include "TypeConverter.h"

/* Max Resolution: 5K */

#if !defined(MAX_RESOLUTION_WIDTH)
#define MAX_RESOLUTION_WIDTH 5120
#endif

#if !defined(MAX_RESOLUTION_HEIGHT)
#define MAX_RESOLUTION_HEIGHT 2880
#endif

#if !defined(MIN_RESOLUTION_WIDTH)
#define MIN_RESOLUTION_WIDTH 1
#endif

#if !defined(MIN_RESOLUTION_HEIGHT)
#define MIN_RESOLUTION_HEIGHT 1
#endif

typedef struct Resolution {
    int width;
    int height;
} Resolution;

/**
 * Creates a resolution instance
 * @param wPixels
 * @param hPixels
 * @return
 */
Resolution *createResolution(int wPixels, int hPixels);

/**
 * Parses the resolution value from pStr and updates success and errorMessage values
 * @param pStr
 * @param res
 * @param success
 * @param errorMessage
 */
void parseResolution(CustomString *pStr, void *res, int *success, CustomString *errorMessage);

/**
 * Frees the memory allocated for the resolution instance
 * @param pRes
 */
void freeResolution(Resolution *pRes);

#endif
