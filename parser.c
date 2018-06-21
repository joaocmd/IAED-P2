#include "parser.h"

/* Reads next word from input and copies to buffer. */
void readWord();

/* Copies to the end of the input line to buffer. */
void readLine();

/* Reads word from input and returns 0 or the value
of the number if it's valid. */
unsigned long parsePositiveUnsignedLong();

/* Checks if the description is valid and returns its length. 
If it's invalid returns -1.*/
int parseDescription();

/* Prints duration of tasks in allTasks with duration >= d. */
void printDuration(HashList allTasks, unsigned long d);

/* Prints the ids of tasks that depend on task. */
void printDependsIds(Task task);

/* Reallocs memory to buffer if it's almost full. */
void checkBufferLimits(int used);

/* Cleans the whole input until it finds a \n or EOF. */
void cleanBuffer();

/* All of these print the correct error message. */
void illegalArgumentError();
void idAlreadyExistsError();
void noSuchTaskError();
void taskWithDependenciesError();
void noTasksExistError();
void noCriticalPathError();

/* Control defines if last read command found nothing(-1),
found \n or EOF after the input(0) or if it finds a space after
the expected input(1) */
static char *buffer;
static int bufferLength;
static int control;

void initBuffer()
{
    buffer = (char*) malloc(sizeof(char)*STARTSIZE);
    bufferLength = STARTSIZE;
}

void readCommand() 
{
    int i = 0;
    char c;

    while((c = getchar()) != ' ' && c != '\n' && i < bufferLength) {
        buffer[i] = c;
        i++;
        checkBufferLimits(i);
    }
    buffer[i] = '\0';

    control = (c == '\n' || c == EOF)? 0 : 1;
}

void readWord()
{
    char c;
    int i = 1;

    /* Clean trailing whitespace */
    while ((c = getchar()) == ' ' || c == '\n' || c == EOF) {
        if (c == '\n' || c == EOF) {
            control = -1;
            return;
        }
    }
    
    /* Found valid character */
    buffer[0] = c;

    while ((c = getchar()) != '\n' && c != ' ' && c != EOF) {
        buffer[i] = c;
        i++;
        checkBufferLimits(i);
    }
    buffer[i] = '\0';
   
    control = (c == '\n' || c == EOF)? 0 : 1;
}

void readLine()
{
    /* Copies content from stdin to buffer until it finds a new line */

    int i = 0;
    char c;

    while ((c = getchar()) != '\n' && c != EOF) {
        buffer[i] = c;
        i++;
        checkBufferLimits(i);
    }
    buffer[i] = '\0';
}

void parseAdd(HashList allTasks)
{
    Task newTask;
    PointerLink dependencyPointerLink;
    unsigned long taskId, duration, dependencyId;
    int descriptionLength;
    char* description;
    Vector dependencies;
    int i;

    if (control == 0) {
        illegalArgumentError();
        return;
    }

    /* Read task id */
    readWord();
    if (control <= 0) {
        illegalArgumentError();
        return;
    }
    taskId = parsePositiveUnsignedLong();
    if (taskId == 0) {
        illegalArgumentError();
        cleanBuffer();
        return;
    }

    if (findLinkInHL(allTasks, taskId) != NULL) {
        idAlreadyExistsError(); 
        cleanBuffer();
        return;
    }
    
    /* Read description */
    if((descriptionLength = parseDescription()) == -1) {
        illegalArgumentError();
        return;
    }

    description = (char*) malloc(sizeof(char)*descriptionLength);
    strcpy(description, buffer);
    
    /* Read duration */
    readWord();
    if (control == -1) {
        illegalArgumentError();
        free(description);
        return;
    }

    duration = parsePositiveUnsignedLong();
    if (duration <= 0) {
        illegalArgumentError();
        cleanBuffer();
        free(description);
        return;
    }

    dependencies = initVector(DEPENDENCIESSIZE);
    /* Read dependencies */
    while (control == 1) {
        readWord();
        dependencyId = parsePositiveUnsignedLong();
        if (dependencyId == 0) {
            illegalArgumentError();
            cleanBuffer();
            freeVector(dependencies);
            return;  
        }  

        if (!hasElementVec(dependencies, dependencyId)) {
            addElementVec(dependencies, dependencyId);
        }
    }
    
    newTask = initTask(taskId, duration, description);
    for (i = 0; i < dependencies->length; i++) {
        dependencyPointerLink = findLinkInHL(allTasks, dependencies->elements[i]);
        if (dependencyPointerLink == NULL) {
            noSuchTaskError(); 
            removeTask(newTask);
            freeVector(dependencies);
            cleanBuffer();
            return;
        }
        addDependency(newTask, getItem(getItemLink(dependencyPointerLink)));
    }

    freeVector(dependencies);
    addItemToHL(allTasks, newTask);
}

void parseDuration(HashList allTasks)
{
    unsigned long duration = 0;

    if (control != 0) {
        readWord();
        if (control != -1) {
            duration = parsePositiveUnsignedLong();
            if (duration == 0) {
                illegalArgumentError();
                return;
            }
        }
    }
    printDuration(allTasks, duration);
}

