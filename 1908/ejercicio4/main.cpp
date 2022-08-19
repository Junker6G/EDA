#include <iostream>
using namespace std;

struct nodoLista
{
    char info;
    nodoLista *sig;
};

typedef nodoLista *ListaChar;

void imprimirlista(ListaChar);
void agregarE(int e, ListaChar L);

int main()
{
    ListaChar L1 = NULL;

    imprimirlista(L1);
}

void agregarE(int e, ListaChar L){
    ListaChar nuevo = new nodoLista;
    if (L == NULL)
    {
        nuevo->info = e;
        nuevo->sig = NULL;
        L = nuevo;
    }else
    agregarE(e, L->sig); 
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