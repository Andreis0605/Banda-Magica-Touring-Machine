/*STAN Andrei -314CC*/
#ifndef stdio
#define stdio
#include <stdio.h>
#endif

#include "date.h"

//functia care afiseaza valoarea memotrata in lista
//pe pozitia pe care sea afla degetul in acel moment
void show_current(LIST *lista, FILE *write)
{
    fprintf(write, "%c\n", lista->current->value);
}

//funcia care afiseaza banda
void show(LIST *lista, FILE *write)
{
    //folosim un pointer auxiliar pentru a parcurge toata banda
    NOD *aux;
    aux = lista->sentinel;
    aux = aux->next;
    while (aux != NULL)
    {
        //la fiecare pas, verificam daca aux este elementul curent
        if (aux == lista->current)
            //daca da, il afisam intre bare verticale
            fprintf(write, "|%c|", aux->value);
        else
            //daca nu, il afisam normal
            fprintf(write, "%c", aux->value);
        aux = aux->next;
    }
    fprintf(write, "\n");
}