void printDuration(HashList allTasks, unsigned long duration)
{
    ItemLink iLink;
    Task iTask;
    int validCritical;

    validCritical = hasCriticalPath(allTasks);
    iLink = getFirstItemLinkHL(allTasks);
    while (iLink != NULL) {
        iTask = getItem(iLink);
        if (getDuration(iTask) >= duration) {
            printTask(iTask, validCritical);
        }
        iLink = getNextItemLink(iLink);
    }
}

void parseDepend(HashList allTasks)
{
    unsigned long id;
    Task task;
    PointerLink link;

    if (control == 0) {
        illegalArgumentError();
        return;
    } 
    
    readWord();
    if (control == -1) {
        illegalArgumentError();
        return;
    } 
    id = parsePositiveUnsignedLong();
    if (id == 0) {
        illegalArgumentError();
        return;
    } 

    if ((link = findLinkInHL(allTasks, id)) == NULL) {
        noSuchTaskError();
        return;
    } 
    
    task = getItem(getItemLink(link));
    printDependsIds(task);
}

void printDependsIds(Task task)
{
    ItemList dependants;

    printf("%lu:", getId(task));
    dependants = getDependants(task);
    
    if (isEmptyIL(dependants)) {
        puts(" no dependencies");
    } else {
        printItemKeys(dependants);
    }
}

void parseRemove(HashList allTasks)
{
    unsigned long id;
    PointerLink link;
    Task task;

    if (control == 0) {
        illegalArgumentError();
        return;
    } 

    readWord();
    if (control == -1) {
        illegalArgumentError();
        return;
    } 
    
    id = parsePositiveUnsignedLong();
    if (id == 0) {
        illegalArgumentError();
        return;
    }
    if ((link = findLinkInHL(allTasks, id)) == NULL) {
        noSuchTaskError();
        return;
    }
    
    task = getItem(getItemLink(link));
    if (!isEmptyIL(getDependants(task))) {
        taskWithDependenciesError();
        return;
    }

    freeHLLink(allTasks, link);
    removeTask(task);
}

void parsePath(HashList allTasks)
{
    cleanBuffer();
    calculateCriticalPath(allTasks);
}

void parseFirst(HashList allTasks)
{
    Task task = NULL;
    ItemLink link;
    unsigned long id;
    int max = 0;
    int nDependencies;

    cleanBuffer();
    
    /* Set id to first task */
    link = getFirstItemLinkHL(allTasks);
    if (link != NULL) {
        task = getItem(link);
        id = getId(task);
    } else {
        noTasksExistError();   
        return;
    }
    
    while (link != NULL) {
        task = getItem(link);
        nDependencies = getDependenciesLength(task);
        if (nDependencies > max) {
            id = getId(task);
            max = nDependencies;
        }
        link = getNextItemLink(link);
    }

    printf("%lu\n", id);
}

void parseSecond(HashList allTasks)
{
    unsigned long max = 0; 
    unsigned long id = 0;
    unsigned long lateFinish;
    ItemLink link;
    Task task;

    cleanBuffer();

    if (!hasCriticalPath(allTasks)) {
        noCriticalPathError();
        return;
    }

    link = getFirstItemLinkHL(allTasks);
    if (link == NULL) {
        noTasksExistError();
        return;
    }

    while (link != NULL) {
        task = getItem(link);
        /* Get terminal tasks. */
        if (isEmptyIL(getDependants(task))) {
            lateFinish = getLateStart(task) + getDuration(task);
            if (lateFinish > max) {
                max = lateFinish;
                id = getId(task);
            }
        }
        link = getNextItemLink(link);
    }

    printf("%lu\n", id);
}


void parseExit(HashList allTasks)
{
    free(buffer);
    freeHashList(allTasks);
    exit(0);
}

void invalidCommand()
{
    illegalArgumentError();
    cleanBuffer();
}

unsigned long parsePositiveUnsignedLong() 
{
    /* Returns the value of the number if it's valid. If invalid
    returns 0 */

    int i;
    unsigned long value = 0;

    for (i = 0; isdigit(buffer[i]); i++);  
    
    if (strlen(buffer) == i) {
        sscanf(buffer, "%lu", &value);
    }
   
    return value;
}

int parseDescription()
{
    char c;
    int i = 0;

    /* Clean trailing whitespace */
    while ((c = getchar()) == ' ');
    
    /* Found valid character */
    if (c != '"') {
        return -1; 
    }

    while ((c = getchar()) != '"' && c != '\n' && c != EOF) {
        buffer[i] = c;
        i++;
        checkBufferLimits(i);
    }
    buffer[i] = '\0';

    return (c == '\n' || c == EOF || i > MAXDESCRIPTION)? -1 : i+1;
}

void checkBufferLimits(int used)
{
    if (bufferLength - used < BUFFERTHRESHOLD) {
        bufferLength += STARTSIZE;
        buffer = (char*) realloc(buffer, sizeof(char) * bufferLength);
    }
}

void cleanBuffer() {
    char c;
    
    if (control > 0) {
        while ((c = getchar()) != '\n' && c != EOF);
    }
}

int command(char *command)
{
    return (strcmp(buffer, command) == 0);
}

void idAlreadyExistsError() {puts("id already exists");}
void illegalArgumentError() {puts("illegal arguments");}
void noSuchTaskError() {puts("no such task");}
void taskWithDependenciesError() {puts("task with dependencies");}
void noTasksExistError() {puts("no tasks exist");}
void noCriticalPathError() {puts("no valid late start calculated");}
