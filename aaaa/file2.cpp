#include <iostream>
using namespace std;
#define MAX_COLA_ACOTADA 100

// PRACTICO PILA COLA LISTA
// EJERCICIO 2A

struct nodoCola
{
    int info;
    nodoCola *sig;
};

typedef nodoCola *Cola;

struct nodoPila
{
    int info;
    nodoCola *sig;
};

typedef nodoCola *Pila;

// FILOSOFÍA --> F I F O --> FIRST IN FIRST OUT
// UTILIZAREMOS CELDA DUMMY

// ----------------------- ESPECIFICACIÓN ---------------------------------

// *** CONSTRUCTORAS ****

// CREAR Y DEVOLVER UNA NUEVA COLA
Cola crear();

// AGREGAR AL FINAL DE LA COLA
void agregar(Cola, int);

// *** SELECTORAS ***

// DEVOLVER PRÓXIMO ELEMENTO Y LO ELIMINA DE LA COLA
// PRE-CONDICIÓN: !es_vacia (c), siendo c la Cola pasada por parámetro
int proximo(Cola);

// *** PREDICADOS ***

// DEVOLVER SI UNA COLA ES VACÍA O NO
bool es_vacia(Cola);

// *** DESTRUCTORAS ***

// DESTRUIR UNA COLA
void destruir(Cola);

// ---------------------------------------------------------------

// ------------------------ IMPLEMENTACIÓN -----------------------

Cola crear()
{
    // nodo Dummy
    Cola res = new nodoCola;
    res->sig = NULL;
    return res;
}

void agregar(Cola c, int elem)
{
    while (c->sig != NULL)
        c = c->sig;
    Cola nodo = new nodoCola;
    nodo->info = elem;
    nodo->sig = NULL;
    c->sig = nodo;
}

int proximo(Cola c)
{
    int val = c->sig->info;
    Cola borrar = c->sig;
    c->sig = borrar->sig;
    delete borrar;
    return val;
}

bool es_vacia(Cola c)
{
    return (c->sig == NULL);
}

void destruir(Cola c)
{
    Cola borrar;
    while (c->sig != NULL)
    {
        borrar = c->sig;
        c->sig = borrar->sig;
        delete borrar;
    }
}

int sacar (Pila & p) {
    int val = p->info;
    Pila borrar = p;
    p = p->sig;
    delete borrar;
    return val;
}
// -----------------------------------------------------------------

// EJERCICIO 2B

struct nodoColaOpt
{
    Cola inicio;
    Cola fin;
};

typedef nodoColaOpt *ColaOptimizada;

// *** CONSTRUCTORAS ****

// CREAR Y DEVOLVER UNA NUEVA COLA
ColaOptimizada crearOptimizado()
{
    ColaOptimizada res = new nodoColaOpt;
    res->inicio = res->fin = NULL;
    return res;
}

// AGREGAR AL FINAL DE LA COLA
void agregarOptimizado(ColaOptimizada c, int elem)
{
    Cola nodo = new nodoCola;
    nodo->info = elem;
    nodo->sig = NULL;
    if (c->inicio == NULL)
    {
        c->inicio = c->fin = nodo;
    }
    else
    {
        c->fin->sig = nodo;
        c->fin = nodo;
    }
}

// *** SELECTORAS ***

// DEVOLVER PRÓXIMO ELEMENTO Y LO ELIMINA DE LA COLA
// PRE-CONDICIÓN: !es_vacia (c), siendo c la Cola pasada por parámetro
int proximo(ColaOptimizada c)
{
    int val = c->inicio->info;
    Cola borrar = c->inicio;
    c->inicio = borrar->sig;
    delete borrar;
    if (c->inicio == NULL)
        c->fin = NULL;
    return val;
}

// *** PREDICADOS ***

// DEVOLVER SI UNA COLA ES VACÍA O NO
bool es_vacia(ColaOptimizada c)
{
    return (c->inicio == NULL);
}

// *** DESTRUCTORAS ***

