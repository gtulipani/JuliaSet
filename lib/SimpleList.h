#ifndef TP0_LIST_H
#define TP0_LIST_H

#include <stdlib.h>
#include <memory.h>

#if !defined(FALSE)
#define FALSE 0
#endif

#if !defined(TRUE)
#define TRUE 1
#endif

/**
 * Movements that the structure will handle.
 */
typedef enum {
    first,
    next,
    previous
} SimpleListMovement;

/**
 * Aux SimpleList structure. Part of the internal logic of the SimpleList
 */
typedef struct SimpleListNode {
    void *elem;
    struct SimpleListNode *next;
} SimpleListNode;

/**
 * Head structure. Type to be instanced, although the fields should never be directly accessed.
 */
typedef struct {
    SimpleListNode *first, *current;
    int size;
} SimpleList;

/**
 * @pre     List pointed by pL wasn't created.
 * @post    pL creted and empty.
 */
void simpleListCreate(SimpleList *pL, int size);

/**
 * @pre     pL pointer to already created List.
 * @post    pL is empty.
 */
void simpleListEmpty(SimpleList *pL);

/**
 * @pre     l already created.
 * @return  TRUE if l has elements.
 *          FALSE if l is empty.
 */
int simpleListIsEmpty(SimpleList l);

/**
 * @pre     l already created and not empty.
 * @post    pE contains the pointer to the current element of the List.
 */
void simpleListCurrent(SimpleList l, void *pE);

/**
 * @pre     pL pointer to already created and not empty List.
 * @param   m  Movement through the list.
 * @post    If pL points to non-empty table, then:
 *              If m = first, the current is pointing to the first element of the list.
 *              If m = next and the current is not the last element, it's pointing to the next element of the list.
 * @return  TRUE if pL points to non-empty table, and m = first or m = next and current element is not the last.
 *          FALSE if m = previous or current is pointing to last element in the List.
 */
int simpleListMoveCurrent(SimpleList *pL, SimpleListMovement m);

/**
 * @pre     pL pointer to already created and not empty List.
 * @post    Current element is deleted. Current is pointing to next element or previous one if it was the last.
 */
void simpleListDeleteCurrent(SimpleList *pL);

/**
 * @pre     pL pointing to already created List.
 * @post    e added to the list and according to the movement m:
 *              If m = first, e is inserted as first element in the List.
 *              If m = next, e is inserted after current element in the List.
 *              If m = previous, e is inserted before current element
 * @return  TRUE if the element could be inserted
 *          FALSE because of following reasons:
 *              No memory avaiable to allocate for the new element
 *              e is pointing to NULL
 */
int simpleListInsertCurrent(SimpleList *pL, SimpleListMovement m, void *e);

/* L_ELEM_CTE
 * Pre: Ls creada y no vacía.
 * Post: Se modifica el elemento corriente para que pase a tener los datos indicados en pE.
 */
/**
 * @pre     l already created and not empty.
 * @post    Current element is overriden with pE
 */
void simpleListModifyCurrent(SimpleList l, void *pE);

#endif
