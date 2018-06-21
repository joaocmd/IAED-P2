#ifndef HASHLIST_H
#define HASHLIST_H

typedef struct hashlist *HashList;

#include "hashtable.h"
#include "itemlist.h"

struct hashlist {
    int validCriticalP;
    unsigned long duration;
    HashTable table; 
    ItemList list;
};

/* Allocates and initializes values for a new hashlist, returns
its pointer. */
HashList initHashList(int M);

/* Indicates whether it has a valid critical path or not. */
int hasCriticalPath(HashList hList);

/* Adds item to the hashlist. */
void addItemToHL(HashList hList, Item item);

/* Frees the PointerLink and the ItemLink in the hashlist. */
void freeHLLink(HashList hList, PointerLink pointerLink);

/* Frees all PointerLinks, ItemLinks and Tasks(!!) in the hashlist. */
void freeHashList(HashList hList);

/* Returns the PointerLink with the correspondant searchValue. */
PointerLink findLinkInHL(HashList hList, unsigned long searchValue);

/* Returns first ItemLink of the hashlist. */
ItemLink getFirstItemLinkHL(HashList hList);

/* Returns if the hashlist is empty or not. */
int isEmptyHL(HashList hList);

/* Calculates and prints the critical path for the
hashlist. */
void calculateCriticalPath(HashList hList);

#endif
