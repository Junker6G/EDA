#include <iostream>
using namespace std;

struct nodoABInt
{
    int info;
    nodoABInt *der;
    nodoABInt *izq;
};

typedef nodoABInt *ABInt;

struct nodoListaInt
{
    int info;
    nodoListaInt *sig;
};

typedef nodoListaInt *ListaInt;

int main()
{

    return 0;
}

ListaInt agregarFinal(ListaInt L, int elem)
{
    ListaInt nuevo = new nodoListaInt;
    nuevo->info = elem;
    nuevo->sig = NULL;
    nuevo->info = elem;
    nuevo->sig = NULL;
    if (L == NULL)
        L = nuevo;
    else
    {
        ListaInt aux = L;
        while (aux->sig != NULL)
            aux = aux->sig;
        aux->sig = nuevo;
    }
}