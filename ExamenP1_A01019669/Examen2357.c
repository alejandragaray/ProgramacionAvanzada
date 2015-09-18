#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1000
#define EXTRA 1
#define PISOS_EDIFICIO 4
#define PISOS_TORRE 3
#define DIAMETROS 3



typedef struct
{
    int* modales;
    int simetrico;
    int T;
} Edificio;

typedef struct
{
    int inferior;
    int superior;
    
} Diametro;

typedef struct
{
    int* modales;
    char* nombre;
    int T;
    Diametro* diametros;
    
} Torre;

typedef struct
{
    char* tipo;
    int modal;
    int T;
} Nave;

typedef struct
{
    char* nombre;
    char* apellido;
    char* fecha_nacimiento;
    char* fecha_ingreso;
    int salario;
    char* puesto;
    int borrado;
    int id;
    
} Ingeniero;

typedef struct
{
    char* fecha;
    Edificio* edificios;
    Nave* naves;
    Torre* torres;
    Ingeniero* ingeniero;
    int totalE;
    int totalT;
    int totalN;
    int tamano;
    
} Edificacion;

typedef struct
{
    Ingeniero* ingenieros;
    int total;
    int ocupados;
    int max;
    
} Nomina;

typedef struct
{
    Edificacion* edificaciones;
    int total;
    int tamano;
    
} Modelado;

void agregarNomina(Nomina *n, char* nombre, char* apellido, char* fecha_nac, char* fecha_ing, char* puesto, int salario);
void imprimir(Nomina *);
void editarIngeniero(Nomina*);
void eliminarIngeniero(Nomina*);
void agregarEdificacion(Modelado*);
void imprimirModelado(Modelado *);


Nomina *n;
Modelado *m;

int main()
{
    n = (Nomina*)malloc(sizeof(Nomina));
    m = (Modelado*)malloc(sizeof(Modelado));
    m->edificaciones = (Edificacion*)malloc(N*sizeof(Edificacion));
    //m->edificaciones->fecha = "17sep2015";
    m->edificaciones->edificios = (Edificio*)malloc(N*sizeof(Edificio));
    m->edificaciones->naves = (Nave*)malloc(N*sizeof(Nave));
    m->edificaciones->torres = (Torre*)malloc(N*sizeof(Torre));
    
    m->tamano = N;
    m->total = 0;
    
    n->max = 0;
    n->ingenieros = (Ingeniero *) malloc(n->total * sizeof(Ingeniero));
    n->total = EXTRA;
    n->ocupados = 0;
    
    
    
    agregarNomina(n,"Alejandra", "Garay", "21-05-1994", "01-06-2015", "Ingeniera", 50000);
    agregarNomina(n,"Ramiro", "Bifaretti", "03-12-1993", "01-07-2015", "Ingeniero", 12000);
    agregarNomina(n,"Cesar", "Millan", "07-06-1993", "01-03-2015", "Programador", 55000);
    imprimir(n);
    
    editarIngeniero(n);
    imprimir(n);
    
    eliminarIngeniero(n);
    imprimir(n);
    
    agregarEdificacion(m);
    imprimirModelado(m);
    
    return 0;
}

void imprimir(Nomina *n){
    
    Ingeniero* aux;
    
    for (aux = n->ingenieros; aux < n->ingenieros + n->ocupados; aux++){
        if(aux->borrado == 0)
        {
            printf("\nNombre: %s\nApellido: %s\nid: %d\n",aux->nombre, aux->apellido, aux->id);
            printf("\n-------------------------------------------------\n");
            
        }
        
    }
    
}

void imprimirModelado(Modelado *m){
    
    Edificacion* auxE;
    
    for(auxE = m->edificaciones; auxE < m->edificaciones + m->tamano; auxE++)
    {
        if(auxE->ingeniero != NULL)
        {
            printf("\nIngeniero de las siguientes edificaciones: %s\n %s\n",auxE->ingeniero->nombre, auxE->ingeniero->apellido);
            
            printf("\n-------------------------------------------------\n");
        }
        
    }
    printf("\nFecha de edificacion %s\n",auxE->fecha);
    
    Edificio* aux;
    for (aux = m->edificaciones->edificios; aux < m->edificaciones->edificios + m->edificaciones->totalE; aux++){
        printf("\nEdificio: \n");
        int* modales;
        int modalesEdificio = 0;
        for(modales = aux->modales; modales < aux->modales + PISOS_EDIFICIO; modales++)
        {
            modalesEdificio++;
        }
        printf("\nSimetrico: %d\nPeriodo: %d\nModales: %d",aux->simetrico, aux->T, modalesEdificio);
        
    }
    
    Torre* auxT;
    for (auxT = m->edificaciones->torres; auxT < m->edificaciones->torres + m->edificaciones->totalT; auxT++){
        printf("\n----------------------------------------------\n");
        printf("\nTorre: \n");
        int* modales;
        int modalesTorre = 0;
        for(modales = aux->modales; modales < aux->modales + PISOS_TORRE; modales++)
        {
            modalesTorre++;
        }
        
        int diametro1;
        int diametro2;
        Diametro* ds;
        for(ds = auxT->diametros; ds < auxT->diametros + DIAMETROS; ds++)
        {
            
            printf("\nDiametros: \n");
            diametro1 = ds->inferior;
            diametro2 = ds->superior;
            printf("Inferior: %d\nSuperior: %d\n");
        }
        
        printf("\nNombre: %s\nPeriodo: %d\nModales: %d",auxT->nombre, auxT->T, modalesTorre);
        
    }
    
    Nave* auxN;
    for (auxN = m->edificaciones->naves; auxN < m->edificaciones->naves + m->edificaciones->totalN; auxN++)
    {
        printf("\n----------------------------------------------\n");
        printf("\nNave: \n");
        printf("\nTipo: %s\nPeriodo: %d\nModales: %d",auxN->tipo, auxN->T, auxN->modal);
        
    }
    
    
    
}

