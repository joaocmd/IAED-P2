/* Joao Carlos Morgado David - 89471 */

#define MODULO 137
#include "parser.h"
#include "task.h"
#include "itemlist.h"
#include "pointerlist.h"
#include "hashtable.h"
#include "hashlist.h"

int main()
{
    HashList tasks;
    
    tasks = initHashList(MODULO);
    initBuffer();

    while(1) {
        readCommand();
        if (command("add")) {
            parseAdd(tasks);
        } else if (command("duration")) {
            parseDuration(tasks); 
        } else if (command("depend")) {
            parseDepend(tasks);
        } else if (command("remove")) {
            parseRemove(tasks);
        } else if (command("path")) {
            parsePath(tasks);
        } else if (command("first")) {
            parseFirst(tasks);
        } else if (command("second")) {
            parseSecond(tasks);
        } else if (command("exit")) {
            parseExit(tasks);
        } else {
            invalidCommand();
        }
    };
 
    return 0;
}
