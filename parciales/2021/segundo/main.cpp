#include <iostream>
using namespace std;

struct nodoAB
{
    int info;
    nodoAB *izq, *der;
};
typedef nodoAB *AB;

AB cortarArbol(AB &a, int x);

int main()
{

    return 0;
}

AB cortarArbol(AB &a, int x)
{
    if (a == NULL)
    {
        return NULL;
    }
    if (a->info == x)
    {
        AB res = a;
        a = NULL;
        return res;
    }
    else
    {
        cortarArbol(a->der, x);
        cortarArbol(a->izq, x);
    }
    return NULL;
}