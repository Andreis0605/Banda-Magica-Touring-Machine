/*STAN Andrei -314CC*/
#include <stdio.h>
#include <stdlib.h>

#include "date.h"

// functia care executa operatia MOVE_LEFT
int move_left(LIST *lista)
{
    // functia intoarce 0 cand operatia nu este posibila
    // pentru a putea verifica daca trebuie pusa pe
    // stiva de UNDO
    if (lista->current->prev != lista->sentinel)
    {
        lista->current = lista->current->prev;
        return 1;
    }
    else
        return 0;
}

// functia care executa operatia de MOVE_LEFT
void move_right(LIST *lista)
{
    // verifica daca degetul e pe ultimul element din lista
    if (lista->current->next == NULL)
    {
        // daca da, creeaza un nou nod ce are inauntru caracterul #
        // si il adauga in lista
        NOD *aux;
        aux = (NOD *)malloc(sizeof(NOD));
        if (aux == NULL)
        {
            printf("Nu s-a putut aloca memori in MOVE_Right");
            exit(1);
        }
        aux->value = '#';
        aux->next = NULL;
        aux->prev = lista->current;
        lista->current->next = aux;
        lista->current = lista->current->next;
    }
    else
    {
        // daca nu,doar deplaseaza degetul
        lista->current = lista->current->next;
    }
}

// functia care executa operatiile WRITE
void write(LIST *lista, char c)
{
    // scrie la pozitia curenta listera primita ca argument
    lista->current->value = c;
}

// functia care executa operatia de INSERR_RIGHT
void insert_right(LIST *lista, char c)
{
    // aloca memorie pentru noul nod
    NOD *aux;
    aux = (NOD *)malloc(sizeof(NOD));
    if (aux == NULL)
    {
        printf("Nu s-a putut aloca memori in INSERT_RIGHT");
        exit(1);
    }
    aux->value = c;
    // vreificam daca suntem pe ultima pozitie
    // si adaugam noul nod in banda corespunzator
    if (lista->current->next == NULL)
    {
        lista->current->next = aux;
        aux->prev = lista->current;
        aux->next = NULL;
    }
    else
    {
        aux->prev = lista->current;
        aux->next = lista->current->next;
        lista->current->next->prev = aux;
        lista->current->next = aux;
    }
    // mutam degetul pe elementul nou adaugat
    lista->current = lista->current->next;
}

// functia care executa operatia de INSERR_LEFT
void insert_left(LIST *lista, char c, FILE *write)
{
    // aloca memorie pentru noul nod
    NOD *aux;
    aux = (NOD *)malloc(sizeof(NOD));
    if (aux == NULL)
        {
            printf("Nu s-a putut aloca memori in INSERT_LEFT");
            exit(1);
        }
    aux->value = c;
    // verific daca este posibil sa fac operatia
    if (lista->current->prev == lista->sentinel)
    {
        // daca nu, afisez eroare si eliberez
        // memoria pentru nodul alocat
        fprintf(write, "ERROR\n");
        free(aux);
    }
    else
    {
        // daca da, adaug nodul in banda
        aux->next = lista->current;
        aux->prev = lista->current->prev;
        lista->current->prev->next = aux;
        lista->current->prev = aux;
        // mut degetul pe pozitia nodului
        lista->current = lista->current->prev;
    }
}

// functia care executa operatia de MOVE_LEFT_CHAR
void move_left_char(LIST *lista, char c, FILE *write)
{
    // Se parcurge lista cu un pointer pornind de la deget
    // si se cauta un nod care are ca valoare retinuta caracterul cautat
    NOD *aux;
    aux = lista->current;
    while (aux != lista->sentinel && aux->value != c)
    {
        aux = aux->prev;
    }
    // verificam daca am gasit acest nod
    if (aux == lista->sentinel)
    {
        // daca nu, afisam eroare
        fprintf(write, "ERROR\n");
    }
    else
    {
        // daca da, mutam degetul pe acest nod
        lista->current = aux;
    }
}

// functia care executa operatia de MOVE_RIGHT_CHAR
void move_right_char(LIST *lista, char c)
{
    // Se parcurge lista cu un pointer pornind de la deget
    // si se cauta un nod care are ca valoare retinuta caracterul cautat
    NOD *aux;
    aux = lista->current;
    while (aux->next != NULL && aux->value != c)
    {
        aux = aux->next;
    }
    // verificam daca am gasit acest nod
    if (aux->next == NULL && aux->value != c)
    {
        // daca nu, adaugam un nou nod la capatul benzii
        // care are in ele caracterul #
        NOD *add;
        add = (NOD *)malloc(sizeof(NOD));
        if (add == NULL)
        {
            printf("Nu s-a putut aloca memori in MOVE_RIGHT_CHAR");
            exit(1);
        }
        add->value = '#';
        add->prev = aux;
        add->next = NULL;
        aux->next = add;
        lista->current = add;
    }
    else
    {
        // daca da, mutam degetul pe acest nod
        lista->current = aux;
    }
}