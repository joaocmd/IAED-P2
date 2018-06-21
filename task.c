#include "task.h"

/* Frees the memory of the list of dependencies of task.
It goes to each dependency's dependants list and removes
the node from it.*/
void freeDependencyLinks(Task task);

unsigned long getId(Task task)
{
    return task->id;
}

unsigned long getDuration(Task task)
{
    return task->duration;
}

unsigned long getEarlyStart(Task task)
{
    return task->early;
}

unsigned long getLateStart(Task task)
{
    return task->late;
}

int getDependenciesLength(Task task)
{
    return task->nDependencies;
}

void setLateStart(Task task, unsigned long value)
{
    task->late = value;
}

void resetLate(Task task)
{
    task->late = ULONG_MAX;
}

ItemList getDependants(Task task)
{
    return task->dependants;
}

ItemList getDependencies(Task task)
{
    return task->dependencies;
}

Task initTask(unsigned long id, unsigned long duration,
             char *description) {
    Task newTask = (Task) malloc(sizeof(struct task));
    newTask->early = 0;
    newTask->id = id;
    newTask->duration = duration;
    newTask->description = description;
    newTask->dependants = initItemList();
    newTask->dependencies = initItemList();
    newTask->nDependencies = 0;

    return newTask;
}

void removeTask(Task task)
{
    freeDependencyLinks(task);
    freeTask(task);
}

void freeTask(Task task)
{
    free(task->description);
    freeItemLinks(task->dependants);
    freeItemLinks(task->dependencies);
    free(task);
}

void freeDependencyLinks(Task task)
{
    ItemLink itemLink;
    ItemLink depItemLink;
    Task iTask;

    itemLink = getFirstLinkIL(task->dependencies);
    while (itemLink != NULL) {
        iTask = getItem(itemLink);
        depItemLink = findItemLink(iTask->dependants, getId(task));
        freeItemLink(iTask->dependants, depItemLink);
        itemLink = getNextItemLink(itemLink);
    }
}

void addDependency(Task task, Task dependency)
{
    unsigned long early;

    addItemToList(task->dependencies, dependency);
    addItemToList(dependency->dependants, task);

    early = dependency->duration + dependency->early;
    if (task->early < early) {
        task->early = early;
    }
    task->nDependencies++;
}

void printTask(Task task, int hasCriticalPath)
{
    if (!hasCriticalPath) {
        printf("%lu \"%s\" %lu", task->id, task->description, task->duration);
    } else {
        if (task->early == task->late) {
            printf("%lu \"%s\" %lu [%lu CRITICAL]", task->id, task->description,
                    task->duration, task->early);
        } else {
            printf("%lu \"%s\" %lu [%lu %lu]", task->id, task->description,
                task->duration, task->early, task->late);
        }
    }
    printItemKeys(task->dependencies);
}
