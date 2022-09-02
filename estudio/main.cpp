#include <iostream>
using namespace std;

struct nodoListaInt
{
    int info;
    nodoListaInt *sig;
};

typedef nodoListaInt *ListaInt;

// Prototipo
void print(ListaInt L);
ListaInt ejercicio1(ListaInt L, int elem);

int main()
{

    return 0;
}

void print(ListaInt L)
{
    cout << "Lista -->   ";
    while (L != NULL)
    {
        cout << L->info << "---" << endl;
        L = L->sig;
    }
    cout << "#" << endl;
}

ListaInt ejercicio1(ListaInt L, int elem)
{
    ListaInt nuevo = new nodoListaInt;
    nuevo->info = elem;
    if (L == NULL || L->info > elem)
    {
        nuevo->sig = L;
        return nuevo;
    }
    ListaInt aux = new nodoListaInt;
    while (aux->sig != NULL && aux->sig->info < elem)
        aux = aux->sig;
    nuevo->sig = aux->sig;
    aux->sig = nuevo;
    return L;
}
