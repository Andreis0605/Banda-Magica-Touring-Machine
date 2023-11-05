/*STAN Andrei -314CC*/
#ifndef date
#define date

// structura care va retine nodurile din banda
typedef struct nod
{
    char value;
    struct nod *next, *prev;
} NOD;

// structura care va retine banda
typedef struct list
{
    struct nod *sentinel, *current;
} LIST;

// structura care va retine nodurile din coada de executie
typedef struct execution_node
{
    int operation;
    char argument;
    struct nod *current_banda;
    struct execution_node *next, *prev;
} EXEC_NODE;

// structura care retine coada de executie
typedef struct execution_queue
{
    struct execution_node *first, *last;
} EXEC_QUEUE;

// structura care retine nodurile pentru stivele undo si redo
typedef struct udrd_node
{
    struct nod *position;
    struct udrd_node *next, *prev;
} UDRD_NODE;

// struxtura care retine o stiva undo/redo
typedef struct udrd_stack
{
    struct udrd_node *first, *last;
} UDRD_STACK;

#endif