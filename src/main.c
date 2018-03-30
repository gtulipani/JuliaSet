#include <stdio.h>
#include <memory.h>
#include "../lib/Resolution.h"
#include "../lib/ComplexNumber.h"
#include "../lib/IntVector.h"
#include "../lib/Argument.h"
#include "../lib/TypeConverter.h"

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
 * Main values used for the algorithm. Replaced by the ones provided by the user
 */
double width;
double height;
Resolution *resolution;
CustomString *output;
long double seed_x = DEFAULT_SEED_X;
long double seed_y = DEFAULT_SEED_Y;
long double center_x = DEFAULT_CENTER_X;
long double center_y = DEFAULT_CENTER_Y;
/**
 * List of valid Arguments
 */
SimpleList *argList;

/**
 * Parses the output value from pStr and updates success and errorMessage values
 * @param pStr
 * @param pOutput
 * @param success
 * @param errorMessage
 */
void parseOutput(CustomString *pStr, CustomString *pOutput, int *success, CustomString *errorMessage) {
    if (strcmp(pStr->characters,"-") != 0) {
        stringCopy(pOutput, pStr);
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
void parseDouble(CustomString *pStr, double *result, int *success, CustomString *errorMessage) {
    *success = FALSE;
    CustomString *formattedError = initializeString(STRING_MAX);
    switch (str2double(result, pStr->characters)) {
        case STR2DOUBLE_INCONVERTIBLE: {
            sprintf(formattedError->characters, "The %s value can't be converted to floating point value.", pStr->characters);
            stringCopy(errorMessage, formattedError);
            break;
        }
        case STR2DOUBLE_OVERFLOW: {
            sprintf(formattedError->characters, "The %s value exceeds the maximum supported value.", pStr->characters);
            stringCopy(errorMessage, formattedError);
            break;
        }
        case STR2DOUBLE_UNDERFLOW: {
            sprintf(formattedError->characters, "The %s value falls behind the minimum supported value.", pStr->characters);
            stringCopy(errorMessage, formattedError);
            break;
        }
        default: {
            *success = TRUE;
            break;
        }
    }
    freeString(formattedError);
}

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
    FILE *outputFile;
    if ((outputFile = fopen(output->characters, "w")) == NULL) {
        fprintf(stderr, "No se pudo crear archivo");
        return -1;
    }
    fprintf(outputFile, "%s\n", PGM_FIRST_LINE);
    fprintf(outputFile, "%d %d\n", pRes->width, pRes->height);
    fprintf(outputFile, "%d\n", MAX_INTENSITY);

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
            fprintf(outputFile, "%d\n", intensity);
            freeComplex(complex);
        }
    }
    fclose(outputFile);
    return 0;
}

/**
 * Iterate over the arguments and changed the corresponding parameters
 * @param argc Quantity of arguments
 * @param argv Array of arguments including the program invocation
 */
int detectArguments(int argc, char *argv[]) {
    /*storeValidArguments();*/
    int i = 1;
    int parsedSuccesfully;
    CustomString *errorMessage = initializeString(STRING_MAX);
    do {
        parsedSuccesfully = 0;
        CustomString *argument = initializeString(STRING_MAX);

        parseString(argv[i], argument);
        if ((strcmp(argument->characters, "-r") == 0) || (strcmp(argument->characters, "--resolution") == 0)) {
            if (i == argc) {
                errorMessage->characters = "Missing value for argument --resolution";
            } else {
                parseString(argv[++i], argument);
                parseResolution(argument, resolution, &parsedSuccesfully, errorMessage);
            }
        }
        if ((strcmp(argument->characters, "-c") == 0) || (strcmp(argument->characters, "--center") == 0)) {
            if (i == argc) {
                errorMessage->characters = "Missing value for argument --center";
            } else {
                parseString(argv[++i], argument);
                /*parseCenter(argument, &parsedSuccesfully, errorMessage);*/
            }
        }
        if ((strcmp(argument->characters, "-w") == 0) || (strcmp(argument->characters, "--width") == 0)) {
            if (i == argc) {
                errorMessage->characters = "Missing value for argument --width";
            } else {
                parseString(argv[++i], argument);
                parseDouble(argument, &width, &parsedSuccesfully, errorMessage);
            }
        }
        if ((strcmp(argument->characters, "-H") == 0) || (strcmp(argument->characters, "--height") == 0)) {
            if (i == argc) {
                errorMessage->characters = "Missing value for argument --height";
            } else {
                parseString(argv[++i], argument);
                parseDouble(argument, &height, &parsedSuccesfully, errorMessage);
            }
        }
        if ((strcmp(argument->characters, "-s") == 0) || (strcmp(argument->characters, "--seed") == 0)) {
            if (i == argc) {
                errorMessage->characters = "Missing value for argument --height";
            } else {
                parseString(argv[++i], argument);
                /*parseSeed(argument, &parsedSuccesfully, errorMessage);*/
            }
        }
        if ((strcmp(argument->characters, "-o") == 0) || (strcmp(argument->characters, "--output") == 0)) {
            if (i == argc) {
                errorMessage->characters = "Missing value for argument --output";
            } else {
                parseString(argv[++i], argument);
                parseOutput(argument, output, &parsedSuccesfully, errorMessage);
            }
        }
        i++;
        free(argument);
    } while ((i < argc) && (parsedSuccesfully == TRUE));
    if (parsedSuccesfully == FALSE) {
        fprintf(stderr, "%s", errorMessage->characters);
    }
    free(errorMessage);
    /*freeArguments(argList);
    free(argList);*/
    return 0;
}

int main(int argc, char *argv[]) {
    output = initializeString(STRING_MAX);
    parseString(DEFAULT_OUTPUT, output);
    resolution = createResolution(DEFAULT_RESOLUTION_WIDTH, DEFAULT_RESOLUTION_HEIGHT);
    width = DEFAULT_WIDTH;
    height = DEFAULT_HEIGHT;

    if (argc > 1) {
        detectArguments(argc, argv);
    }

    seed = createComplexNumber(seed_x, seed_y);
    rowAndColumnCenter = createIntVector((resolution->width) / 2, (resolution->height) / 2);

    widthPerPixel = (width / (resolution->width));
    heightPerPixel = (height / (resolution->height));

    fractalCenter = createComplexNumber(center_x, center_y);
    createFractal(resolution);
    // Free Memory
    freeResolution(resolution);
    freeComplex(seed);
    freeIntVector(rowAndColumnCenter);
    freeComplex(fractalCenter);
}

int argumentValid(char *arg) {
    simpleListMoveCurrent(argList, first);
    Argument *pArg = NULL;
    do {
        simpleListCurrent(*argList, pArg);

    } while (simpleListMoveCurrent(argList, next));
    return 1;
}

/**
 * Store the valid arguments that the program can receive into a SimpleList of Arguments
 */
void storeValidArguments() {
    simpleListCreate(argList, sizeof(Argument));
    simpleListInsertCurrent(argList, first, createArgument('r', "resolution"));
    simpleListInsertCurrent(argList, next, createArgument('c', "center"));
    simpleListInsertCurrent(argList, next, createArgument('w', "width"));
    simpleListInsertCurrent(argList, next, createArgument('H', "height"));
    simpleListInsertCurrent(argList, next, createArgument('s', "seed"));
    simpleListInsertCurrent(argList, next, createArgument('o', "output"));
}