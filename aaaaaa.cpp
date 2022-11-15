#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <iomanip>
#include <string>
#include <thread>
#include <chrono>

#define empty -1000000

using namespace std;
using std::stoi;
using std::string;

//  --------------- ESTRUCUTRAS ---------------
struct nodoTablas;
struct nodoColumnas;
struct nodoFilas;

typedef nodoTablas *Tabla;

struct nodoColumna
{
    string nombreColumna;
    nodoColumna *sig;
    nodoColumna *ant;
    nodoFilas *filas;
    bool primary_key;
    bool nn;
    bool tipo_dato;
};
typedef nodoColumna *columna;

struct nodoFilas
{
    nodoFilas *sig;
    nodoFilas *ant;
    nodoFilas *arriba;
    nodoFilas *abajo;
    int dato_int;
    string dato_string;
};
typedef nodoFilas *filas;

struct nodoTablas
{
    nodoColumna *columna;
    string nombreTabla;
    nodoTablas *sig;
    nodoTablas *ant;
};

Tabla BD = NULL;

// -----------  VOIDS   ------------
void sub_menu();
void submenu_tablas();
void submenu_columnas();
void submenu_tuplas();
void submenu_imprimir();

//  ------------------------------ FUNCIONES TABLAS ------------------------------
void createTable(string nuevaTabla)
{
    if (BD == NULL)
    {

        Tabla insertar_t = new nodoTablas;
        insertar_t->nombreTabla = nuevaTabla;
        insertar_t->columna = NULL;
        insertar_t->sig = NULL;
        insertar_t->ant = NULL;
        BD = insertar_t;
        return;
    }
    while (BD != NULL)
    {
        Tabla insertar_t = new nodoTablas;
        insertar_t->nombreTabla = nuevaTabla;
        insertar_t->columna = NULL;
        insertar_t->ant = NULL;
        insertar_t->sig = NULL;

        if (BD->nombreTabla == nuevaTabla)
        {
            cout << "Ya existe una tabla con el nombre ingresado... " << nuevaTabla << endl;
            return;
        }
        if (BD->sig == NULL)
        {
            BD->sig = insertar_t;
            insertar_t->ant = BD;

            while (BD->ant != NULL)
            {
                BD = BD->ant;
            }
            return;
        }
        BD = BD->sig;
    }
}
void dropTable(string tablaEliminar)
{
    if (BD == NULL)
    {
        cout << "ERROR - NO HAY TABLAS EXISTENTES -" << endl;
        return;
    }
    Tabla aux = BD;
    while (aux != NULL)
    {
        if (aux->nombreTabla == tablaEliminar)
        {
            if (aux->ant == NULL)
            {
                Tabla borrar = aux;
                if (aux->sig != NULL)
                {
                    BD = aux->sig;
                    aux = aux->sig;

                    borrar->sig->ant = NULL;
                    borrar->sig = NULL;
                    delete borrar;
                    cout << "SE ELIMINO..." << tablaEliminar << "...AL INICIO" << endl;
                    return;
                }
                else
                {
                    BD = NULL;
                    delete borrar;
                    cout << "SE ELIMINO..." << tablaEliminar << "...AL INICIO" << endl;
                    return;
                }
            }
            if (aux->sig == NULL)
            {
                Tabla borrar = aux;
                aux = aux->ant;
                borrar->ant->sig = NULL;
                borrar->ant = NULL;
                delete borrar;
                cout << "SE ELIMINO..." << tablaEliminar << "...AL FINAL" << endl;
                return;
            }
            Tabla borrar = aux;
            aux = aux->sig;
            borrar->sig->ant = borrar->ant;
            borrar->ant->sig = borrar->sig;
            borrar->ant = NULL;
            borrar->sig = NULL;
            delete borrar;
            cout << "SE ELIMINO... " << tablaEliminar << endl;
            return;
        }
        aux = aux->sig;
    }
    cout << "ERROR - NO EXISTE DICHA TABLA -" << endl;
}

//  ------------------------------ FUNCIONES COLUMNA ------------------------------
void addCol(string nomTabla, string nombreCol, string tipoCol, string calificadorCol)
{
    while (BD == NULL)
    {
        cout << "ERROR - NO HAY TABLAS EXISTENTES -" << endl;
        return;
    }
    Tabla aux = BD;
    while (aux != NULL)
    {
        if (aux->nombreTabla == nomTabla)
        {
            columna aux1 = aux->columna;

            if (aux->columna == NULL)
            {
                columna nuevaColumna = new nodoColumna;
                aux->columna = nuevaColumna;
                nuevaColumna->sig = NULL;
                nuevaColumna->ant = NULL;
                nuevaColumna->filas = NULL;
                nuevaColumna->nombreColumna = nombreCol;
                nuevaColumna->primary_key = false;
                nuevaColumna->nn = false;

                if (tipoCol == "int")
                {
                    nuevaColumna->tipo_dato = true;
                }
                else
                {
                    if (tipoCol == "string")
                        nuevaColumna->tipo_dato = false;
                }
                if (calificadorCol == "primary_key")
                {
                    nuevaColumna->primary_key = true;
                }
                if (calificadorCol == "nn")
                {
                    nuevaColumna->nn = true;
                }
                if (calificadorCol == "any")
                {
                    nuevaColumna->nn = false;
                    nuevaColumna->primary_key = false;
                }
                return;
            }

            do
            {
                if (aux1->nombreColumna == nombreCol)
                {
                    cout << "Ya existe una columna en " << nombreCol << endl;
                    return;
                }
                if (aux1->primary_key == true && calificadorCol == "primary_key")
                {
                    cout << "Ya existe una columna con PRIMARY KEY" << endl;
                    return;
                }
                aux1 = aux1->sig;
            } while (aux1 != NULL);

            columna aux2 = aux->columna;
            while (aux2->sig != NULL)
            {
                aux2 = aux2->sig;
            }
            columna nuevaColumna = new nodoColumna;
            nuevaColumna->sig = NULL;
            nuevaColumna->ant = aux2;
            aux2->sig = nuevaColumna;
            nuevaColumna->filas = NULL;
            nuevaColumna->nombreColumna = nombreCol;
            nuevaColumna->primary_key = false;
            nuevaColumna->nn = false;

            while (aux2->ant != NULL)
            {
                aux2 = aux2->ant;
            }

            aux->columna = aux2;

            if (tipoCol == "int")
            {
                nuevaColumna->tipo_dato = true;
            }
            else
            {
                if (tipoCol == "string")
                    nuevaColumna->tipo_dato = false;
            }
            if (calificadorCol == "primary_key")
            {
                nuevaColumna->primary_key = true;
            }
            if (calificadorCol == "nn")
            {
                nuevaColumna->nn = true;
            }
            return;
        }
        aux = aux->sig;
    }
    cout << "No existe la tabla ingresada" << nomTabla << endl;
}

