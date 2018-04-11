#include <stdio.h>
#include <memory.h>
#include "../lib/Resolution.h"
#include "../lib/IntVector.h"
#include "../lib/Argument.h"

#define PGM_FIRST_LINE "P2"

#if !defined(FALSE)
#define FALSE 0
#endif

#if !defined(TRUE)
#define TRUE 1
#endif

#define INTENSITY_VALUES 256
#define MAX_INTENSITY (INTENSITY_VALUES - 1)
#define FRACTAL_MAXIMUM 2
#define DEFAULT_SEED_X (-0.726895347709114071439L)
#define DEFAULT_SEED_Y 0.188887129043845954792L
#define DEFAULT_RESOLUTION_WIDTH 640
#define DEFAULT_RESOLUTION_HEIGHT 480
#define DEFAULT_WIDTH 2.0F
#define DEFAULT_HEIGHT 2.0F
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
double widthPerPixel;
double heightPerPixel;
/**
 * Main values used for the algorithm. Replaced by the ones provided by the user
 */
double width;
double height;
Resolution *resolution;
CustomString *output;
ComplexNumber *seed;
ComplexNumber *center;
/**
 * List of valid Arguments
 */
SimpleList argList;

/**
 * Parses the output value from pStr and updates success and errorMessage values
 * @param pStr
 * @param pOutput
 * @param success
 * @param errorMessage
 */
void parseOutput(CustomString *pStr, void *pOutput, int *success, CustomString *errorMessage) {
    if (strcmp(pStr->characters, "-") != 0) {
        stringCopy((CustomString *) pOutput, pStr);
    }
    *success = TRUE;
}

/**
 * Parses the double value from pStr and updates success and errorMessage values.
 * @param pStr
 * @param result
 * @param success
 * @param errorMessage
 */
void parseDouble(CustomString *pStr, void *result, int *success, CustomString *errorMessage) {
    *success = FALSE;
    switch (str2double((double *) result, pStr->characters)) {
        case STR2DOUBLE_INCONVERTIBLE: {
            sprintf(errorMessage->characters, "The %s value can't be converted to floating point value.",
                    pStr->characters);
            break;
        }
        case STR2DOUBLE_OVERFLOW: {
            sprintf(errorMessage->characters, "The %s value exceeds the maximum supported value.", pStr->characters);
            break;
        }
        case STR2DOUBLE_UNDERFLOW: {
            sprintf(errorMessage->characters, "The %s value falls behind the minimum supported value.",
                    pStr->characters);
            break;
        }
        default: {
            *success = TRUE;
            break;
        }
    }
}

/**
 * Obtains the X Coordinate from the center of the screen to be drawed
 * @param center {@link IntVector} Relative center to the upper left corner from the plain to be drawed
 * @param column Coordinate where the column to transform is currently located from left to right
 * @return
 */
double getXCoordinate(IntVector *center, double column) {
    return ((-1) * center->x) + column;
}

/**
 * Obtains the Y Coordinate from the center of the screen to be drawed
 * @param center {@link IntVector} Relative center to the upper left corner from the plain to be drawed
 * @param row Coordinate where the row to transform is currently located from left to right
 * @return
 */
double getYCoordinate(IntVector *center, double row) {
    return center->y - row;
}

ComplexNumber *createComplexByAddress(int row, int column) {
    double real = getXCoordinate(rowAndColumnCenter, column) * widthPerPixel;
    double imaginary = getYCoordinate(rowAndColumnCenter, row) * heightPerPixel;
    ComplexNumber *result = createComplexNumber(real, imaginary);
    sumComplex(result, center); /* Move the point according to the user's input */
    return result;
}

int createFractal(Resolution *pRes) {
    FILE *destiny;
    if (strcmp(output->characters, "\0") != 0) {
        if ((destiny = fopen(output->characters, "w")) == NULL) {
            fprintf(stderr, "No se pudo crear archivo");
            return -1;
        }
    } else {
        destiny = stdout;
    }
    fprintf(destiny, "%s\n", PGM_FIRST_LINE);
    fprintf(destiny, "%d %d\n", pRes->width, pRes->height);
    fprintf(destiny, "%d\n", MAX_INTENSITY);

    /* Iterate per row */
    for (int row = 0; row < pRes->height; row++) {
        /* Iterate per column */
        for (int column = 0; column < pRes->width; column++) {
            ComplexNumber *complex = createComplexByAddress(row, column);
            int intensity;
            /* Iterate and determinate intensity */
            for (intensity = 0; intensity < MAX_INTENSITY; ++intensity) {
                if (absComplex(complex) > FRACTAL_MAXIMUM) {
                    break;
                }
                powComplex(complex, 2);
                sumComplex(complex, seed);
            }
            fprintf(destiny, "%d\n", intensity);
            freeComplex(complex);
        }
    }
    if (strcmp(output->characters, "\0") != 0) {
        fclose(destiny);
    }
    return 0;
}

