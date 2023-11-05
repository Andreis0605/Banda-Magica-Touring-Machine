/*STAN Andrei -314CC*/
#include "date.h"

// prototiprile functiilor din execute.c
void init_exec_queue(EXEC_QUEUE *queue);
void add_exec_queue(EXEC_QUEUE *queue, int operation, char argument,
                    struct nod *current);
void execute(EXEC_QUEUE *queue, LIST *lista, FILE *write, UDRD_STACK *undo,
             UDRD_STACK *redo);