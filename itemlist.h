#ifndef ITEMLIST_H
#define ITEMLIST_H

#include <stdlib.h>

typedef struct itemlistnode *ItemLink;
typedef struct itemlist *ItemList;
/* Item that composes the lists. */
#define Item Task
#include "task.h"
#define freeItem(A) freeTask(A)
#define key(A) getId(A)

struct itemlistnode {
    Item item; 
    ItemLink previous;
    ItemLink next;
};

struct itemlist {
    ItemLink head;    
    ItemLink last;
};

/* Allocates and initializes values for a new ItemList, returns
its pointer. */
ItemList initItemList();

/* Appends item to the list. Returns the link to the node 
to make operations possible. */
ItemLink addItemToList(ItemList list, Item item);

/* Frees a single ItemLink in the list. */
void freeItemLink(ItemList list, ItemLink link);

/* Frees all ItemLink in the list. */
void freeItemLinks(ItemList list);

/* Returns the ItemLink with the correspondant searchValue. */
ItemLink findItemLink(ItemList list, unsigned long searchValue);

/* Given an ItemLink, returns the Item of the node. */
Item getItem(ItemLink link);

/* Given an ItemList, returns the first ItemLink of it. */
ItemLink getFirstLinkIL(ItemList list);

/* Given an ItemList, returns the last ItemLink of it. */
ItemLink getLastLinkIL(ItemList list);

/* Given an ItemLink, returns the next ItemLink. */
ItemLink getNextItemLink(ItemLink link);

/* Given an ItemLink returns the previous ItemLink. */
ItemLink getPrevItemLink(ItemLink link);

/* Returns if the ItemList is empty or not. */
int isEmptyIL(ItemList list);

/* Prints the key of each item on list, by the order
they were added. */
void printItemKeys(ItemList list);

#endif
