#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "ArrayList.h"
#include "tramites.h"

/*
* Opciones del sistema:
*
*1. TRAMITE   URGENTE: Se  otorga  un  numero  de  turno  para  los tramites urgentes.
*2. TRAMITE REGULAR: Se  otorga un numero  de turno para  los tramites regulares.
*3. PROXIMO CLIENTE: El sistema le indicara al usuario quien es el próximo turno a ser atendido y a que tramite corresponde.
*4. LISTAR: En esta opción se listan las personas pendientes de ser atendidas en cada tramite.
*5. INFORMAR:  Los clientes atendidos en cada uno de los tramites ordenados por DNI de manera descendente.
*
*/


int main()
{

    char seguir='s';
    int opcion=0;
    int numTurno=0;
    eTramite* nuevoTramite;

    ArrayList* listaUrgente= al_newArrayList();
    ArrayList* listaRegular= al_newArrayList();
    ArrayList* listaAtendido= al_newArrayList();
    ArrayList* clon=al_newArrayList();

    eTramite* aux;


    int i;

    do
    {
        //printf("1)Tramite urgente\n2)Tramite regular\n3)Proximo cliente\n4)Listar\n5)Informar\n6)Salir\n");
        printf("1)Tramite urgente\n2)Tramite regular\n3)Proximo cliente\n4)Listar\n5)Informar\n6)salir\n7)al_Clone\n8)al_Sublist\n9-Set\n10)al-ContainsAll\n");
        printf("11)al_Clear\n12)al_Push\nIngrese numero de opcion: ");
        scanf("%d",&opcion);
    printf("\n\n");
        switch(opcion)
        {
        case 1:
            nuevoTramite = tramite_turnoUrgente(numTurno);
            if(nuevoTramite != NULL)
            {
                numTurno++;
                listaUrgente->add(listaUrgente,nuevoTramite);
            }
                else
                {
                    printf("No se pudo cargar su tramite.");
                }
                    getche();
                    system("cls");

                    break;
        case 2:
            nuevoTramite= tramite_turnoRegular(numTurno);

            if(nuevoTramite != NULL)
            {
                numTurno++;
                listaRegular->add(listaRegular,nuevoTramite);
            }
                else
                {
                    printf("No se pudo cargar su tramite.");
                }

                    getche();
                    system("cls");
                    break;
        case 3:
            tramite_siguiente(listaUrgente,listaRegular,listaAtendido);
                getche();
                system("cls");
                break;
        case 4:
            tramite_listarPendientes(listaUrgente,listaRegular);
                getche();
                system("cls");
                break;
        case 5:
            al_sort(listaAtendido,tramite_ordenarDNI,0);

            printf("Tramites urgentes atendidos:\n");

                for(i=0; i<al_len(listaAtendido); i++)
                {
                    aux=(eTramite*)al_get(listaAtendido,i);
                    if(aux->idTramite==100)
                    {
                        printf("DNI:%ld\tTurno: %d\n",aux->dni,aux->turno);
                    }
                }

            printf("Tramites regulares atendidos:\n");

                for(i=0; i<al_len(listaAtendido); i++)
                {
                    aux=(eTramite*)al_get(listaAtendido,i);
                    if(aux->idTramite==102)
                    {
                        printf("DNI:%ld\tTurno: %d\n",aux->dni,aux->turno);
                    }
                }

                getche();
                system("cls");
                break;

        case 6:
            seguir='n';
            break;
        case 7:
            clon=al_clone(listaAtendido);

            printf("Lista clonada\n");
                for(i=0; i<al_len(clon); i++)
                {
                    aux=(eTramite*)al_get(clon,i);
                    if(aux->idTramite==100)
                    {
                        printf("DNI:%ld\tTurno: %d\n",aux->dni,aux->turno);
                    }
                }
                printf("\n");

                getche();
                system("cls");
                break;
        case 8:

            clon=al_subList(listaAtendido,0,2);
            printf("Lista subLista");
            for(i=0; i<al_len(clon); i++)
            {
                aux=(eTramite*)al_get(clon,i);
                if(aux->idTramite==100)
                {
                    printf("DNI:%ld\tTurno: %d\n",aux->dni,aux->turno);
                }
            }



                printf("\n");

                getche();
                system("cls");
                break;

        case 9:
                nuevoTramite =(eTramite*) malloc(sizeof(eTramite));
                nuevoTramite->dni=10;
                nuevoTramite->idTramite=100;
                nuevoTramite->turno =58;
                if(al_set(listaAtendido,0,nuevoTramite))
                    {
                    printf("se seteo");
                    }
            break;
        case 10:
            printf("al_containsAll\n");

            if(!al_containsAll(listaAtendido,listaUrgente))
                printf("No lo contiene/n");
                else
                     printf("Lo contiene/n");

                    break;
        case 11:
            al_clear(listaAtendido);
            printf("clear");
                    break;
        case 12:
            printf("push\n");
             nuevoTramite =(eTramite*) malloc(sizeof(eTramite));
            nuevoTramite->dni=10;
            nuevoTramite->idTramite=100;
            nuevoTramite->turno =58;

            al_push(listaAtendido,0,nuevoTramite);
                    break;
        case 13:
            printf("Is empty");
            if(al_isEmpty(listaAtendido))
                printf("esta vacio");
                else if(al_isEmpty(listaRegular)==0)
                    printf("No esta vacio");
                    else
                        printf("null");
                    break;
        }

    }
    while(seguir=='s');

    return 0;
}

