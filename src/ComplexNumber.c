#include <stdlib.h>
#include <math.h>
#include "../lib/ComplexNumber.h"

ComplexNumber *createComplexNumber(long double real, long double imaginary) {
    ComplexNumber *complex;
    if ((complex = (ComplexNumber *) malloc(sizeof(ComplexNumber))) == NULL) {
        return NULL;
    }

    complex->real = real;
    complex->imaginary = imaginary;

    return complex;
}

long double absComplex(ComplexNumber *pComp) {
    return sqrtl(powl(pComp->real, 2) + powl(pComp->imaginary, 2));
}

void powComplex(ComplexNumber *pBase, int exponent) {
    if (exponent == 2) {
        long double auxReal = powl(pBase->real, exponent) - powl(pBase->imaginary, exponent);
        long double auxImaginary = 2 * pBase->real * pBase->imaginary;
        pBase->real = auxReal;
        pBase->imaginary = auxImaginary;
    }
}

void sumComplex(ComplexNumber *pComp1, ComplexNumber *pComp2) {
    pComp1->real += pComp2->real;
    pComp1->imaginary += pComp2->imaginary;
}

void freeComplex(ComplexNumber *pComp) {
    free(pComp);
}