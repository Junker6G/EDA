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
void submenu_operaciones_tablas();
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

    Tabla aux = BD;
    Tabla insertar_t = new nodoTablas;
    insertar_t->nombreTabla = nuevaTabla;
    insertar_t->columna = NULL;
    insertar_t->ant = NULL;
    insertar_t->sig = NULL;
    while (aux != NULL)
    {
        if (aux->nombreTabla == nuevaTabla)
        {
            cout << "Ya existe una tabla con el nombre ingresado... " << nuevaTabla << endl;
            return;
        }
        aux = aux->sig;
    }

    aux = BD;
    while (aux != NULL)
    {
        if (aux->sig == NULL)
        {
            aux->sig = insertar_t;
            insertar_t->ant = aux;
            return;
        }
        if (aux->ant == NULL && aux->nombreTabla > nuevaTabla)
        {
            insertar_t->sig = aux;
            insertar_t->ant = aux->ant;
            BD = insertar_t;
            return;
        }
        if (aux->nombreTabla > nuevaTabla)
        {
            insertar_t->sig = aux;
            insertar_t->ant = aux->ant;
            aux->ant->sig = insertar_t;
            aux->ant = insertar_t;
            return;
        }
        aux = aux->sig;
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
                if (aux1->tipo_dato == true)
                {
                    cout << "El dato es INTEGER" << endl
                         << endl;
                }
                else
                {
                    cout << "El dato es STRING" << endl
                         << endl;
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
        cout << " - " << aux1->nombreColumna << " - ";
        aux1 = aux1->sig;

        if (aux1 == NULL)
        {
            cout << endl;
        }
    }
    aux1 = aux->columna;
    cout << endl;
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
    cout << endl;
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
            filas auxFilas = aux2->filas;

            if (calificadorCol == "primary_key")
            {
                if (auxFilas != NULL)
                {
                    cout << "ERROR No se puede crear una columna PK cuando la tabla ya se encuentra poblada" << endl;
                    return;
                }
            }
            if (calificadorCol == "nn")
            {
                if (auxFilas != NULL)
                {
                    cout << "ERROR No se puede crear una columna NN cuando la tabla ya se encuentra poblada" << endl;
                    return;
                }
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
            if (calificadorCol == "any")
            {
                if (auxFilas != NULL)
                {
                    filas nodoVacio = new nodoFilas;
                    nuevaColumna->filas = nodoVacio;
                    nodoVacio->sig = NULL;
                    nodoVacio->ant = auxFilas;
                    nodoVacio->abajo = NULL;
                    auxFilas->sig = nodoVacio;
                    auxFilas = auxFilas->abajo;
                    filas ultimoNodoVacio = nodoVacio;
                    while (auxFilas != NULL)
                    {
                        filas nodoVacio = new nodoFilas;
                        ultimoNodoVacio->abajo = nodoVacio;
                        nodoVacio->arriba = ultimoNodoVacio;
                        nodoVacio->sig = NULL;
                        nodoVacio->ant = auxFilas;
                        nodoVacio->abajo = NULL;
                        auxFilas->sig = nodoVacio;
                        ultimoNodoVacio = nodoVacio;
                        auxFilas = auxFilas->abajo;
                    }
                    // cout << "awaken" << endl;
                }
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
            aux = aux->sig;
            if (aux == NULL)
            {
                cout << "No existe la tabla... " << tabla << endl;
                return;
            }
        }
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

                    aux1->nombreColumna = nombreColNuevo;
                    cout << "Se cambio el nombre de la columna " << nombreColNuevo << endl;

                    if (tipoColNuevo == "int" && aux1->tipo_dato == false && aux1->filas == NULL)
                    {
                        aux1->tipo_dato = true;
                    }

                    if (tipoColNuevo == "string" && aux1->tipo_dato == true && aux1->filas != NULL)
                    {
                        aux1->tipo_dato = false;
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

                    if (calificadorColNuevo == "primary_key")
                    {
                        aux1->primary_key = true;
                        aux1->nn = false;
                    }
                    else
                    {
                        if (calificadorColNuevo == "nn")
                        {
                            aux1->primary_key = false;
                            aux1->nn = true;
                        }
                        else
                        {
                            if (calificadorColNuevo == "any")
                            {
                                aux1->primary_key = false;
                                aux1->nn = false;
                            }
                            else
                            {
                                cout << "NO se reconoce el nuevo calificador..." << endl;
                            }
                        }
                    }

                    return;
                }
                aux1 = aux1->sig;
            }
            aux = aux->sig;
        }
        cout << "No existe el nombre de columna ingresado" << endl;
        return;
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
        nuevo->dato_int = empty;
        nuevo->dato_string = "";
        string valor = "";
        valor = valoresTupla.substr(0, valoresTupla.find(limite));
        // cout << "valores tupla -> " << valoresTupla << endl;
        valoresTupla.erase(0, valoresTupla.find(limite) + 1);
        // cout << "valores tupla despues -> " << valoresTupla << endl;

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

        /*cout << endl
             << aux1->nombreColumna << endl;*/
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
    cout << "Se ha creado una nueva TUPLA" << endl;
}

