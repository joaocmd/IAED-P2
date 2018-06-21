#ifndef TASK_H
#define TASK_H

#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdio.h>

typedef struct task *Task;
#include "itemlist.h"
#include "hashlist.h"

struct task {
    unsigned long id, duration;
    unsigned long early, late;
    char *description;
    int nDependencies;
    ItemList dependants;
    ItemList dependencies;
};

/* Returns the id of the task. */
unsigned long getId(Task task);

/* Returns the duration of the task. */
unsigned long getDuration(Task task);

/* Returns the dependant tasks of the task (ItemList). */
ItemList getDependants(Task task);

/* Returns the dependencies of the task (ItemList). */
ItemList getDependencies(Task task);

/* Changes the value of the task's late start to value. */
void setLateStart(Task task, unsigned long value);

/* Resets the value of late start for task. */
void resetLate(Task task);

/* Initializes and allocates space for a new task, given its
id, duration and description. */
Task initTask(unsigned long id, unsigned long duration,
             char *description);

/* Frees the space allocated by task. Also traverses the task
dependencies and fixes them using freeDependencyLinks() (private
function) */
void removeTask(Task task);

/* Frees the memory allocated for task. */
void freeTask(Task task);

/* Adds dependency to the list of dependencies of task. */
void addDependency(Task task, Task dependency);

/* Prints the relevant information about the task.
hasCriticalPath should be given by a hashlist.*/
void printTask(Task task, int hasCriticalPath);

#endif
