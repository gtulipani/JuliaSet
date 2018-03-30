#include <stdlib.h>
#include <memory.h>
#include "../lib/CustomString.h"

CustomString *initializeString(int size) {
    CustomString *str = NULL;

    if ((str = (CustomString *) malloc(sizeof(CustomString))) == NULL) {
        return NULL;
    }

    if ((str->characters = (char *) malloc((size_t) size)) == NULL) {
        free(str);
        return NULL;
    }

    str->size = size;

    memset(str->characters, '\0', 1);
    return str;
}

void parseString(char *str, CustomString *res) {
    memcpy(res->characters, str, STRING_MAX);
}

void stringCopy(CustomString *dest, CustomString *orig) {
    if (orig == NULL) {
        dest = NULL;
    } else {
        dest->size = orig->size;
        strcpy(dest->characters, orig->characters);
    }
}

CustomString *stringToken(CustomString *pStr, char *delim) {
    CustomString *aux = initializeString(STRING_MAX);
    stringCopy(aux, pStr);
    aux->characters = ((pStr == NULL) ?
                       memcpy(aux->characters, strtok(NULL, delim), STRING_MAX) :
                       memcpy(aux->characters, strtok(aux->characters, delim), STRING_MAX));
    if (aux->characters == NULL) {
        freeString(aux);
        return NULL;
    }
    return aux;
}

void freeString(CustomString *pStr) {
    free(pStr->characters);
    free(pStr);
}