// DESTRUIR UNA COLA
void destruir(ColaOptimizada c)
{
    Cola borrar, aux = c->inicio;
    while (aux != NULL)
    {
        borrar = aux;
        aux = borrar->sig;
        delete borrar;
    }
    c->inicio = c->fin = NULL;
}

// -----------------------------------------------------------------

// EJERCICIO 2C

struct nodoColaAcotada
{
    Cola inicio;
    Cola fin;
    int cant;
};

typedef nodoColaAcotada *ColaAcotada;

// *** CONSTRUCTORAS ****

// CREAR Y DEVOLVER UNA NUEVA COLA
ColaAcotada crear_acotada();

// AGREGAR AL FINAL DE LA COLA
// Precondición: c no puede estar llena
void agregar_acotada(ColaAcotada c, int);

// *** SELECTORAS ***

// DEVOLVER PRÓXIMO ELEMENTO Y LO ELIMINA DE LA COLA
// PRE-CONDICIÓN: !es_vacia (c), siendo c la Cola pasada por parámetro
int proximo_acotada(ColaAcotada c);

// *** PREDICADOS ***

// DEVOLVER SI UNA COLA ES VACÍA O NO
bool es_vacia_acotada(ColaAcotada c);

// DEVOLVER SI UNA COLA ES VACÍA O NO
bool esta_llena(ColaAcotada c);

// *** DESTRUCTORAS ***

// DESTRUIR UNA COLA
void destruir_acotada(ColaAcotada c);

// -----------------------------------------------------------------

// EJERCICIO 2D -- MEMORIA DINÁMICA

// ****** CONSTRUCTORAS *******

ColaAcotada crear_acotada()
{
    ColaAcotada res = new nodoColaAcotada;
    res->inicio = res->fin = NULL;
    res->cant = 0;
    return res;
}

// AGREGAR AL FINAL DE LA COLA
//  Precondición: c no está llena
void agregarOptimizado(ColaAcotada c, int elem)
{
    Cola nodo = new nodoCola;
    nodo->info = elem;
    nodo->sig = NULL;
    if (c->inicio == NULL)
    {
        c->inicio = c->fin = nodo;
    }
    else
    {
        c->fin->sig = nodo;
        c->fin = nodo;
    }
    c->cant++;
}

// *** SELECTORAS ***

// DEVOLVER PRÓXIMO ELEMENTO Y LO ELIMINA DE LA COLA
// PRE-CONDICIÓN: !es_vacia (c), siendo c la Cola pasada por parámetro
int proximo(ColaAcotada c)
{
    int val = c->inicio->info;
    Cola borrar = c->inicio;
    c->inicio = borrar->sig;
    delete borrar;
    if (c->inicio == NULL)
        c->fin = NULL;
    c->cant--;
    return val;
}

// *** PREDICADOS ***

// DEVOLVER SI UNA COLA ES VACÍA O NO
bool es_vacia_acotada(ColaAcotada c)
{
    return c->cant == 0;
}

// DEVOLVER SI UNA COLA ES VACÍA O NO
bool esta_llena(ColaAcotada c)
{
    return c->cant == MAX_COLA_ACOTADA;
}

// *** DESTRUCTORAS ***

// DESTRUIR UNA COLA
void destruir(ColaAcotada c)
{
    Cola borrar, aux = c->inicio;
    while (aux != NULL)
    {
        borrar = aux;
        aux = borrar->sig;
        delete borrar;
    }
    c->inicio = c->fin = NULL;
    c->cant = 0;
}

// -----------------------------------------------------------------

// EJERCICIO 2D -- MEMORIA ESTÁTICA (CON ARREGLOS)

struct cola_estatica
{
    int info[MAX_COLA_ACOTADA];
    int cant;
    int pos;
};

typedef cola_estatica *ColaAcotadaArreglos;

// *** CONSTRUCTORAS ****

// CREAR Y DEVOLVER UNA NUEVA COLA
ColaAcotadaArreglos crear_cola_estatica()
{
    ColaAcotadaArreglos res = new cola_estatica;
    res->cant = res->pos = 0;
    return res;
}

