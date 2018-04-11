#ifndef TP0_COMPLEXNUMBER_H
#define TP0_COMPLEXNUMBER_H

#include "CustomString.h"

#if !defined(FALSE)
    #define FALSE 0
#endif

#if !defined(TRUE)
    #define TRUE 1
#endif

typedef struct ComplexNumber {
    double real;
    double imaginary;
} ComplexNumber;

/**
 * Creates a complex number
 * @param real
 * @param imaginary
 * @return
 */
ComplexNumber *createComplexNumber(double real, double imaginary);

double absComplex(ComplexNumber *pComp);

/**
 * Perform the pow operation to a complex number and stores the result in the same number
 * @param pBase {@link ComplexNumber} to be powed
 * @param exponent Only 2 as value is supported
 */
void powComplex(ComplexNumber *pBase, int exponent);

/**
 * Sums to complex number and stores the result in the first operand
 * @param pComp1
 * @param pComp2
 */
void sumComplex(ComplexNumber *pComp1, ComplexNumber *pComp2);

/**
 * Parses the complex number value from pStr and updates success and errorMessage values
 * @param pStr
 * @param pComplex
 * @param success
 * @param errorMessage
 */
void parseComplex(CustomString *pStr, void *pComplex, int *success, CustomString *errorMessage);

/**
 * Frees the memory used by the Complex Number
 * @param pComp
 */
void freeComplex(ComplexNumber *pComp);

#endif
