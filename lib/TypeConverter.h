#ifndef TP0_TYPECONVERTER_H
#define TP0_TYPECONVERTER_H

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "ComplexNumber.h"

typedef enum {
    STR2INT_SUCCESS,
    STR2INT_OVERFLOW,
    STR2INT_UNDERFLOW,
    STR2INT_INCONVERTIBLE
} str2int_errno;

typedef enum {
    STR2DOUBLE_SUCCESS,
    STR2DOUBLE_OVERFLOW,
    STR2DOUBLE_UNDERFLOW,
    STR2DOUBLE_INCONVERTIBLE
} str2double_errno;

typedef enum {
    STR2COMPLEX_SUCCESS,
    STR2COMPLEX_OVERFLOW,
    STR2COMPLEX_UNDERFLOW,
    STR2COMPLEX_INCONVERTIBLE
} str2complex_errno;

/**
 * Convert string s to int out.
 * @param   out The converted int. Cannot be NULL.
 * @param   s The format is the same as strtol, except that the following are inconvertible:
 *              - empty string
 *              - leading whitespace
 *              - any trailing characters that are not part of the number
 *          Cannot be NULL.
 * @param   base base Base to interpret string in. Same range as strtol (2 to 36).
 * @return  Indicates if the operation succeeded, or why it failed.
 */
str2int_errno str2int(int *out, char *s, int base);

/**
 * Convert string s to double out.
 * @param   out The converted double. Cannot be NULL.
 * @param   s Input string to be converted.
 *          The format is the same as strtod, except that the following are inconvertible:
 *              - empty string
 *              - any trailing characters that are not part of the number
 *          Cannot be NULL.
 * @return  Indicates if the operation succeeded, or why it failed.
 */
str2double_errno str2double(double *out, char *s);

/**
 * Convert string s to complex number.
 * @param   out The converted complex. Cannot be NULL.
 * @param   s Input string to be converted.
 *          The format is similar to strtod, except that the following are inconvertible:
 *              - empty string
 *              - any trailing characters that are not part of the number
 *          Cannot be NULL.
 * @return  Indicates if the operation succeeded, or why it failed.
 */
str2complex_errno str2complex(ComplexNumber *out, char *s);

#endif
