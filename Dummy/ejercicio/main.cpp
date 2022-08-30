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

void imprimirlista(ListaInt L)
{
    cout << "|X| - ";
    while (L->sig != NULL)
    {
        L = L->sig;
        cout << L->info << " - " << endl;
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

void eliminar(ListaInt L, int elem)
{
    ListaInt borrar;
    while (L->sig != NULL)
    {
        if (L->sig->info == elem && L->sig->info != elem)
        {
            ListaInt borrar = L->sig;
            L->sig = borrar->sig;
            delete borrar;
        }
        else
        {
            L = L->sig;
        }
    }
}

void interseccion(ListaInt L1, ListaInt L2)
{
    ListaInt nuevo = new nodoListaint;
    nuevo->sig = NULL;
}

int main()
{
    ListaInt L = new nodoListaint;
    L->sig = NULL;

    insertarAlComienzo(L, 1);

    imprimirlista(L);

    return 0;
}
