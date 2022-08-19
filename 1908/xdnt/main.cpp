#include <iostream>
using namespace std;

struct nodoLista
{
    int info;
    nodoLista *sig;
};

typedef nodoLista *ListaInt;

void imprimirlista(ListaInt);
ListaInt sumarFinal(int elem, ListaInt &L);

int main()
{
    ListaInt L1 = NULL;

    sumarFinal(5, L1);
    sumarFinal(3, L1);
    sumarFinal(1, L1);
    sumarFinal(55, L1);
    sumarFinal(2, L1);
    sumarFinal(6, L1);
    sumarFinal(8, L1);
    sumarFinal(12, L1);

    imprimirlista(L1);
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