void dropCol(string tabla, string columnaEliminar)
{
    if (BD == NULL)
    {
        cout << "ERROR - NO HAY TABLAS EXISTENTES -" << endl;
        return;
    }
    Tabla aux = BD;
    while (aux != NULL)
    {
        if (aux->nombreTabla == tabla)
        {
            if (aux->columna == NULL)
            {
                cout << "No existe ninguna columna" << endl;
                return;
            }

            columna aux1 = aux->columna;
            while (aux1 != NULL)
            {
                if (aux1->nombreColumna == columnaEliminar)
                {
                    if (aux1->ant == NULL)
                    {
                        columna borrar = aux1;
                        if (aux1->sig != NULL)
                        {
                            if (aux1->filas == NULL)
                            {
                                aux1 = aux1->sig;
                                borrar->sig->ant = NULL;
                                borrar->sig = NULL;
                                delete borrar;
                                cout << "SE ELIMINO..." << columnaEliminar << "...AL INICIO" << endl;
                                return;
                            }
                            else
                            {
                                filas aux2 = aux1->filas;
                                aux1 = aux1->sig;
                                borrar->sig->ant = NULL;
                                borrar->sig = NULL;
                                while (aux2 != NULL)
                                {
                                    aux2->sig->ant = NULL;
                                    aux2->sig = NULL;
                                    aux2 = aux2->abajo;
                                }
                                delete borrar;
                                delete aux2;
                                cout << "SE ELIMINO..." << columnaEliminar << "...AL INICIO" << endl;
                                return;
                            }
                        }
                        aux->sig = NULL;
                        delete borrar;
                        cout << "SE ELIMINO..." << columnaEliminar << " " << tabla << " YA NO CONTIENE COLUMNAS" << endl;
                        return;
                    }

                    if (aux1->sig == NULL)
                    {
                        if (aux1->filas == NULL)
                        {
                            columna borrar = aux1;
                            aux1 = aux1->ant;
                            borrar->ant->sig = NULL;
                            borrar->ant = NULL;
                            delete borrar;
                            cout << "SE ELIMINO..." << columnaEliminar << "...AL FINAL" << endl;
                            return;
                        }
                        else
                        {
                            filas aux2 = aux1->filas;
                            columna borrar = aux1;
                            aux1 = aux1->ant;
                            borrar->ant->sig = NULL;
                            borrar->ant = NULL;
                            while (aux2 != NULL)
                            {
                                aux2->ant->sig = NULL;
                                aux2->ant = NULL;
                                aux2 = aux2->abajo;
                            }
                            delete borrar;
                            delete aux2;
                            cout << "SE ELIMINO..." << columnaEliminar << "...AL FINAL" << endl;
                            return;
                        }
                    }

                    if (aux1->filas == NULL)
                    {
                        columna borrar = aux1;
                        aux1 = aux1->sig;
                        borrar->sig->ant = borrar->ant;
                        borrar->ant->sig = borrar->sig;
                        borrar->ant = NULL;
                        borrar->sig = NULL;
                        delete borrar;
                        cout << "SE ELIMINO... " << columnaEliminar << endl;
                        return;
                    }
                    else
                    {
                        filas aux2 = aux1->filas;
                        columna borrar = aux1;
                        aux1 = aux1->sig;
                        borrar->sig->ant = borrar->ant;
                        borrar->ant->sig = borrar->sig;
                        borrar->ant = NULL;
                        borrar->sig = NULL;
                        while (aux2 != NULL)
                        {
                            aux2->sig->ant = aux2->ant;
                            aux2->ant->sig = aux2->sig;
                            aux2->ant = NULL;
                            aux2->sig = NULL;
                            aux2 = aux2->abajo;
                        }
                        delete borrar;
                        delete aux2;
                        cout << "SE ELIMINO... " << columnaEliminar << endl;
                        return;
                    }
                }
                aux1 = aux1->sig;
            }
            cout << "No existe la columna buscada..." << columnaEliminar << endl;
        }
        else
        {
            cout << "No existe.. " << tabla << endl;
        }
        aux = aux->sig;
    }
}

void alterCol(string tabla, string nombreCol, string tipoColNuevo, string calificadorColNuevo, string nombreColNuevo)
{
    if (BD == NULL)
    {
        cout << "ERROR - NO HAY TABLAS EXISTENTES -" << endl;
        return;
    }
    Tabla aux = BD;
    while (aux != NULL)
    {
        if (aux->nombreTabla == tabla)
        {
            if (aux->columna == NULL)
            {
                cout << "No existe ninguna columna" << endl;
                return;
            }

            columna aux1 = aux->columna;
            while (aux1 != NULL)
            {
                if (aux1->nombreColumna == nombreCol)
                {
                    columna aux2 = aux->columna;
                    do
                    {
                        if (aux2->nombreColumna == nombreColNuevo)
                        {
                            cout << "Ya existe una columna en " << nombreCol << endl;
                            return;
                        }
                        if (aux2->primary_key == true && calificadorColNuevo == "primary_key")
                        {
                            cout << "Ya existe una columna con PRIMARY KEY" << endl;
                            return;
                        }
                        aux2 = aux2->sig;
                    } while (aux2 != NULL);

                    nombreCol = nombreColNuevo;
                    cout << "Se cambio el nombre de la columna " << nombreCol << endl;

                    if (tipoColNuevo == "string" && aux1->tipo_dato == true && aux1->filas != NULL)
                    {
                        filas convertidor = aux1->filas;
                        while (convertidor != NULL)
                        {
                            stringstream ss;
                            ss << convertidor->dato_int;
                            convertidor->dato_int = NULL;
                            convertidor->dato_string = ss.str();
                            convertidor = convertidor->abajo;
                        }
                    }
                }
                aux1 = aux1->sig;
            }
            aux = aux->sig;
        }
        cout << "No existe el nombre de columna ingresado" << endl;
    }
    cout << "No existe.. " << tabla << endl;
}

