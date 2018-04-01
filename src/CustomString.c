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

/* Used internally to manipulate pointers and update the Strings according to the keepDelimiter and delimiterAtBeginning flags */
void parseDividedStrings(CustomString *leftAux, CustomString *rightAux, CustomString *pStrLeft, CustomString *pStrRight,
                         int keepDelimiter, int delimiterAtBeginning) {
    memcpy(pStrRight->characters, rightAux->characters, STRING_MAX);
    memcpy(pStrLeft->characters, leftAux->characters, STRING_MAX);

    if (keepDelimiter == FALSE) { /* If must not keep delimiter, omits the first char */
        /* Uses the pointer to ommit first character */
        rightAux->characters++;
        memcpy(pStrRight->characters, rightAux->characters, STRING_MAX);
        rightAux->characters--;

        if (delimiterAtBeginning == TRUE) {
            /* If there is also a delimiter at the beginning of the argument, omits it too */
            leftAux->characters++;
            memcpy(pStrLeft->characters, leftAux->characters, STRING_MAX);
            leftAux->characters--;
        }
    }
}

strdivide_errno
stringDivide(CustomString *pStrToDivide, CustomString *pStrLeft, CustomString *pStrRight, char c1, char c2,
             int keepDelimiter) {
    if (strlen(pStrToDivide->characters) == 0) {
        return STR_DIVIDE_INVALID;
    }
    CustomString *copy = initializeString(STRING_MAX);
    CustomString *aux = initializeString(STRING_MAX);
    CustomString *leftAux = initializeString(STRING_MAX);
    CustomString *rightAux = initializeString(STRING_MAX);
    stringCopy(copy, pStrToDivide);
    stringCopy(aux, pStrToDivide);
    int delimiterAtBeginning = FALSE;
    if ((copy->characters[0] == c1) || (copy->characters[0] == c2)) {
        delimiterAtBeginning = TRUE;
        /* Delimiter at the beginning, must discard that delimiter for the strchr */
        if (strlen(copy->characters) != 1) {
            aux->characters++;
        } else {
            /* pStrToDivide was conformed by the delimiter only */
            freeString(copy);
            freeString(aux);
            freeString(leftAux);
            freeString(rightAux);
            return STR_DIVIDE_INVALID;
        }
    }
    char *c1Str = strchr(aux->characters, c1);
    char *c2Str = strchr(aux->characters, c2);
    if ((c1Str == NULL) && (c2Str == NULL)) {
        /* No delimiter found, replace pStrLeft only and either keeps or ommits delimiter according to the parameter */
        memcpy(pStrLeft->characters, aux->characters, STRING_MAX);
        if (delimiterAtBeginning == TRUE) {
            aux->characters--;
            if (keepDelimiter == TRUE) {
                memcpy(pStrLeft->characters, aux->characters, STRING_MAX);
            }
        }
        freeString(copy);
        freeString(aux);
        freeString(leftAux);
        freeString(rightAux);
        return STR_DIVIDE_ONLY_LEFT;
    }

    if (c1Str != NULL) { /* Found first delimiter, replace both pStrLeft and pStrRight */
        /* Replaced values inside leftAux and rightAux, in case we need to update the pointers */
        memcpy(rightAux->characters, c1Str, STRING_MAX);
        memcpy(leftAux->characters, copy->characters, strlen(copy->characters) - strlen(c1Str));
        parseDividedStrings(leftAux, rightAux, pStrLeft, pStrRight, keepDelimiter, delimiterAtBeginning);
    }

    if (c2Str != NULL) { /* Found seconds delimiter, replace both pStrLeft and pStrRight */
        /* Replaced values inside leftAux and rightAux, in case we need to update the pointers */
        memcpy(rightAux->characters, c2Str, STRING_MAX);
        memcpy(leftAux->characters, copy->characters, strlen(copy->characters) - strlen(c2Str));
        parseDividedStrings(leftAux, rightAux, pStrLeft, pStrRight, keepDelimiter, delimiterAtBeginning);
    }
    if (delimiterAtBeginning == TRUE) {
        aux->characters--;
    }
    freeString(copy);
    freeString(aux);
    freeString(leftAux);
    freeString(rightAux);
    return STR_DIVIDE_SUCCESS;
}

void freeString(CustomString *pStr) {
    free(pStr->characters);
    free(pStr);
}
