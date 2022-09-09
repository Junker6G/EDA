#include <iostream>
using namespace std;

#define MIN_INT -10000;

struct nodoABChar
{
    char info;
    nodoABChar *izq;
    nodoABChar *der;
};

typedef nodoABChar *ABChar;

struct nodoAB
{
    int info;
    nodoAB *izq;
    nodoAB *der;
};

typedef nodoAB *ABInt;

struct nodoListaChar
{
    char info;
    nodoListaChar *sig;
};

typedef nodoListaChar *ListaChar;

// PROTOTIPO
ListaChar cons(ListaChar L, char e);
ListaChar merge(ListaChar L1, ListaChar L2);
ABInt multiplicador(ABInt AB, int i);
void imprimir_arbol (ABChar a);
ABChar construir_arbol (ABInt subarbol_izq, int raiz, ABInt subarbol_der);

int main()
{
    return 0;
}

ListaChar cons(ListaChar L, char e)
{
    ListaChar nuevo = new nodoListaChar;
    nuevo->info = e;
    nuevo->sig = L;
    return nuevo;
}

ListaChar merge(ListaChar L1, ListaChar L2)
{
    ListaChar aux = L1;
    while (aux != NULL && aux->sig)
        aux = aux->sig;
    if (aux == NULL)
        return L2;
    aux->sig = L2;
    return L1;
}

ABChar construir_arbol (ABChar subarbol_izq, char raiz, ABChar subarbol_der) {
    ABChar a = new nodoABChar;
    a->info = raiz;
    a->izq = subarbol_izq;
    a->der = subarbol_der;
    return a;
}


void imprimir_arbol (ABChar a) {
    if (a != NULL) {
        imprimir_arbol (a->izq);
        cout << "|" << a->info << "|  ";
        imprimir_arbol(a->der); 
    }
}

ABInt multiplicador(ABInt AB, int i)
{
    if (AB == NULL)
        return 0;
        
    AB->info = AB->info * i;
    multiplicador(AB->izq, i);
    multiplicador(AB->der, i);

    return AB;
}

int retornar_nivel(ABInt abb, int i){
    if (abb == NULL)
    {
        return 0;
    }
    if (abb->info == i)
    {
        return 1;
    }
    retornar_nivel(abb->izq, i);
    retornar_nivel(abb->der, i);
}