void agregarNomina(Nomina *n, char* nombre, char* apellido, char* fecha_nac, char* fecha_ing, char* puesto, int salario)
{
    
    Ingeniero *i = (Ingeniero*)malloc(sizeof(Ingeniero));
    
    i->nombre = (char*)malloc(N*sizeof(char));
    i->apellido = (char*)malloc(N*sizeof(char));
    i->fecha_nacimiento = (char*)malloc(N*sizeof(char));
    i->fecha_ingreso =  (char*)malloc(N*sizeof(char));
    i->puesto = (char*)malloc(N*sizeof(char));
    
    
    strcpy(i->nombre, nombre);
    strcpy(i->apellido, apellido);
    strcpy(i->fecha_nacimiento ,fecha_nac);
    strcpy(i->fecha_ingreso, fecha_ing);
    strcpy(i->puesto ,puesto);
    i->salario = salario;
    i->borrado = 0;
    
    i->id = n->max;
    
    n->max = n->max + 1;
    
    if (n->ocupados < n->total)
    {
        *(n->ingenieros + n->ocupados) = *(i);
        n->ocupados++;
    }
    else
    {
        n->ingenieros = (Ingeniero*)realloc(n->ingenieros, sizeof(Ingeniero) * (n->total + 1));
        n->total = n->total + 1;
        *(n->ingenieros + n->ocupados) = *i;
        n->ocupados++;
    }
    
}



void editarIngeniero(Nomina* n)
{
    
    char* nombre = "Pablo";
    char* apellido = "Cardenas";
    char* fecha_nacimiento = "21-09-1993";
    char* fecha_ingreso = "01-02-2011";
    char* puesto = "Limpiador";
    int salario = 2;
    
    
    Ingeniero *aux = n->ingenieros;
    
    int idBuscado = 0;
    int contador = 0;
    while(contador < n->ocupados && aux->id != idBuscado)
    {
        aux++;
        contador++;
    }
    if(aux != NULL)
    {
        printf("%s %s\n", aux->nombre, aux->apellido);
        strcpy(aux->nombre, nombre);
        strcpy(aux->apellido,apellido);
        //strcpy(aux->fecha_nacimiento,fecha_nacimiento);
        //strcpy(aux->fecha_ingreso, fecha_ingreso);
        //strcpy(aux->puesto, puesto);
        aux->salario = salario;
        printf("Se ha editado en la nomina\n");
        printf("----------------------------------------------------\n");
        
    }
    else
    {
        printf("\nTrabajador no existe");
    }
}

void eliminarIngeniero(Nomina* n)
{
    
    Ingeniero *aux = n->ingenieros;
    
    int idBuscado = 0;
    int contador = 0;
    while(contador < n->ocupados && aux->id != idBuscado)
    {
        aux++;
        contador++;
    }
    if(aux != NULL)
    {
        printf("%s %s\n", aux->nombre, aux->apellido);
        free(aux->nombre);
        free(aux->apellido);
        free(aux->fecha_ingreso);
        free(aux->fecha_nacimiento);
        free(aux->puesto);
        aux->borrado = 1;
        
        
        
        printf("Se ha borrado de la nomina\n");
        printf("----------------------------------------------------\n");
        
    }
    else
    {
        printf("\nTrabajador no existe");
    }
}

void agregarEdificacion(Modelado * m)
{
    Edificacion *ed = m->edificaciones + m->total;
    m->total = m->total + 1;
    
    
    
    Ingeniero *i = (Ingeniero*)malloc(sizeof(Ingeniero));
    
    i->nombre = (char*)malloc(N*sizeof(char));
    i->apellido = (char*)malloc(N*sizeof(char));
    strcpy(i->nombre, "Juan");
    strcpy(i->apellido, "Carpio");
    
    ed->ingeniero = i;
    
    Edificio * edificio = m->edificaciones->edificios + m->edificaciones->totalE;
    m->edificaciones->totalE = m->edificaciones->totalE + 1;
    
    edificio->simetrico = 1;
    edificio->T = 3;
    edificio->modales = (int*)malloc(PISOS_EDIFICIO*sizeof(int));
    
    int cont = 1;
    
    int j;
    for(j = 0; j<PISOS_EDIFICIO; ++j)
    {
        *(edificio->modales + j) = (cont);
        cont++;
    }
    
    
    Nave * nave = m->edificaciones->naves + m->edificaciones->totalN;
    m->edificaciones->totalN = m->edificaciones->totalN + 1;
    
    nave->modal = 1;
    nave->T = 6;
    nave->tipo = (char*)malloc(60 * sizeof(char));
    strcpy(nave->tipo, "Creciente");
    
    Torre * torre = m->edificaciones->torres + m->edificaciones->totalT;
    m->edificaciones->totalT = m->edificaciones->totalT + 1;
    
    torre->nombre = (char*)malloc(60 * sizeof(char));
    strcpy(torre->nombre, "torreB");
    torre->T = 6;
    
    torre->modales = (int*)malloc(PISOS_TORRE*sizeof(int));
    
    int contTo = 1;
    
    int k;
    for(k = 0; k<PISOS_TORRE; ++k)
    {
        *(torre->modales + k) = (contTo);
        contTo++;
    }
    
    torre->diametros = (Diametro*)malloc(N*sizeof(Diametro));
    Diametro* auxD;
    for(auxD = torre->diametros; auxD < torre->diametros + DIAMETROS; auxD++)
    {
        auxD->inferior = rand();
        auxD->superior = rand();
    }
    
    
}





