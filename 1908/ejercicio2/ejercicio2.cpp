// Defina una función "recursiva" que dada una lista l de
// enteros retorne una nueva lista que contenga todos los
// elementos positivos de l, en el mismo orden

#include <iostream>
using namespace std;

struct nodoLista
{
    int info;
    nodoLista *sig;
};

typedef nodoLista *ListaInt;

void imprimirlista(ListaInt);
ListaInt retornarPositivos(int elem, ListaInt L);
ListaInt retornarPositivos3(int elem, ListaInt L);
ListaInt sumarFinal(int elem, ListaInt &L);
ListaInt positivos(ListaInt L);


int main()
{
    ListaInt L1 = NULL;

    sumarFinal(5, L1);
    sumarFinal(3, L1);
    sumarFinal(-1, L1);
    sumarFinal(55, L1);
    sumarFinal(-2, L1);
    sumarFinal(-6, L1);
    sumarFinal(-8, L1);
    sumarFinal(12, L1);

    imprimirlista(L1);

    positivos(L1);

    imprimirlista(L1);
}

ListaInt positivos(ListaInt L)
{
    if (L == NULL)
        return NULL;

    if (L->info < 0)
        return positivos(L->sig);

    if (L->info >= 0)
    {
        ListaInt nuevo = new nodoLista;
        nuevo->info = L->info;
        nuevo->sig = positivos(L->sig);
        return nuevo;
    }
}

ListaInt sumarFinal(int elem, ListaInt &L)
{
    ListaInt nuevo = new nodoLista;
    nuevo->info = elem;
    nuevo->sig = NULL;
    if (L == NULL)
        L = nuevo;

    else
    {
        ListaInt aux = L;
        while (aux->sig != NULL)
        {
            aux = aux->sig;
        }
        aux->sig = nuevo;
    }
}

ListaInt retornarPositivos(int elem, ListaInt L)
{
    ListaInt nuevo = new nodoLista;
    nuevo->info = elem;
    if (L == NULL || L->info > 0)
    {
        nuevo->sig = L;
        return nuevo;
    }
    else
    {
        ListaInt aux = L;
        while (aux->sig != NULL && aux->sig->info >= 0)
        {
            aux = aux->sig;
        }
        nuevo->sig = aux->sig;
        aux->sig = nuevo;
        return L;
    }
}

ListaInt retornarPositivos3(int elem, ListaInt L)
{
    if (L == NULL)
    {
        return L;
    }
    else
    {
        if (L->info > 0)
        {
            ListaInt nuevo = new nodoLista;
            nuevo->info = elem;
            ListaInt aux = L;
            aux = L;
            L = nuevo;
        }
        else
        {
            retornarPositivos3(elem, L->sig);
        }
    }
}

void imprimirlista(ListaInt L)
{
    cout << "Impresion de lista" << endl;
    while (L != NULL)
    {
        cout << " | " << L->info << " | - ";
        L = L->sig;
    }
    cout << "FIN" << endl;
}