void deleteTupla(string nombreTabla, string condicionEliminar)
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

    if (condicionEliminar.find(distinto) < no_encontrado)
    {
        valorColumna = condicionEliminar.substr(0, condicionEliminar.find(distinto));
        valorTupla = condicionEliminar.substr(condicionEliminar.find(distinto) + 2);
        condicion_ = 1;
    }
    else
    {
        if (condicionEliminar.find(mayor) < no_encontrado)
        {
            valorColumna = condicionEliminar.substr(0, condicionEliminar.find(mayor));
            valorTupla = condicionEliminar.substr(condicionEliminar.find(mayor) + 1);
            condicion_ = 2;
        }
        else
        {
            if (condicionEliminar.find(menor) < no_encontrado)
            {
                valorColumna = condicionEliminar.substr(0, condicionEliminar.find(menor));
                valorTupla = condicionEliminar.substr(condicionEliminar.find(menor) + 1);
                condicion_ = 3;
            }
            else
            {
                if (condicionEliminar.find(igual) < no_encontrado)
                {
                    valorColumna = condicionEliminar.substr(0, condicionEliminar.find(igual));
                    valorTupla = condicionEliminar.substr(condicionEliminar.find(igual) + 1);
                    condicion_ = 4;
                }
                else
                {
                    if (condicionEliminar == "")
                    {
                        condicion_ = 5;
                    }
                }
            }
        }
    }
    Tabla aux = BD;
    columna aux1 = aux->columna;
    int valorTuplaInt = 0;
    // cout << "comparador -> " << condicion_ << endl;

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
            aux1 = aux->columna;
            break;
        }
        aux = aux->sig;
        if (aux == NULL)
        {
            cout << "No existe la tabla..." << nombreTabla << endl;
            return;
        }
    }

    if (condicion_ == 5)
    {
        // cout << "caso 5" << endl;
        filas borrar = NULL;
        filas buscar = aux1->filas;

        if (aux1->filas == NULL)
        {
            return;
        }
        while (true)
        {
            while (buscar->abajo != NULL)
            {
                buscar = buscar->abajo;
            }
            while (true)
            {
                borrar = buscar;
                buscar = buscar->arriba;
                borrar->abajo = NULL;
                borrar->arriba = NULL;
                borrar->ant = NULL;
                borrar->sig = NULL;
                delete borrar;
                if (buscar == NULL)
                {
                    cout << aux1->nombreColumna << endl;
                    aux1 = aux1->sig;
                    if (aux1 == NULL)
                    {
                        aux1 = aux->columna;
                        while (true)
                        {
                            aux1->filas = NULL;
                            aux1 = aux1->sig;
                            if (aux1 == NULL)
                            {
                                return;
                            }
                        }
                    }
                    buscar = aux1->filas;
                    break;
                }
            }
        }
    }

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
            return;
        }
    }

    filas buscar = aux1->filas;
    if (aux1->tipo_dato == true)
    {
        valorTuplaInt = stoi(valorTupla);
        // cout << "cambio int" << valorTupla << endl;
    }

    // cout << valorTuplaInt << endl;
    switch (condicion_)
    {
    case 2:
        if (aux1->tipo_dato == true)
        {

            // cout << "check" << endl;
            if (aux1->filas->dato_int > valorTuplaInt)
            {
                if (aux1->filas->abajo == NULL)
                {
                    columna auxCol = aux1;
                    filas aux2 = NULL;
                    while (auxCol->ant != NULL)
                    {
                        auxCol = auxCol->ant;
                    }
                    while (true)
                    {
                        aux2 = auxCol->filas;
                        auxCol->filas = NULL;
                        delete aux2;
                        auxCol = auxCol->sig;
                        if (auxCol == NULL)
                            return;
                    }
                }
                else
                {
                    columna auxCol = aux1;
                    filas borrar = NULL;
                    while (auxCol->ant != NULL)
                    {
                        auxCol = auxCol->ant;
                    }
                    while (true)
                    {
                        borrar = auxCol->filas;
                        auxCol->filas = borrar->abajo;
                        borrar->abajo->arriba = NULL;
                        borrar->abajo = NULL;
                        auxCol = auxCol->sig;
                        if (auxCol == NULL)
                        {
                            // cout << "chau" << endl;
                            break;
                        }
                    }
                }
            }
            filas buscar = aux1->filas;
            while (true)
            {
                /*cout << "el valor de la fila -> " << buscar->dato_int << endl
                     << "valorTupla -> " << valorTuplaInt << endl;*/
                if (buscar->dato_int > valorTuplaInt)
                {
                    filas aux2 = buscar;
                    while (aux2->ant != NULL)
                    {
                        aux2 = aux2->ant;
                    }
                    filas borrar = NULL;
                    while (true)
                    {
                        borrar = aux2;
                        if (aux2->abajo != NULL)
                        {
                            aux2->abajo->arriba = aux2->arriba;
                            aux2->arriba->abajo = aux2->abajo;
                            aux2->abajo = NULL;
                            aux2->arriba = NULL;
                        }
                        else
                        {
                            aux2->arriba->abajo = NULL;
                            aux2->abajo = NULL;
                            aux2->arriba = NULL;
                        }
                        aux2 = aux2->sig;
                        delete borrar;
                        if (aux2 == NULL)
                        {
                            buscar = aux1->filas;
                            break;
                        }
                    }
                }
                else
                {
                    buscar = buscar->abajo;
                }
                if (buscar == NULL)
                {
                    // cout << "fin" << endl;
                    return;
                }
            }
        }
        else
        {
            if (aux1->filas->dato_string > valorTupla)
            {
                if (aux1->filas->abajo == NULL)
                {
                    columna auxCol = aux1;
                    filas aux2 = NULL;
                    while (auxCol->ant != NULL)
                    {
                        auxCol = auxCol->ant;
                    }
                    while (true)
                    {
                        aux2 = auxCol->filas;
                        auxCol->filas = NULL;
                        delete aux2;
                        auxCol = auxCol->sig;
                        if (auxCol == NULL)
                            return;
                    }
                }
                else
                {
                    columna auxCol = aux1;
                    filas borrar = NULL;
                    while (auxCol->ant != NULL)
                    {
                        auxCol = auxCol->ant;
                    }
                    while (true)
                    {
                        borrar = auxCol->filas;
                        auxCol->filas = borrar->abajo;
                        borrar->abajo->arriba = NULL;
                        borrar->abajo = NULL;
                        auxCol = auxCol->sig;
                        if (auxCol == NULL)
                        {
                            // cout << "chau" << endl;
                            break;
                        }
                    }
                }
            }
            filas buscar = aux1->filas;
            while (true)
            {
                /*cout << "el valor de la fila -> " << buscar->dato_string << endl
                     << "valorTupla -> " << valorTupla << endl;*/
                if (buscar->dato_string > valorTupla)
                {
                    filas aux2 = buscar;
                    while (aux2->ant != NULL)
                    {
                        aux2 = aux2->ant;
                    }
                    filas borrar = NULL;
                    while (true)
                    {
                        borrar = aux2;
                        if (aux2->abajo != NULL)
                        {
                            aux2->abajo->arriba = aux2->arriba;
                            aux2->arriba->abajo = aux2->abajo;
                            aux2->abajo = NULL;
                            aux2->arriba = NULL;
                        }
                        else
                        {
                            aux2->arriba->abajo = NULL;
                            aux2->abajo = NULL;
                            aux2->arriba = NULL;
                        }
                        aux2 = aux2->sig;
                        delete borrar;
                        if (aux2 == NULL)
                        {
                            buscar = aux1->filas;
                            break;
                        }
                    }
                }
                else
                {
                    buscar = buscar->abajo;
                }
                if (buscar == NULL)
                {
                    // cout << "fin" << endl;
                    return;
                }
            }
        }
        break;
    case 4:
        if (aux1->tipo_dato == true)
        {

            // cout << "check" << endl;
            if (aux1->filas->dato_int == valorTuplaInt)
            {
                if (aux1->filas->abajo == NULL)
                {
                    columna auxCol = aux1;
                    filas aux2 = NULL;
                    while (auxCol->ant != NULL)
                    {
                        auxCol = auxCol->ant;
                    }
                    while (true)
                    {
                        aux2 = auxCol->filas;
                        auxCol->filas = NULL;
                        delete aux2;
                        auxCol = auxCol->sig;
                        if (auxCol == NULL)
                            return;
                    }
                }
                else
                {
                    columna auxCol = aux1;
                    filas borrar = NULL;
                    while (auxCol->ant != NULL)
                    {
                        auxCol = auxCol->ant;
                    }
                    while (true)
                    {
                        borrar = auxCol->filas;
                        auxCol->filas = borrar->abajo;
                        borrar->abajo->arriba = NULL;
                        borrar->abajo = NULL;
                        auxCol = auxCol->sig;
                        if (auxCol == NULL)
                        {
                            // cout << "chau" << endl;
                            break;
                        }
                    }
                }
            }
            filas buscar = aux1->filas;
            while (true)
            {
                /*cout << "el valor de la fila -> " << buscar->dato_int << endl
                     << "valorTupla -> " << valorTuplaInt << endl;*/
                if (buscar->dato_int == valorTuplaInt)
                {
                    filas aux2 = buscar;
                    while (aux2->ant != NULL)
                    {
                        aux2 = aux2->ant;
                    }
                    filas borrar = NULL;
                    while (true)
                    {
                        borrar = aux2;
                        if (aux2->abajo != NULL)
                        {
                            aux2->abajo->arriba = aux2->arriba;
                            aux2->arriba->abajo = aux2->abajo;
                            aux2->abajo = NULL;
                            aux2->arriba = NULL;
                        }
                        else
                        {
                            aux2->arriba->abajo = NULL;
                            aux2->abajo = NULL;
                            aux2->arriba = NULL;
                        }
                        aux2 = aux2->sig;
                        delete borrar;
                        if (aux2 == NULL)
                        {
                            buscar = aux1->filas;
                            break;
                        }
                    }
                }
                else
                {
                    buscar = buscar->abajo;
                }
                if (buscar == NULL)
                {
                    // cout << "fin" << endl;
                    return;
                }
            }
        }
        else
        {
            if (aux1->filas->dato_string == valorTupla)
            {
                if (aux1->filas->abajo == NULL)
                {
                    columna auxCol = aux1;
                    filas aux2 = NULL;
                    while (auxCol->ant != NULL)
                    {
                        auxCol = auxCol->ant;
                    }
                    while (true)
                    {
                        aux2 = auxCol->filas;
                        auxCol->filas = NULL;
                        delete aux2;
                        auxCol = auxCol->sig;
                        if (auxCol == NULL)
                            return;
                    }
                }
                else
                {
                    columna auxCol = aux1;
                    filas borrar = NULL;
                    while (auxCol->ant != NULL)
                    {
                        auxCol = auxCol->ant;
                    }
                    while (true)
                    {
                        borrar = auxCol->filas;
                        auxCol->filas = borrar->abajo;
                        borrar->abajo->arriba = NULL;
                        borrar->abajo = NULL;
                        auxCol = auxCol->sig;
                        if (auxCol == NULL)
                        {
                            // cout << "chau" << endl;
                            break;
                        }
                    }
                }
            }
            filas buscar = aux1->filas;
            while (true)
            {
                /*cout << "el valor de la fila -> " << buscar->dato_string << endl
                     << "valorTupla -> " << valorTupla << endl;*/
                if (buscar->dato_string == valorTupla)
                {
                    filas aux2 = buscar;
                    while (aux2->ant != NULL)
                    {
                        aux2 = aux2->ant;
                    }
                    filas borrar = NULL;
                    while (true)
                    {
                        borrar = aux2;
                        if (aux2->abajo != NULL)
                        {
                            aux2->abajo->arriba = aux2->arriba;
                            aux2->arriba->abajo = aux2->abajo;
                            aux2->abajo = NULL;
                            aux2->arriba = NULL;
                        }
                        else
                        {
                            aux2->arriba->abajo = NULL;
                            aux2->abajo = NULL;
                            aux2->arriba = NULL;
                        }
                        aux2 = aux2->sig;
                        delete borrar;
                        if (aux2 == NULL)
                        {
                            buscar = aux1->filas;
                            break;
                        }
                    }
                }
                else
                {
                    buscar = buscar->abajo;
                }
                if (buscar == NULL)
                {
                    // cout << "fin" << endl;
                    return;
                }
            }
        }
        break;
    case 3:
        if (aux1->tipo_dato == true)
        {

            // cout << "check" << endl;
            if (aux1->filas->dato_int < valorTuplaInt)
            {
                if (aux1->filas->abajo == NULL)
                {
                    columna auxCol = aux1;
                    filas aux2 = NULL;
                    while (auxCol->ant != NULL)
                    {
                        auxCol = auxCol->ant;
                    }
                    while (true)
                    {
                        aux2 = auxCol->filas;
                        auxCol->filas = NULL;
                        delete aux2;
                        auxCol = auxCol->sig;
                        if (auxCol == NULL)
                            return;
                    }
                }
                else
                {
                    columna auxCol = aux1;
                    filas borrar = NULL;
                    while (auxCol->ant != NULL)
                    {
                        auxCol = auxCol->ant;
                    }
                    while (true)
                    {
                        borrar = auxCol->filas;
                        auxCol->filas = borrar->abajo;
                        borrar->abajo->arriba = NULL;
                        borrar->abajo = NULL;
                        auxCol = auxCol->sig;
                        if (auxCol == NULL)
                        {
                            // cout << "chau" << endl;
                            break;
                        }
                    }
                }
            }
            filas buscar = aux1->filas;
            while (true)
            {
                /*cout << "el valor de la fila -> " << buscar->dato_int << endl
                     << "valorTupla -> " << valorTuplaInt << endl;*/
                if (buscar->dato_int < valorTuplaInt)
                {
                    filas aux2 = buscar;
                    while (aux2->ant != NULL)
                    {
                        aux2 = aux2->ant;
                    }
                    filas borrar = NULL;
                    while (true)
                    {
                        borrar = aux2;
                        if (aux2->abajo != NULL)
                        {
                            aux2->abajo->arriba = aux2->arriba;
                            aux2->arriba->abajo = aux2->abajo;
                            aux2->abajo = NULL;
                            aux2->arriba = NULL;
                        }
                        else
                        {
                            aux2->arriba->abajo = NULL;
                            aux2->abajo = NULL;
                            aux2->arriba = NULL;
                        }
                        aux2 = aux2->sig;
                        delete borrar;
                        if (aux2 == NULL)
                        {
                            buscar = aux1->filas;
                            break;
                        }
                    }
                }
                else
                {
                    buscar = buscar->abajo;
                }
                if (buscar == NULL)
                {
                    // cout << "fin" << endl;
                    return;
                }
            }
        }
        else
        {
            if (aux1->filas->dato_string < valorTupla)
            {
                if (aux1->filas->abajo == NULL)
                {
                    columna auxCol = aux1;
                    filas aux2 = NULL;
                    while (auxCol->ant != NULL)
                    {
                        auxCol = auxCol->ant;
                    }
                    while (true)
                    {
                        aux2 = auxCol->filas;
                        auxCol->filas = NULL;
                        delete aux2;
                        auxCol = auxCol->sig;
                        if (auxCol == NULL)
                            return;
                    }
                }
                else
                {
                    columna auxCol = aux1;
                    filas borrar = NULL;
                    while (auxCol->ant != NULL)
                    {
                        auxCol = auxCol->ant;
                    }
                    while (true)
                    {
                        borrar = auxCol->filas;
                        auxCol->filas = borrar->abajo;
                        borrar->abajo->arriba = NULL;
                        borrar->abajo = NULL;
                        auxCol = auxCol->sig;
                        if (auxCol == NULL)
                        {
                            // cout << "chau" << endl;
                            break;
                        }
                    }
                }
            }
            filas buscar = aux1->filas;
            while (true)
            {
                /*cout << "el valor de la fila -> " << buscar->dato_string << endl
                     << "valorTupla -> " << valorTupla << endl;*/
                if (buscar->dato_string < valorTupla)
                {
                    filas aux2 = buscar;
                    while (aux2->ant != NULL)
                    {
                        aux2 = aux2->ant;
                    }
                    filas borrar = NULL;
                    while (true)
                    {
                        borrar = aux2;
                        if (aux2->abajo != NULL)
                        {
                            aux2->abajo->arriba = aux2->arriba;
                            aux2->arriba->abajo = aux2->abajo;
                            aux2->abajo = NULL;
                            aux2->arriba = NULL;
                        }
                        else
                        {
                            aux2->arriba->abajo = NULL;
                            aux2->abajo = NULL;
                            aux2->arriba = NULL;
                        }
                        aux2 = aux2->sig;
                        delete borrar;
                        if (aux2 == NULL)
                        {
                            buscar = aux1->filas;
                            break;
                        }
                    }
                }
                else
                {
                    buscar = buscar->abajo;
                }
                if (buscar == NULL)
                {
                    // cout << "fin" << endl;
                    return;
                }
            }
        }
        break;
    case 1:
        if (aux1->tipo_dato == true)
        {

            // cout << "check" << endl;
            if (aux1->filas->dato_int != valorTuplaInt)
            {
                if (aux1->filas->abajo == NULL)
                {
                    columna auxCol = aux1;
                    filas aux2 = NULL;
                    while (auxCol->ant != NULL)
                    {
                        auxCol = auxCol->ant;
                    }
                    while (true)
                    {
                        aux2 = auxCol->filas;
                        auxCol->filas = NULL;
                        delete aux2;
                        auxCol = auxCol->sig;
                        if (auxCol == NULL)
                            return;
                    }
                }
                else
                {
                    columna auxCol = aux1;
                    filas borrar = NULL;
                    while (auxCol->ant != NULL)
                    {
                        auxCol = auxCol->ant;
                    }
                    while (true)
                    {
                        borrar = auxCol->filas;
                        auxCol->filas = borrar->abajo;
                        borrar->abajo->arriba = NULL;
                        borrar->abajo = NULL;
                        auxCol = auxCol->sig;
                        if (auxCol == NULL)
                        {
                            // cout << "chau" << endl;
                            break;
                        }
                    }
                }
            }
            filas buscar = aux1->filas;
            while (true)
            {
                /*cout << "el valor de la fila -> " << buscar->dato_int << endl
                     << "valorTupla -> " << valorTuplaInt << endl;*/
                if (buscar->dato_int != valorTuplaInt)
                {
                    filas aux2 = buscar;
                    while (aux2->ant != NULL)
                    {
                        aux2 = aux2->ant;
                    }
                    filas borrar = NULL;
                    while (true)
                    {
                        borrar = aux2;
                        if (aux2->abajo != NULL)
                        {
                            aux2->abajo->arriba = aux2->arriba;
                            aux2->arriba->abajo = aux2->abajo;
                            aux2->abajo = NULL;
                            aux2->arriba = NULL;
                        }
                        else
                        {
                            aux2->arriba->abajo = NULL;
                            aux2->abajo = NULL;
                            aux2->arriba = NULL;
                        }
                        aux2 = aux2->sig;
                        delete borrar;
                        if (aux2 == NULL)
                        {
                            buscar = aux1->filas;
                            break;
                        }
                    }
                }
                else
                {
                    buscar = buscar->abajo;
                }
                if (buscar == NULL)
                {
                    // cout << "fin" << endl;
                    return;
                }
            }
        }
        else
        {
            if (aux1->filas->dato_string != valorTupla)
            {
                if (aux1->filas->abajo == NULL)
                {
                    columna auxCol = aux1;
                    filas aux2 = NULL;
                    while (auxCol->ant != NULL)
                    {
                        auxCol = auxCol->ant;
                    }
                    while (true)
                    {
                        aux2 = auxCol->filas;
                        auxCol->filas = NULL;
                        delete aux2;
                        auxCol = auxCol->sig;
                        if (auxCol == NULL)
                            return;
                    }
                }
                else
                {
                    columna auxCol = aux1;
                    filas borrar = NULL;
                    while (auxCol->ant != NULL)
                    {
                        auxCol = auxCol->ant;
                    }
                    while (true)
                    {
                        borrar = auxCol->filas;
                        auxCol->filas = borrar->abajo;
                        borrar->abajo->arriba = NULL;
                        borrar->abajo = NULL;
                        auxCol = auxCol->sig;
                        if (auxCol == NULL)
                        {
                            // cout << "chau" << endl;
                            break;
                        }
                    }
                }
            }
            filas buscar = aux1->filas;
            while (true)
            {
                /*cout << "el valor de la fila -> " << buscar->dato_string << endl
                     << "valorTupla -> " << valorTupla << endl;*/
                if (buscar->dato_string != valorTupla)
                {
                    filas aux2 = buscar;
                    while (aux2->ant != NULL)
                    {
                        aux2 = aux2->ant;
                    }
                    filas borrar = NULL;
                    while (true)
                    {
                        borrar = aux2;
                        if (aux2->abajo != NULL)
                        {
                            aux2->abajo->arriba = aux2->arriba;
                            aux2->arriba->abajo = aux2->abajo;
                            aux2->abajo = NULL;
                            aux2->arriba = NULL;
                        }
                        else
                        {
                            aux2->arriba->abajo = NULL;
                            aux2->abajo = NULL;
                            aux2->arriba = NULL;
                        }
                        aux2 = aux2->sig;
                        delete borrar;
                        if (aux2 == NULL)
                        {
                            buscar = aux1->filas;
                            break;
                        }
                    }
                }
                else
                {
                    buscar = buscar->abajo;
                }
                if (buscar == NULL)
                {
                    cout << "fin" << endl;
                    return;
                }
            }
        }
        break;
    }
}

