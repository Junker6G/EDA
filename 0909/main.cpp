#include <iostream>
using namespace std;


struct nodoABChar {
    char info;
    nodoABChar * izq;
    nodoABChar * der;
};

typedef nodoABChar * ABChar;

struct nodoListaChar {
    char info;
    nodoListaChar * sig;
};

typedef nodoListaChar * ListaChar;

ListaChar cons (ListaChar L, char e);
ListaChar merge (ListaChar L1, ListaChar L2);

int main()
{
    return 0;
}

ListaChar cons (ListaChar L, char e) {
    ListaChar nuevo = new nodoListaChar;
    nuevo->info = e;
    nuevo->sig = L;
    return nuevo;
}

ListaChar merge (ListaChar L1, ListaChar L2) {
    ListaChar aux = L1;
    while (aux != NULL && aux->sig)
        aux = aux->sig;
    if (aux == NULL)
        return L2;
    aux->sig = L2;
    return L1;
}
