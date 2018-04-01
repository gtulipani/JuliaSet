#ifndef TP0_STRING_H
#define TP0_STRING_H

#if !defined(FALSE)
#define FALSE 0
#endif

#if !defined(TRUE)
#define TRUE 1
#endif

#if !defined(STRING_MAX)
#define STRING_MAX 50
#endif

typedef struct CustomString {
    char *characters;
    int size;
} CustomString;

typedef enum {
    STR_DIVIDE_INVALID,
    STR_DIVIDE_ONLY_LEFT,
    STR_DIVIDE_SUCCESS
} strdivide_errno;

/**
 * Creates the String instance, allocates the memory and initializes it to '\0'
 * @param size
 * @return
 */
CustomString *initializeString(int size);

/**
 * Parses a char * inside a *res
 * @param str
 * @param res String already initialized
 */
void parseString(char *str, CustomString *res);

/**
 * Copy the content of one String to the other
 * @param dest
 * @param orig
 */
void stringCopy(CustomString *dest, CustomString *orig);

/**
 * Divides a String into two different Strings by values c1 or c2
 * @pre     pStrToDivide, pStrLeft and pStrRight already created and initialized
 * @param   pStrToDivide    String to divide
 * @param   pStrLeft        Contains the left part of the String as result
 * @param   pStrRight       Contains the right part of the String as result
 * @param   c1
 * @param   c2
 * @param   keepDelimiter   If TRUE the delimiter is included in the result
 * @return  STR_DIVIDE_SUCCESS if the parsing was succesfull
 *          STR_DIVIDE_INVALID if pStrToDivide was empty or conformed only by the delimiter
 *          STR_DIVIDE_ONLY_LEFT if no delimiter was found, and only pStrLeft has been replaced
 */
strdivide_errno
stringDivide(CustomString *pStrToDivide, CustomString *pStrLeft, CustomString *pStrRight, char c1, char c2,
             int keepDelimiter);

/**
 * Frees the memory used by pStr
 * @param pStr
 */
void freeString(CustomString *pStr);

#endif
