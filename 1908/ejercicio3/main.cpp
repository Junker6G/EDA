#include <iostream>
using namespace std;

struct nodoLista
{
    char info;
    nodoLista *sig;
};

typedef nodoLista *ListaChar;

void imprimirlista(ListaChar);
void eliminarN(ListaChar & L, int n);

int main()
{
    ListaChar L1 = NULL;

    imprimirlista(L1);
}

void eliminarN(ListaChar & L, int n){
    ListaChar borrar;
    while (L != NULL && n > 0)
    {
        borrar = L;
        L = L->sig;
        delete borrar;
        n--;
    }
    
}

void imprimirlista(ListaChar L)
{
    cout << "Impresion de lista" << endl;
    while (L != NULL)
    {
        cout << " | " << L->info << " | - ";
        L = L->sig;
    }
    cout << "FIN" << endl;
}