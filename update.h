/*STAN Andrei -314CC*/
#include <stdio.h>

#include "date.h"

//prototipurile functiilor din update.c
int move_left(LIST *lista);
void move_right(LIST *lista);
void write(LIST *lista, char c);
void insert_right(LIST *lista, char c);
void insert_left(LIST *lista, char c,FILE *write);
void move_left_char(LIST *lista, char c,FILE *write);
void move_right_char(LIST *lista, char c);