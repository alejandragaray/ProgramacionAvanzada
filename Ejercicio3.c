#include <stdio.h>
#include <stdlib.h>

#define N 5
typedef struct
{
    int edad;
    char* nombre;
    char* apellido;

} Paciente;

typedef struct
{
    Paciente* paciente;
    int id_cama;
    int status;

} Cama;

typedef struct
{
    Cama* camas;
    int total;
    int ocupadas;

} Hospital;

void imprimir(Hospital*);
void agregar(Hospital*);
void encontrarPaciente(Hospital*);
void alta(Hospital*);
void libera(Hospital *);

typedef void (*Opcion) (Hospital *);


Opcion opciones[] = {agregar, imprimir, encontrarPaciente, alta, libera };

int main() {
    Hospital *h = (Hospital*)malloc(sizeof(Hospital));
    h->total = N;
    h->ocupadas = 0;
    h->camas = (Cama*)malloc(h->total * sizeof(Cama));

    int cama_id = 0;
    Cama * aux;
    for(aux = h->camas + h->ocupadas; aux < h->camas + h->total; aux++)
    {
        cama_id++;
        aux->id_cama = cama_id;

        aux->status = 0;
    }

    int opcion = 0;
    while(opcion != 5)
    {
        printf("\n--Menu de opciones--");
        printf("\n 1. Agregar paciente");
        printf("\n 2. Imprimir hospital");
        printf("\n 3. Encontrar pacuente por cama");
        printf("\n 4. Dar de alta un paciente");
        printf("\n 5. Salir");
        printf("\n");

        scanf("%d", &opcion);

        if(opcion == 5)
        {
            printf("--Has salido--");
            break;
        }
        opciones[opcion-1](h);

    }

    libera(h);
    free(h);
}

void imprimir(Hospital *h){

    Cama* aux;
    for (aux = h->camas; aux < h->camas + h->ocupadas; aux++){
        if(aux->status != 0)
            printf("\nCama: %d\nNombre: %s\nApellido: %s\nEdad: %d\n",aux->id_cama, aux->paciente->nombre, aux->paciente->apellido, aux->paciente->edad);
        printf("\n-------------------------------------------------\n");
    }

}
void agregar(Hospital *h){

    Paciente *p = (Paciente*)malloc(sizeof(Paciente));

    p->nombre = (char*)malloc(20*sizeof(char));
    p->apellido = (char*)malloc(20*sizeof(char));

    printf("Nombre: ");
    scanf("%s", p->nombre);
    printf("\nApellido: ");
    scanf("%s", p->apellido);
    printf("\nEdad: ");
    scanf("%d", &p->edad);

    if (h->ocupadas < h->total){
        Cama * aux = h->camas;
        while( aux->status == 1)
        {
            aux++;
        }
        aux->paciente = p;
        aux->status = 1;

        h->ocupadas++;
    }
    else {

        h->camas = (Cama*)realloc(h->camas,sizeof(Cama)*(h->total+N));
        h->total = h->total+N;
        Cama * aux = h->camas+ h->ocupadas;

        int cama_id = aux->id_cama+N;

        for(aux = h->camas + h->ocupadas; aux < h->camas + h->total; aux++)
        {
            cama_id++;
            aux->id_cama = cama_id;

            aux->status = 0;
        }
        aux = h->camas + h-> ocupadas;

        while( aux->status == 1 && aux < h->camas+ h->total)
        {
            aux++;
        }
        h->ocupadas++;
        aux->paciente = p;
        aux->status = 1;



    }
}

void encontrarPaciente(Hospital *h)
{
    int opt;
    printf("\nIngrese el numero de cama para saber paciente: \n");
    scanf("%d", &opt);

    Cama *aux = h->camas;
    if(opt < h->total)
    {
        while(aux->id_cama != opt)
        {
            aux++;
        }
        if(aux->paciente != NULL)
            printf("Nombre: %s\n" ,aux->paciente->nombre);
        else
            printf("Cama: %d\nesta vacia",aux->id_cama);
    }
    else
    {
        printf("\nCama no existe");
    }

}

void alta(Hospital *h)
{
    int opt;
    printf("\nIngrese la cama del paciente a dar de alta: \n");
    scanf("%d", &opt);

    Cama *aux = h->camas;
    if(opt < h->total)
    {
        while(aux->id_cama != opt)
        {
            aux++;
        }
        if(aux->paciente != NULL)
        {
            free(aux->paciente->nombre);
            free(aux->paciente->apellido);
            aux->status = 0;
            printf("Se ha dado de alta al paciente\n");
        }
        else
            printf("Cama: %d\nesta vacia",aux->id_cama);
    }
    else
    {
        printf("\nCama no existe");
    }

}

void libera(Hospital * h)
{
    Cama * aux;
    for(aux = h->camas; aux < h->camas+h->total; aux++)
    {
        if(aux->paciente != NULL)
        {
            free(aux->paciente->apellido);
            free(aux->paciente->nombre);
            free(aux->paciente);
        }

    }
    free(h->camas);
}

