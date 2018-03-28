#ifndef TP0_RESOLUTION_H
#define TP0_RESOLUTION_H

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
Resolution* createResolution(int wPixels, int hPixels);

/**
 * Frees the memory allocated for the resolution instance
 * @param pRes
 */
void freeResolution(Resolution *pRes);

#endif
