#include <iostream>

using namespace std;

// -------- Estructuras --------
struct nodoLista{
	int info;
	nodoLista * sig;
};

typedef nodoLista * ListaInt;

// -------- Prototipo Funciones ----------------- 
void imprimirlista(ListaInt);
void Agregar_al_Comienzo(int elem, ListaInt & L);
void Agregar_al_Final_Recursivo(int elem, ListaInt & L);
void Agregar_al_Final_Iterativo(int elem, ListaInt & L);
ListaInt Agregar_Ordenado (int elem, ListaInt L);




int main (){
	
	ListaInt L1 = NULL;
//	ListaInt aux;
//	for(int i = 10; i >= 1; i-- ){
//		aux = new nodoLista;
//		aux->info = i;
//		aux->sig = L1;
//		L1 = aux;
//	}
	L1 = Agregar_Ordenado(1,L1);
	L1 = Agregar_Ordenado(4,L1);
	L1 = Agregar_Ordenado(3,L1);
	L1 = Agregar_Ordenado(2,L1);
	L1 = Agregar_Ordenado(8,L1);
	L1 = Agregar_Ordenado(12,L1);
	L1 = Agregar_Ordenado(11,L1);
	
	imprimirlista(L1);
	

}

void imprimirlista(ListaInt L){
	cout <<"Impresion de lista"<< endl;
	while (L != NULL){
		cout <<" | " << L->info << " | - ";
		L = L->sig;
	}
	cout << "#" << endl;
}

void Agregar_al_Comienzo(int elem, ListaInt & L){
	ListaInt nuevo = new nodoLista;
	nuevo->info = elem;
	nuevo->sig = L;
	L = nuevo;
}

void Agregar_al_Final_Recursivo(int elem, ListaInt & L){
	if (L == NULL){
		ListaInt nuevo = new nodoLista;
		nuevo->info = elem ;
		nuevo->sig = NULL;
		L = nuevo;
	} else {
		Agregar_al_Final_Recursivo(elem, L->sig);
	}
}

void Agregar_al_Final_Iterativo(int elem, ListaInt & L){
	ListaInt nuevo = new nodoLista;
	nuevo->info = elem ;
	nuevo->sig = NULL;
	if (L == NULL){
		L = nuevo;
	} else {
			ListaInt aux = L;
			while(aux->sig != NULL){
				aux = aux->sig;
			}
			aux->sig = nuevo;
	}
}

ListaInt Agregar_Ordenado (int elem, ListaInt L){
		ListaInt nuevo = new nodoLista;
		nuevo->info = elem ;
	if(L == NULL || L->info > elem){
		nuevo->sig = L;
		return nuevo;
	} else{
		ListaInt aux = L;
		while(aux->sig != NULL && aux->sig->info < elem){
			aux = aux->sig;
		}
		nuevo->sig= aux->sig;
		aux->sig = nuevo;
		return L;
	}
}