/**
 * Store the valid arguments that the program can receive into a SimpleList of Arguments
 */
void storeValidArguments() {
    simpleListCreate(&argList, sizeof(Argument));
    simpleListInsertCurrent(&argList, MOVEMENT_FIRST,
                            createArgument("-r", "--resolution", parseResolution, resolution));
    simpleListInsertCurrent(&argList, MOVEMENT_NEXT, createArgument("-c", "--center", parseComplex, center));
    simpleListInsertCurrent(&argList, MOVEMENT_NEXT, createArgument("-w", "--width", parseDouble, &width));
    simpleListInsertCurrent(&argList, MOVEMENT_NEXT, createArgument("-H", "--height", parseDouble, &height));
    simpleListInsertCurrent(&argList, MOVEMENT_NEXT, createArgument("-s", "--seed", parseComplex, seed));
    simpleListInsertCurrent(&argList, MOVEMENT_NEXT, createArgument("-o", "--output", parseOutput, output));
}

/**
 * Iterate over the supported arguments and parses them in a generic way
 * @param pArguments        List of parameters to parse
 * @param currentIndex      Current index of parameter to read
 * @param argumentsQuantity Total quantity of parameters received by the program
 * @param parsedSuccesfully Turns FALSE if some parameter couldn't be parsed or if the value wasn't specified
 * @param errorMessage      It's filled with the proper error message
 */
void findInExistingArguments(char *pArguments[], int *currentIndex, int argumentsQuantity, int *parsedSuccesfully,
                             CustomString *errorMessage) {
    CustomString *argument = initializeString(STRING_MAX);
    parseString(pArguments[*currentIndex], argument);
    int argumentFound = FALSE;
    if (simpleListIsEmpty(argList) == FALSE) {
        simpleListMoveCurrent(&argList, MOVEMENT_FIRST);
        do {
            Argument *aux = createEmptyArgument();
            simpleListCurrent(argList, aux);
            if (aux != NULL) {
                if ((strcmp(argument->characters, aux->shortName) == 0) ||
                    (strcmp(argument->characters, aux->longName) == 0)) {
                    /* Found existing argument */
                    if (*currentIndex == argumentsQuantity) {
                        /* Last argument and couldn't find value */
                        sprintf(errorMessage->characters, "Missing value for argument %s", aux->longName);
                    } else {
                        /* Get value for parameter */
                        parseString(pArguments[++(*currentIndex)], argument);
                        aux->parser(argument, aux->elem, parsedSuccesfully, errorMessage);
                        argumentFound = TRUE;
                        (*currentIndex)++;
                    }
                }
            }
        } while ((simpleListMoveCurrent(&argList, MOVEMENT_NEXT) != FALSE) && (argumentFound == FALSE));
    }
    if (argumentFound == FALSE) {
        *parsedSuccesfully = FALSE;
        sprintf(errorMessage->characters, "Argument %s is not supported by the program.", argument->characters);
    }
    freeString(argument);
}

/**
 * Iterate over the arguments and changed the corresponding parameters
 * @param argc Quantity of arguments
 * @param argv Array of arguments including the program invocation
 */
int detectArguments(int argc, char *argv[]) {
    int i = 1;
    int parsedSuccesfully;
    CustomString *errorMessage = initializeString(STRING_MAX);
    storeValidArguments();

    /* Iterate argv */
    do {
        parsedSuccesfully = 0;
        findInExistingArguments(argv, &i, argc, &parsedSuccesfully, errorMessage);
    } while ((i < argc) && (parsedSuccesfully == TRUE));

    /* Error handling */
    if (parsedSuccesfully == FALSE) {
        fprintf(stderr, "%s", errorMessage->characters);
    }

    free(errorMessage);
    freeArguments(&argList);
    simpleListEmpty(&argList);
    return parsedSuccesfully;
}

int main(int argc, char *argv[]) {
    output = initializeString(STRING_MAX);
    resolution = createResolution(DEFAULT_RESOLUTION_WIDTH, DEFAULT_RESOLUTION_HEIGHT);
    width = DEFAULT_WIDTH;
    height = DEFAULT_HEIGHT;
    seed = createComplexNumber(DEFAULT_SEED_X, DEFAULT_SEED_Y);
    center = createComplexNumber(DEFAULT_CENTER_X, DEFAULT_CENTER_Y);

    int validArguments = TRUE;

    if (argc > 1) {
        validArguments = detectArguments(argc, argv);
    }

    if (validArguments == TRUE) {
        rowAndColumnCenter = createIntVector((resolution->width) / 2, (resolution->height) / 2);
        widthPerPixel = (width / (resolution->width));
        heightPerPixel = (height / (resolution->height));
        createFractal(resolution);
    }

    /* Free Memory */
    freeResolution(resolution);
    freeComplex(seed);
    freeIntVector(rowAndColumnCenter);
    freeComplex(center);
    return (validArguments == TRUE) ? 0 : 1;
}
