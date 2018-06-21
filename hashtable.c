#include "hashtable.h"

int hash(HashTable hTable, unsigned long hashValue)
{
    return (hashValue%hTable->M);
}

HashTable initHashTable(int M)
{
    int i;

    HashTable newHTable = (HashTable) malloc(sizeof(struct hashtable));
    newHTable->M = M;
    newHTable->pointerLists = (PointerList*) malloc(sizeof(PointerList)*M);

    for (i = 0; i < M; i++) {
        newHTable->pointerLists[i] = initPointerList();
    }

    return newHTable;
}

void freeLinkHashTable(HashTable hTable, PointerLink pointerLink)
{
    int i = hash(hTable, getId(getItem(getItemLink(pointerLink))));
    freePointerLink(hTable->pointerLists[i], pointerLink);
}

void freeHashTable(HashTable hTable)
{
    int i;

    for (i = 0; i < hTable->M; i++) {
        freePointerLinks(hTable->pointerLists[i]);
    }

    free(hTable->pointerLists);
    free(hTable);
}

void addLinkToHash(HashTable hTable, ItemLink itemLink)
{
    Item item = getItem(itemLink);
    int i = hash(hTable, hashKey(item));  

    addPointerToList(hTable->pointerLists[i], itemLink);
}

PointerLink findLinkInHash(HashTable hTable, unsigned long searchValue)
{
    int i = hash(hTable, searchValue);  
    return findPointerLink(hTable->pointerLists[i], searchValue);
}
