/*STAN Andrei -314CC*/
#include <stdio.h>
#include <stdlib.h>

#include "date.h"
#include "update.h"
#include "udrd.h"

// functia care initializeaza o coada de execute
void init_exec_queue(EXEC_QUEUE *queue)
{
    queue->first = NULL;
    queue->last = NULL;
}

// functia care adauga un nod in coada de execute
void add_exec_queue(EXEC_QUEUE *queue, int operation, char argument,
                    struct nod *current)
{
    // alocam memoria pentru noul nod
    EXEC_NODE *aux;
    aux = (EXEC_NODE *)malloc(sizeof(EXEC_NODE));
    if (aux == NULL)
    {
        printf("Nu s-a putut aloca memorie in add_exec_queue");
        exit(1);
    }
    // ii dam toate vaorile de care are nevoie
    aux->operation = operation;
    aux->argument = argument;
    aux->current_banda = current;

    // verificam daca coada este goala
    if (queue->first == NULL && queue->last == NULL)
    {
        // daca da, introducem elementul pe prima pozitie
        // si facem ca pointerii spre primul si ultimul element
        // sa pointeze catre acesta
        queue->first = aux;
        queue->last = aux;
        aux->next = NULL;
        aux->prev = NULL;
    }
    else
    {
        // daca nu, introducem elementul in coada in mod normal
        aux->prev = queue->last;
        queue->last->next = aux;
        aux->next = NULL;
        queue->last = aux;
    }
}

// functia care realizeaza operatia de EXECUTE
void execute(EXEC_QUEUE *queue, LIST *lista, FILE *w, UDRD_STACK *undo,
             UDRD_STACK *redo)
{
    // folosim un pointer catre primul element la coada
    EXEC_NODE *aux;
    aux = queue->first;

    // verificam daca coada nu e vida
    if (aux != NULL)
    {
        // daca nu e vida, executa operatia din
        // pointerul auxiliar

        // verificam ce tip de operatie avem de facut
        // in functie de codificarea operatiilor
        switch (aux->operation)
        {
        case 1:
        {
            // pentru MOVE_LEFT, adaugam in stiva de undo
            // aceasta operatie si o executam
            push_udrd(undo, lista->current, 1);
            if (move_left(lista) == 0)
            {
                // daca MOVE_LEFT nu s-a putut executa, o scoatem din
                // stiva de undo
                delete_udrd_top(undo);
            }
        }
        break;
        case 2:
        {
            // pentru MOVE_LEFT, adaugam in stiva de undo
            // aceasta operatie si o executam
            push_udrd(undo, lista->current, 2);
            move_right(lista);
        }
        break;
        case 3:
            // executam MOVE_LEFT_CHAR
            move_left_char(lista, aux->argument, w);
            break;
        case 4:
            // executam MOVE_RIGHT_CHAR
            move_right_char(lista, aux->argument);
            break;
        case 5:
            // executam INSERT_LEFT
            insert_left(lista, aux->argument, w);
            break;
        case 6:
            // executam INSERT_RIGHT
            insert_right(lista, aux->argument);
            break;
        case 7:
        {
            // in momentul in care inatlnim operatia WRITE
            // golim stivele de undo si redo si dupa executam operatia in sine
            empty_udrd(undo);
            empty_udrd(redo);
            write(lista, aux->argument);
        }
        break;
        default:
            break;
        }

        // trecem la urmatorul element din coada
        queue->first = queue->first->next;
        if (queue->first == NULL)
        {
            // ne asiguram ca aceasta coada ramane initiallizata
            queue->last = NULL;
        }
        // eliberam memmoria pentru nodul care a fost "executat"
        free(aux);
    }
    else
    {
        // daca da, ne asiguram ca coada ramane initializata
        queue->last = NULL;
    }
}