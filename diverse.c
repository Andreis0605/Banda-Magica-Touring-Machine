/*STAN Andrei -314CC*/
#include <stdio.h>
#include <stdlib.h>

#include "date.h"

// functia care initilizeaza banda si care
// creaza nodul santinela si primul nod din banda
void init_banda(LIST *banda)
{
    // alocam memorie pentru primele 2 noduri
    NOD *aux1, *aux2;
    aux1 = (NOD *)malloc(sizeof(NOD));
    aux2 = (NOD *)malloc(sizeof(NOD));
    if (aux1 == NULL)
    {
        printf("Nu s-a putut aloca memorie in init_BANDA");
        exit(1);
    }
    if (aux2 == NULL)
    {
        printf("Nu s-a putut aloca memorie in init_BANDA");
        exit(1);
    }
    // ii dam valoarea # primului nod si legam cele 2 noduri intre ele
    aux2->value = '#';
    aux1->next = aux2;
    aux1->prev = NULL;
    aux2->prev = aux1;
    aux2->next = NULL;

    // facem ca banda sa indice catre cei doi pointeri nou creati
    banda->sentinel = aux1;
    banda->current = aux2;
}

// functia care elibereaza memoria alocata pentru banda
void free_banda(LIST *banda)
{
    // folosim doi pointeri pentru a parcurge banda
    NOD *aux1, *aux2;
    aux1 = banda->sentinel;
    aux2 = aux1->next;
    while (aux2 != NULL)
    {
        // la fiecate pas eliberam memoria primului pointer si
        // trecem la urmatoarea pozitie in banda
        free(aux1);
        aux1 = aux2;
        aux2 = aux2->next;
    }
    //la sfarsit, eliberam memoria pentru ultimele 2 pozitii din banda
    free(aux1);
    free(aux2);
    banda->sentinel = NULL;
    banda->current = NULL;
}