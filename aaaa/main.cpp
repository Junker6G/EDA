#include <iostream>

using namespace std;

struct nodoPila {
    int info;
    nodoPila * sig;
};

struct nodoCola {
    int info;
    nodoPila * sig;
};

// FILOSOFÍA --> L I F O --> LAST IN FIRST OUT

typedef nodoPila * Pila;
typedef nodoPila * Cola;


/*** ESPECIFICACIÓN ***/

// CREAR Y DEVOLVER UNA NUEVA PILA
Pila crear ();

//AGREGAR AL COMIENZO DE LA PILA
void agregar (Pila &, int);

// DEVOLVER PRÓXIMO ELEMENTO
// PRE-CONDICIÓN: !es_vacia (p), siendo p la Pila pasada por parámetro
int sacar (Pila &);

//DEVOLVER SI UNA PILA ES VACÍA O NO
bool es_vacia (Pila);

//DESTRUIR UNA PILA
void destruir (Pila &);

bool mismosElementos (Pila &p, Cola &c);

int main () {
    Pila nueva = crear ();
    agregar (nueva, 1);
    agregar (nueva, 2);
    agregar (nueva, 3);
    agregar (nueva, 4);
    
    while (!es_vacia(nueva))
        cout << sacar (nueva) << endl;

    destruir (nueva);

    if (es_vacia(nueva))
        cout << "Se ha borrado con exito..." << endl;
    else 
        cout << "La pila no es vacía... algo anda mal..." << endl;

}

Pila crear () {
    return NULL;
}

void agregar (Pila & p, int elem) {
    Pila nodo = new nodoPila;
    nodo->info = elem;
    nodo->sig = p;
    p = nodo;
}

int sacar (Pila & p) {
    int val = p->info;
    Pila borrar = p;
    p = p->sig;
    delete borrar;
    return val;
}

bool es_vacia (Pila p) {
    return (p == NULL);
}

void destruir (Pila & p) {
    if (p != NULL) {
        destruir (p->sig);
        delete p;
        p = NULL;
    }
}

bool mismosElementos (Pila &p, Cola &c){
    Pila copia = crear();
}