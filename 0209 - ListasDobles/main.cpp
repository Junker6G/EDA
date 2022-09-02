#include <iostream>
using namespace std;

struct nodoDobleInt
{
    int info;
    nodoDobleInt *sig;
    nodoDobleInt *ant;
};

typedef nodoDobleInt *ListaDobleInt;

void cons(ListaDobleInt &L, int n);
void imprimir(ListaDobleInt L);
void snoc(ListaDobleInt L, int n);
bool boolIguales(ListaDobleInt L1, ListaDobleInt L2);
int maximo(ListaDobleInt L);
bool balaceado(ListaDobleInt L);

int main()
{

    return 0;
}

void imprimir(ListaDobleInt L)
{
    while (L != NULL)
    {
        cout << "##############" << endl;
        cout << "info: " << L->info << endl;
        cout << "sig: " << L->sig << endl;
        cout << "ant: " << L->ant << endl;
        cout << "##############" << endl;
        L = L->sig;
    }
}

// Pre-condicion: L apunta al comienzo de la izquierda
void cons(ListaDobleInt &L, int n)
{
    ListaDobleInt nodo = new nodoDobleInt;
    nodo->info = n;
    nodo->sig = L;
    nodo->ant = NULL;
    if (L == NULL)
    {
        L = nodo;
    }
    else
    {
        L->ant = nodo;
    }
}

void snoc(ListaDobleInt L, int n)
{
    while (L != NULL && L->sig != NULL)
        L = L->sig;
    ListaDobleInt nodo = new nodoDobleInt;
    nodo->info = n;
    nodo->sig = NULL;
    nodo->ant = L;
    if (L == NULL)
    {
        L = nodo;
    }
    else
    {
        L->sig = nodo;
    }
}

// VER SI DOS LISTAS SON IGUALES (ITERATIVOS)
bool boolIguales(ListaDobleInt L1, ListaDobleInt L2)
{
}

// DEVOLVER ELEMENTO INT MAXIMO ASUMIENDO DE QUE NO ES VACIA
int maximo(ListaDobleInt L)
{
    int paElante, paTra = L->info;
    while (L->sig != NULL)
    {
        L = L->sig;
        if (L->info > paElante)
            paElante = L->info;
    }

    while (L->ant != NULL)
    {
        L = L->ant;
        if (L->info > paTra)
            paTra = L->info;
    }

    if (paElante > paTra)
    {
        cout << "El mayor valor de la lista es -->  " << paElante << endl;
        return paElante;
    }
    else
    {
        cout << "El mayor valor de la lista es -->  " << paTra << endl;
        return paTra;
    }
}

// BOOL BALACEADA
bool balanceado(ListaDobleInt L)
{
    int cont = 0;
    ListaDobleInt aux = L;

    while (cont != -1 && cont != 2)
    {
        if (L->sig != NULL)
        {
            cont++;
            L = L->sig;
        }
        if (aux->ant != NULL)
        {
            cont--;
            aux = aux->ant;
        }
    }
}