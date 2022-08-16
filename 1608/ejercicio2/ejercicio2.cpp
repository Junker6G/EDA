// Defina una función "recursiva" que dada una lista l de
// enteros retorne una nueva lista que contenga todos los
// elementos positivos de l, en el mismo orden

#include <iostream>
using namespace std;

struct nodoLista
{
    int info;
    nodoLista *sig;
};

typedef nodoLista *ListaInt;

void imprimirlista(ListaInt);
ListaInt retornarPositivos(int elem, ListaInt L);

int main()
{
    ListaInt L1 = NULL;

    L1 = retornarPositivos(1, L1);
    L1 = retornarPositivos(23, L1);
    L1 = retornarPositivos(-44, L1);
    L1 = retornarPositivos(22, L1);
    L1 = retornarPositivos(5, L1);
    L1 = retornarPositivos(-12, L1);
    L1 = retornarPositivos(-42, L1);

	imprimirlista(L1);
    }

ListaInt retornarPositivos(int elem, ListaInt L){
    ListaInt nuevo = new nodoLista;
    nuevo->info = elem;
    if (L == NULL || L->info > 0)
    {
        nuevo->sig = L;
        return nuevo;
    }else
    {
        ListaInt aux = L;
        while (aux->sig != NULL && aux->sig->info >= 0)
        {
            aux = aux->sig;
        }
        nuevo->sig = aux->sig;
        aux->sig = nuevo;
        return L;
    }

}

void imprimirlista(ListaInt L){
	cout <<"Impresion de lista"<< endl;
	while (L != NULL){
		cout <<" | " << L->info << " | - ";
		L = L->sig;
	}
	cout << "#" << endl;
}