//  ------------------------------ FUNCIONES TUPLAS ------------------------------
void insertInto(string nombreTabla, string columnasTupla, string valoresTupla)
{
    string limite = ":";
    int no_encontrado = 999999;

    if (columnasTupla.find(limite) > no_encontrado || columnasTupla == "")
    {
        cout << "[ " << columnasTupla << " ]"
             << "No cumple con las condiciones requeridas" << endl;
        return;
    }
    if (valoresTupla.find(limite) > no_encontrado || valoresTupla == "")
    {
        cout << "[ " << valoresTupla << " ]"
             << "No cumple con las condiciones requeridas" << endl;
        return;
    }
    string columnasTuplaCopia = columnasTupla;
    string valoresTuplaCopia = valoresTupla;
    int cant_palabrasColumna = 1;
    int cant_palabrasTupla = 1;

    while (columnasTuplaCopia.find(limite) < no_encontrado)
    {
        columnasTuplaCopia.erase(0, columnasTuplaCopia.find(limite) + 1);
        cant_palabrasColumna++;
    }

    while (valoresTuplaCopia.find(limite) < no_encontrado)
    {
        valoresTuplaCopia.erase(0, valoresTuplaCopia.find(limite) + 1);
        cant_palabrasTupla++;
    }

    if (cant_palabrasColumna != cant_palabrasTupla)
    {
        cout << "ERROR - La cantidad de palabras es distinta" << endl;
        return;
    }

    if (BD == NULL)
    {
        cout << "ERROR - NO HAY TABLAS EXISTENTES -" << endl;
        return;
    }

    Tabla existeTabla = BD;
    Tabla aux = NULL;
    columna aux1 = NULL;
    while (existeTabla != NULL)
    {
        if (existeTabla->nombreTabla == nombreTabla)
        {
            aux = existeTabla;
            if (aux->columna != NULL)
            {
                aux1 = existeTabla->columna;
            }
            else
            {
                cout << "ERROR - LA TABLA NO TIENE COLUMNAS" << endl;
                return;
            }
            break;
        }
        existeTabla = existeTabla->sig;
        if (existeTabla == NULL)
        {
            cout << "ERROR - NO EXISTE LA TABLA" << endl;
            return;
        }
    }
    columna cantidadColumnas = aux1;
    int cantidad = 0;
    while (cantidadColumnas != NULL)
    {
        cantidad++;
        cantidadColumnas = cantidadColumnas->sig;
    }
    if (cantidad != cant_palabrasColumna)
    {
        cout << "ERROR - LA CANTIDAD DE COLUMNAS DE LA TABLA Y LA CANTIDAD DE COLUMNAS INGRESADAS NO COINCIDEN" << endl;
        return;
    }

    filas nuevaFila = NULL;
    while (aux1 != NULL)
    {
        filas nuevo = new nodoFilas;
        nuevo->sig = NULL;
        nuevo->ant = NULL;
        nuevo->abajo = NULL;
        nuevo->arriba = NULL;
        nuevo->dato_int = NULL;
        nuevo->dato_string = "";
        string valor = "";
        valor = valoresTupla.substr(0, valoresTupla.find(limite));
        valoresTupla.erase(0, valoresTupla.find(limite) + 1);

        if (aux1->primary_key == true)
        {
            if (valor == "")
            {
                cout << "ERROR - EL VALOR AL INGRESAR EN LA COLUMNA PK ES VACIO, POR ENDE NO SE CREARA LA NUEVA FILA" << endl;
                return;
            }
            if (aux1->filas != NULL)
            {
                filas buscarKey = aux1->filas;
                if (aux1->tipo_dato == true)
                {
                    int aux = stoi(valor);
                    while (buscarKey != NULL)
                    {
                        if (buscarKey->dato_int == aux)
                        {
                            cout << "ERROR - YA EXISTE UNA FILA CON VALOR DE LA PK A INSERTAR" << endl;
                            return;
                        }
                        buscarKey = buscarKey->abajo;
                    }
                }
                else
                {
                    while (buscarKey != NULL)
                    {
                        if (buscarKey->dato_string == valor)
                        {
                            cout << "ERROR - YA EXISTE UNA FILA CON VALOR DE LA PK A INSERTAR" << endl;
                            return;
                        }
                        buscarKey = buscarKey->abajo;
                    }
                }
            }
        }
        if (aux1->nn == true)
        {
            if (valor == "")
            {
                cout << "ERROR - EL VALOR AL INGRESAR EN LA COLUMNA NOT NULL ES VACIO, POR ENDE NO SE CREARA LA NUEVA FILA" << endl;
                return;
            }
        }

        if (aux1->tipo_dato == true)
        {
            int nuevoValor = stoi(valor);
            nuevo->dato_int = nuevoValor;
            if (nuevaFila == NULL)
            {
                nuevaFila = nuevo;
            }
            else
            {
                nuevaFila->sig = nuevo;
                nuevo->ant = nuevaFila;
                nuevaFila = nuevaFila->sig;
            }
        }
        else
        {
            string nuevoValor = valor;
            nuevo->dato_string = nuevoValor;
            if (nuevaFila == NULL)
            {
                nuevaFila = nuevo;
            }
            else
            {
                nuevaFila->sig = nuevo;
                nuevo->ant = nuevaFila;
                nuevaFila = nuevaFila->sig;
            }
        }
        aux1 = aux1->sig;
    }
    while (nuevaFila->ant != NULL)
    {
        nuevaFila = nuevaFila->ant;
    }

    aux1 = aux->columna;
    if (aux1->filas == NULL)
    {
        while (aux1 != NULL)
        {
            aux1->filas = nuevaFila;
            aux1 = aux1->sig;
            nuevaFila = nuevaFila->sig;
        }
    }
    else
    {
        filas conectar = aux1->filas;
        while (conectar->abajo != NULL)
        {
            conectar = conectar->abajo;
        }
        while (conectar != NULL)
        {
            conectar->abajo = nuevaFila;
            nuevaFila->arriba = conectar;
            conectar = conectar->sig;
            nuevaFila = nuevaFila->sig;
        }
    }
    cout << "Se ha creaado una nueva TUPLA" << endl;
}

