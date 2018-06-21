#include "pointerlist.h"

PointerList initPointerList()
{
    /* Creates space for a new list and returns its address */
    PointerList newList = (PointerList) malloc(sizeof(struct pointerlist));
    newList->head = NULL;

    return newList;
}

PointerLink NEWPOINTER(ItemLink itemLink)
{
    /* Creates space for new list node and returns its address */
    PointerLink x = (PointerLink) malloc(sizeof(struct pointerlistnode));
    x->listPointer = itemLink;
    x->previous = NULL;
    x->next = NULL;

    return x;
}

void freePointerLink(PointerList list, PointerLink link)
{
    /* Not head of the list */
    if (link->previous != NULL) {
        link->previous->next = link->next;
    } else {
        list->head = link->next;
    }

    /* Not last element of the list */
    if (link->next != NULL) {
        link->next->previous = link->previous;
    }

    free(link);
}

void freePointerLinks(PointerList list)
{
    PointerLink iLink;
    PointerLink next;

    for (iLink = list->head; iLink != NULL; iLink = next) {
        freeItem(getItem(iLink->listPointer));
        free(iLink->listPointer);
        next = iLink->next;
        free(iLink);
        iLink = next;
    }

    free(list);
}

PointerLink addPointerToList(PointerList list, ItemLink itemLink)
{
    PointerLink newNode = NEWPOINTER(itemLink);

    if(list->head != NULL) {
        list->head->previous = newNode;
    }
    newNode->next = list->head;
    list->head = newNode;
   
    return newNode;
}

ItemLink getItemLink(PointerLink link)
{
    return link->listPointer;
}

PointerLink findPointerLink(PointerList list, unsigned long searchValue)
{
    PointerLink i;

    for (i = list->head; i != NULL; i = i->next) {
        if (searchKey(getItem(i->listPointer)) == searchValue) {
            return i; 
        }
    }

    return NULL;
}
