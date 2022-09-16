#include <iostream>
using namespace std;

// Práctico de Listas

struct nodoListaInt {
    int info;
    nodoListaInt * sig;
};

typedef nodoListaInt * ListaInt;

struct nodoListaChar {
    char info;
    nodoListaChar * sig;
};

typedef nodoListaChar * ListaChar;

struct nodoListaCharChar {
    char a;
    char b;
    nodoListaCharChar * sig;
};

typedef nodoListaCharChar * ListaCharChar;

struct nodoListaBool {
    bool info;
    nodoListaBool * sig;
};

typedef nodoListaBool * ListaBool;

struct nodoListaOcurrencias {
    int elem;
    unsigned ocurrencias;
    nodoListaOcurrencias * sig;
};

typedef nodoListaOcurrencias * ListaOcurrencias;


void imprimir(ListaInt L) {
    while (L != NULL) {
        cout << "|" << L->info << "| - ";
        L = L->sig;
    }
    cout << "#" << endl;
}

void imprimir(ListaOcurrencias L) {
    while (L != NULL) {
        cout << "(" << L->elem << "," << L->ocurrencias << ") - ";
        L = L->sig;
    }
    cout << "#" << endl;
}

void agregar_comienzo (ListaInt & L, int elem) {
    ListaInt nuevo = new nodoListaInt;
    nuevo->info = elem;
    nuevo->sig = L;
    L = nuevo;
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

ListaInt ejercicio_2 (ListaInt l) {
    if (l == NULL)  
        return NULL;
    if (l->info < 0)
        return ejercicio_2 (l->sig);
    ListaInt res = new nodoListaInt;
    res->info = l->info;
    res->sig = ejercicio_2 (l->sig);
    return res;
}

void ejercicio_3 (ListaChar & l, int n) {
    ListaChar borrar;
    while (l != NULL && n > 0) {
        borrar = l;
        l = l->sig;
        n--;
        delete borrar;
    }
}

void imprimir(ListaChar L) {
    while (L != NULL) {
        cout << "|" << L->info << "| - ";
        L = L->sig;
    }
    cout << "#" << endl;
}

void agregar_final (ListaChar & l, char elem) {
    ListaChar nuevo = new nodoListaChar;
    nuevo->info = elem;
    nuevo->sig = NULL;
    if (l == NULL)
        l = nuevo;
    else {
        ListaChar aux = l;
        while (aux->sig != NULL)
            aux = aux->sig;
        aux->sig = nuevo;
    }
}

ListaChar ejercicio_4 (ListaChar l, char elem) {
    ListaChar res = new nodoListaChar;
    if (l == NULL) {
        res->info = elem;
        res->sig = NULL;
        return res;
    }
    res->info = l->info;
    res->sig = ejercicio_4(l->sig, elem);
    return res;
}

void ejercicio_5 (ListaCharChar & l) {
    if (l != NULL) {
        ListaCharChar borrar;
        if (l->a == l->b) {
            borrar = l;
            l = l->sig;
            delete borrar;
        }
        else {
            ListaCharChar aux = l;
            while (aux->sig != NULL && aux->sig->a != aux->sig->b)
                aux = aux->sig;
            if (aux->sig != NULL) {
                borrar = aux->sig;
                aux->sig = borrar->sig;
                delete borrar;
            }
        }
    }
}

void ejercicio_6 (ListaBool & L) {
    if (L == NULL)
        return;
    if (L->info == true)
        ejercicio_6 (L->sig);
    else {
        ListaBool borrar = L;
        L = L->sig;
        delete borrar;
        ejercicio_6 (L);    
    }
}

void ejercicio_7 (ListaInt & L1, int x, ListaInt L2) {
    ListaInt nuevo = new nodoListaInt;
    nuevo->info = x;
    nuevo->sig = L2;
    if (L1 == NULL)
        L1 = nuevo;
    else {
        ListaInt aux = L1;
        while (aux->sig != NULL)
            aux = aux->sig;
        aux->sig = nuevo;
    }
}

void ejercicio_7_recursivo (ListaInt & L1, int x, ListaInt L2) {
    if (L1 == NULL) {
        L1 = new nodoListaInt;
        L1->info = x;
        L1->sig = L2;
    }
    else 
        ejercicio_7_recursivo(L1->sig, x,L2);
}

ListaInt ejercicio_9_iterativo (ListaInt L1, ListaInt L2) {
    if (L1 == NULL && L2 == NULL)
        return NULL;
    ListaInt res, aux;
    res = new nodoListaInt;
    aux = res;
    // soluciono la cuestión del primer nodo
    if (L1 == NULL || (L2 != NULL && L2->info < L1->info)) {
        aux->info = L2->info;
        L2 = L2->sig;
    }
    else {
        if (L2 == NULL || (L1->info <= L2->info)) {
            aux->info = L1->info;
            L1 = L1->sig;
        }
    }
    // recorro el resto
    while (L1 != NULL || L2 != NULL) {    
        aux->sig = new nodoListaInt;
        aux = aux->sig;
        if (L2 == NULL || (L1 != NULL && L1->info <= L2->info)) {
            aux->info = L1->info;
            L1 = L1->sig;
        }
        else {
            aux->info = L2->info;
            L2 = L2->sig;
        }
    }
    aux->sig = NULL;
    return res;
}

ListaInt ejercicio_9_recursivo (ListaInt L1, ListaInt L2) {
    if (L1 == NULL && L2 == NULL)
        return NULL;
    ListaInt res = new nodoListaInt;
    if (L1 == NULL || (L2 != NULL && L2->info < L1->info)) {
        res->info = L2->info;
        res->sig = ejercicio_9_recursivo (L1, L2->sig);
        return res;
    }
    res->info = L1->info;
    res->sig = ejercicio_9_recursivo (L1->sig, L2);
    return res;
    
}

ListaInt ejercicio_10 (ListaInt L) {
    ListaInt res = NULL, aux;
    while (L != NULL) {
        if (res == NULL || res->info != L->info) {
            aux = new nodoListaInt;
            aux->info = L->info;
            aux->sig = res;
            res = aux; 
            L = L->sig;   
        }
        else 
            L = L->sig;
    }
    return res;
}

// L1 es sublista de L2??
bool ejercicio_11 (ListaInt L1, ListaInt L2) {
    ListaInt aux = L1;
    while (L2 != NULL && L1 != NULL) {
        if (L1->info == L2->info) {
            L1 = L1->sig;
            L2 = L2->sig;
        }
        else {
            if (L1 != aux)
                L1 = aux;
            else
                L2 = L2->sig; 
        }
    }
    return (L1 == NULL);
}

bool ejercicio_11_recursivo (ListaInt L1, ListaInt L2) {
    if (L1 == NULL)
        return true;
    if (L2 == NULL)
        return false;
    bool misterio = false;
    if (L1->info == L2->info)
        misterio = ejercicio_11_recursivo (L1->sig, L2->sig);
    return (misterio || ejercicio_11_recursivo (L1, L2->sig));
}

// Pre-Condición: L no vacía
int minimo (ListaInt L) {
    int min = L->info;
    while (L->sig != NULL) {
        L = L->sig;
        if (L->info < min)
            min = L->info;
    }
    return min;
}

void borrar_ocurrencias (ListaInt & L, int elem) {
    if (L != NULL) {
        if (L->info == elem) {
            ListaInt borrar = L;
            L = L->sig;
            delete borrar;
            borrar_ocurrencias (L, elem);
        }
        else 
            borrar_ocurrencias (L->sig, elem);
    }
}

void ejercicio_12 (ListaInt & L) {
    if (L != NULL) {
        int min = minimo (L);
        borrar_ocurrencias (L, min);
    }
}

void borrarMinimo (ListaInt & L) {
    if (L != NULL) {
        ListaInt aux = L, borrar;
        int min = aux->info;
        aux = aux->sig;
        while (aux != NULL) {
            if (aux->info < min)
                min = aux->info;
            aux = aux->sig;
        }
        while (L != NULL && L->info != min) {
            borrar = L;
            L = L->sig;
            delete borrar;
        }
        aux = L;
        while (aux->sig != NULL) {
            if (aux->sig->info == min) {
                borrar = aux->sig;
                aux->sig = borrar->sig;
                delete borrar;
            }
            else
                aux = aux->sig;
        }
    }
}


void ejercicio_13 (ListaInt & L, int elem) {
    if (L == NULL || L->info > elem) {
        ListaInt nuevo = new nodoListaInt;
        nuevo->info = elem;
        nuevo->sig = L;
        L = nuevo;
    }
    else 
        ejercicio_13 (L->sig, elem);
}

void ejercicio_13_iterativo (ListaInt & L, int elem) {
    ListaInt nuevo = new nodoListaInt;
    nuevo->info = elem;
    if (L == NULL || L->info > elem) {
        nuevo->sig = L;
        L = nuevo;
    }
    else {
        ListaInt aux = L;
        while (aux->sig != NULL && aux->sig->info < elem)
            aux = aux->sig;
        nuevo->sig = aux->sig;
        aux->sig = nuevo;
    }
}

ListaInt ejercicio_14 (ListaInt L, int k) {
    ListaInt res = NULL, aux;
    while (L != NULL && k > 0) {
        if (res == NULL) {
            res = new nodoListaInt;
            aux = res;
        }
        else {
            aux->sig = new nodoListaInt;
            aux = aux->sig;
        }
        aux->info = L->info;
        L = L->sig;
        k--;
    }
    if (res != NULL)
        aux->sig = NULL;
    return res;
}

ListaInt ejercicio_14_recursivo (ListaInt L, int k) {
    if (L == NULL || k < 1)
        return NULL;
    ListaInt res = new nodoListaInt;
    res->info = L->info;
    res->sig = ejercicio_14_recursivo (L->sig, k-1);
    return res;
}

void borrar (ListaInt & L) {
    if (L != NULL) {
        borrar (L->sig);
        delete L;
    }
}

ListaOcurrencias ejercicio_15 (ListaInt L) {
    if (L == NULL)
        return NULL;
    ListaInt copia = NULL;
    while (L != NULL) {
        ejercicio_13 (copia, L->info);
        L = L->sig;
    }
    ListaOcurrencias res = new nodoListaOcurrencias;
    ListaOcurrencias aux = res;
    res->elem = copia->info;
    res->ocurrencias = 1;
    copia = copia->sig;
    while (copia != NULL) {
        if (copia->info != aux->elem) {
            aux->sig = new nodoListaOcurrencias;
            aux = aux->sig;
            aux->elem = copia->info;
            aux->ocurrencias = 1;
        }
        else 
            aux->ocurrencias++;
        copia = copia->sig;
    }
    aux->sig = NULL;
    borrar(copia);
    return res;
}

void ejercicio_16 (ListaInt L) {
    if (L != NULL) {
        borrar_ocurrencias (L->sig, L->info);
        ejercicio_16 (L->sig);
    }
}

void ejercicio_17 (ListaChar L) {
    if (L == NULL)
        return;
    ListaChar borrar;
    while (L->sig != NULL) {
        if (L->info == L->sig->info) {
            borrar = L->sig;
            L->sig = borrar->sig;
            delete borrar;
        }
        else 
            L = L->sig;
    }
}

int main(){
    ListaInt L = NULL;
    cout << endl << endl;
    agregar_comienzo(L, 2);
    agregar_comienzo(L, 1);
    agregar_comienzo(L, 9);
    agregar_comienzo(L, 7);
    agregar_comienzo(L, 5);
    agregar_comienzo(L, 2);
    agregar_comienzo(L, 9);
    agregar_comienzo(L, 7);
    agregar_comienzo(L, 7);
    agregar_comienzo(L, 2);
    agregar_comienzo(L, 1);
    agregar_comienzo(L, 9);
    agregar_comienzo(L, 7);
    agregar_comienzo(L, 5);
    agregar_comienzo(L, 2);
    agregar_comienzo(L, 9);
    agregar_comienzo(L, 7);
    agregar_comienzo(L, 7);
    cout << "La lista antes de eliminar repetidos: " << endl;
    imprimir(L);
    cout << endl << endl;
    ejercicio_16 (L);
    cout << "La lista despues de eliminar repetidos: " << endl;
    imprimir(L);
    return 0;
}
