#include <iostream>
using namespace std;

// Práctico de Listas

struct nodoListaInt
{
    int info;
    nodoListaInt *sig;
};

typedef nodoListaInt *ListaInt;

struct nodoListaChar
{
    char info;
    nodoListaChar *sig;
};

typedef nodoListaChar *ListaChar;

struct nodoListaCharChar
{
    char a;
    char b;
    nodoListaCharChar *sig;
};

typedef nodoListaCharChar *ListaCharChar;

struct nodoListaBool
{
    bool info;
    nodoListaBool *sig;
};

typedef nodoListaBool *ListaBool;

void imprimir(ListaInt L)
{
    while (L != NULL)
    {
        cout << "|" << L->info << "| - ";
        L = L->sig;
    }
    cout << "#" << endl;
}

int main()
{
    // ListaInt L1 = ejercicio_1 (NULL, 2);
    // L1 = ejercicio_1 (L1, 3);
    // L1 = ejercicio_1 (L1, 4);
    // imprimir(L1);
    // cout << endl;

    // ListaInt L2 = ejercicio_1 (NULL, 1);
    // L2 = ejercicio_1 (L2, 2);
    // L2 = ejercicio_1 (L2, 2);
    // L2 = ejercicio_1 (L2, 3);
    // L2 = ejercicio_1 (L2, 5);
    // L2 = ejercicio_1 (L2, 5);
    // L2 = ejercicio_1 (L2, 6);
    // imprimir(L2);

    // if (ejercicio_11 (L1, L2))
    //     cout << "L1 es sublista de L2" << endl;
    // else
    //     cout << "L1 NO es sublista de L2" << endl;

    return 0;
}

int minimo(ListaInt L)
{
    int min = L->info;
        while (L->sig != NULL)
    {
        if (L->info <= min)
        {
            min = L->info;
            L = L->sig;
        }
    }
}

borrar_ocurrencias(L elem){

}



void borrarMin(ListaInt &L)
{
    // if (L != NULL)
    // {
    //     int min = minimo(L);
    //     borrar_ocurrencias (L, min)
    // }

    ListaInt aux = new nodoListaInt;
    aux = L;
    int min = aux->info;

    while (aux->sig != NULL)
    {
        if (aux->info <= min)
        {
            min = aux->info;
            aux = aux->sig;
        }
    }
    aux = L;
    while (aux->sig != NULL)
    {
        if (aux->info == min)
        {
            ListaInt borrar = L;
            aux = aux->sig;
            delete borrar;
        }
    }
}