void updateTuplas(string nombreTabla, string condicionModificar, string columnaModificar, string valorModificar)
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

    Tabla aux = BD;
    columna aux1 = aux->columna;
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
            aux1 = aux->columna;
            break;
        }
        aux = aux->sig;
        if (aux == NULL)
        {
            cout << "No existe la tabla..." << nombreTabla << endl;
            return;
        }
    }
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
            return;
        }
    }

    filas buscar = aux1->filas;
    int valorTuplaInt = 0;
    if (aux1->tipo_dato == true)
    {
        valorTuplaInt = stoi(valorTupla);
        cout << "cambio int " << valorTupla << endl;
    }

    switch (condicion_)
    {
    case 4:
    {
        filas buscar = aux1->filas;
        if (aux1->tipo_dato == true)
        {
            while (true)
            {
                if (aux1->filas->dato_int != valorTuplaInt)
                {
                    if (aux1->filas->abajo == NULL)
                    {
                        cout << "No existe la fila que busca para modificar..." << endl;
                        break;
                    }
                }
                if (buscar->dato_int == valorTuplaInt)
                {
                    // cout << "Se encontro la fila a modificar..." << endl;
                    filas modificar = buscar;
                    columna colModificar = aux1;
                    while (colModificar->ant != NULL)
                    {
                        colModificar = colModificar->ant;
                        modificar = modificar->ant;
                    }
                    while (true)
                    {
                        if (colModificar->nombreColumna == columnaModificar)
                        {
                            // cout << "Se encontro la columna a modificar..." << endl;
                            break;
                        }
                        else
                        {
                            colModificar = colModificar->sig;
                            modificar = modificar->sig;
                        }
                        if (colModificar == NULL)
                        {
                            // cout << "NO se encontro la columna a modificar..." << endl;
                            return;
                        }
                    }
                    if ((colModificar->primary_key || colModificar->nn) && valorModificar == "")
                    {
                        cout << "NO se puede insertar un valor nulo en esta columna..." << endl;
                        return;
                    }
                    if (colModificar->tipo_dato)
                    {
                        int aux = stoi(valorModificar);
                        modificar->dato_int = aux;
                        // cout << "aaaa" << endl;
                    }
                    else
                    {
                        modificar->dato_string = valorModificar;
                        // cout << "bbbb" << endl;
                    }
                }

                buscar = buscar->abajo;
                if (buscar == NULL)
                {
                    // cout << "No se encontro la fila buscada para modificar..." << endl;
                    break;
                }
            }
        }
        else
        {
            while (true)
            {
                if (aux1->filas->dato_string != valorTupla)
                {
                    if (aux1->filas->abajo == NULL)
                    {
                        cout << "No existe la fila que busca para modificar..." << endl;
                        break;
                    }
                }
                if (buscar->dato_string == valorTupla)
                {
                    cout << "Se encontro la fila a modificar..." << endl;
                    // asi mando el puntero al inicio???
                    filas modificar = buscar;
                    columna colModificar = aux1;
                    while (colModificar->ant != NULL)
                    {
                        colModificar = colModificar->ant;
                        modificar = modificar->ant;
                    }
                    while (true)
                    {
                        if (colModificar->nombreColumna == columnaModificar)
                        {
                            cout << "Se encontro la columna a modificar..." << endl;
                            break;
                        }
                        else
                        {
                            colModificar = colModificar->sig;
                            modificar = modificar->sig;
                        }
                        if (colModificar == NULL)
                        {
                            cout << "NO se encontro la columna a modificar..." << endl;
                            return;
                        }
                    }
                    if ((colModificar->primary_key || colModificar->nn) && valorModificar == "")
                    {
                        cout << "NO se puede insertar un valor nulo en esta columna..." << endl;
                        return;
                    }
                    if (colModificar->tipo_dato)
                    {
                        int aux = stoi(valorModificar);
                        modificar->dato_int = aux;
                    }
                    else
                    {
                        modificar->dato_string = valorModificar;
                    }
                }
                buscar = buscar->abajo;
                if (buscar == NULL)
                {
                    cout << "No se encontro la fila buscada para modificar..." << endl;
                    break;
                }
            }
        }
    }
    case 1:
    {
        filas buscar = aux1->filas;
        if (aux1->tipo_dato == true)
        {
            while (true)
            {
                if (aux1->filas->dato_int != valorTuplaInt)
                {
                    if (aux1->filas->abajo == NULL)
                    {
                        cout << "No existe la fila que busca para modificar..." << endl;
                        break;
                    }
                }
                if (buscar->dato_int != valorTuplaInt)
                {
                    // cout << "Se encontro la fila a modificar..." << endl;
                    filas modificar = buscar;
                    columna colModificar = aux1;
                    while (colModificar->ant != NULL)
                    {
                        colModificar = colModificar->ant;
                        modificar = modificar->ant;
                    }
                    while (true)
                    {
                        if (colModificar->nombreColumna == columnaModificar)
                        {
                            // cout << "Se encontro la columna a modificar..." << endl;
                            break;
                        }
                        else
                        {
                            colModificar = colModificar->sig;
                            modificar = modificar->sig;
                        }
                        if (colModificar == NULL)
                        {
                            // cout << "NO se encontro la columna a modificar..." << endl;
                            return;
                        }
                    }
                    if ((colModificar->primary_key || colModificar->nn) && valorModificar == "")
                    {
                        cout << "NO se puede insertar un valor nulo en esta columna..." << endl;
                        return;
                    }
                    if (colModificar->tipo_dato)
                    {
                        int aux = stoi(valorModificar);
                        modificar->dato_int = aux;
                        // cout << "aaaa" << endl;
                    }
                    else
                    {
                        modificar->dato_string = valorModificar;
                        // cout << "bbbb" << endl;
                    }
                }

                buscar = buscar->abajo;
                if (buscar == NULL)
                {
                    // cout << "No se encontro la fila buscada para modificar..." << endl;
                    break;
                }
            }
        }
        else
        {
            while (true)
            {
                if (aux1->filas->dato_string != valorTupla)
                {
                    if (aux1->filas->abajo == NULL)
                    {
                        cout << "No existe la fila que busca para modificar..." << endl;
                        break;
                    }
                }
                if (buscar->dato_string != valorTupla)
                {
                    cout << "Se encontro la fila a modificar..." << endl;
                    // asi mando el puntero al inicio???
                    filas modificar = buscar;
                    columna colModificar = aux1;
                    while (colModificar->ant != NULL)
                    {
                        colModificar = colModificar->ant;
                        modificar = modificar->ant;
                    }
                    while (true)
                    {
                        if (colModificar->nombreColumna == columnaModificar)
                        {
                            cout << "Se encontro la columna a modificar..." << endl;
                            break;
                        }
                        else
                        {
                            colModificar = colModificar->sig;
                            modificar = modificar->sig;
                        }
                        if (colModificar == NULL)
                        {
                            cout << "NO se encontro la columna a modificar..." << endl;
                            return;
                        }
                    }
                    if ((colModificar->primary_key || colModificar->nn) && valorModificar == "")
                    {
                        cout << "NO se puede insertar un valor nulo en esta columna..." << endl;
                        return;
                    }
                    if (colModificar->tipo_dato)
                    {
                        int aux = stoi(valorModificar);
                        modificar->dato_int = aux;
                    }
                    else
                    {
                        modificar->dato_string = valorModificar;
                    }
                }
                buscar = buscar->abajo;
                if (buscar == NULL)
                {
                    cout << "No se encontro la fila buscada para modificar..." << endl;
                    break;
                }
            }
        }
    }
    case 2:
    {
        filas buscar = aux1->filas;
        if (aux1->tipo_dato == true)
        {
            while (true)
            {
                if (aux1->filas->dato_int != valorTuplaInt)
                {
                    if (aux1->filas->abajo == NULL)
                    {
                        cout << "No existe la fila que busca para modificar..." << endl;
                        break;
                    }
                }
                if (buscar->dato_int > valorTuplaInt)
                {
                    // cout << "Se encontro la fila a modificar..." << endl;
                    filas modificar = buscar;
                    columna colModificar = aux1;
                    while (colModificar->ant != NULL)
                    {
                        colModificar = colModificar->ant;
                        modificar = modificar->ant;
                    }
                    while (true)
                    {
                        if (colModificar->nombreColumna == columnaModificar)
                        {
                            // cout << "Se encontro la columna a modificar..." << endl;
                            break;
                        }
                        else
                        {
                            colModificar = colModificar->sig;
                            modificar = modificar->sig;
                        }
                        if (colModificar == NULL)
                        {
                            // cout << "NO se encontro la columna a modificar..." << endl;
                            return;
                        }
                    }
                    if ((colModificar->primary_key || colModificar->nn) && valorModificar == "")
                    {
                        cout << "NO se puede insertar un valor nulo en esta columna..." << endl;
                        return;
                    }
                    if (colModificar->tipo_dato)
                    {
                        int aux = stoi(valorModificar);
                        modificar->dato_int = aux;
                        // cout << "aaaa" << endl;
                    }
                    else
                    {
                        modificar->dato_string = valorModificar;
                        // cout << "bbbb" << endl;
                    }
                }

                buscar = buscar->abajo;
                if (buscar == NULL)
                {
                    // cout << "No se encontro la fila buscada para modificar..." << endl;
                    break;
                }
            }
        }
        else
        {
            while (true)
            {
                if (aux1->filas->dato_string != valorTupla)
                {
                    if (aux1->filas->abajo == NULL)
                    {
                        cout << "No existe la fila que busca para modificar..." << endl;
                        break;
                    }
                }
                if (buscar->dato_string > valorTupla)
                {
                    cout << "Se encontro la fila a modificar..." << endl;
                    // asi mando el puntero al inicio???
                    filas modificar = buscar;
                    columna colModificar = aux1;
                    while (colModificar->ant != NULL)
                    {
                        colModificar = colModificar->ant;
                        modificar = modificar->ant;
                    }
                    while (true)
                    {
                        if (colModificar->nombreColumna == columnaModificar)
                        {
                            cout << "Se encontro la columna a modificar..." << endl;
                            break;
                        }
                        else
                        {
                            colModificar = colModificar->sig;
                            modificar = modificar->sig;
                        }
                        if (colModificar == NULL)
                        {
                            cout << "NO se encontro la columna a modificar..." << endl;
                            return;
                        }
                    }
                    if ((colModificar->primary_key || colModificar->nn) && valorModificar == "")
                    {
                        cout << "NO se puede insertar un valor nulo en esta columna..." << endl;
                        return;
                    }
                    if (colModificar->tipo_dato)
                    {
                        int aux = stoi(valorModificar);
                        modificar->dato_int = aux;
                    }
                    else
                    {
                        modificar->dato_string = valorModificar;
                    }
                }
                buscar = buscar->abajo;
                if (buscar == NULL)
                {
                    cout << "No se encontro la fila buscada para modificar..." << endl;
                    break;
                }
            }
        }
    }
    case 3:
    {
        filas buscar = aux1->filas;
        if (aux1->tipo_dato == true)
        {
            while (true)
            {
                if (aux1->filas->dato_int != valorTuplaInt)
                {
                    if (aux1->filas->abajo == NULL)
                    {
                        cout << "No existe la fila que busca para modificar..." << endl;
                        break;
                    }
                }
                if (buscar->dato_int < valorTuplaInt)
                {
                    // cout << "Se encontro la fila a modificar..." << endl;
                    filas modificar = buscar;
                    columna colModificar = aux1;
                    while (colModificar->ant != NULL)
                    {
                        colModificar = colModificar->ant;
                        modificar = modificar->ant;
                    }
                    while (true)
                    {
                        if (colModificar->nombreColumna == columnaModificar)
                        {
                            // cout << "Se encontro la columna a modificar..." << endl;
                            break;
                        }
                        else
                        {
                            colModificar = colModificar->sig;
                            modificar = modificar->sig;
                        }
                        if (colModificar == NULL)
                        {
                            // cout << "NO se encontro la columna a modificar..." << endl;
                            return;
                        }
                    }
                    if ((colModificar->primary_key || colModificar->nn) && valorModificar == "")
                    {
                        cout << "NO se puede insertar un valor nulo en esta columna..." << endl;
                        return;
                    }
                    if (colModificar->tipo_dato)
                    {
                        int aux = stoi(valorModificar);
                        modificar->dato_int = aux;
                        // cout << "aaaa" << endl;
                    }
                    else
                    {
                        modificar->dato_string = valorModificar;
                        // cout << "bbbb" << endl;
                    }
                }

                buscar = buscar->abajo;
                if (buscar == NULL)
                {
                    // cout << "No se encontro la fila buscada para modificar..." << endl;
                    break;
                }
            }
        }
        else
        {
            while (true)
            {
                if (aux1->filas->dato_string != valorTupla)
                {
                    if (aux1->filas->abajo == NULL)
                    {
                        cout << "No existe la fila que busca para modificar..." << endl;
                        break;
                    }
                }
                if (buscar->dato_string < valorTupla)
                {
                    cout << "Se encontro la fila a modificar..." << endl;
                    // asi mando el puntero al inicio???
                    filas modificar = buscar;
                    columna colModificar = aux1;
                    while (colModificar->ant != NULL)
                    {
                        colModificar = colModificar->ant;
                        modificar = modificar->ant;
                    }
                    while (true)
                    {
                        if (colModificar->nombreColumna == columnaModificar)
                        {
                            cout << "Se encontro la columna a modificar..." << endl;
                            break;
                        }
                        else
                        {
                            colModificar = colModificar->sig;
                            modificar = modificar->sig;
                        }
                        if (colModificar == NULL)
                        {
                            cout << "NO se encontro la columna a modificar..." << endl;
                            return;
                        }
                    }
                    if ((colModificar->primary_key || colModificar->nn) && valorModificar == "")
                    {
                        cout << "NO se puede insertar un valor nulo en esta columna..." << endl;
                        return;
                    }
                    if (colModificar->tipo_dato)
                    {
                        int aux = stoi(valorModificar);
                        modificar->dato_int = aux;
                    }
                    else
                    {
                        modificar->dato_string = valorModificar;
                    }
                }
                buscar = buscar->abajo;
                if (buscar == NULL)
                {
                    cout << "No se encontro la fila buscada para modificar..." << endl;
                    break;
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
    // cout << columnas << endl;
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
        // cout << "cree la columna " << copiarColumna->nombreColumna << endl;
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
                // cout << aux1->nombreColumna << endl;
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

    // cout << condicion_ << endl;
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
            filas copiarFila = buscar;
            columna aux1 = aux->columna;
            while (copiarFila->ant)
            {
                copiarFila = copiarFila->ant;
            }
            while (true)
            {
                // cout << "el valor es... " << val << endl;
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

void unionTable(string nombreTabla1, string nombreTabla2, string nombreTabla3)
{
    if (nombreTabla1 == "" || nombreTabla2 == "" || nombreTabla3 == "")
    {
        cout << "ERROR - Uno o varios de los campos es vacio por ende no se puede enfectuar el UNION" << endl;
        return;
    }
    Tabla aux = BD;
    if (aux == NULL)
    {
        cout << "No existen tablas..." << endl;
        return;
    }
    Tabla tabla1 = NULL;
    while (true)
    {
        if (aux->nombreTabla == nombreTabla1)
        {
            if (aux->columna == NULL)
            {
                cout << "No existen columnas..." << endl;
                return;
            }
            tabla1 = aux;
            aux = BD;
            break;
        }
        aux = aux->sig;
        if (aux == NULL)
        {
            cout << "No existe la tabla..." << nombreTabla1 << endl;
            return;
        }
    }

    Tabla tabla2 = NULL;
    while (true)
    {
        if (aux->nombreTabla == nombreTabla2)
        {
            if (aux->columna == NULL)
            {
                cout << "No existen columnas..." << endl;
                return;
            }
            tabla2 = aux;
            aux = BD;
            break;
        }
        aux = aux->sig;
        if (aux == NULL)
        {
            cout << "No existe la tabla..." << nombreTabla2 << endl;
            return;
        }
    }

    while (aux != NULL)
    {
        if (aux->nombreTabla == nombreTabla3)
        {
            cout << "Ya existe una tabla llamada " << nombreTabla3 << endl;
            return;
        }
        aux = aux->sig;
    }

    columna auxCol1 = tabla1->columna;
    columna auxCol2 = tabla2->columna;

    while (true)
    {
        if ((auxCol1 == NULL && auxCol2 != NULL) || (auxCol1 != NULL && auxCol2 == NULL))
        {
            cout << "Ambas tablas no tienen igual esquema..." << endl;
            return;
        }
        if (auxCol1->nombreColumna != auxCol2->nombreColumna)
        {
            cout << "Ambas tablas no tienen igual esquema..." << endl;
            return;
        }
        if ((auxCol1->tipo_dato == true && auxCol2->tipo_dato == false) || (auxCol1->tipo_dato == false && auxCol2->tipo_dato == true))
        {
            cout << "Ambas tablas no tienen igual esquema..." << endl;
            return;
        }
        if ((auxCol1->primary_key == true && auxCol2->primary_key == false) || (auxCol1->primary_key == false && auxCol2->primary_key == true))
        {
            cout << "Ambas tablas no tienen igual esquema..." << endl;
            return;
        }
        if ((auxCol1->nn == true && auxCol2->nn == false) || (auxCol1->nn == false && auxCol2->nn == true))
        {
            cout << "Ambas tablas no tienen igual esquema..." << endl;
            return;
        }
        auxCol1 = auxCol1->sig;
        auxCol2 = auxCol2->sig;

        if (auxCol1 == NULL && auxCol2 == NULL)
        {
            auxCol1 = tabla1->columna;
            auxCol2 = tabla2->columna;
            cout << "Los esquemas son iguales" << endl
                 << endl;
            break;
        }
    }

    createTable(nombreTabla3);
    while (true)
    {
        string tipoDato;
        string calificador;
        if (auxCol1->tipo_dato == true)
        {
            tipoDato = "int";
        }
        else
        {
            tipoDato = "string";
        }

        if (auxCol1->primary_key == true)
        {
            calificador = "primary_key";
        }
        else
        {
            if (auxCol1->nn == true)
            {
                calificador = "nn";
            }
            else
            {
                calificador = "any";
            }
        }
        addCol(nombreTabla3, auxCol1->nombreColumna, tipoDato, calificador);
        auxCol1 = auxCol1->sig;
        tipoDato = "";
        calificador = "";

        if (auxCol1 == NULL)
        {
            cout << "Creo las columnas" << endl;
            break;
        }
    }
    auxCol1 = tabla1->columna;
    filas auxFilas = auxCol1->filas;
    filas copiar = auxFilas;
    string insertColumna = "";
    string insertFila = "";
    while (true)
    {
        if (insertColumna == "")
        {
            insertColumna = auxCol1->nombreColumna;
        }
        else
        {
            insertColumna = insertColumna + ":" + auxCol1->nombreColumna;
        }
        auxCol1 = auxCol1->sig;
        if (auxCol1 == NULL)
        {
            auxCol1 = tabla1->columna;
            break;
        }
    }

    if (auxFilas != NULL)
    {
        cout << endl
             << "[ "
             << nombreTabla1 << " ] Tiene tuplas..." << endl
             << endl;
        while (true)
        {
            auxCol1 = tabla1->columna;
            copiar = auxFilas;
            // cout << "1" << endl;
            while (true)
            {
                // cout << "2" << endl;
                if (auxCol1->tipo_dato)
                {
                    if (copiar->dato_int != empty)
                    {
                        string auxInsert;
                        stringstream ss;
                        ss << copiar->dato_int;
                        auxInsert = ss.str();
                        if (insertFila == "")
                        {
                            insertFila = auxInsert;
                        }
                        else
                        {
                            insertFila = insertFila + ":" + auxInsert;
                        }
                        copiar = copiar->sig;
                        auxCol1 = auxCol1->sig;
                    }
                    else
                    {
                        if (insertFila == "")
                        {
                            insertFila = ":";
                        }
                        else
                        {
                            insertFila = insertFila + ":";
                        }
                        copiar = copiar->sig;
                        auxCol1 = auxCol1->sig;
                    }
                }
                else
                {
                    if (copiar->dato_string != "")
                    {
                        if (insertFila == "")
                        {
                            insertFila = copiar->dato_string;
                        }
                        else
                        {
                            insertFila = insertFila + ":" + copiar->dato_string;
                        }
                        copiar = copiar->sig;
                        auxCol1 = auxCol1->sig;
                    }
                    else
                    {
                        if (insertFila == "")
                        {
                            insertFila = ":";
                        }
                        else
                        {
                            insertFila = insertFila + ":";
                        }
                        copiar = copiar->sig;
                        auxCol1 = auxCol1->sig;
                    }
                }
                if (copiar == NULL)
                {
                    cout << "Termine de copiar la tupla" << endl;
                    break;
                }
            }
            /*cout << "insertColumna -> " << insertColumna << endl
                 << "insertFila -> " << insertFila << endl
                 << endl;*/
            insertInto(nombreTabla3, insertColumna, insertFila);
            insertFila = "";
            auxFilas = auxFilas->abajo;
            if (auxFilas == NULL)
            {
                // cout << "Termine de copiar la primera tabla" << endl;
                break;
            }
        }
    }
    auxCol2 = tabla2->columna;
    filas auxFilas2 = auxCol2->filas;
    filas copiar2 = auxFilas2;
    string insertFila2 = "";
    if (auxFilas2 != NULL)
    {
        cout << endl
             << "[ "
             << nombreTabla1 << " ] Tiene tuplas..." << endl
             << endl;
        while (true)
        {
            auxCol2 = tabla1->columna;
            copiar2 = auxFilas2;
            // cout << "1" << endl;
            while (true)
            {
                // cout << "2" << endl;
                if (auxCol2->tipo_dato)
                {
                    if (copiar2->dato_int != empty)
                    {
                        string auxInsert;
                        stringstream ss;
                        ss << copiar2->dato_int;
                        auxInsert = ss.str();
                        if (insertFila2 == "")
                        {
                            insertFila2 = auxInsert;
                        }
                        else
                        {
                            insertFila2 = insertFila2 + ":" + auxInsert;
                        }
                        copiar2 = copiar2->sig;
                        auxCol2 = auxCol2->sig;
                    }
                    else
                    {
                        copiar2 = copiar2->sig;
                        auxCol2 = auxCol2->sig;
                    }
                }
                else
                {
                    if (copiar2->dato_string != "")
                    {
                        if (insertFila2 == "")
                        {
                            insertFila2 = copiar2->dato_string;
                        }
                        else
                        {
                            insertFila2 = insertFila2 + ":" + copiar2->dato_string;
                        }
                        copiar2 = copiar2->sig;
                        auxCol2 = auxCol2->sig;
                    }
                    else
                    {
                        copiar2 = copiar2->sig;
                        auxCol2 = auxCol2->sig;
                    }
                }
                if (copiar2 == NULL)
                {
                    // cout << "Termine de copiar2 la tupla" << endl;
                    break;
                }
            }
            /*cout << "insertColumna -> " << insertColumna << endl
                 << "insertFila -> " << insertFila2 << endl
                 << endl;*/
            insertInto(nombreTabla3, insertColumna, insertFila2);
            insertFila2 = "";
            auxFilas2 = auxFilas2->abajo;
            if (auxFilas2 == NULL)
            {
                cout << "Termine de copiar la primera tabla" << endl;
                break;
            }
        }
    }
    else
    {
        cout << endl
             << "[ "
             << nombreTabla1 << " ] No tiene tuplas..." << endl
             << endl;
    }
}

void intersect(string nombreTabla1, string nombreTabla2, string nombreTabla3)
{
    if (nombreTabla1 == "" || nombreTabla2 == "" || nombreTabla3 == "")
    {
        cout << "ERROR - Uno o varios de los campos es vacio por ende no se puede enfectuar el UNION" << endl;
        return;
    }
    Tabla aux = BD;
    if (aux == NULL)
    {
        cout << "No existen tablas..." << endl;
        return;
    }
    Tabla tabla1 = NULL;
    while (true)
    {
        if (aux->nombreTabla == nombreTabla1)
        {
            if (aux->columna == NULL)
            {
                cout << "No existen columnas..." << endl;
                return;
            }
            tabla1 = aux;
            aux = BD;
            break;
        }
        aux = aux->sig;
        if (aux == NULL)
        {
            cout << "No existe la tabla..." << nombreTabla1 << endl;
            return;
        }
    }

    Tabla tabla2 = NULL;
    while (true)
    {
        if (aux->nombreTabla == nombreTabla2)
        {
            if (aux->columna == NULL)
            {
                cout << "No existen columnas..." << endl;
                return;
            }
            tabla2 = aux;
            aux = BD;
            break;
        }
        aux = aux->sig;
        if (aux == NULL)
        {
            cout << "No existe la tabla..." << nombreTabla2 << endl;
            return;
        }
    }

    while (aux != NULL)
    {
        if (aux->nombreTabla == nombreTabla3)
        {
            cout << "Ya existe una tabla llamada " << nombreTabla3 << endl;
            return;
        }
        aux = aux->sig;
    }

    columna auxCol1 = tabla1->columna;
    columna auxCol2 = tabla2->columna;

    while (true)
    {
        if ((auxCol1 == NULL && auxCol2 != NULL) || (auxCol1 != NULL && auxCol2 == NULL))
        {
            cout << "Ambas tablas no tienen igual esquema..." << endl;
            return;
        }
        if (auxCol1->nombreColumna != auxCol2->nombreColumna)
        {
            cout << "Ambas tablas no tienen igual esquema..." << endl;
            return;
        }
        if ((auxCol1->tipo_dato == true && auxCol2->tipo_dato == false) || (auxCol1->tipo_dato == false && auxCol2->tipo_dato == true))
        {
            cout << "Ambas tablas no tienen igual esquema..." << endl;
            return;
        }
        if ((auxCol1->primary_key == true && auxCol2->primary_key == false) || (auxCol1->primary_key == false && auxCol2->primary_key == true))
        {
            cout << "Ambas tablas no tienen igual esquema..." << endl;
            return;
        }
        if ((auxCol1->nn == true && auxCol2->nn == false) || (auxCol1->nn == false && auxCol2->nn == true))
        {
            cout << "Ambas tablas no tienen igual esquema..." << endl;
            return;
        }
        auxCol1 = auxCol1->sig;
        auxCol2 = auxCol2->sig;

        if (auxCol1 == NULL && auxCol2 == NULL)
        {
            auxCol1 = tabla1->columna;
            auxCol2 = tabla2->columna;
            cout << "Los esquemas son iguales" << endl
                 << endl;
            break;
        }
    }

    createTable(nombreTabla3);
    while (true)
    {
        string tipoDato;
        string calificador;
        if (auxCol1->tipo_dato == true)
        {
            tipoDato = "int";
        }
        else
        {
            tipoDato = "string";
        }

        if (auxCol1->primary_key == true)
        {
            calificador = "primary_key";
        }
        else
        {
            if (auxCol1->nn == true)
            {
                calificador = "nn";
            }
            else
            {
                calificador = "any";
            }
        }
        addCol(nombreTabla3, auxCol1->nombreColumna, tipoDato, calificador);
        auxCol1 = auxCol1->sig;
        tipoDato = "";
        calificador = "";

        if (auxCol1 == NULL)
        {
            cout << "Creo las columnas" << endl;
            break;
        }
    }

    auxCol1 = tabla1->columna;
    string insertColumna = "";
    string insertFila = "";
    while (true)
    {
        if (insertColumna == "")
        {
            insertColumna = auxCol1->nombreColumna;
        }
        else
        {
            insertColumna = insertColumna + ":" + auxCol1->nombreColumna;
        }
        auxCol1 = auxCol1->sig;
        if (auxCol1 == NULL)
        {
            auxCol1 = tabla1->columna;
            break;
        }
    }

    cout << insertColumna << endl
         << endl;

    cout << tabla1->nombreTabla << endl
         << tabla2->nombreTabla << endl;
    filas buscar1 = tabla1->columna->filas;
    filas buscar2 = tabla2->columna->filas;
    columna col = tabla1->columna;

    if (buscar1 == NULL)
    {
        cout << "NO existen filas para realizar el intersect..." << endl;
        return;
    }

    while (buscar1 != NULL)
    {
        while (buscar2 != NULL)
        {
            if (col->tipo_dato)
            {
                if (buscar1->dato_int == buscar2->dato_int)
                {
                    cout << buscar1->dato_int << " - coincide con - " << buscar2->dato_int << endl;
                    filas verificar1 = buscar1;
                    filas verificar2 = buscar2;
                    columna verificarCol = col;
                    while (verificarCol != NULL)
                    {
                        if (verificarCol->tipo_dato)
                        {
                            if (verificar1->dato_int != verificar2->dato_int)
                            {
                                cout << "las filas son distintas" << endl;
                                break;
                            }
                            else if (verificarCol->sig == NULL)
                            {
                                cout << "las filas son iguales" << endl;
                                filas copiar = buscar1;
                                columna copiarCol = tabla1->columna;
                                string insertValores = "";
                                while (copiarCol != NULL)
                                {
                                    if (copiarCol->tipo_dato)
                                    {
                                        stringstream ss;
                                        string aux;
                                        if (copiar->dato_int == empty)
                                        {
                                            insertValores = insertValores + ":";
                                        }
                                        else
                                        {
                                            ss << copiar->dato_int;
                                            aux = ss.str();
                                            if (insertValores == "")
                                            {
                                                insertValores = aux;
                                            }
                                            else
                                            {
                                                insertValores = insertValores + ":" + aux;
                                            }
                                        }
                                    }
                                    else
                                    {
                                        if (copiar->dato_string == "")
                                        {
                                            insertValores = insertValores + ":";
                                        }
                                        else
                                        {
                                            if (insertValores == "")
                                            {
                                                insertValores = copiar->dato_string;
                                            }
                                            else
                                            {
                                                insertValores = insertValores + ":" + copiar->dato_string;
                                            }
                                        }
                                    }
                                    copiarCol = copiarCol->sig;
                                    copiar = copiar->sig;
                                }
                                cout << insertValores << endl;
                                insertInto(nombreTabla3, insertColumna, insertValores);
                                break;
                            }
                        }
                        else
                        {
                            if (verificar1->dato_string != verificar2->dato_string)
                            {
                                cout << "las filas son distintas" << endl;
                                break;
                            }
                            else if (verificarCol->sig == NULL)
                            {
                                cout << "las filas son iguales" << endl;
                                filas copiar = buscar1;
                                columna copiarCol = tabla1->columna;
                                string insertValores = "";
                                while (copiarCol != NULL)
                                {
                                    if (copiarCol->tipo_dato)
                                    {
                                        stringstream ss;
                                        string aux;
                                        if (copiar->dato_int == empty)
                                        {
                                            insertValores = insertValores + ":";
                                        }
                                        else
                                        {
                                            ss << copiar->dato_int;
                                            aux = ss.str();
                                            if (insertValores == "")
                                            {
                                                insertValores = aux;
                                            }
                                            else
                                            {
                                                insertValores = insertValores + ":" + aux;
                                            }
                                        }
                                    }
                                    else
                                    {
                                        if (copiar->dato_string == "")
                                        {
                                            insertValores = insertValores + ":";
                                        }
                                        else
                                        {
                                            if (insertValores == "")
                                            {
                                                insertValores = copiar->dato_string;
                                            }
                                            else
                                            {
                                                insertValores = insertValores + ":" + copiar->dato_string;
                                            }
                                        }
                                    }
                                    copiarCol = copiarCol->sig;
                                    copiar = copiar->sig;
                                }
                                cout << insertValores << endl;
                                insertInto(nombreTabla3, insertColumna, insertValores);
                                break;
                            }
                        }
                        verificar1 = verificar1->sig;
                        verificar2 = verificar2->sig;
                        verificarCol = verificarCol->sig;
                    }
                    buscar2 = buscar2->abajo;
                }
                else
                {
                    buscar2 = buscar2->abajo;
                }
            }
            else
            {
                if (buscar1->dato_string == buscar2->dato_string)
                {
                    cout << buscar1->dato_string << " - coincide con - " << buscar2->dato_string << endl;
                    buscar2 = buscar2->abajo;
                }
                else
                {
                    buscar2 = buscar2->abajo;
                }
            }
        }
        buscar1 = buscar1->abajo;
        buscar2 = tabla2->columna->filas;
        cout << endl;
    }

    cout << endl;
}

void minusTable(string nombreTabla1, string nombreTabla2, string nombreTabla3)
{
    if (nombreTabla1 == "" || nombreTabla2 == "" || nombreTabla3 == "")
    {
        cout << "ERROR - Uno o varios de los campos es vacio por ende no se puede enfectuar el UNION" << endl;
        return;
    }
    Tabla aux = BD;
    if (aux == NULL)
    {
        cout << "No existen tablas..." << endl;
        return;
    }
    Tabla tabla1 = NULL;
    while (true)
    {
        if (aux->nombreTabla == nombreTabla1)
        {
            if (aux->columna == NULL)
            {
                cout << "No existen columnas..." << endl;
                return;
            }
            tabla1 = aux;
            aux = BD;
            break;
        }
        aux = aux->sig;
        if (aux == NULL)
        {
            cout << "No existe la tabla..." << nombreTabla1 << endl;
            return;
        }
    }

    Tabla tabla2 = NULL;
    while (true)
    {
        if (aux->nombreTabla == nombreTabla2)
        {
            if (aux->columna == NULL)
            {
                cout << "No existen columnas..." << endl;
                return;
            }
            tabla2 = aux;
            aux = BD;
            break;
        }
        aux = aux->sig;
        if (aux == NULL)
        {
            cout << "No existe la tabla..." << nombreTabla2 << endl;
            return;
        }
    }

    while (aux != NULL)
    {
        if (aux->nombreTabla == nombreTabla3)
        {
            cout << "Ya existe una tabla llamada " << nombreTabla3 << endl;
            return;
        }
        aux = aux->sig;
    }

    columna auxCol1 = tabla1->columna;
    columna auxCol2 = tabla2->columna;

    while (true)
    {
        if ((auxCol1 == NULL && auxCol2 != NULL) || (auxCol1 != NULL && auxCol2 == NULL))
        {
            cout << "Ambas tablas no tienen igual esquema..." << endl;
            return;
        }
        if (auxCol1->nombreColumna != auxCol2->nombreColumna)
        {
            cout << "Ambas tablas no tienen igual esquema..." << endl;
            return;
        }
        if ((auxCol1->tipo_dato == true && auxCol2->tipo_dato == false) || (auxCol1->tipo_dato == false && auxCol2->tipo_dato == true))
        {
            cout << "Ambas tablas no tienen igual esquema..." << endl;
            return;
        }
        if ((auxCol1->primary_key == true && auxCol2->primary_key == false) || (auxCol1->primary_key == false && auxCol2->primary_key == true))
        {
            cout << "Ambas tablas no tienen igual esquema..." << endl;
            return;
        }
        if ((auxCol1->nn == true && auxCol2->nn == false) || (auxCol1->nn == false && auxCol2->nn == true))
        {
            cout << "Ambas tablas no tienen igual esquema..." << endl;
            return;
        }
        auxCol1 = auxCol1->sig;
        auxCol2 = auxCol2->sig;

        if (auxCol1 == NULL && auxCol2 == NULL)
        {
            auxCol1 = tabla1->columna;
            auxCol2 = tabla2->columna;
            cout << "Los esquemas son iguales" << endl
                 << endl;
            break;
        }
    }

    createTable(nombreTabla3);
    while (true)
    {
        string tipoDato;
        string calificador;
        if (auxCol1->tipo_dato == true)
        {
            tipoDato = "int";
        }
        else
        {
            tipoDato = "string";
        }

        if (auxCol1->primary_key == true)
        {
            calificador = "primary_key";
        }
        else
        {
            if (auxCol1->nn == true)
            {
                calificador = "nn";
            }
            else
            {
                calificador = "any";
            }
        }
        addCol(nombreTabla3, auxCol1->nombreColumna, tipoDato, calificador);
        auxCol1 = auxCol1->sig;
        tipoDato = "";
        calificador = "";

        if (auxCol1 == NULL)
        {
            cout << "Creo las columnas" << endl;
            break;
        }
    }
    auxCol1 = tabla1->columna;
    filas auxFilas = auxCol1->filas;
    filas copiar = auxFilas;
    string insertColumna = "";
    string insertFila = "";
    while (true)
    {
        if (insertColumna == "")
        {
            insertColumna = auxCol1->nombreColumna;
        }
        else
        {
            insertColumna = insertColumna + ":" + auxCol1->nombreColumna;
        }
        auxCol1 = auxCol1->sig;
        if (auxCol1 == NULL)
        {
            auxCol1 = tabla1->columna;
            break;
        }
    }

    filas buscar1 = tabla1->columna->filas;
    filas buscar2 = tabla2->columna->filas;
    columna col = tabla1->columna;
    bool existe = false;
    if (buscar1 == NULL)
    {
        cout << "NO existen filas para realizar el intersect..." << endl;
        return;
    }

    while (buscar1 != NULL)
    {
        while (buscar2 != NULL)
        {
            if (col->tipo_dato)
            {
                if (buscar1->dato_int == buscar2->dato_int)
                {
                    cout << buscar1->dato_int << " - coincide con - " << buscar2->dato_int << endl;
                    filas verificar1 = buscar1;
                    filas verificar2 = buscar2;
                    columna verificarCol = col;
                    while (verificarCol != NULL)
                    {
                        if (verificarCol->tipo_dato)
                        {
                            if (verificar1->dato_int != verificar2->dato_int)
                            {
                                cout << "las filas son distintas" << endl;
                                break;
                            }
                            else if (verificarCol->sig == NULL)
                            {
                                cout << "las filas son iguales" << endl;
                                existe = true;
                                break;
                            }
                        }
                        else
                        {
                            if (verificar1->dato_string != verificar2->dato_string)
                            {
                                cout << "las filas son distintas" << endl;
                                break;
                            }
                            else if (verificarCol->sig == NULL)
                            {
                                cout << "las filas son iguales" << endl;
                                existe = true;
                                break;
                            }
                        }
                        verificar1 = verificar1->sig;
                        verificar2 = verificar2->sig;
                        verificarCol = verificarCol->sig;
                    }
                    buscar2 = buscar2->abajo;
                }
                else
                {
                    buscar2 = buscar2->abajo;
                }
            }
            else
            {
                if (buscar1->dato_string == buscar2->dato_string)
                {
                    cout << buscar1->dato_string << " - coincide con - " << buscar2->dato_string << endl;
                    buscar2 = buscar2->abajo;
                }
                else
                {
                    buscar2 = buscar2->abajo;
                }
            }
        }
        if (!existe)
        {
            cout << buscar1->dato_int << endl;
            filas copiar = buscar1;
            columna copiarCol = tabla1->columna;
            string insertValores = "";
            while (copiarCol != NULL)
            {
                if (copiarCol->tipo_dato)
                {
                    stringstream ss;
                    string aux;
                    if (copiar->dato_int == empty)
                    {
                        insertValores = insertValores + ":";
                    }
                    else
                    {
                        ss << copiar->dato_int;
                        aux = ss.str();
                        if (insertValores == "")
                        {
                            insertValores = aux;
                        }
                        else
                        {
                            insertValores = insertValores + ":" + aux;
                        }
                    }
                }
                else
                {
                    if (copiar->dato_string == "")
                    {
                        insertValores = insertValores + ":";
                    }
                    else
                    {
                        if (insertValores == "")
                        {
                            insertValores = copiar->dato_string;
                        }
                        else
                        {
                            insertValores = insertValores + ":" + copiar->dato_string;
                        }
                    }
                }
                copiarCol = copiarCol->sig;
                copiar = copiar->sig;
            }
            cout << insertValores << endl;
            insertInto(nombreTabla3, insertColumna, insertValores);
            insertValores = "";
            cout << "inserto" << endl;
        }
        else
        {
            existe = false;
        }

        buscar1 = buscar1->abajo;
        buscar2 = tabla2->columna->filas;
        cout << endl;
    }
}

int main()
{
    system("cls");
    createTable("alo");
    createTable("diente");
    createTable("caracol");
    createTable("mariposa");
    createTable("arbol");

    addCol("alo", "cedula", "int", "nn");
    addCol("alo", "nombres", "string", "any");
    addCol("alo", "apellidos", "string", "nn");

    addCol("arbol", "cedula", "int", "nn");
    addCol("arbol", "nombres", "string", "any");
    addCol("arbol", "apellidos", "string", "nn");

    insertInto("alo", "cedula:nombres:apellidos", "3:esteban:quito");
    insertInto("alo", "cedula:nombres:apellidos", "5:juan:antonio");
    insertInto("alo", "cedula:nombres:apellidos", "9:ateban:quito");
    insertInto("alo", "cedula:nombres:apellidos", "2:miguelito:abduscan");
    insertInto("alo", "cedula:nombres:apellidos", "3:mili:vairosa");
    // insertInto("alo", "cedula:nombres:apellidos", "5:juan:antonio");
    // insertInto("alo", "cedula:nombres:apellidos", "3:mili:vairo");

    insertInto("arbol", "cedula:nombres:apellidos", "6:carlos:delvalle");
    insertInto("arbol", "cedula:nombres:apellidos", "3:mili:vairosa");
    insertInto("arbol", "cedula:nombres:apellidos", "5:juan:antonio");
    insertInto("arbol", "cedula:nombres:apellidos", "9:ana:clara");

    system("cls");

    // printDataTable("alo", "");
    // deleteTupla("alo", "nombres<esteban");
    // intersect("alo", "arbol", "rinoceronte");
    // updateTuplas("alo", "cedula>2", "apellidos", "puta");
    printDataTable("alo", "");
    minusTable("alo", "arbol", "lupa");
    printDataTable("lupa", "");
    // printDataTable("rinoceronte", "");
    // printDataTable("alo", "");
    // addCol("arbol", "ciudad", "string", "any");
    // deleteTupla("alo", "cedula=5");
    // printMetadata("arbol");
    // addCol("alo", "colores", "int", "nn");
    // insertInto("alo", "cedula:nombres:apellidos", "4:jose:manuel");
    // insertInto("arbol", "cedula:nombres:apellidos:ciudad", "4:kai:sa:runaterra");
    // printDataTable("arbol", "");

    // unionTable("alo", "arbol", "cacatua");
    // printMetadata("cacatua");
    // deleteTupla("alo", "");
    // alterCol("alo", "cedula", "string", "any", "modifique");
    // printDataTable("alo", "");
    // printDataTable("cacatua", "");

    // createTable("alo");
    // printTables(BD);
    // imprimir(BD);
    // imprimir(BD);
    // addCol("alo", "queso", "", "");
    //
    // addCol("personas", "nombres", "string", "nn");
    // addCol("personas", "apellido", "string", "nn");
    // addCol("personas", "edad", "string", "nn");
    // addCol("personas", "nombrePerro", "string", "nn");
    // dropTable("hi"); printTables(BD);
    // addCol("pescados", "naranja", "", "primary_key");
    // addCol("alo", "soca", "int", "nn");
    // addCol("alo", "quiesoto", "int", "nn");

    // system("cls");
    // cout << "llegue al print" << endl
    //      << endl
    // insertInto("personas", "cedula:nombres:apellido:edad", "1:esteban:quito:25");
    // insertInto("personas", "cedula:nombres:apellido:edad", "7:mili:vairo:19");
    // insertInto("personas", "cedula:nombres:apellido:edad", "2:jose:antonio:23"); //       << endl;

    // insertInto("personas", "cedula:nombres:apellidos:edad", "3:decime:quesi:57");
    //  dropCol("personas", "nombres");
    //
    // selectWhere("personas", "", "mascotas");
    // selectWhere("personas", "nombres=jose", "mascotas");
    // updateTupla("personas", "cedula=7", "apellido", "vaioro");
    //

    // printDataTable("mascotas", "");
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
}

//  ------------------------------ MENUS ------------------------------
/*int main()
{
    system("cls");

    int opcion;

    cout << "BIENVENIDO :D\n"
         << endl;

    do
    {
        cout << "1 - INGRESAR A LA BASE DE DATOS\n"
             << "2 - OPERACIONES ENTRE TABLAS\n"
             << "3 - VISUALIZAR SU BASE DE DATOS\n"
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
            submenu_operaciones_tablas();
            break;

        case 3:
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
    string nombreColumnaNuevo;
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
            cout << "Ingrese el tipo de dato a utilizar ('string', 'int')" << endl;
            cin >> tipo_dato;
            cout << "Ingrese el calificador de dato a utilizar ('primary_key', 'nn', 'any')" << endl;
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
            cout << "Ingrese el nombre de la columna a modificar" << endl;
            cin >> nombreColumna;
            cout << "Ingrese el nuevo tipo de dato" << endl;
            cin >> tipo_dato;
            cout << "Ingrese el nuevo calificador de dato" << endl;
            cin >> calificador;
            cout << "Ingrese el nombre de la nueva columna" << endl;
            cin >> nombreColumnaNuevo;
            cout << endl;
            alterCol(nombreTabla, nombreColumna, tipo_dato, calificador, nombreColumnaNuevo);
            break;
        }
        case 3:
        {
            system("cls");
            cout << "Ingrese el nombre de la TABLA donde eliminara su COLUMNA" << endl;
            cin >> nombreTabla;
            cout << "Ingrese el nombre de la columna a eliminar" << endl;
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
    string condicionEliminar;
    string condicionModificar;
    string columnaModificar;
    string valorModificar;
    int opcion;

    do
    {
        cout << "1 - CREAR TUPLAS\n"
             << "2 - ELIMINAR TUPLAS\n"
             << "3 - MODIFICAR TUPLAS\n"
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
            cout << "Ingrese el los nombres de las columnas separados por dos puntos (:)" << endl
                 << "ej. columna1:columna2:columna3" << endl;
            cin >> nombreColumna;
            cout << "Ingrese el los valores de las columnas separados por dos puntos (:)" << endl
                 << "ej. valor1:valor2:valor3" << endl;
            cin >> valoresTuplas;
            cout << endl;
            insertInto(nombreTabla, nombreColumna, valoresTuplas);
            break;
        }
        case 2:
        {
            system("cls");
            cout << "Ingrese el nombre de la TABLA" << endl;
            cin >> nombreTabla;
            cout << "Ingrese la columna en conjunto con las condicion y el valor de la tupla que eliminara" << endl;
            cin >> condicionEliminar;
            deleteTupla(nombreTabla, condicionEliminar);
            break;
        }
        case 3:
        {
            system("cls");
            cout << "Ingrese el nombre de la TABLA" << endl;
            cin >> nombreTabla;
            cout << "Ingrese la columna en conjunto con las condicion y el valor de la tupla que modificara" << endl;
            cin >> condicionModificar;
            cout << "Ingrese la columna a modificar:" << endl;
            cin >> columnaModificar;
            cout << "Ingrese el valor de la tupla que va a modificar:" << endl;
            cin >> valorModificar;
            updateTuplas(nombreTabla, condicionModificar, columnaModificar, valorModificar);
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

void submenu_operaciones_tablas()
{
    string nombreTabla;
    string nombreTabla2;
    string nombreTabla1;
    string nombreTabla3;
    string condicion;

    int opcion;
    do
    {
        cout << "1 - SELECT_WHERE\n"
             << "2 - UNION  \n"
             << "3 - INTERSECT\n"
             << "0 - Volver al submenu" << endl;

        cin >> opcion;
        getchar();
        switch (opcion)
        {
       case 1:
        {
            system("cls");
            cout << "Ingrese el nombre de su TABLA" << endl;
            cin >> nombreTabla;
            cout << "Ingrese la condicion" << endl;
            cin >> condicion;
            cout << "Ingrese el nombre de la nueva TABLA a crear" << endl;
            cin >> nombreTabla2;
            selectWhere(nombreTabla, condicion, nombreTabla2);
            break;
        }
        case 2:
        {
            system("cls");
            cout << "Ingrese el nombre de la TABLA 1" << endl;
            cin >> nombreTabla1;
            cout << "Ingrese el nombre de la TABLA 2" << endl;
            cin >> nombreTabla2;
            cout << "Ingrese el nombre de la TABLA a crear" << endl;
            cin >> nombreTabla3;
            unionTable(nombreTabla1, nombreTabla2, nombreTabla3);
            break;
        }
        case 3:
        {
            system("cls");
            cout << "Ingrese el nombre de la TABLA 1" << endl;
            cin >> nombreTabla1;
            cout << "Ingrese el nombre de la TABLA 2" << endl;
            cin >> nombreTabla2;
            cout << "Ingrese el nombre de la TABLA a crear" << endl;
            cin >> nombreTabla3;
            intersect ( nombreTabla1, nombreTabla2, nombreTabla3);
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
            cout << endl;
            printTables(BD);
            break;
        }
        case 2:
        {
            system("cls");
            cout << "Ingrese el nombre de la TABLA que busca" << endl;
            cin >> nombreTabla;
            cout << endl;
            printMetadata(nombreTabla);
            break;
        }
        case 3:
            system("cls");
            cout << "Ingrese el nombre de la TABLA que busca" << endl;
            cin >> nombreTabla;
            cout << endl;
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
*/