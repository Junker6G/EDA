#include <iostream>
using namespace std;

struct nodoDobleInt {
    int info;
    nodoDobleInt * sig;
    nodoDobleInt * ant;
};

typedef nodoDobleInt * ListaDobleInt;

void agregarComienzo (ListaDobleInt & L, int elem) {
    ListaDobleInt nuevo = new nodoDobleInt;
    nuevo->info = elem;
    nuevo->ant = NULL;
    nuevo->sig = L;
    if (L != NULL)
        L->ant = nuevo;
    L = nuevo;
}

void agregarFinal (ListaDobleInt & L, int elem) {
    ListaDobleInt nuevo = new nodoDobleInt;
    nuevo->info = elem;
    nuevo->sig = NULL;
    if (L == NULL) {
        nuevo->ant = NULL;
        L = nuevo;
    }
    else {
        while (L->sig != NULL)
            L = L->sig;
        nuevo->ant = L;
        L->sig = nuevo;
    }
}

void imprimir (ListaDobleInt L) {
    if (L == NULL)
        return;
    ListaDobleInt aux = L;
    while (L->ant != NULL)
        L = L->ant;
    while (L != NULL) {
        if (aux == L)
            cout << "|" << L->info << "| = ";
        else 
            cout << L->info << " = ";
        L = L->sig;
    }
    cout << endl;
}

// Devuelve true si las listas tienen los mismos elementos y en el mismo orden
bool iguales (ListaDobleInt L1, ListaDobleInt L2) {
    while (L1 != NULL && L1->ant != NULL)
        L1 = L1->ant;
    while (L2 != NULL && L2->ant != NULL)
        L2 = L2->ant;
    // ESTOY EN EL COMIENZO DE AMBAS
    while (L1 != NULL && L2 != NULL && (L1->info == L2->info)) {
        L1 = L1->sig;
        L2 = L2->sig;
    }
    return (L1 == NULL && L2 == NULL);
}

void adelantar (ListaDobleInt & L, int cant) {
    while (L != NULL && L->sig != NULL && cant-- > 0)
        L = L->sig;
}

void atrasar (ListaDobleInt & L, int cant) {
    while (L != NULL && L->ant != NULL && cant-- > 0)
        L = L->ant;
}

// Devuelve el elemento máximo de la lista
// Pre-Condición: L no está vacía
int maximo (ListaDobleInt L) {
    int max = L->info;
    ListaDobleInt der, izq;
    izq = der = L;
    while (der->sig != NULL) {
        der = der->sig;
        if (der->info > max)
            max = der->info;
    }
    while (izq->ant != NULL) {
        izq = izq->ant;
        if (izq->info > max)
            max = izq->info;
    }
    return max;
}

// Devuelve el elemento máximo de la lista
// Pre-Condición: L no está vacía
int maximo_optimizado (ListaDobleInt L) {
    int max = L->info;
    ListaDobleInt der, izq;
    izq = der = L;
    while (der->sig != NULL || izq->ant != NULL) {
        if (der->sig != NULL) {
            der = der->sig;
            if (der->info > max)
                max = der->info;
        }
        if (izq->ant != NULL) {
            izq = izq->ant;
            if (izq->info > max)
                max = izq->info;
        }
    }
    return max;
}

// Devuelve si la lista tiene como mucho 1 elemento de diferencia entre la derecha y la izquierda
bool balanceada (ListaDobleInt L) {
    int cont = 0;
    ListaDobleInt izq, der;
    izq = der = L;
    while (izq != NULL || der != NULL) {
        if (cont > 1 || cont < -1)
            return false;
        if (der != NULL) {
            cont++;
            der = der->sig;
        }
        if (izq != NULL) {
            cont--;
            izq = izq->ant;
        }
    }
    return (cont == -1 || cont == 0 || cont == 1);
}

void agregar_balanceado (ListaDobleInt & L, int elem) {
    ListaDobleInt nuevo = new nodoDobleInt;
    nuevo->info = elem;
    if (L == NULL) {
        nuevo->sig = nuevo->ant = NULL;
        L = nuevo;
    }
    else {
        ListaDobleInt der = L->sig;
        ListaDobleInt izq = L->ant;
        while (der != NULL & izq != NULL) {
            der = der->sig;
            izq = izq->ant;
        }
        if (der == NULL) {
            nuevo->sig = L->sig;
            nuevo->ant = L;
            L->sig = nuevo;
            if (nuevo->sig != NULL)
                nuevo->sig->ant = nuevo;
        }
        else {
            nuevo->sig = L;
            nuevo->ant = L->ant;
            L->ant = nuevo;
            if (nuevo->ant != NULL)
                nuevo->ant->sig = nuevo;
        }
    }
}

int main () {
    ListaDobleInt L2 = NULL;
    agregarFinal(L2, 1);
    agregarFinal(L2, 9);
    agregarFinal(L2, 3);
    agregarFinal(L2, 5);
    agregarFinal(L2, 6);
    agregarFinal(L2, 11);
    agregarFinal(L2, 8);
    agregarFinal(L2, 4);
    atrasar(L2, 3);
    imprimir(L2);
    cout << "El maximo es: " << maximo_optimizado(L2) << endl;

    return 0;
}