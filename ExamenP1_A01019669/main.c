#include <stdio.h>
#include <stdlib.h>

#define N 50
#define EXTRA 10




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
    
} Ingeniero;

typedef struct
{
    Edificio* edificios;
    Nave* naves;
    Torre* torres;
    Ingeniero* ingeniero;
    
} Edificacion;

typedef struct
{
    Ingeniero* ingenieros;
    int total;
    int ocupados;
} Nomina;

void agregarNomina(Nomina *);
void agregarEdificacion(Edificacion*);
void imprimir(Nomina *);


int main()
{
    Nomina *n = (Nomina*)malloc(sizeof(Nomina));
    n->total = EXTRA;
    n->ocupados = 0;
    
    Edificacion *ed = (Edificacion*)malloc(sizeof(Edificacion));
    
    agregarNomina(n);
    
    imprimir(n);
    /*Ingeniero *i = (Ingeniero*)malloc(sizeof(Ingeniero));
     
     i->nombre = (char*)malloc(N*sizeof(char));
     
     i->nombre = "Alejandra";
     
     printf("Nombre\t%s", i->nombre);*/
    
    
    
    return 0;
}

void imprimir(Nomina *n){
    
    Ingeniero* aux;
    for (aux = n->ingenieros; aux < n->ingenieros + n->ocupados; aux++){
        
        printf("\nNombre: %s\nApellido: %s\n",aux->nombre, aux->apellido);
        printf("\n-------------------------------------------------\n");
    }
    
}

void agregarNomina(Nomina *n)
{
    
    Ingeniero *i = (Ingeniero*)malloc(sizeof(Ingeniero));
    
    i->nombre = (char*)malloc(N*sizeof(char));
    i->apellido = (char*)malloc(N*sizeof(char));
    i->fecha_nacimiento = (char*)malloc(N*sizeof(char));
    i->fecha_ingreso =  (char*)malloc(N*sizeof(char));
    i->puesto = (char*)malloc(N*sizeof(char));
    
    i->nombre = "Alejandra";
    i->apellido = "Garay";
    i->fecha_nacimiento = "21-05-1994";
    i->fecha_ingreso = "01-06-2015";
    i->puesto = "Ingeniera";
    
    
    n->ingenieros = (Ingeniero *) malloc(n->total * sizeof(Ingeniero));
    
    
    if (n->ocupados < n->total) {
        *(n->ingenieros + n->ocupados) = *(i);
        n->ocupados++;
    }
    else {
        n->ingenieros = (Ingeniero*)realloc(n->ingenieros, sizeof(Ingeniero) * (n->total +EXTRA));
        n->total = n->total +1;
        
        *(n->ingenieros + n->total -1) = *i;
        n->total++;
    }
    
}







