//
// Created by alejandra on 8/24/15.
//

#include <stdio.h>
#include <stdlib.h>
#define N 100
typedef struct {
    char *nombre;
    char *apellido;
    char *rol;
    int edad;
    int embarcacion;

} Tripulante;

typedef struct {
    Tripulante *tripulantes;
    char *nombre;
    char *propietario;
    char *eslora;
    char *manga;
    int max;
    int totalTripulantes;


} Embarcacion;

typedef struct {
    Embarcacion *barcos;
    int tamano;
    int totalBarcos;

} Puerto;

typedef void (*Opcion) (Puerto *);

void imprimir(Puerto *);
void agregar(Puerto *);
void encontrar(Puerto *);
void propietario(Puerto *);
void desplegarInfo(Puerto *);
void liberarMemoria(Puerto *);

Opcion opciones[] = {agregar, imprimir, encontrar, propietario, desplegarInfo };

int main() {

    Puerto *pto = (Puerto *) malloc(sizeof(Puerto));
    pto->tamano = 1;
    pto->totalBarcos = 0;
    pto->barcos = (Embarcacion *) malloc(pto->tamano * sizeof(Embarcacion));

    int opcion = 0;
    while(opcion != 6)
    {
        printf("\n--Menu de opciones--");
        printf("\n 1. Agregar barco con tripulantes");
        printf("\n 2. Imprimir puerto");
        printf("\n 3. Ver tripulantes por embarcacion");
        printf("\n 4. Ver propietario por embarcacion");
        printf("\n 5. Desplegar embarcaciones y tripulacion");
        printf("\n 6. Salir");
        printf("\n");

        scanf("%d", &opcion);

        if(opcion == 6)
        {
            printf("--Has salido--");
            break;
        }
        opciones[opcion-1](pto);

    }


    liberarMemoria(pto);

    free(pto);
    return 0;
}



void imprimir(Puerto *puerto) {

    if(puerto->totalBarcos != 0)
    {

        Embarcacion *aux;
        for (aux = puerto->barcos; aux < puerto->barcos + puerto->totalBarcos; aux++) {
            printf("Nombre del barco:%s\n", aux->nombre);
        }
        printf("\n ---------------------------- \n");
    }
    else
    {
        printf("\n No hay barcos, agrega uno \n");
    }


}

void agregar(Puerto *p) {

    Embarcacion em1;
    em1.nombre = (char *) malloc(N * sizeof(char));
    em1.eslora = (char *) malloc(N * sizeof(char));
    em1.propietario = (char *) malloc(N * sizeof(char));
    em1.manga = (char *) malloc(N * sizeof(char));


    printf("Ingrese maximo de tripulantes: ");
    scanf("%d", &em1.max);

    printf("\nPropietario: ");
    scanf("%s", em1.propietario);

    printf("\nNombre del barco: ");
    scanf("%s", em1.nombre);

    printf("\nEslora: ");
    scanf("%s", em1.eslora);

    printf("\nManga: ");
    scanf("%s", em1.manga);

    em1.totalTripulantes = 0;


    em1.tripulantes = (Tripulante *) malloc(em1.max * sizeof(Tripulante));

    int aux;
    for (aux = em1.totalTripulantes; aux < em1.max; aux++) {
        Tripulante t;
        t.nombre = (char *) malloc(N * sizeof(char));
        t.apellido = (char *) malloc(N * sizeof(char));
        t.rol = (char *) malloc(N * sizeof(char));

        printf("\n--Tripulante-- ");
        printf("\nNombre: ");
        scanf("%s", t.nombre);
        printf("\nApellido: ");
        scanf("%s", t.apellido);
        printf("\nRol de tripulante: ");
        scanf("%s", t.rol);
        printf("\nEdad: ");
        scanf("%d", &t.edad);

        *(em1.tripulantes + em1.totalTripulantes) = t;
        em1.totalTripulantes++;
    }

    if (p->totalBarcos < p->tamano) {
        *(p->barcos + p->totalBarcos) = em1;
        p->totalBarcos++;
    }
    else {
        p->barcos = (Embarcacion*)realloc(p->barcos, sizeof(Embarcacion) * (p->tamano +1));
        p->tamano = p->tamano +1;

        *(p->barcos + p->tamano -1) = em1;
        p->totalBarcos++;
    }

}

void encontrar(Puerto *puerto)
{
    if(puerto->totalBarcos != 0) {
        Embarcacion *aux;
        Tripulante *auxt;

        printf("\nBarcos disponibles: \n");
        for (aux = puerto->barcos; aux < puerto->barcos + puerto->totalBarcos; aux++) {
            printf("\nBarco: %s\n", aux->nombre);

            printf("\n------------Tripulantes------------- \n");
            for (auxt = aux->tripulantes; auxt < aux->tripulantes + aux->totalTripulantes; auxt++) {
                printf("\nNombre: %s\nRol: %s\n", auxt->nombre, auxt->rol);
            }
        }
        printf("\n------------------------- \n");
    }
    else
    {
        printf("\n ------No hay barcos, agrega uno------\n");
    }


}
void propietario(Puerto *puerto)
{
    if(puerto->totalBarcos != 0) {
        Embarcacion *aux;

        printf("\nBarcos disponibles: \n");
        for (aux = puerto->barcos; aux < puerto->barcos + puerto->totalBarcos; aux++) {
            printf("\nBarco: %s\nPropietario:%s\n", aux->nombre, aux->propietario);
            printf("\n------------------------- \n");
        }

    }
    else
    {
        printf("\n ------No hay barcos, agrega uno------\n");
    }
}
void desplegarInfo(Puerto *puerto)
{
    if(puerto->totalBarcos != 0) {
        Embarcacion *aux;
        Tripulante *auxt;

        printf("\nBarcos en el puerto: \n");
        for (aux = puerto->barcos; aux < puerto->barcos + puerto->totalBarcos; aux++) {
            printf("\nBarco: %s\nPropietario: %s\nManga: %s\nMaximo de tripulantes:%d\n", aux->nombre, aux->propietario, aux->manga, aux->max);

            printf("\n------------Tripulantes------------- \n");
            for (auxt = aux->tripulantes; auxt != aux->tripulantes + aux->totalTripulantes; auxt++) {
                printf("\nNombre: %s\nApellido: %s\nRol: %s\nEdad: %d\n", auxt->nombre, auxt->apellido, auxt->rol, auxt->edad);
            }
        }
        printf("\n------------------------- \n");
    }
    else
    {
        printf("\n ------No hay barcos, agrega uno------\n");
    }
}

void liberarMemoria(Puerto * p)
{
    Embarcacion * aux1;
    for(aux1 = p->barcos; aux1 < p->barcos+p->tamano; aux1++)
    {
        if(aux1->tripulantes != NULL)
        {
            Tripulante * aux2 = p->barcos->tripulantes;

                    free(aux2->nombre);
                    free(aux2->apellido);
                    free(aux2->rol);



        }
            free(aux1->nombre);
            free(aux1->eslora);
            free(aux1->manga);
            free(aux1->propietario);
            free(aux1->tripulantes);
    }

    free(p->barcos);

}

