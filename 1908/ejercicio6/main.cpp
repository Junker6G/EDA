#include <iostream>
using namespace std;

struct nodoLista
{
    char info;
    nodoLista *sig;
};

struct nodoBool
{
    bool info;
    nodoBool * sig;
};


typedef nodoLista *ListaChar;
typedef nodoBool *ListaBool;


void imprimirlista(ListaChar);
void noFalse(ListaBool & L);


int main()
{
    ListaChar L1 = NULL;

}

void noFalse(ListaBool & L){
    ListaBool aux = L;
    if (L != NULL)
    {
        if (L->info == false)
        {
            aux = L->sig;
            delete L;
            L = aux;
            noFalse(L);
        }else{
            noFalse(L->sig);
        }
           
    }
}

void imprimirlista(ListaBool L)
{
    cout << "Impresion de lista" << endl;
    while (L != NULL)
    {
        cout << " | " << L->info << " | - ";
        L = L->sig;
    }
    cout << "FIN" << endl;
}