/*
void deleteTupla(string nombreTabla, string condicionEliminar)
{
    string valorColumna;
    string valorTupla;
    string vacio = "";
    string igual = "=";
    string mayor = ">";
    string menor = "<";
    string distinto = "<>";
    int condicion;
    int no_encontrado = 999999;

    if (condicionEliminar.find(igual) < no_encontrado)
    {
        valorColumna = condicionEliminar.substr(0, condicionEliminar.find(igual));
        valorTupla = condicionEliminar.substr(condicionEliminar.find(igual) + 1);
        condicion = 1;
    }
    else
    {
        if (condicionEliminar.find(mayor) < no_encontrado)
        {
            valorColumna = condicionEliminar.substr(0, condicionEliminar.find(mayor));
            valorTupla = condicionEliminar.substr(condicionEliminar.find(mayor) + 1);
            condicion = 2;
        }
        else
        {
            if (condicionEliminar.find(menor) < no_encontrado)
            {
                valorColumna = condicionEliminar.substr(0, condicionEliminar.find(menor));
                valorTupla = condicionEliminar.substr(condicionEliminar.find(menor) + 1);
                condicion = 3;
            }

            else
            {
                if (condicionEliminar.find(distinto) < no_encontrado)
                {
                    valorColumna = condicionEliminar.substr(0, condicionEliminar.find(distinto));
                    valorTupla = condicionEliminar.substr(condicionEliminar.find(distinto) + 1);
                    condicion = 4;
                }
                else
                {
                    if (condicionEliminar.find(vacio) < no_encontrado)
                    {
                        valorColumna = condicionEliminar.substr(0, condicionEliminar.find(vacio));
                        valorTupla = condicionEliminar.substr(condicionEliminar.find(vacio) + 1);
                        condicion = 5;
                    }
                }
            }
        }
    }

    Tabla aux = BD;
    if (aux == NULL)
    {
        cout << "No existen tablas..." << endl;
        return;
    }
    while (aux != NULL)
    {
        if (aux->nombreTabla == nombreTabla)
        {
            if (aux->columna == NULL)
            {
                cout << "No existen columnas..." << endl;
                return;
            }
            break;
        }
        aux = aux->sig;
        if (aux == NULL)
        {
            cout << "No existe la tabla..." << nombreTabla << endl;
            return;
        }
    }

    columna aux1 = aux->columna;
    while (aux1 != NULL)
    {

        if (aux1->nombreColumna == valorColumna)
        {
            cout << aux1->nombreColumna << endl;
            cout << "Existe la columna..." << aux1->nombreColumna << endl;
            if (aux1->filas == NULL)
            {
                cout << "No existen filas..." << endl;
                return;
            }
            break;
        }
        aux1 = aux1->sig;

        if (aux1 == NULL)
        {
            cout << "No existe la columna..." << valorColumna << endl;
        }
    }

    /*filas aux2 = aux1->filas;
    if (aux1->filas != NULL)
    {
        while (aux2 != NULL)
        {

            if (aux1->tipo_dato == true)
            {
                filas convertidor = aux1->filas;

                    while (convertidor != NULL)
                    {
                        stringstream ss;
                        ss << convertidor->dato_int;
                        convertidor->dato_int = NULL;
                        convertidor->dato_string = ss.str();
                        convertidor = convertidor->abajo;
                    }
                break;
            }

            else
            {
                if (aux2->dato_string == valorTupla)
                {
                    cout << "dato string" << endl;
                    cout << aux2->dato_string << endl;
                    break;
                }
            }

            if (aux1->nn == true)
            {
                if (valorTupla == "")
                {
                    cout << "El valor ingresado es vacio..." << endl;
                    return;
                }
            }

            aux2 = aux2->abajo;

            if (aux2 == NULL)
            {
                cout << "No existe la tupla ingresada..." << valorTupla << endl;
                return;
            }
        }
    }
    switch (condicion)
    {
    case 3:
        filas aux2 = aux1->filas;
        if (aux1->filas != NULL)
        {
            while (aux2 != NULL)
            {

                if (aux1->tipo_dato == true)
                {
                    filas convertidor = aux1->filas;

                    while (convertidor != NULL)
                    {
                        stringstream ss;
                        ss << convertidor->dato_int;
                        convertidor->dato_int = NULL;
                        convertidor->dato_string = ss.str();
                        convertidor = convertidor->abajo;
                    }

                    break;
                }

                else
                {
                    if (aux2->dato_string < valorTupla)
                    {
                        cout << "dato string" << endl;
                        cout << aux2->dato_string << endl;
                        break;
                    }
                }

                if (aux1->nn == true)
                {
                    if (valorTupla == "")
                    {
                        cout << "El valor ingresado es vacio..." << endl;
                        return;
                    }
                }

                aux2 = aux2->abajo;

                if (aux2 == NULL)
                {
                    cout << "No existe la tupla ingresada..." << valorTupla << endl;
                    return;
                }
            }
        }
        // aux2 = aux2->sig;

        columna desconectar = aux->columna;
        filas borrar = aux2;
        if (aux2->abajo == NULL)
        {

            while (desconectar != NULL)
            {
                desconectar->filas = borrar;
                // desconectar->filas->arriba = NULL;
                //  borrar->abajo = NULL;
                // borrar = borrar->sig;
                borrar->sig->ant = borrar->ant;
                borrar->ant->sig = borrar->sig;
                borrar->ant = NULL;
                borrar->sig = NULL;
                // borrar = NULL;
                desconectar = desconectar->sig;
                desconectar = NULL;
            }
            // delete desconectar;
            delete borrar;
            cout << "Se elimino la fidsdsla con exito..." << endl;

            return;
        }
        else
        {
            if (aux2->arriba == NULL && aux2->abajo != NULL)
            {
                while (desconectar != NULL)
                {
                    desconectar->filas = borrar->abajo;
                    desconectar->filas->arriba = NULL;
                    borrar->abajo = NULL;
                    borrar = borrar->sig;
                    borrar->ant = NULL;
                    borrar->sig = NULL;
                    borrar = NULL;
                    desconectar = desconectar->sig;
                    aux1->filas = aux2;
                    desconectar = NULL;
                }
                // delete desconectar;
                delete borrar;
                cout << "Se elimino la fila con exito..." << endl;
            }
        }
        break;
    }
}
*/
void updateTupla(string nombreTabla, string condicionModificar, string columnaModificar, string valorModficar)
{
    string valorColumna;
    string valorTupla;
    string vacio = "";
    string igual = "=";
    string mayor = ">";
    string menor = "<";
    string distinto = "<>";
    int condicion_;
    int no_encontrado = 999999;

     if (condicionModificar.find(distinto) < no_encontrado)
    {
        valorColumna = condicionModificar.substr(0, condicionModificar.find(distinto));
        valorTupla = condicionModificar.substr(condicionModificar.find(distinto) + 2);
        condicion_ = 1;
    }
    else
    {
        if (condicionModificar.find(mayor) < no_encontrado)
        {
            valorColumna = condicionModificar.substr(0, condicionModificar.find(mayor));
            valorTupla = condicionModificar.substr(condicionModificar.find(mayor) + 1);
            condicion_ = 2;
        }
        else
        {
            if (condicionModificar.find(menor) < no_encontrado)
            {
                valorColumna = condicionModificar.substr(0, condicionModificar.find(menor));
                valorTupla = condicionModificar.substr(condicionModificar.find(menor) + 1);
                condicion_ = 3;
            }
            else
            {
                if (condicionModificar.find(igual) < no_encontrado)
                {
                    valorColumna = condicionModificar.substr(0, condicionModificar.find(igual));
                    valorTupla = condicionModificar.substr(condicionModificar.find(igual) + 1);
                    condicion_ = 4;
                }
                else
                {
                    if (condicionModificar.find(vacio) < no_encontrado)
                    {
                        condicion_ = 5;
                    }
                }
            }
        }
    }

    
}

