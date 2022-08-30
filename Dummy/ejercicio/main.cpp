#include <iostream>
using namespace std;

struct nodoListaint
{
    int info;
    nodoListaint *sig;
};

typedef nodoListaint *ListaInt;

void imprimirlista(ListaInt);
void insertarAlComienzo(ListaInt L, int elem);
void insertarAlFinal(ListaInt L, int elem);
void insertarOrdenado(ListaInt L, int elem);

int main()
{
    ListaInt L = new nodoListaint;
    L->sig = new nodoListaint;

    insertarAlComienzo(L, 1);

    imprimirlista(L);

    return 0;
}

void imprimir(ListaInt L)
{
    L = L->sig;
    while (L != NULL)
    {
        cout << L->info << "-" << endl;
        L = L->sig;
    }
    cout << "fin de la lista" << endl;
}

void insertarAlComienzo(ListaInt L, int elem)
{
    ListaInt nuevo = new nodoListaint;
    nuevo->info = elem;
    nuevo->sig = L->sig;
    L->sig = nuevo;
}

void insertarAlFinal(ListaInt L, int elem)
{
    ListaInt nuevo = new nodoListaint;
    nuevo->info = elem;
    nuevo->sig = NULL;
    while (L->sig != NULL)
    {
        L = L->sig;
    }
    L->sig = nuevo;
}

void insertarOrdenado(ListaInt L, int elem)
{
    ListaInt nuevo = new nodoListaint;
    nuevo->info = elem;
    while (L->sig != NULL && L->sig->info < elem)
    {
        L = L->sig;
    }

    nuevo->sig = L->sig;
    L->sig = nuevo;
}

void eliminarElemento(ListaInt L, int elem) {
    
}