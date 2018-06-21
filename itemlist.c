#include "itemlist.h"

ItemList initItemList()
{
    /* Creates space for a new list and returns its address */
    ItemList newList = (ItemList) malloc(sizeof(struct itemlist));
    newList->head = NULL;
    newList->last = NULL;

    return newList;
}

ItemLink NEWITEM(Item item)
{
    /* Creates space for new list node and returns its address */
    ItemLink x = (ItemLink) malloc(sizeof(struct itemlistnode));
    x->previous = NULL;
    x->next = NULL;
    x->item = item;

    return x;
}

void freeItemLink(ItemList list, ItemLink link)
{
    /* Head of the list */
    if (link->previous == NULL) {
        list->head = link->next;
    } else {
        link->previous->next = link->next;
    }
    /*Last elementof the list*/
    if (link->next == NULL) {
        list->last = link->previous;
    } else {
        link->next->previous = link->previous;
    }

    free(link);
}

void freeItemLinks(ItemList list)
{
    ItemLink iLink;
    ItemLink next;

    for (iLink = list->head; iLink != NULL; iLink = next) {
       next = iLink->next; 
       free(iLink);
       iLink = next;
    }

    free(list);
}

ItemLink addItemToList(ItemList list, Item item)
{
    ItemLink newNode = NEWITEM(item);

    if (list->head == NULL) {
        list->head = newNode;
    } else {
        list->last->next = newNode;
    }
    newNode->previous = list->last;
    list->last = newNode;

    return newNode;
}

ItemLink findItemLink(ItemList list, unsigned long searchValue)
{
    ItemLink i;

    for (i = list->last; i != NULL; i = i->previous) {
        if (key(getItem(i)) == searchValue) {
            return i;
        }
    }

    return NULL;
}

Item getItem(ItemLink link)
{
    return link->item;
}

ItemLink getFirstLinkIL(ItemList list)
{
    return list->head;
}

ItemLink getLastLinkIL(ItemList list)
{
    return list->last;
}

ItemLink getNextItemLink(ItemLink link)
{
    return link->next;
}

ItemLink getPrevItemLink(ItemLink link)
{
    return link->previous;
}

int isEmptyIL(ItemList list)
{
    return (list->head == NULL);
}

void printItemKeys(ItemList list)
{
    ItemLink link;

    for (link = list->head; link != NULL; link = link->next) {
        printf(" %lu", key(getItem(link)));
    }
    printf("\n");
}
