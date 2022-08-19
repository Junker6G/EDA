#include <iostream>
using namespace std;

struct nodoLista
{
    int info;
    nodoLista *sig;
};

typedef nodoLista *ListaInt;

void imprimirlista(ListaInt);
ListaInt sumarAlFinal(int elem, ListaInt &L);

int main()
{
    ListaInt L1 = NULL;

    sumarAlFinal(5, L1);
    sumarAlFinal(3, L1);
    sumarAlFinal(1, L1);
    sumarAlFinal(55, L1);
    sumarAlFinal(2, L1);
    sumarAlFinal(6, L1);
    sumarAlFinal(8, L1);
    sumarAlFinal(12, L1);

    imprimirlista(L1);
}

ListaInt sumarAlFinal(int elem, ListaInt &L)
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