// Problemas con Celda Dummy
#include <iostream>
using namespace std;

struct nodoListaInt {
    int info;
    nodoListaInt * sig;
};

typedef nodoListaInt * ListaInt;

void imprimir(ListaInt L) {
    cout << "|X| - ";
    while (L->sig != NULL) {
        L = L->sig;
        cout << "|" << L->info << "| - ";
    }
    cout << "#" << endl;
}

void insertar_comienzo (ListaInt L, int elem) {
    ListaInt nuevo = new nodoListaInt;
    nuevo->info = elem;
    nuevo->sig = L->sig;
    L->sig = nuevo;
}

void insertar_final (ListaInt L, int elem) {
    ListaInt nuevo = new nodoListaInt;
    nuevo->info = elem;
    nuevo->sig = NULL;
    while (L->sig != NULL)
        L = L->sig;
    L->sig = nuevo;
}

int largo (ListaInt L) {
    int cant = 0;
    while (L->sig != NULL) {
        cant++;
        L = L->sig;
    }
    return cant;
}

// Pre-Condición: L está ordenada de menor a mayor
void insertar_ordenado (ListaInt L, int elem) {
    ListaInt nuevo = new nodoListaInt;
    nuevo->info = elem;
    while (L->sig != NULL && L->sig->info < elem)
        L = L->sig;
    nuevo->sig = L->sig;
    L->sig = nuevo;
}

// Pre-Condición: L está ordenada de menor a mayor
void eliminar_elemento (ListaInt L, int elem) {
    while (L->sig != NULL && L->sig->info != elem)
        L = L->sig;
    if (L->sig != NULL) {
        ListaInt borrar = L->sig;
        L->sig = borrar->sig;
        delete borrar;
    }
}

// Pre-Condición: L1 y L2 están ordenadas de menor a mayor y no tienen elementos repetidos
ListaInt unir (ListaInt L1, ListaInt L2) {
    ListaInt res = new nodoListaInt;
    ListaInt aux = res;
    while (L1->sig != NULL || L2->sig != NULL) {
        aux->sig = new nodoListaInt;
        aux = aux->sig;
        if (L2->sig == NULL || (L1->sig != NULL && L1->sig->info < L2->sig->info)) {
            aux->info = L1->sig->info;
            L1 = L1->sig;
            continue;
        }
        if (L1->sig == NULL || (L1->sig->info > L2->sig->info)) {
            aux->info = L2->sig->info;
            L2 = L2->sig;
            continue;
        }
        // tiene la misma información
        aux->info = L1->sig->info;
        L1 = L1->sig;
        L2 = L2->sig;
    }
    aux->sig = NULL;
    return res;
}

ListaInt intersectar (ListaInt L1, ListaInt L2) {
    ListaInt res = new nodoListaInt;
    ListaInt aux = res;
    L1 = L1->sig;
    L2 = L2->sig;
    while (L1 != NULL && L2 != NULL) {
        if (L1->info == L2->info) {
            aux->sig = new nodoListaInt;
            aux = aux->sig;
            aux->info = L2->info;
            L2 = L2->sig;
            L1 = L1->sig;
            continue;
        }
        if (L1->info < L2->info) {
            L1 = L1->sig;
            continue;
        }
        L2 = L2->sig;
    }
    aux->sig = NULL;
    return res;
}

void test () {
    ListaInt L = new nodoListaInt;
    L->sig = NULL;
    insertar_comienzo (L, 10);
    insertar_comienzo (L, 8);
    insertar_comienzo (L, 6);
    insertar_comienzo (L, 4);
    insertar_comienzo (L, 2);
    imprimir(L);

    cout << endl << endl;

    ListaInt L2 = new nodoListaInt;
    L2->sig = NULL;
    insertar_comienzo (L2, 9);
    insertar_comienzo (L2, 7);
    insertar_comienzo (L2, 5);
    insertar_comienzo (L2, 3);
    insertar_comienzo (L2, 1);
    imprimir(L2);

    cout << endl << endl;
    
    ListaInt L3 = intersectar (L, L2);
    imprimir(L3);

}

int main () {
    ListaInt L = new nodoListaInt;
    L->sig = NULL;
    insertar_comienzo (L, 7);
    insertar_comienzo (L, 6);
    insertar_comienzo (L, 4);
    insertar_comienzo (L, 3);
    insertar_comienzo (L, 2);
    insertar_final (L, 8);
    insertar_final (L, 9);
    insertar_final (L, 10);
    insertar_ordenado (L, 1);
    insertar_ordenado (L, 5);
    imprimir(L);
    eliminar_elemento(L, 1);
    eliminar_elemento(L, 5);
    eliminar_elemento(L, 10);
    imprimir(L);

    return 0;
}