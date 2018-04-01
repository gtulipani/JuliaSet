#ifndef TP0_ARGUMENT_H
#define TP0_ARGUMENT_H

#include "SimpleList.h"
#include "CustomString.h"

/**
 * Generic function that parses an argument
 * @param   CustomString *  String where to parse the argument from
 * @param   void *          Result element
 * @param   int *           Success element
 * @param   CustomString *  ErrorMessage element
 */
typedef void (*Parser)(CustomString *, void *, int *, CustomString *);

typedef struct Argument {
    char *shortName;
    char *longName;
    Parser parser;
    void *elem;
} Argument;

/**
 * Creates an argument instance
 * @param shortName E.g. "-c"2
 * @param longName  E.g. "--center
 * @param parser    Parser function defined at the beginning of the file
 * @return
 */
Argument *createArgument(char *shortName, char *longName, Parser parser, void *elem);

/**
 * Creates an empty argument. Used to be replaced then in memory flows
 */
Argument *createEmptyArgument();

/**
 * Frees the memory used by a List of arguments
 */
void freeArguments(SimpleList *pL);

#endif