//  ------------------------------ FUNCIONES ENTRE TABLAS ------------------------------
void selectWhere(string nombreTabla1, string condicion, string nombreTabla2)
{
    string valorColumna;
    string valorTupla;
    string vacio = "";
    string igual = "=";
    string mayor = ">";
    string menor = "<";
    string distinto = "<>";
    int condicion_;
    int no_encontrado = 999999;

    if (condicion.find(distinto) < no_encontrado)
    {
        valorColumna = condicion.substr(0, condicion.find(distinto));
        valorTupla = condicion.substr(condicion.find(distinto) + 2);
        condicion_ = 1;
    }
    else
    {
        if (condicion.find(mayor) < no_encontrado)
        {
            valorColumna = condicion.substr(0, condicion.find(mayor));
            valorTupla = condicion.substr(condicion.find(mayor) + 1);
            condicion_ = 2;
        }
        else
        {
            if (condicion.find(menor) < no_encontrado)
            {
                valorColumna = condicion.substr(0, condicion.find(menor));
                valorTupla = condicion.substr(condicion.find(menor) + 1);
                condicion_ = 3;
            }
            else
            {
                if (condicion.find(igual) < no_encontrado)
                {
                    valorColumna = condicion.substr(0, condicion.find(igual));
                    valorTupla = condicion.substr(condicion.find(igual) + 1);
                    condicion_ = 4;
                }
                else
                {
                    if (condicion.find(vacio) < no_encontrado)
                    {
                        condicion_ = 5;
                    }
                }
            }
        }
    }

    Tabla aux = BD;
    if (aux == NULL)
    {
        cout << "No existen tablas..." << endl;
        return;
    }

    while (aux != NULL)
    {
        if (aux->nombreTabla == nombreTabla1)
        {
            if (aux->columna == NULL)
            {
                cout << "No existen columnas..." << endl;
                return;
            }
            break;
        }
        if (aux->nombreTabla == nombreTabla2)
        {
            cout << "Ya existe una tabla con este nombre... " << nombreTabla2 << endl;
            return;
        }
        aux = aux->sig;
        if (aux == NULL)
        {
            cout << "No existe la tabla..." << nombreTabla1 << endl;
            return;
        }
    }

    while (aux != NULL)
    {
        if (aux->nombreTabla == nombreTabla2)
        {
            cout << "Ya existe una tabla con este nombre... " << nombreTabla2 << endl;
            return;
        }
        else
        {
            createTable(nombreTabla2);
            cout << "Se creo una nueva tabla... " << nombreTabla2 << endl;
            break;
        }
        aux = aux->sig;
    }

    string columnas = "";
    columna copiarColumna = aux->columna;
    while (copiarColumna != NULL)
    {
        if (columnas == "")
        {
            columnas = copiarColumna->nombreColumna;
        }
        else
        {
            columnas = columnas + ":" + copiarColumna->nombreColumna;
        }
        copiarColumna = copiarColumna->sig;
    }
    cout << columnas << endl;
    copiarColumna = aux->columna;
    while (true)
    {
        string calificador, tipodato;
        if (copiarColumna->primary_key)
        {
            calificador = "primary_key";
        }
        else if (copiarColumna->nn)
        {
            calificador = "nn";
        }
        else
        {
            calificador = "any";
        }

        if (copiarColumna->tipo_dato)
        {
            tipodato = "int";
        }
        else
        {
            tipodato = "string";
        }
        addCol(nombreTabla2, copiarColumna->nombreColumna, tipodato, calificador);
        cout << "cree la columna " << copiarColumna->nombreColumna << endl;
        if (copiarColumna->sig == NULL)
        {
            break;
        }
        copiarColumna = copiarColumna->sig;
    }

    string val = "";
    columna aux1 = aux->columna;
    columna condicionColumna = NULL;
    filas buscar = NULL;

    if (condicion != "")
    {
        while (aux1 != NULL)
        {

            if (aux1->nombreColumna == valorColumna)
            {
                condicionColumna = aux1;
                buscar = aux1->filas;
                cout << aux1->nombreColumna << endl;
                cout << "Existe la columna..." << aux1->nombreColumna << endl;
                if (aux1->filas == NULL)
                {
                    cout << "No existen filas..." << endl;
                    return;
                }
                break;
            }
            aux1 = aux1->sig;

            if (aux1 == NULL)
            {
                cout << "No existe la columna..." << valorColumna << endl;
                return;
            }
        }
    }
    else
    {
        condicionColumna = aux1;
    }

    cout << condicion_ << endl;
    switch (condicion_)
    {
    case 1:
        while (buscar != NULL)
        {
            if (condicionColumna->tipo_dato)
            {
                int comparar = stoi(valorTupla);
                if (buscar->dato_int != comparar)
                {
                    filas copiarFila = buscar;
                    columna aux1 = aux->columna;
                    while (copiarFila->ant)
                    {
                        copiarFila = copiarFila->ant;
                    }
                    while (true)
                    {
                        if (aux1->tipo_dato)
                        {
                            stringstream ss;
                            string aux;
                            ss << copiarFila->dato_int;
                            aux = ss.str();
                            if (val == "")
                            {
                                val = aux;
                            }
                            else
                            {
                                val = val + ":" + aux;
                            }
                        }
                        else
                        {
                            if (val == "")
                            {
                                val = copiarFila->dato_string;
                            }
                            else
                            {
                                val = val + ":" + copiarFila->dato_string;
                            }
                        }
                        if (aux1->sig == NULL)
                        {
                            break;
                        }
                        aux1 = aux1->sig;
                        copiarFila = copiarFila->sig;
                    }
                }
            }
            else
            {
                if (buscar->dato_string != valorTupla)
                {
                    filas copiarFila = buscar;
                    columna aux1 = aux->columna;
                    while (copiarFila->ant)
                    {
                        copiarFila = copiarFila->ant;
                    }
                    while (true)
                    {
                        if (aux1->tipo_dato)
                        {
                            stringstream ss;
                            string aux;
                            ss << copiarFila->dato_int;
                            aux = ss.str();
                            if (val == "")
                            {
                                val = aux;
                            }
                            else
                            {
                                val = val + ":" + aux;
                            }
                        }
                        else
                        {
                            if (val == "")
                            {
                                val = copiarFila->dato_string;
                            }
                            else
                            {
                                val = val + ":" + copiarFila->dato_string;
                            }
                        }
                        if (aux1->sig == NULL)
                        {
                            break;
                        }
                        aux1 = aux1->sig;
                        copiarFila = copiarFila->sig;
                    }
                }
            }

            if (val != "")
            {
                insertInto(nombreTabla2, columnas, val);
                val = "";
            }

            buscar = buscar->abajo;
        }
        break;
    case 2:
        while (buscar != NULL)
        {
            if (condicionColumna->tipo_dato)
            {
                int comparar = stoi(valorTupla);
                if (buscar->dato_int > comparar)
                {
                    filas copiarFila = buscar;
                    columna aux1 = aux->columna;
                    while (copiarFila->ant)
                    {
                        copiarFila = copiarFila->ant;
                    }
                    while (true)
                    {
                        if (aux1->tipo_dato)
                        {
                            stringstream ss;
                            string aux;
                            ss << copiarFila->dato_int;
                            aux = ss.str();
                            if (val == "")
                            {
                                val = aux;
                            }
                            else
                            {
                                val = val + ":" + aux;
                            }
                        }
                        else
                        {
                            if (val == "")
                            {
                                val = copiarFila->dato_string;
                            }
                            else
                            {
                                val = val + ":" + copiarFila->dato_string;
                            }
                        }
                        if (aux1->sig == NULL)
                        {
                            break;
                        }
                        aux1 = aux1->sig;
                        copiarFila = copiarFila->sig;
                    }
                }
            }
            else
            {
                if (buscar->dato_string > valorTupla)
                {
                    filas copiarFila = buscar;
                    columna aux1 = aux->columna;
                    while (copiarFila->ant)
                    {
                        copiarFila = copiarFila->ant;
                    }
                    while (true)
                    {
                        if (aux1->tipo_dato)
                        {
                            stringstream ss;
                            string aux;
                            ss << copiarFila->dato_int;
                            aux = ss.str();
                            if (val == "")
                            {
                                val = aux;
                            }
                            else
                            {
                                val = val + ":" + aux;
                            }
                        }
                        else
                        {
                            if (val == "")
                            {
                                val = copiarFila->dato_string;
                            }
                            else
                            {
                                val = val + ":" + copiarFila->dato_string;
                            }
                        }
                        if (aux1->sig == NULL)
                        {
                            break;
                        }
                        aux1 = aux1->sig;
                        copiarFila = copiarFila->sig;
                    }
                }
            }

            if (val != "")
            {
                insertInto(nombreTabla2, columnas, val);
                val = "";
            }

            buscar = buscar->abajo;
        }
        break;
    case 3:
        while (buscar != NULL)
        {
            if (condicionColumna->tipo_dato)
            {
                int comparar = stoi(valorTupla);
                if (buscar->dato_int < comparar)
                {
                    filas copiarFila = buscar;
                    columna aux1 = aux->columna;
                    while (copiarFila->ant)
                    {
                        copiarFila = copiarFila->ant;
                    }
                    while (true)
                    {
                        if (aux1->tipo_dato)
                        {
                            stringstream ss;
                            string aux;
                            ss << copiarFila->dato_int;
                            aux = ss.str();
                            if (val == "")
                            {
                                val = aux;
                            }
                            else
                            {
                                val = val + ":" + aux;
                            }
                        }
                        else
                        {
                            if (val == "")
                            {
                                val = copiarFila->dato_string;
                            }
                            else
                            {
                                val = val + ":" + copiarFila->dato_string;
                            }
                        }
                        if (aux1->sig == NULL)
                        {
                            break;
                        }
                        aux1 = aux1->sig;
                        copiarFila = copiarFila->sig;
                    }
                }
            }
            else
            {
                if (buscar->dato_string < valorTupla)
                {
                    filas copiarFila = buscar;
                    columna aux1 = aux->columna;
                    while (copiarFila->ant)
                    {
                        copiarFila = copiarFila->ant;
                    }
                    while (true)
                    {
                        if (aux1->tipo_dato)
                        {
                            stringstream ss;
                            string aux;
                            ss << copiarFila->dato_int;
                            aux = ss.str();
                            if (val == "")
                            {
                                val = aux;
                            }
                            else
                            {
                                val = val + ":" + aux;
                            }
                        }
                        else
                        {
                            if (val == "")
                            {
                                val = copiarFila->dato_string;
                            }
                            else
                            {
                                val = val + ":" + copiarFila->dato_string;
                            }
                        }
                        if (aux1->sig == NULL)
                        {
                            break;
                        }
                        aux1 = aux1->sig;
                        copiarFila = copiarFila->sig;
                    }
                }
            }

            if (val != "")
            {
                insertInto(nombreTabla2, columnas, val);
                val = "";
            }

            buscar = buscar->abajo;
        }
        break;
    case 4:
        while (buscar != NULL)
        {
            if (condicionColumna->tipo_dato)
            {
                int comparar = stoi(valorTupla);
                if (buscar->dato_int == comparar)
                {
                    filas copiarFila = buscar;
                    columna aux1 = aux->columna;
                    while (copiarFila->ant)
                    {
                        copiarFila = copiarFila->ant;
                    }
                    while (true)
                    {
                        if (aux1->tipo_dato)
                        {
                            stringstream ss;
                            string aux;
                            ss << copiarFila->dato_int;
                            aux = ss.str();
                            if (val == "")
                            {
                                val = aux;
                            }
                            else
                            {
                                val = val + ":" + aux;
                            }
                        }
                        else
                        {
                            if (val == "")
                            {
                                val = copiarFila->dato_string;
                            }
                            else
                            {
                                val = val + ":" + copiarFila->dato_string;
                            }
                        }
                        if (aux1->sig == NULL)
                        {
                            break;
                        }
                        aux1 = aux1->sig;
                        copiarFila = copiarFila->sig;
                    }
                }
            }
            else
            {
                if (buscar->dato_string == valorTupla)
                {
                    filas copiarFila = buscar;
                    columna aux1 = aux->columna;
                    while (copiarFila->ant)
                    {
                        copiarFila = copiarFila->ant;
                    }
                    while (true)
                    {
                        if (aux1->tipo_dato)
                        {
                            stringstream ss;
                            string aux;
                            ss << copiarFila->dato_int;
                            aux = ss.str();
                            if (val == "")
                            {
                                val = aux;
                            }
                            else
                            {
                                val = val + ":" + aux;
                            }
                        }
                        else
                        {
                            if (val == "")
                            {
                                val = copiarFila->dato_string;
                            }
                            else
                            {
                                val = val + ":" + copiarFila->dato_string;
                            }
                        }
                        if (aux1->sig == NULL)
                        {
                            break;
                        }
                        aux1 = aux1->sig;
                        copiarFila = copiarFila->sig;
                    }
                }
            }

            if (val != "")
            {
                insertInto(nombreTabla2, columnas, val);
                val = "";
            }

            buscar = buscar->abajo;
        }
        break;
    case 5:
        buscar = aux1->filas;
        while (buscar != NULL)
        {
            cout << "anachii" << endl;
            filas copiarFila = buscar;
            columna aux1 = aux->columna;
            while (copiarFila->ant)
            {
                copiarFila = copiarFila->ant;
            }
            while (true)
            {
                cout << "el valor es... " << val << endl;
                if (aux1->tipo_dato)
                {
                    stringstream ss;
                    string aux;
                    ss << copiarFila->dato_int;
                    aux = ss.str();
                    if (val == "")
                    {
                        val = aux;
                    }
                    else
                    {
                        val = val + ":" + aux;
                    }
                }
                else
                {
                    if (val == "")
                    {
                        val = copiarFila->dato_string;
                    }
                    else
                    {
                        val = val + ":" + copiarFila->dato_string;
                    }
                }
                if (aux1->sig == NULL)
                {
                    break;
                }
                aux1 = aux1->sig;
                copiarFila = copiarFila->sig;
            }
            insertInto(nombreTabla2, columnas, val);
            val = "";

            buscar = buscar->abajo;
        }
        break;
    }
}