// AGREGAR AL FINAL DE LA COLA
// Precondición: c no puede estar llena
void agregar_cola_estatica(ColaAcotadaArreglos c, int elem)
{
    int prox_pos = (c->pos + c->cant) % MAX_COLA_ACOTADA;
    c->info[prox_pos] = elem;
    c->cant++;
}

// *** SELECTORAS ***

// DEVOLVER PRÓXIMO ELEMENTO Y LO ELIMINA DE LA COLA
// PRE-CONDICIÓN: !es_vacia (c), siendo c la Cola pasada por parámetro
int proximo_cola_estatica(ColaAcotadaArreglos c)
{
    int val = c->info[c->pos];
    c->cant--;
    c->pos = (c->pos + 1) % MAX_COLA_ACOTADA;
    return val;
}

// *** PREDICADOS ***

// DEVOLVER SI UNA COLA ES VACÍA O NO
bool es_vacia_cola_estatica(ColaAcotadaArreglos c)
{
    return c->cant == 0;
}

// DEVOLVER SI UNA COLA ES VACÍA O NO
bool esta_llena_cola_estatica(ColaAcotadaArreglos c)
{
    return c->cant == MAX_COLA_ACOTADA;
}

// *** DESTRUCTORAS ***

// DESTRUIR UNA COLA
void destruir_cola_estatica(ColaAcotadaArreglos c)
{
    c->cant = c->pos = 0;
}

// -----------------------------------------------------------------

void test_acotada_estatica()
{
    ColaAcotadaArreglos c = crear_cola_estatica();
    agregar_cola_estatica(c, 2234);
    agregar_cola_estatica(c, 2);
    agregar_cola_estatica(c, 3);
    agregar_cola_estatica(c, 4);

    int *ptr = c->info;
    cout << "LUGAR PRIMERO:" << ptr[0] << endl
         << endl;
    cout << "LA DIRECCIÓN DE MEMORIA DEL ARREGLO ES: " << ptr << endl
         << endl;

    int proximo = proximo_cola_estatica(c);
    cout << "EL PROXIMO ELEMENTO DE LA COLA ES: " << proximo << endl;
    agregar_cola_estatica(c, 5);
    proximo = proximo_cola_estatica(c);
    cout << "EL PROXIMO ELEMENTO DE LA COLA ES: " << proximo << endl;
    proximo = proximo_cola_estatica(c);
    cout << "EL PROXIMO ELEMENTO DE LA COLA ES: " << proximo << endl;
    proximo = proximo_cola_estatica(c);
    cout << "EL PROXIMO ELEMENTO DE LA COLA ES: " << proximo << endl;
    proximo = proximo_cola_estatica(c);
    cout << "EL PROXIMO ELEMENTO DE LA COLA ES: " << proximo << endl;
    agregar_cola_estatica(c, 6);
    proximo = proximo_cola_estatica(c);
    cout << "EL PROXIMO ELEMENTO DE LA COLA ES: " << proximo << endl
         << endl;
    delete c;
    cout << "LUGAR SOBREVIVIENTE " << ptr[0];
}

//-------------------------------------------------------------------

// EJERCICIO 3

bool mismosElementos(Pila &p, Cola &c)
{
    Pila copia = crear();
    while (!es_vacia(c))
        agregar(copia, proximo(c));
    while (!es_vacia(p) && !es_vacia(copia))
    {
        if (sacar(p) != sacar(copia))
            return false;
    }
    return (es_vacia(p) && es_vacia(copia));
}

int main()
{
    test_acotada_estatica();
}

// EJERCICIO 4

bool mismosElementos (Pila &p, Cola &c){
    Pila copia = crear();
    while (!es_vacia(c))
    {
        agregar(copia, proximo(c));
    }
    while (!es_vacia(p) && !es_vacia(copia))
    {
        if (sacar(p) != sacar(copia))
        {
            return false;
        }
    }
    return es_vacia(p) && es_vacia(copia);
}
