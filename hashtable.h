#ifndef HASHTABLE_H
#define HASHTABLE_H

typedef struct hashtable *HashTable;

#include <stdlib.h>
#include "pointerlist.h"
#include "task.h"
/* The item's value to be hashed */
#define hashKey(A) getId(A)

struct hashtable {
    int M;
    PointerList *pointerLists;
};


/* Allocates and initializes values for a new hashtable, returns
its pointer. */
HashTable initHashTable(int M);

/* Frees a single PointerLink in the hashtable. */
void freeLinkHashTable(HashTable hTable, PointerLink pointerLink);

/* Frees all PointerLinks in the list. */
void freeHashTableLinks(HashTable hTable);

/* Adds a new PointerLink to the hashtable. Receives itemLink
to hash the correct position in the hashtable. */
void addLinkToHash(HashTable hashId, ItemLink itemLink);

/* Returns the PointerLink with the correspondant searchValue. */
PointerLink findLinkInHash(HashTable hTable, unsigned long searchValue);

#endif
