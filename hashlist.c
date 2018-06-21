#include "hashlist.h"

/* Calculates the late start for task, taking in account the project
duration pDuration. */
void calculateLateStart(Task task, unsigned long pDuration);

/* Calculates the late start for task recursively. Returns the
value of late start.*/
unsigned long recursLateStart(Task task);

int hasCriticalPath(HashList hList)
{
    return hList->validCriticalP;
}

HashList initHashList(int M)
{
    HashList newHList = (HashList) malloc(sizeof(struct hashlist));
    newHList->validCriticalP = 0;
    newHList->duration = 0;
    newHList->table = initHashTable(M);
    newHList->list = initItemList();

    return newHList;
}

void addItemToHL(HashList hList, Task task)
{
    ItemLink link = addItemToList(hList->list, task);
    addLinkToHash(hList->table, link);
    hList->validCriticalP = 0;
}

void freeHLLink(HashList hList, PointerLink pointerLink)
{
    ItemLink itemLink = getItemLink(pointerLink);

    hList->validCriticalP = 0;
    freeLinkHashTable(hList->table, pointerLink);  
    freeItemLink(hList->list, itemLink);
}

PointerLink findLinkInHL(HashList hList, unsigned long searchValue)
{ 
    return findLinkInHash(hList->table, searchValue);
}

void freeHashList(HashList hList)
{
    freeHashTable(hList->table);
    free(hList->list);
    free(hList);
}

ItemLink getFirstItemLinkHL(HashList hList)
{
    return getFirstLinkIL(hList->list);
}

int isEmptyHL(HashList hList)
{
    return isEmptyIL(hList->list);
}

void calculateProjectDuration(HashList hList)
{
    ItemLink itemLink;
    Task task;
    unsigned long duration;
   
    itemLink = getFirstLinkIL(hList->list);
    while (itemLink != NULL) {
        task = getItem(itemLink); 

        /* Find final tasks */
        if (isEmptyIL(getDependants(task))) {
            duration = task->duration + getEarlyStart(task);
            if (duration > hList->duration) {
                hList->duration = duration;
            }
        }

        itemLink = getNextItemLink(itemLink);
    }
}

void calculateCriticalPath(HashList hList)
{
    ItemLink itemLink;
    Task task;
  
    if (!hList->validCriticalP) { 
        hList->duration = 0;
        calculateProjectDuration(hList);
        itemLink = getFirstLinkIL(hList->list);
        while (itemLink != NULL) {
            task = getItem(itemLink); 
            resetLate(task);
            itemLink = getNextItemLink(itemLink);
        }

        itemLink = getLastLinkIL(hList->list);
        while (itemLink != NULL) {
            task = getItem(itemLink); 
            calculateLateStart(task, hList->duration);
            itemLink = getPrevItemLink(itemLink);
        }
    }

    /* Print Critical Path. */
    hList->validCriticalP = 1;
    itemLink = getFirstLinkIL(hList->list);
    while (itemLink != NULL) {
        task = getItem(itemLink); 
        if (getEarlyStart(task) == getLateStart(task)) {
            printTask(task, hList->validCriticalP);
        }
        itemLink = getNextItemLink(itemLink);
    }

    printf("project duration = %lu\n", hList->duration);
}

void calculateLateStart(Task task, unsigned long pDuration)
{
    if (isEmptyIL(getDependants(task))) {
        setLateStart(task, pDuration - getDuration(task));
    } else {
        setLateStart(task, recursLateStart(task));
    }
}

unsigned long recursLateStart(Task task)
{
    ItemLink dependantLink;
    Task dependantTask;
    unsigned long min = ULONG_MAX;
    unsigned long lateStart;

    dependantLink = getFirstLinkIL(getDependants(task));
    while (dependantLink != NULL) {
        dependantTask = getItem(dependantLink);
        if (getLateStart(dependantTask) == ULONG_MAX) {
            return recursLateStart(task);
        } else {
            lateStart = getLateStart(dependantTask) - getDuration(task);
            if (lateStart < min) {
                min = lateStart;
            }
        }
        dependantLink = getNextItemLink(dependantLink);
    }

    return min;
}
