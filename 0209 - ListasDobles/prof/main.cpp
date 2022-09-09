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

void imprimir_arbol (ABChar a) {
    if (a != NULL) {
        imprimir_arbol (a->izq);
        cout << "|" << a->info << "|  ";
        imprimir_arbol(a->der); 
    }
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

ABChar construir_arbol (ABChar subarbol_izq, char raiz, ABChar subarbol_der) {
    ABChar a = new nodoABChar;
    a->info = raiz;
    a->izq = subarbol_izq;
    a->der = subarbol_der;
    return a;
}

// EJERCICIO 1
ListaChar preOrden (ABChar a) {
    if (a == NULL)
        return NULL;
    return merge (cons (preOrden(a->izq), a->info), preOrden (a->der));
}

void imprimirListaChar (ListaChar L) {
    if (L == NULL)
        cout << "#" << endl;
    else {
        while (L != NULL) {
            cout << "|" << L->info << "| ";
            L = L->sig;
        }
    }
}

void imprimirNivel (ABChar a, unsigned N) {
    if (a != NULL && N > 0) {
        if (N == 1)
            cout << "   " << a->info;
        else {
            imprimirNivel (a->izq, N - 1);
            imprimirNivel (a->der, N - 1);
        }
    }
}

// EJERCICIO 4
ListaChar listaNivel (ABChar a, unsigned N) {
    if (a == NULL || N < 1)
        return NULL;
    return merge (listaNivel (a->izq, N-1), cons (listaNivel (a->der, N-1),a->info));
}


int main () {
    ABChar a1 = construir_arbol (NULL, 'b', NULL);
    ABChar a2 = construir_arbol (NULL,'c', NULL);
    ABChar a3 = construir_arbol (a1, 'a', a2);
    a1->izq = new nodoABChar;
    a1->izq->info = 'd';
    a1->izq->izq = NULL;
    a1->izq->der = NULL;
    a1->der = new nodoABChar;
    a1->der->info = 'e';
    a1->der->izq = NULL;
    a1->der->der = NULL;
    a2->izq = new nodoABChar;
    a2->izq->info = 'f';
    a2->izq->izq = NULL;
    a2->izq->der = NULL;
    a2->der = new nodoABChar;
    a2->der->info = 'g';
    a2->der->izq = NULL;
    a2->der->der = NULL;

    cout << "      ";
    imprimirNivel (a3, 1);
    cout << endl << "    ";
    imprimirNivel (a3, 2);
    cout << endl;
    imprimirNivel (a3, 3);
    cout << endl << endl;

    ListaChar L = listaNivel (a3, 5);
    imprimirListaChar (L);


    return 0;
}


