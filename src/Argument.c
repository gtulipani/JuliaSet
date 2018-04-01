#include <stdlib.h>
#include "../lib/Argument.h"

Argument *createArgument(char *shortName, char *longName, Parser parser, void *elem) {
    Argument *argument = createEmptyArgument();

    argument->shortName = shortName;
    argument->longName = longName;
    argument->parser = parser;
    argument->elem = elem;

    return argument;
}

Argument *createEmptyArgument() {
    Argument *argument;
    if ((argument = (Argument *) malloc(sizeof(Argument))) == NULL) {
        return NULL;
    }

    return argument;
}

void freeArguments(SimpleList *pL) {
    simpleListEmpty(pL);
}

