#ifndef TP0_COMPLEXNUMBER_H
#define TP0_COMPLEXNUMBER_H

typedef struct ComplexNumber {
    long double real;
    long double imaginary;
} ComplexNumber;

/**
 * Creates a complex number
 * @param real
 * @param imaginary
 * @return
 */
ComplexNumber *createComplexNumber(long double real, long double imaginary);

long double absComplex(ComplexNumber *pComp);

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
 * Frees the memory used by the Complex Number
 * @param pComp
 */
void freeComplex(ComplexNumber *pComp);

#endif
