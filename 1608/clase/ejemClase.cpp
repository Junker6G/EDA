#include <iostream>
using namespace std;

// Ejemplos de Listas

struct nodoListaInt {
    int info;
    nodoListaInt * sig;
};

typedef nodoListaInt * ListaInt;

void imprimir(ListaInt L) {
    while (L != NULL) {
        cout << L->info << endl;
        L = L->sig;
    }
}

ListaInt ejercicio_1 (ListaInt L, int elem) {
    ListaInt nuevo = new nodoListaInt;
    nuevo->info = elem;
    if (L == NULL || L->info > elem) {
        nuevo->sig = L;
        return nuevo;
    }
    ListaInt aux = L;
    while (aux->sig != NULL && aux->sig->info < elem)
        aux = aux->sig;
    nuevo->sig = aux->sig;
    aux->sig = nuevo;
    return L;
}

int main(){
    ListaInt res = NULL;
    res = ejercicio_1(res, 1);
    res = ejercicio_1(res, 4);
    res = ejercicio_1(res, 9);
    res = ejercicio_1(res, 3);
    res = ejercicio_1(res, 2);
    res = ejercicio_1(res, 5);
    imprimir(res);
    return 0;
}
