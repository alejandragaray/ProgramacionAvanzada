
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define POBLACION 2
#define PREGUNTAS 2
#define RESPUESTAS 6
#define N 50
#define BLOQUES 2

typedef struct {

    char *nombre;
    int edad;

} Persona;

typedef struct {

    char* descripcion;
    char** respuestas;
    int* opciones;

} Pregunta;

typedef struct {
    Pregunta* preguntas;
} Encuesta;

typedef void (*Opcion) (Encuesta *);

void datosPoblacion(Encuesta *);
void imprimirPersonas(Encuesta *);
void imprimirEncuesta(Encuesta *);
void contestarEncuesta(Encuesta *);
void libera(Encuesta *);
void llenarEncuesta(Encuesta*);

Opcion opciones[] = {imprimirPersonas, imprimirEncuesta, datosPoblacion, llenarEncuesta, contestarEncuesta};


Persona *personas = (Persona*)malloc(POBLACION*sizeof(Persona));

int main() {


    Encuesta *e = (Encuesta*)malloc(sizeof(Encuesta));
    e->preguntas = (Pregunta*)malloc(PREGUNTAS*sizeof(Pregunta));
    

        opciones[2](e);
        opciones[3](e);
        opciones[4](e);

    int opcion = 0;
    while(opcion != 6)
    {
        printf("\n--Menu de opciones--");
        printf("\n 1. Imprimir poblacion");
        printf("\n 2. Imprimir datos de la encuesta");
        printf("\n 6. Salir");
        printf("\n");

        scanf("%d", &opcion);

        if(opcion == 6)
        {
            printf("--Has salido--");
            break;
        }
        opciones[opcion-1](e);

    }


    libera(e);
    free(e);
    return 0;
}


void imprimirPersonas(Encuesta *)
{
    Persona *aux;
    for (aux = personas; aux < (personas + POBLACION); aux++)
    {
        printf("\nNombre: %s\nEdad: %d\n", aux->nombre, aux->edad);
    }
}

void imprimirEncuesta(Encuesta * e)
{
    Pregunta *aux;
    char **respuestas;

    for (aux = e->preguntas; aux < (e->preguntas + PREGUNTAS); aux++)
    {
        printf("\nDescripcion de pregunta: %s\n", aux->descripcion);

        for (respuestas = aux->respuestas; respuestas < aux->respuestas + RESPUESTAS; ++respuestas){

            printf("Posible opcion: %s\n", *(respuestas));
        }
    }
}

void datosPoblacion(Encuesta * e)
{

    Persona *aux;
    for (aux = personas; aux < (personas + POBLACION); aux++)
    {
        Persona p;
        p.nombre = (char*)malloc(N * sizeof(char));

        printf("\n------------Ingresa los datos de la persona----------\n");
        printf("Nombre: ");
        scanf("%s", p.nombre);
        printf("Edad: ");
        scanf("%d",&p.edad);

        if (p.edad > 17 && p.edad < 120)
        {
            printf("Edad correcta");
        }
        else
        {
            while(p.edad < 17 || p.edad > 120)
            {
                printf("Ingrese una edad entre 17 y 120: ");
                scanf("%d",&p.edad);
            }
            printf("Edad correcta");
        }
        *(aux) = p;
    }

}

void llenarEncuesta(Encuesta* e){

    srand (time(NULL));

    Pregunta *aux;

    for (aux = e->preguntas; aux < e->preguntas + PREGUNTAS; ++aux)
    {
        Pregunta p;

        p.descripcion = (char*)malloc(N * sizeof(char));

        p.respuestas = (char**)malloc(RESPUESTAS*sizeof(char*));

        printf("\nIngresa tu pregunta: ");
        scanf("%s", p.descripcion);

        char **respuestas;

        for (respuestas = p.respuestas; respuestas < p.respuestas + RESPUESTAS; ++respuestas)
        {
            *(respuestas) = (char*)malloc(N*sizeof(char));

            char * random = (char*)malloc(N*sizeof(char));

            int r = rand()%100;
            sprintf(random, "%d", r);

            *(respuestas) = random;
        }
        *(aux) = p;
    }
}

void contestarEncuesta( Encuesta* e){

    srand(time(NULL));

    Persona* encuestado;

    for (encuestado = personas; encuestado < personas + POBLACION; ++encuestado)
    {

        Pregunta * totalPreguntas;

        printf("\n------------------------------------------\n");
        printf("\nEncuestado: %s\n", encuestado->nombre);

        for (totalPreguntas = e->preguntas; totalPreguntas < e->preguntas + PREGUNTAS; totalPreguntas++)
        {
            printf("\nDescripcion de pregunta: %s\n",totalPreguntas->descripcion);

            char **posiblesOpciones;
            int i = 1;

            for (posiblesOpciones = totalPreguntas->respuestas; posiblesOpciones < totalPreguntas->respuestas + RESPUESTAS; ++posiblesOpciones)
            {
                printf("%d) %s\t",i,*(posiblesOpciones));
                i = i +1;
            }

            printf("\n");

            int res = rand() % 7;

            printf("El encuestado contesto: %d\n\n",res + 1);
            if (res < 6)
            {
                *(totalPreguntas->opciones + res) = *(totalPreguntas->opciones + res) + 1;

                if ( 17 <  encuestado->edad && encuestado->edad < 46 )
                {
                    *(totalPreguntas->opciones + RESPUESTAS + res) = *(totalPreguntas->opciones + RESPUESTAS +res) + 1;
                }

                else
                {
                    *(totalPreguntas->opciones + RESPUESTAS * BLOQUES + res) = *(totalPreguntas->opciones + RESPUESTAS * BLOQUES + res) + 1;
                }
            }
        }
    }
}


void libera(Encuesta *e){

    Persona* encuestado;
    for (encuestado = personas; encuestado < personas + POBLACION; ++encuestado)
    {
        free(encuestado->nombre);
    }
    free(personas);

    Pregunta *preguntas;
    for (preguntas = e->preguntas; preguntas < e->preguntas + PREGUNTAS; ++ preguntas)
    {
        free(preguntas->descripcion);

        char **respuestas;
        for (respuestas = preguntas->respuestas; respuestas < preguntas->respuestas + RESPUESTAS; ++respuestas)
        {
            free(*(respuestas));
        }
        free(preguntas->respuestas);
    }

    free(e->preguntas);

}