//  ------------------------------ PRINTS ------------------------------
void printTables(Tabla BD)
{
    if (BD == NULL)
    {
        cout << "No existen tablas" << endl;
        return;
    }
    cout << "Las tablas encontradas son: " << endl;
    while (BD != NULL)
    {
        cout << "-" << BD->nombreTabla << endl;
        BD = BD->sig;
    }
    cout << endl;
}

void printMetadata(string nombreTabla)
{
    Tabla aux = BD;
    if (aux == NULL)
    {
        cout << "No existen tablas" << endl;
        return;
    }
    while (aux != NULL)
    {
        if (aux->nombreTabla == nombreTabla)
        {
            if (aux->columna == NULL)
            {
                cout << "No existen columnas" << endl;
                return;
            }
            cout << "-" << aux->nombreTabla << endl;
            columna aux1 = aux->columna;
            do
            {

                cout << aux1->nombreColumna << endl;

                if (aux1->primary_key == true)
                {
                    cout << "El calificador es PRIMARY KEY" << endl;
                }
                else
                {
                    if (aux1->nn == true)
                    {
                        cout << "El calificador es NOT EMPTY" << endl;
                    }
                    else
                    {
                        cout << "El calificador es ANY" << endl;
                    }
                }
                if (aux1->tipo_dato = true)
                {
                    cout << "El dato es INTEGER" << endl;
                }
                else
                {
                    cout << "El dato es STRING" << endl;
                }
                aux1 = aux1->sig;
            } while (aux1 != NULL);
        }

        aux = aux->sig;
        if (aux == NULL)
        {
            return;
        }
    }
}

