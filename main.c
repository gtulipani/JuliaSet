#include <stdio.h>
#include "Resolution.h"
#include "ComplexNumber.h"
#include "IntVector.h"

#define PGM_FIRST_LINE "P2"

#define INTENSITY_VALUES 256
#define MAX_INTENSITY (INTENSITY_VALUES - 1)
#define FRACTAL_MAXIMUM 2
#define DEFAULT_SEED_X (-0.726895347709114071439L)
#define DEFAULT_SEED_Y 0.188887129043845954792L
#define DEFAULT_RESOLUTION_WIDTH 640
#define DEFAULT_RESOLUTION_HEIGHT 480
#define DEFAULT_WIDTH 2.0F
#define DEFAULT_HEIGHT 2.0F
#define DEFAULT_OUTPUT "output.pgm"
#define DEFAULT_CENTER_X 0L
#define DEFAULT_CENTER_Y 0L

/**
 * Relative center to the upper left corner from the plain to be drawed, calculated based on the width and height.
 * E.g. if the width is 7 and the height is 5, the center will have the coordinates: (3, 2). The rows and columns
 * start from 0
 */
IntVector *rowAndColumnCenter;
/**
 * Center position from whom the fractal will be drawed, according to the users input
 */
ComplexNumber *fractalCenter;
ComplexNumber *seed;
long double widthPerPixel;
long double heightPerPixel;

/**
 * Obtains the X Coordinate from the center of the screen to be drawed
 * @param center {@link IntVector} Relative center to the upper left corner from the plain to be drawed
 * @param column Coordinate where the column to transform is currently located from left to right
 * @return
 */
long double getXCoordinate(IntVector *center, long double column) {
    return ((-1) * center->x) + column;
}

/**
 * Obtains the Y Coordinate from the center of the screen to be drawed
 * @param center {@link IntVector} Relative center to the upper left corner from the plain to be drawed
 * @param row Coordinate where the row to transform is currently located from left to right
 * @return
 */
long double getYCoordinate(IntVector *center, long double row) {
    return center->y - row;
}

ComplexNumber *createComplexByAddress(int row, int column) {
    long double real = getXCoordinate(rowAndColumnCenter, column) * widthPerPixel;
    long double imaginary = getYCoordinate(rowAndColumnCenter, row) * heightPerPixel;
    ComplexNumber *result = createComplexNumber(real, imaginary);
    sumComplex(result, fractalCenter); //Move the point according to the user's input
    return result;
}

int createFractal(Resolution *pRes) {
    FILE *output;
    if ((output = fopen(DEFAULT_OUTPUT, "w")) == NULL) {
        fprintf(stderr, "No se pudo crear archivo");
        return -1;
    }
    fprintf(output, "%s\n", PGM_FIRST_LINE);
    fprintf(output, "%d %d\n", pRes->width, pRes->height);
    fprintf(output, "%d\n", MAX_INTENSITY);

    // Iterate per row
    for (int row = 0; row < pRes->height; row++) {
        // Iterate per column
        for (int column = 0; column < pRes->width; column++) {
            ComplexNumber *complex = createComplexByAddress(row, column);
            int intensity;
            // Iterate and determinate intensity
            for (intensity = 0; intensity < MAX_INTENSITY; ++intensity) {
                if (absComplex(complex) > FRACTAL_MAXIMUM) {
                    break;
                }
                powComplex(complex, 2);
                sumComplex(complex, seed);
            }
            fprintf(output, "%d\n", intensity);
            freeComplex(complex);
        }
    }
    fclose(output);
    return 0;
}

int main(int argc, char *argv[]) {
    float width = DEFAULT_WIDTH;
    float height = DEFAULT_HEIGHT;
    int resolution_x = DEFAULT_RESOLUTION_WIDTH;
    int resolution_y = DEFAULT_RESOLUTION_HEIGHT;
    long double seed_x = DEFAULT_SEED_X;
    long double seed_y = DEFAULT_SEED_Y;
    long double center_x = DEFAULT_CENTER_X;
    long double center_y = DEFAULT_CENTER_Y;

    Resolution *pRes = createResolution(resolution_x, resolution_y);
    seed = createComplexNumber(seed_x, seed_y);
    rowAndColumnCenter = createIntVector((pRes->width) / 2, (pRes->height) / 2);

    widthPerPixel = (width / (pRes->width));
    heightPerPixel = (height / (pRes->height));

    fractalCenter = createComplexNumber(center_x, center_y);
    createFractal(pRes);
    // Free Memory
    freeResolution(pRes);
    freeComplex(seed);
    freeIntVector(rowAndColumnCenter);
    freeComplex(fractalCenter);
}