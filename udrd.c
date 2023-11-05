/*STAN Andrei -314CC*/
#include <stdio.h>
#include <stdlib.h>

#include "date.h"
#include "update.h"

// functia care initializeaza o stiva undo/redo
void init_udrd(UDRD_STACK *stiva)
{
    stiva->first = NULL;
    stiva->last = NULL;
}

// functia care goleste o stiva undo/redo
void empty_udrd(UDRD_STACK *stiva)
{
    // folosind un nod pointer auxiliar, parcurgem toata stiva
    // si eliberam memoria pentru fiecare nod in parte
    UDRD_NODE *aux;
    aux = stiva->last;
    while (stiva->last != stiva->first)
    {
        stiva->last = stiva->last->prev;
        free(aux);
        aux = stiva->last;
    }
    free(aux);
    // la sfarsit, avem o stiva goala si initializata
    stiva->first = NULL;
    stiva->last = NULL;
}

// functia care adauga un nod intr-o stiva undo/redo
void push_udrd(UDRD_STACK *stiva, struct nod *position)
{
    // se aloca memorie pentru noul nod
    UDRD_NODE *aux;
    aux = (UDRD_NODE *)malloc(sizeof(UDRD_NODE));
    if(aux == NULL)
    {
        printf("Nu s-a putut aloca memorie in push_udrd");
        exit(1);
    }
    aux->position = position;
    // verificam daca stiva este goala
    if (stiva->first == NULL)
    {
        // daca da, atat inceputul cat si sfarsitul stivei
        // pointeza catre noul element
        aux->next = NULL;
        aux->prev = NULL;
        stiva->first = aux;
        stiva->last = aux;
    }
    else
    {
        // daca nu, este adaugat in varful stivei
        aux->prev = stiva->last;
        aux->next = NULL;
        stiva->last->next = aux;
        stiva->last = aux;
    }
}

// functia care scoate un element dintr-o stiva undo/redo si il adauga
// intr-o alta stiva, executand in acelasi timp si operatia memorata
// in varful stivei sursa
void pop_udrd(UDRD_STACK *sursa, UDRD_STACK *destinatie, LIST *lista)
{
    // folosim un pointer auxiliar care indica varful stivei sursa
    UDRD_NODE *aux;
    aux = sursa->last;
    // daca stiva nu este goala
    if (aux != NULL)
    {
        // adaugam in stiva destinatie un element care
        // va face operatia opusa celei din stiva sursa
        push_udrd(destinatie, lista->current);

        // executam operatia memorata
        //(mutam degetul pe pozitia memorata in stiva)
        lista->current = aux->position;

        // scadem cu un nivel in stiva si ne asiguram
        // ca daca stiva ramane vida nu ramane si neinitializata
        sursa->last = sursa->last->prev;
        if (sursa->last == NULL)
            sursa->first = NULL;

        // eliberam memoria pentru vechiul varf al stivei
        free(aux);
    }
}

// functie care sterge elementul din varful stivei
// folosita cand operatia adaugata in stiva nu se poate efectua
void delete_udrd_top(UDRD_STACK *stiva)
{
    // folosim un pointer auxiliar care indica spre
    // elementul din varful listei
    UDRD_NODE *aux;
    aux = stiva->last;

    // verificam daca stiva nu e vida
    if (aux != NULL)
    {
        // daca nu, putem sterge elemntul
        if (stiva->last == stiva->first)
        {
            // daca avem doar un element in stiva ii elberam
            // memoria si ne asiguram ca stiva sa ramana initializata
            free(aux);
            stiva->last = NULL;
            stiva->first = NULL;
        }
        else
        {
            // daca avem mai multe elemente in stiva
            // scadem nivelul stivei si eliberam memoria
            // pentru varf
            stiva->last = stiva->last->prev;
            stiva->last->next = NULL;
            free(aux);
        }
    }
    else
    {
        //daca stiva e goala, ne asiguram sa fie initializata
        stiva->first = NULL;
    }
}
