#include <iostream>
using namespace std;

#define MIN_INT -10000;

struct nodoABChar
{
    char info;
    nodoABChar *izq;
    nodoABChar *der;
};

typedef nodoABChar *ABChar;

struct nodoAB
{
    int info;
    nodoAB *izq;
    nodoAB *der;
};

typedef nodoAB *ABInt;

struct nodoListaChar
{
    char info;
    nodoListaChar *sig;
};

typedef nodoListaChar *ListaChar;

struct nodoListaInt
{
    int info;
    nodoListaInt *sig;
};

typedef nodoListaInt *ListaInt;

// PROTOTIPO
ListaChar cons(ListaChar L, char e);
ListaChar merge(ListaChar L1, ListaChar L2);
ABInt multiplicador(ABInt AB, int i);
void imprimir_arbol(ABChar a);
ABChar construir_arbol(ABInt subarbol_izq, int raiz, ABInt subarbol_der);
void agregar_final (ListaChar & l, char elem);
ListaInt retornar_ruta(ABInt AB, int i);

int main()
{
    return 0;
}

ListaChar cons(ListaChar L, char e)
{
    ListaChar nuevo = new nodoListaChar;
    nuevo->info = e;
    nuevo->sig = L;
    return nuevo;
}

ListaChar merge(ListaChar L1, ListaChar L2)
{
    ListaChar aux = L1;
    while (aux != NULL && aux->sig)
        aux = aux->sig;
    if (aux == NULL)
        return L2;
    aux->sig = L2;
    return L1;
}

ABChar construir_arbol(ABChar subarbol_izq, char raiz, ABChar subarbol_der)
{
    ABChar a = new nodoABChar;
    a->info = raiz;
    a->izq = subarbol_izq;
    a->der = subarbol_der;
    return a;
}

void imprimir_arbol(ABChar a)
{
    if (a != NULL)
    {
        imprimir_arbol(a->izq);
        cout << "|" << a->info << "|  ";
        imprimir_arbol(a->der);
    }
}

ABInt multiplicador(ABInt AB, int i)
{
    if (AB == NULL)
        return 0;

    AB->info = AB->info * i;
    multiplicador(AB->izq, i);
    multiplicador(AB->der, i);

    return AB;
}

int retornar_nivel(ABInt abb, int i)
{
    if (abb == NULL)
        return MIN_INT;
    if (abb->info == i)
        return 1;
    int nivel_izq = retornar_nivel(abb->izq, i);
    if (nivel_izq > 0)
        return nivel_izq + 1;
    int nivel_der = retornar_nivel(abb->der, i);
    if (nivel_der > 0)
        return nivel_der + 1;
    return 0;
}

ListaInt retornar_ruta(ABInt AB, int i)
{
    if (AB == NULL)
        return NULL;

    if (AB->info == i)
       return agregar_final (NULL, i);

    ListaInt lista_izq = retornar_ruta(AB->izq, i);
    if (lista_izq != NULL)
        return agregar_final (lista_izq, i);

    ListaInt lista_der = retornar_ruta(AB->der, i);
    if (lista_der != NULL)
        return agregar_final (lista_der, i);

    return NULL;
}

ListaInt agregar_final (ListaInt l, int elem) {
    ListaInt nuevo = new nodoListaInt;
    nuevo->info = elem;
    nuevo->sig = NULL;
    if (l == NULL)
       return nuevo;
    else {
        ListaInt aux = l;
        while (aux->sig != NULL)
            aux = aux->sig;
        aux->sig = nuevo;
    }
    return nuevo;
}