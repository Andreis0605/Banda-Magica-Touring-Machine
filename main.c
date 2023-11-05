/*STAN Andrei -314CC*/
#ifndef stdio
#define stdio
#include <stdio.h>
#endif

#ifndef stdlib
#define stdlib
#include <stdlib.h>
#endif

#include <string.h>

// includerea tuturor headerelor definite
#include "update.h"
#include "query.h"
#include "date.h"
#include "execute.h"
#include "diverse.h"
#include "udrd.h"

int main()
{
    // deschiderea fisierelor pentru scriere si citire
    FILE *read, *write;
    read = fopen("tema1.in", "rt");
    if(read == NULL)
    {
        printf("Nu s-a putut deschide fisierul de intrare");
        exit(1);
    }
    write = fopen("tema1.out", "wt");
    if(write == NULL)
    {
        printf("Nu s-a putut deschide fisierul de iesire");
        exit(1);
    }

    // declarea variabilelor
    UDRD_STACK undo, redo;
    EXEC_QUEUE coada_executie;
    LIST banda;
    int i, n;
    char command[100];

    // initializarea listelor, cozilor si stivelor
    init_exec_queue(&coada_executie);
    init_banda(&banda);
    init_udrd(&undo);
    init_udrd(&redo);

    // citirea datelor de intrare
    fscanf(read, "%d", &n);
    fgetc(read);
    for (i = 0; i < n; i++)
    {
        fgets(command, 100, read);

        // In fiecare linie a fisierului de intrare cautam denumirea
        // unei instructiuni. In cazul unei operatii de tip "update"
        // o punem in coada de executie, specificand tipul ei prin
        // codificari, argumentele ei, daca exista, si pozitia curenta
        // a degetului
        if (strstr(command, "MOVE_LEFT_CHAR"))
        {
            add_exec_queue(&coada_executie, 3, command[15], banda.current);
        }
        else
        {
            if (strstr(command, "MOVE_RIGHT_CHAR"))
            {
                add_exec_queue(&coada_executie, 4, command[16], banda.current);
            }
            else
            {
                if (strstr(command, "MOVE_LEFT"))
                {
                    add_exec_queue(&coada_executie, 1, 0, banda.current);
                }
                else
                {
                    if (strstr(command, "MOVE_RIGHT"))
                    {
                        add_exec_queue(&coada_executie, 2, 0, banda.current);
                    }
                    else
                    {
                        if (strstr(command, "INSERT_LEFT"))
                        {
                            add_exec_queue(&coada_executie, 5, command[12],
                                           banda.current);
                        }
                        else
                        {
                            if (strstr(command, "INSERT_RIGHT"))
                            {
                                add_exec_queue(&coada_executie, 6, command[13],
                                               banda.current);
                            }
                        }
                    }
                }
            }
        }
        if (strstr(command, "WRITE"))
        {
            add_exec_queue(&coada_executie, 7, command[6], banda.current);
        }

        // Opetatiile de tip "query" se executa in momentul
        // in care sunt citite
        if (strstr(command, "SHOW_CURRENT"))
        {
            show_current(&banda, write);
        }
        else
        {
            if (strstr(command, "SHOW"))
            {
                show(&banda, write);
            }
        }
        // Operatia EXECUTE se executa in momentul citirii
        if (strstr(command, "EXECUTE"))
        {
            execute(&coada_executie, &banda, write, &undo, &redo);
        }
        // Opetatiile de UNDO si REDO se executa in momentul citirii
        if (strstr(command, "UNDO"))
        {
            pop_udrd(&undo, &redo, &banda);
        }
        if (strstr(command, "REDO"))
        {
            pop_udrd(&redo, &undo, &banda);
        }
    }

    // eliberarea memoriei
    free_banda(&banda);
    empty_udrd(&undo);
    empty_udrd(&redo);

    // inchiderea fisierelor
    fclose(read);
    fclose(write);

    return 0;
}