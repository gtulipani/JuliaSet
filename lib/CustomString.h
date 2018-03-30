#ifndef TP0_STRING_H
    #define TP0_STRING_H
#endif

#if !defined(STRING_MAX)
    #define STRING_MAX 50
#endif

typedef struct CustomString {
    char* characters;
    int size;
} CustomString;

/**
 * Creates the String instance, allocates the memory and initializes it to '\0'
 * @param size
 * @return
 */
CustomString* initializeString(int size);

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
 * Implementation of strtok for String
 * @param dest
 * @param orig
 */
CustomString *stringToken(CustomString *pStr, char *delim);

/**
 * Frees the memory used by pStr
 * @param pStr
 */
void freeString(CustomString *pStr);
