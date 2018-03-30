#ifndef TP0_ARGUMENT_H
#define TP0_ARGUMENT_H

#include "SimpleList.h"

typedef struct Argument {
    char shortName;
    char* longName;
} Argument;

/**
 * Creates an argument instance
 * @param shortName
 * @param longName
 * @return
 */
Argument *createArgument(char shortName, char* longName);

/**
 * Frees the memory used by the argument
 * @param pArg
 */
void freeArgument(Argument* pArg);

/**
 * Frees the memory used by an array of arguments
 */
void freeArguments(SimpleList * pL);

#endif
