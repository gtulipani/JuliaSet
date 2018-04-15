#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "../lib/TypeConverter.h"

char complexDelimiter[] = "+-";

ComplexNumber *createComplexNumber(double real, double imaginary) {
    ComplexNumber *complex;
    if ((complex = (ComplexNumber *) malloc(sizeof(ComplexNumber))) == NULL) {
        return NULL;
    }

    complex->real = real;
    complex->imaginary = imaginary;

    return complex;
}

double absComplex(ComplexNumber *pComp) {
    return sqrt(pow(pComp->real, 2) + pow(pComp->imaginary, 2));
}

void powComplex(ComplexNumber *pBase, int exponent) {
    if (exponent == 2) {
        double auxReal = pow(pBase->real, exponent) - pow(pBase->imaginary, exponent);
        double auxImaginary = 2 * pBase->real * pBase->imaginary;
        pBase->real = auxReal;
        pBase->imaginary = auxImaginary;
    }
}

void sumComplex(ComplexNumber *pComp1, ComplexNumber *pComp2) {
    pComp1->real += pComp2->real;
    pComp1->imaginary += pComp2->imaginary;
}

void validateComplexNumberParse(CustomString *pStr, str2complex_errno realError, str2complex_errno imaginaryError,
                                int *success,
                                CustomString *errorMessage) {
    if (*success == TRUE) {
        *success = FALSE;
        if ((realError == STR2COMPLEX_INCONVERTIBLE) || (imaginaryError == STR2COMPLEX_INCONVERTIBLE)) {
            sprintf(errorMessage->characters, "The %s value can't be converted to complex value.", pStr->characters);
        } else if ((realError == STR2COMPLEX_OVERFLOW) || (imaginaryError == STR2COMPLEX_OVERFLOW)) {
            sprintf(errorMessage->characters, "The %s value exceeds the maximum supported value.", pStr->characters);
        } else if ((realError == STR2COMPLEX_UNDERFLOW) || (imaginaryError == STR2COMPLEX_UNDERFLOW)) {
            sprintf(errorMessage->characters, "The %s value falls behind the minimum supported value.",
                    pStr->characters);
        } else {
            *success = TRUE;
        }
    }
}

void parseComplex(CustomString *pStr, void *pComplex, int *success, CustomString *errorMessage) {
    *success = TRUE;
    /* Divide the pStr in left and right parts */
    CustomString *pStrLeft = initializeString(STRING_MAX);
    CustomString *pStrRight = initializeString(STRING_MAX);
    strdivide_errno result = stringDivide(pStr, pStrLeft, pStrRight, complexDelimiter[0], complexDelimiter[1], TRUE);

    /* Create an auxiliar complexNumber and perform a list of validations */
    ComplexNumber *complexAux = createComplexNumber(0.0L, 0.0L);
    switch (result) {
        case STR_DIVIDE_INVALID: {
            sprintf(errorMessage->characters, "The %s value can't be converted to complex value.", pStr->characters);
            *success = FALSE;
            break;
        }
        case STR_DIVIDE_SUCCESS: {
            str2complex_errno leftPartError = str2complex(complexAux, pStrLeft->characters);
            str2complex_errno rightPartError = str2complex(complexAux, pStrRight->characters);
            validateComplexNumberParse(pStr, leftPartError, rightPartError, success, errorMessage);
            break;
        }
        case STR_DIVIDE_ONLY_LEFT: {
            str2complex_errno leftPartError = str2complex(complexAux, pStrLeft->characters);
            validateComplexNumberParse(pStr, leftPartError, STR2COMPLEX_SUCCESS, success, errorMessage);
            break;
        }
    }

    /* Assign the result to the real complex number */
    if (*success == TRUE) {
        ((ComplexNumber *) pComplex)->real = complexAux->real;
        ((ComplexNumber *) pComplex)->imaginary = complexAux->imaginary;
    }
    freeString(pStrLeft);
    freeString(pStrRight);
    freeComplex(complexAux);
}

void freeComplex(ComplexNumber *pComp) {
    free(pComp);
}