void printDataTable(string nombreTabla, string ordenadaPor)
{

    Tabla aux = BD;
    if (aux == NULL)
    {
        cout << "No existen tablas" << endl;
        return;
    }
    while (aux != NULL)
    {
        if (aux->nombreTabla == nombreTabla)
        {
            cout << nombreTabla << endl;
            break;
        }

        aux = aux->sig;
        if (aux == NULL)
        {
            cout << "No se encontro la tabla..." << endl;
            return;
        }
    }
    if (aux->columna == NULL)
    {
        cout << "No existen columnas..." << endl;
        return;
    }
    columna aux1 = aux->columna;
    if (aux1->filas == NULL)
    {
        cout << "No existen filas para imprimir..." << endl;
        return;
    }
    while (aux1 != NULL)
    {
        cout << setw(20 + (aux1->nombreColumna.length())) << aux1->nombreColumna;
        aux1 = aux1->sig;

        if (aux1 == NULL)
        {
            cout << endl;
        }
    }
    aux1 = aux->columna;

    filas imprimir = aux1->filas;
    while (imprimir != NULL)
    {
        while (aux1 != NULL)
        {
            if (aux1->tipo_dato == true)
            {
                cout << setw(20) << " [] " << imprimir->dato_int << " [] ";
            }
            else
            {
                cout << setw(20 - (imprimir->dato_string.length())) << " [] " << imprimir->dato_string << " [] ";
            }
            aux1 = aux1->sig;
            if (imprimir->sig != NULL)
            {
                imprimir = imprimir->sig;
            }

            if (aux1 == NULL)
            {
                cout << endl;
            }
        }
        aux1 = aux->columna;
        while (imprimir->ant != NULL)
            imprimir = imprimir->ant;
        imprimir = imprimir->abajo;
    }
}

/*
int main()
{
    system("cls");
    createTable("pescados");
    createTable("tipo_arboles");
    createTable("personas");
    createTable("hi");
    // cout << "nombre de la tabla" << endl;

    // imprimir(BD);
    // imprimir(BD);
    // addCol("alo", "queso", "", "");
    addCol("personas", "cedula", "int", "primary_key");
    addCol("personas", "nombres", "string", "nn");
    addCol("personas", "apellido", "string", "nn");
    addCol("personas", "edad", "string", "nn");
    // addCol("personas", "nombrePerro", "string", "nn");
    // dropTable("hi"); printTables(BD);
    //  addCol("pescados", "naranja", "", "primary_key");
    //  addCol("alo", "soto", "int", "nn");
    //  addCol("alo", "quiesoto", "int", "nn");
    //  alterCol("alo", "quesoto", "", "primary_key", "sioto");
    //  system("cls");
    //  cout << "llegue al print" << endl
    //       << endl
    insertInto("personas", "cedula:nombres:apellido:edad", "1:esteban:quito:25");
    insertInto("personas", "cedula:nombres:apellido:edad", "7:mili:vairo:19");
    insertInto("personas", "cedula:nombres:apellido:edad", "2:jose:soto:23"); //       << endl;

    // insertInto("personas", "cedula:nombres:apellidos:edad", "3:decime:quesi:57");
    //  dropCol("personas", "nombres");
    // deleteTupla("personas", "apellido<quito");
    selectWhere("personas", "", "mascotas");
    // selectWhere("personas", "nombres=jose", "mascotas");
    // updateTupla("personas", "cedula=7", "apellido", "vaioro");
    //   printTables(BD);
    //  printMetadata("mascotas");
    printDataTable("mascotas", "");
    //  printDataTable("personas", "");
    //
    //  cout << endl
    //       << endl
    //       << endl;
    //  cout << "sali del print" << endl
    //       << endl;

    // printMetadata("personas");
    // addCol("alo", "quesoto", "int", "primary_key");

    // imprimir(BD);

    return 0;
}*/

//  ------------------------------ MENUS ------------------------------
int main()
{
    int opcion;

    cout << "BIENVENIDO :D\n"
         << endl;

    do
    {
        cout << "1 - INGRESAR A LA BASE DE DATOS\n"
             << "2 - VISUALIZAR SU BASE DE DATOS\n"
             << "0 - SALIR" << endl;
        cin >> opcion;
        getchar();
        switch (opcion)
        {

        case 1:
            system("cls");
            sub_menu();
            break;

        case 2:
            system("cls");
            submenu_imprimir();
            break;

        case 0:
        default:
            system("cls");
            cout << "..." << endl;
            break;
        }
    } while (opcion != 0);
}

