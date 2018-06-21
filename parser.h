#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "hashlist.h"
#include "itemlist.h"
#include "task.h"
#include "vector.h"

#define STARTSIZE 8001
#define MAXDESCRIPTION 7998
#define BUFFERTHRESHOLD 1
#define DEPENDENCIESSIZE 16

/* Allocates memory for the reading buffer. */
void initBuffer();

/* Reads everything until it finds the end of a word or \n. */
void readCommand();

/* Parses the arguments for the command add, and adds to allTasks. */
void parseAdd(HashList allTasks);

/* Parses the arguments for the command duration. Prints all
tasks with duration >= to the argument given from input.*/
void parseDuration(HashList allTasks);

/* Parses the arguments for the command depend. Prints
the ids of the items that depend on the task given from input.*/
void parseDepend(HashList allTasks);

/* Parses the arguments for the command remove, and removes it 
from allTasks. */
void parseRemove(HashList allTasks);

/* Calculates the critical path for allTasks. */
void parsePath(HashList allTasks);

/* Prints the id of the task with the most dependencies. */
void parseFirst(HashList allTasks);

/* Prints the id of the task with the largest late finish. */
void parseSecond(HashList allTasks);

/* Exits the program and frees remaining memory */
void parseExit(HashList allTasks);

/* Gives an error message and cleans the buffer if it's
not empty */
void invalidCommand();

/* Returns if the command left on buffer is equal to
the argument command. */
int command(char *command);

#endif
