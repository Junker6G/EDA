#include <iostream>
using namespace std;

struct nodoLista
{
    int info;
    nodoLista *sig;
};

typedef nodoLista *Listaint;

void imprimirlista(Listaint);
void juntar(Listaint & L1, int x, Listaint L2);

int main()
{
    Listaint L1 = NULL;

    imprimirlista(L1);
}

void juntar(Listaint & L1, int x, Listaint L2){
    Listaint aux = L1;
    Listaint nuevo = new nodoLista;
    if (L1 != NULL)
    {
        while (aux->sig != NULL)
            aux = aux->sig;
        aux->sig = nuevo;

        nuevo->info = x;
        
        if (L2 == NULL)
        {
            nuevo->sig = NULL;   
        }
        else
        {
            nuevo->sig = L2;
        }
    }
}

void imprimirlista(Listaint L)
{
    cout << "Impresion de lista" << endl;
    while (L != NULL)
    {
        cout << " | " << L->info << " | - ";
        L = L->sig;
    }
    cout << "FIN" << endl;
}