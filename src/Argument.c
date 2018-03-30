#include <stdlib.h>
#include "../lib/Argument.h"

Argument *createArgument(char shortName, char *longName) {
    Argument *argument;
    if ((argument = (Argument *) malloc(sizeof(Argument))) == NULL) {
        return NULL;
    }

    argument->shortName = shortName;
    argument->longName = longName;

    return argument;
}

void freeArgument(Argument *pArg) {
    free(pArg);
}

void freeArguments(SimpleList *pL) {
    simpleListEmpty(pL);
}

