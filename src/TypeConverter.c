#include <math.h>
#include "../lib/TypeConverter.h"

str2int_errno str2int(int *out, char *s, int base) {
    char *end;
    if (s[0] == '\0' || isspace((unsigned char) s[0]))
        return STR2INT_INCONVERTIBLE;
    errno = 0;
    long l = strtol(s, &end, base);
    /* Both checks are needed because INT_MAX == LONG_MAX is possible. */
    if (l > INT_MAX || (errno == ERANGE && l == LONG_MAX))
        return STR2INT_OVERFLOW;
    if (l < INT_MIN || (errno == ERANGE && l == LONG_MIN))
        return STR2INT_UNDERFLOW;
    if (*end != '\0')
        return STR2INT_INCONVERTIBLE;
    *out = (int) l;
    return STR2INT_SUCCESS;
}

str2double_errno str2double(double *out, char *s) {
    char *end;
    if (s[0] == '\0')
        return STR2DOUBLE_INCONVERTIBLE;
    errno = 0;
    double d = strtod(s, &end);
    /* Both checks are needed because INT_MAX == LONG_MAX is possible. */
    if (errno == ERANGE && d == HUGE_VAL)
        return STR2DOUBLE_OVERFLOW;
    if (errno == ERANGE && d == 0)
        return STR2DOUBLE_UNDERFLOW;
    if (*end != '\0')
        return STR2DOUBLE_INCONVERTIBLE;
    *out = d;
    return STR2DOUBLE_SUCCESS;
}

