#include <iostream>
using namespace std;

// Práctico de Listas

struct nodoListaInt
{
    int info;
    nodoListaInt *sig;
};

typedef nodoListaInt *ListaInt;

struct nodoListaChar
{
    char info;
    nodoListaChar *sig;
};

typedef nodoListaChar *ListaChar;

struct nodoListaCharChar
{
    char a;
    char b;
    nodoListaCharChar *sig;
};

typedef nodoListaCharChar *ListaCharChar;

struct nodoListaBool
{
    bool info;
    nodoListaBool *sig;
};

typedef nodoListaBool *ListaBool;

void imprimir(ListaInt L)
{
    while (L != NULL)
    {
        cout << "|" << L->info << "| - ";
        L = L->sig;
    }
    cout << "#" << endl;
}

ListaInt ejercicio_1(ListaInt L, int elem)
{
    ListaInt nuevo = new nodoListaInt;
    nuevo->info = elem;
    if (L == NULL || L->info > elem)
    {
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

ListaInt ejercicio_2(ListaInt l)
{
    if (l == NULL)
        return NULL;
    if (l->info < 0)
        return ejercicio_2(l->sig);
    ListaInt res = new nodoListaInt;
    res->info = l->info;
    res->sig = ejercicio_2(l->sig);
    return res;
}

void ejercicio_3(ListaChar &l, int n)
{
    ListaChar borrar;
    while (l != NULL && n > 0)
    {
        borrar = l;
        l = l->sig;
        n--;
        delete borrar;
    }
}

void imprimir(ListaChar L)
{
    while (L != NULL)
    {
        cout << "|" << L->info << "| - ";
        L = L->sig;
    }
    cout << "#" << endl;
}

void agregar_final(ListaChar &l, char elem)
{
    ListaChar nuevo = new nodoListaChar;
    nuevo->info = elem;
    nuevo->sig = NULL;
    if (l == NULL)
        l = nuevo;
    else
    {
        ListaChar aux = l;
        while (aux->sig != NULL)
            aux = aux->sig;
        aux->sig = nuevo;
    }
}

ListaChar ejercicio_4(ListaChar l, char elem)
{
    ListaChar res = new nodoListaChar;
    if (l == NULL)
    {
        res->info = elem;
        res->sig = NULL;
        return res;
    }
    res->info = l->info;
    res->sig = ejercicio_4(l->sig, elem);
    return res;
}

void ejercicio_5(ListaCharChar &l)
{
    if (l != NULL)
    {
        ListaCharChar borrar;
        if (l->a == l->b)
        {
            borrar = l;
            l = l->sig;
            delete borrar;
        }
        else
        {
            ListaCharChar aux = l;
            while (aux->sig != NULL && aux->sig->a != aux->sig->b)
                aux = aux->sig;
            if (aux->sig != NULL)
            {
                borrar = aux->sig;
                aux->sig = borrar->sig;
                delete borrar;
            }
        }
    }
}

void ejercicio_6(ListaBool &L)
{
    if (L != NULL)
    {
        if (L->info == true)
            ejercicio_6(L->sig);
        else
        {
            ListaBool borrar = L;
            L = L->sig;
            delete borrar;
            ejercicio_6(L);
        }
    }
}

void ejercicio_7(ListaInt &L1, int x, ListaInt L2)
{
    ListaInt nuevo = new nodoListaInt;
    nuevo->info = x;
    nuevo->sig = L2;
    if (L1 == NULL)
        L1 = nuevo;
    else
    {
        ListaInt aux = L1;
        while (aux->sig != NULL)
            aux = aux->sig;
        aux->sig = nuevo;
    }
}

void ejercicio_7_recursivo(ListaInt &L1, int x, ListaInt L2)
{
    if (L1 == NULL)
    {
        ListaInt nuevo = new nodoListaInt;
        nuevo->info = x;
        nuevo->sig = L2;
        L1 = nuevo;
    }
    else
        ejercicio_7_recursivo(L1->sig, x, L2);
}

int main()
{
    ListaChar L1 = NULL;
    agregar_final(L1, 'a');
    agregar_final(L1, 'b');
    agregar_final(L1, 'c');
    agregar_final(L1, 'd');
    agregar_final(L1, 'e');
    ListaChar L2 = ejercicio_4(L1, 'f');
    ejercicio_3(L1, 6);
    cout << "La lista de caracteres L1 es: " << endl;
    imprimir(L1);
    cout << "La lista de caracteres L2 es: " << endl;
    imprimir(L2);
    return 0;
}

void ejercicio9(ListaInt L1, ListaInt L2)
{
    if (L1 == NULL && L2 == NULL)
    {
        return NULL;
    }

    if (L1 != NULL && L2 == NULL)
    {
        ListaInt nuevo = new nodoListaInt;
        nuevo->info = L1->info;
        nuevo->sig = ejercicio9(L1->sig, L2) return nuevo;
    }

    if (L1 == NULL && L2 != NULL)
    {
        ListaInt nuevo = new nodoListaInt;
        nuevo->info = L2->info;
        nuevo->sig = ejercicio9(L1, L2->sig) return nuevo;
    }

    if (L1 != NULL && L2 != NULL)
    {
        if (L1->info < L2->info)
        {
            ListaInt nuevo = new nodoListaInt;
            nuevo->info = L1->info;
            nuevo->sig = ejercicio9(L1->sig, L2) 
        }
        else
        {
            if (L1->info == L2->info)
            {
                ListaInt nuevo = new nodoListaInt;
                nuevo->info = L1->info;
                nuevo->sig->info = L2->info;
                ejercicio9(L1->sig, L2->sig)
            }
            
            ListaInt nuevo = new nodoListaInt;
            nuevo->info = L1->info;
            nuevo->sig = merge(L1, L2->sig);
        }
    }
    return nuevo;
}