void sub_menu()
{

    int opcion;
    do
    {
        cout << "1 - TABLAS\n"
             << "2 - COLUMNAS\n"
             << "3 - TUPLAS\n"
             << "0 - Volver al menu principal" << endl;

        cin >> opcion;
        getchar();
        switch (opcion)
        {
        case 1:
        {
            system("cls");
            submenu_tablas();
            break;
        }
        case 2:
        {
            system("cls");
            submenu_columnas();
            break;
        }
        case 3:
        {
            system("cls");
            submenu_tuplas();
            system("clear");
            break;
        }

        case 0:
        {
            system("cls");
            cout << "Regresando..." << endl;
            main();
        }
        }
    } while (opcion != 0);
}

void submenu_tablas()
{
    string nombreTabla;
    string nombreTabla2;
    string condicion;
    string eliminarTabla;

    int opcion;
    do
    {
        cout << "1 - CREAR TABLAS\n"
             << "2 - ELIMINAR TABLAS\n"
             << "3 - OPERACIONES ENTRE TABLAS\n"
             << "0 - Volver al submenu" << endl;

        cin >> opcion;
        getchar();
        switch (opcion)
        {
        case 1:
        {
            system("cls");
            cout << "Ingrese el nombre de la TABLA a crear" << endl;
            cin >> nombreTabla;
            createTable(nombreTabla);
            break;
        }
        case 2:
        {
            system("cls");
            cout << "Ingrese el nombre de su TABLA a eliminar" << endl;
            cin >> eliminarTabla;
            dropTable(eliminarTabla);
            break;
        }
        case 3:
        {
            system("cls");
            cout << "Ingrese el nombre de su TABLAr" << endl;
            cin >> nombreTabla;
            cout << "Ingrese la condicion" << endl;
            cin >> condicion;
            cout << "Ingrese el nombre de la nueva TABLA a crear";
            cin >> nombreTabla2;
            selectWhere(nombreTabla, condicion, nombreTabla2);
            break;
        }
        case 0:
        {
            system("cls");
            cout << "..." << endl;
            system("cls");
            sub_menu();
        }
        }
    } while (opcion != 0);
}

void submenu_columnas()
{
    string nombreColumna;
    string eliminarColumna;
    string modificarColumna;
    string calificador;
    string tipo_dato;
    string nombreTabla;

    int opcion;

    do
    {
        cout << "1 - CREAR COLUMNA\n"
             << "2 - MODIFICAR COLUMNA\n"
             << "3 - ELIMINAR COLUMNA\n"
             << "0 - Volver al submenu" << endl;

        cin >> opcion;
        getchar();
        switch (opcion)
        {
        case 1:
        {
            system("cls");
            cout << "Ingrese el nombre de la TABLA donde creara la COLUMNA" << endl;
            cin >> nombreTabla;
            cout << "Ingrese el nombre de la Columna a crear" << endl;
            cin >> nombreColumna;
            cout << "Ingrese el tipo de dato a utilizar" << endl;
            cin >> tipo_dato;
            cout << "Ingrese el calificador de dato a utilizar" << endl;
            cin >> calificador;
            cout << endl;
            addCol(nombreTabla, nombreColumna, tipo_dato, calificador);
            break;
        }
        case 2:
        {
            system("cls");
            cout << "Ingrese el nombre de la TABLA donde modificara su COLUMNA" << endl;
            cin >> nombreTabla;
            cout << "Ingrese el nombre de la Columna a modificar" << endl;
            cin >> nombreColumna;
            cout << "Ingrese el tipo de dato a modificar" << endl;
            cin >> tipo_dato;
            cout << "Ingrese el calificador de dato a modificar" << endl;
            cin >> calificador;
            cout << endl;
            addCol(nombreTabla, nombreColumna, tipo_dato, calificador);
            break;
        }
        case 3:
        {
            system("cls");
            cout << "Ingrese el nombre de la TABLA donde eliminara su COLUMNA" << endl;
            cin >> nombreTabla;
            cout << "Ingrese el nombre de la Columna a eliminar" << endl;
            cin >> eliminarColumna;
            dropCol(nombreTabla, nombreColumna);
            break;
        }
        case 0:
        {
            system("cls");
            cout << "..." << endl;
            system("cls");
            sub_menu();
        }
        }
    } while (opcion != 0);
}

void submenu_tuplas()
{
    string nombreTabla;
    string nombreColumna;
    string valoresTuplas;
    string limite = ":";
    int opcion;

    do
    {
        cout << "1 - CREAR TUPLAS\n"
             << "2 - MODIFICAR TUPLAS\n"
             << "3 - ELIMINAR TUPLAS\n"
             << "0 - Volver al submenu" << endl;
        cin >> opcion;
        getchar();
        switch (opcion)
        {
        case 1:
        {
            system("cls");
            cout << "Ingrese el nombre de la TABLA" << endl;
            cin >> nombreTabla;
            cout << "Ingrese el nombre de la COLUMNA" << endl;
            cin >> nombreColumna;
            cout << "Ingrese la TUPLA" << endl;
            cin >> valoresTuplas;
            cout << endl;
            insertInto(nombreTabla, nombreColumna, valoresTuplas);
            break;
        }
        case 2:
        {
            system("cls");
            break;
        }
        case 0:
        {
            system("cls");
            cout << "..." << endl;
            system("cls");
            sub_menu();
        }
        }
    } while (opcion != 0);
}

void submenu_imprimir()
{
    int opcion;
    string nombreTabla;
    do
    {
        cout << "1 - VER TABLAS\n"
             << "2 - VER TABLAS Y COLUMNAS\n"
             << "3 - VER TABLAS, COLUMNAS Y TUPLAS\n"
             << "0 - Volver al submenu" << endl;

        cin >> opcion;
        getchar();
        switch (opcion)
        {
        case 1:
        {
            system("cls");
            printTables(BD);
            break;
        }
        case 2:
        {
            system("cls");
            cout << "Ingrese el nombre de la TABLA que busca" << endl;
            cin >> nombreTabla;
            printMetadata(nombreTabla);
            break;
        }
        case 3:
        system("cls");
            cout << "Ingrese el nombre de la TABLA que busca" << endl;
            cin >> nombreTabla;
            printDataTable(nombreTabla, "");
            break;
        case 0:
        {
            system("cls");
            cout << "..." << endl;
            sub_menu();
        }
        }
    } while (opcion != 0);
}
