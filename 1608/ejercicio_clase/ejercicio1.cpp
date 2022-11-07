
#include <iostream>
#include <iomanip>      // Utilizado para la vista de tablas.
#include <stdlib.h>
#include <string>
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

    string nombreCompletoOriginal = "Eduardo_Pelela";
    string nombreCompleto = nombreCompletoOriginal;
    string demi = "_";

    cout << nombreCompleto.find(demi) << endl; 
    cout << nombreCompleto.substr(0, nombreCompleto.find(demi)) << endl;
    cout << nombreCompleto.substr(nombreCompleto.find(demi) + 1) << endl;
    cout << nombreCompleto.erase(0, nombreCompleto.find(demi) + 1) << endl;
        // ListaInt L1 = NULL;
        // ListaInt aux;

        // for (size_t i = 10; i > 0; i--)
        // {
        //     ListaInt aux = new nodoListaInt;
        //     aux->info = i;
        //     aux->sig = L1;
        //     L1 = aux;
        // }

        // imprimir(L1);
}