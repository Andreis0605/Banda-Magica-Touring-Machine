/*STAN Andrei -314CC*/
#include "date.h"

//prototipusile functiilor din udrd.c
void init_udrd(UDRD_STACK *stiva);
void empty_udrd(UDRD_STACK *stiva);
void push_udrd(UDRD_STACK *stiva, struct nod *position,  int operation);
void pop_udrd(UDRD_STACK *sursa, UDRD_STACK *destinatie, LIST *lista);
void delete_udrd_top(UDRD_STACK *stiva);