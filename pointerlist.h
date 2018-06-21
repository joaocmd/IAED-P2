#ifndef POINTERLIST_H
#define POINTERLIST_H

#include <stdlib.h>

typedef struct pointerlistnode *PointerLink;
typedef struct pointerlist *PointerList;

/* Item that composes the lists. */
#define searchKey(A) getId(A)
#include "itemlist.h"

struct pointerlistnode {
    ItemLink listPointer;
    PointerLink previous;
    PointerLink next;
};

struct pointerlist {
    PointerLink head;    
};

/* Allocates and initializes values for a new PointerList, returns
its pointer. */
PointerList initPointerList();

/* Frees a single PointerLink in the list. */
void freePointerLink(PointerList list, PointerLink link);

/* Frees all PointerLinks in the list, and the corresponding
ItemLink and it's item. */
void freePointerLinks(PointerList list);

/* Appends item to the list. Returns the link to the new
PointerLink to make operations possible. */
PointerLink addPointerToList(PointerList list, ItemLink itemlink);

/* Given a PointerLink, returns the ItemLink. */
ItemLink getItemLink(PointerLink link);

/* Returns the PointerLink with the correspondant searchValue. */
PointerLink findPointerLink(PointerList list, unsigned long searchValue);

#endif
