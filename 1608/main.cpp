#include <iostream>
using namespace std;

// Ejemplo de lista

struct nodoListaInt
{
    int info;
    nodoListaInt *sig;
};

typedef nodoListaInt *ListaInt;

void imprimir(ListaInt & L)
{
    while (L != NULL)
    {
        cout << L->info << endl;
        L = L->sig;
    }
}

int main()
{
    // Inicializamos L1
    ListaInt L1 = new nodoListaInt;
    L1->info = 1;
    L1->sig = NULL;
    // Inicializamos L2
    ListaInt L2 = new nodoListaInt;
    L2->info = 7;

    imprimir(L1);
    if (L1 == NULL)
    {
        cout << "La lista esta vacia" << endl;
    }
    else
    {
        cout << "La lista NO esta vacia" << endl;
    }
}