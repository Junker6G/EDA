#include <iostream>
using namespace std;

struct nodoListaInt
{
    int info;
    nodoListaInt *sig;
};

typedef nodoListaInt *ListaInt;

void imprimir(ListaInt &L)
{
    while (L != NULL)
    {
        cout << L->info << "---";
        L = L->sig;
    }
    cout << "Se acabo la lista" << endl;
}

int main()
{

    ListaInt L1 = NULL;
    ListaInt aux;

    for (size_t i = 10; i > 0; i--)
    {
        ListaInt aux = new nodoListaInt;
        aux->info = i;
        aux->sig = L1;
        L1 = aux;
    }

    imprimir(L1);
}