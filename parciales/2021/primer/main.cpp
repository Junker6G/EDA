#include <iostream>
using namespace std;

struct nodo_lista
{
    int info;
    nodo_lista *sig;
};
typedef nodo_lista *Lista;

struct nodo_ocurrencias
{
    int info;
    unsigned cant;
    nodo_ocurrencias *sig;
};
typedef nodo_ocurrencias *ListaOcurrencias;

// Prototipo
void imprimir(Lista L);
ListaOcurrencias crear_lista_ocurrencias(Lista L);
void eliminar_ocurrencias (ListaOcurrencias L, int elem, unsigned cant);

int main()
{
    /* code */
    return 0;
}

ListaOcurrencias crear_lista_ocurrencias(Lista L)
{
    ListaOcurrencias nuevo = new nodo_ocurrencias;
    nuevo->sig = NULL;
    ListaOcurrencias ret = nuevo;
    if (L->sig == NULL)
        return nuevo;

    L = L->sig;
    while (L != NULL)
    {
        if (nuevo->sig == NULL || nuevo->info != L->info)
        {
            nuevo->sig = new nodo_ocurrencias;
            nuevo->info = L->info;
            nuevo->cant = 1;
        }
        else
            nuevo->cant++;

        L = L->sig;
    }
    nuevo->sig = NULL;

    return ret;
}

void eliminar_ocurrencias (ListaOcurrencias L, int elem, unsigned cant){
    L = L->sig;
    if (L == NULL)
        return;
    
    while (L != NULL)
    {
        if (L->info != elem)
        {
            L = L->sig;
            continue;
        }
        if (L->cant > cant)
        {
            L->cant = L->cant - cant;
            continue;
        }
        
    }
    return
}

void imprimir(Lista L)
{
    cout << "|X| - ";
    while (L->sig != NULL)
    {
        L = L->sig;
        cout << "|" << L->info << "| - ";
    }
    cout << "#" << endl;
}