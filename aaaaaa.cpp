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

        /* if ((nuevaTabla.compare(BD->nombreTabla))==-1){
if ((nuevaTabla.compare(BD->nombreTabla))==-1){
             insertar_t->sig=BD;
             insertar_t->ant=BD->ant;
         }*/
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
            // cout << "Encontre una tabla " << aux->nombreTabla << endl;
            columna aux1 = aux->columna;

            if (aux->columna == NULL)
            {
                columna nuevaColumna = new nodoColumna;
                // cout << aux->nombreTabla << endl;
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
                // cout << "Se ha creado " << nombreCol << endl;
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
            // cout << "Se ha creado " << nombreCol << endl;
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
    // unsigned int no_encontrado = -1;

    // cout << columnasTupla.find(limite) << endl;
    // cout << no_encontrado << endl;
    // cout << columnasTupla << endl;

    if (columnasTupla.find(limite) > no_encontrado || columnasTupla == "")
    {
        cout << "[ " << columnasTupla << " ]"
             << " no cumple con las condiciones requeridas" << endl;
        return;
    }
    if (valoresTupla.find(limite) > no_encontrado || valoresTupla == "")
    {
        cout << "[ " << valoresTupla << " ]"
             << " no cumple con las condiciones requeridas" << endl;
        return;
    }
    string columnasTuplaCopia = columnasTupla;
    string valoresTuplaCopia = valoresTupla;
    int cant_palabrasColumna = 1;
    int cant_palabrasTupla = 1;

    // cout << columnasTuplaCopia.find(limite) << endl << no_encontrado << endl;
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
    // BUSCAMOS LA TAMBLA QUE QUEREMOS
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
    // cout << cantidadColumnas->nombreColumna << endl;
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
    // cout << aux->nombreTabla << endl << aux1->nombreColumna << endl;
    filas nuevaFila = NULL;
    // CONSTRUIMOS LA FILA PARA INSERTAR DESPUES EN LA TABLA
    // cout << valoresTupla << endl;
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
        // cout << valor << endl << valoresTupla << endl;
        // break;
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
                cout << "entre 1" << endl;
            }
            else
            {
                nuevaFila->sig = nuevo;
                nuevo->ant = nuevaFila;
                nuevaFila = nuevaFila->sig;
                cout << "entre 2" << endl;
            }
            // cout << nuevoValor << endl;
        }
        else
        {
            string nuevoValor = valor;
            nuevo->dato_string = nuevoValor;
            if (nuevaFila == NULL)
            {
                nuevaFila = nuevo;
                cout << "entre 1" << endl;
            }
            else
            {
                nuevaFila->sig = nuevo;
                nuevo->ant = nuevaFila;
                nuevaFila = nuevaFila->sig;
                cout << "entre 2" << endl;
            }
        }
        aux1 = aux1->sig;
        cout << "pase al siguiente" << endl;
    }
    while (nuevaFila->ant != NULL)
    {
        nuevaFila = nuevaFila->ant;
    }
    // while (nuevaFila != NULL)
    // {
    //     cout << nuevaFila->dato_int << endl << nuevaFila->dato_string << endl << endl;
    //     nuevaFila = nuevaFila->sig;
    // }
    aux1 = aux->columna;
    if (aux1->filas == NULL)
    {
        while (aux1 != NULL)
        {
            aux1->filas = nuevaFila;
            cout << "conecte" << endl;
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
            cout << "conecte2" << endl;
            conectar = conectar->sig;
            nuevaFila = nuevaFila->sig;
        }
    }
    cout << "NUEVA FILA CREADA CON EXITO!!!" << endl;
}

void deleteTupla(string nombreTabla, string condicionEliminar)
{
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
        if (aux == NULL){
            cout << "No existen tablas..." <<nombreTabla<< endl;
            return;
        }
    }
    if(condicionEliminar)
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
    // TABLAS
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
    // addCol("personas", "nombrePerro", "string", "nn");

    // addCol("pescados", "naranja", "", "primary_key");
    // addCol("alo", "soto", "int", "nn");
    // addCol("alo", "quiesoto", "int", "nn");
    // alterCol("alo", "quesoto", "", "primary_key", "sioto");
    // system("cls");
    // cout << "llegue al print" << endl
    //      << endl
    //      << endl;

    insertInto("personas", "cedula:nombres:apellidos", "2:jose:soto");
    insertInto("personas", "cedula:nombres:apellidos", "3:decime:quesi");
    insertInto("personas", "cedula:nombres:apellidos", "1:esteban:quito");

    printDataTable("personas", "");
    // printMetadata("pescados");
    // cout << endl
    //      << endl
    //      << endl;
    // cout << "sali del print" << endl
    //      << endl;
    // printTables(BD);
    // printMetadata("personas");
    // dropTable("hi");addCol("alo", "qu
    // esoto", "int", "primary_key");
    // dropCol("alo", "quesoto");
    // imprimir(BD);

    return 0;
}

//  ------------------------------ MENUS ------------------------------
/*int main()
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
            cout << "SALIENDO DEL JUEGO" << endl;
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
            //     submenu_tuplas();
            //  system("clear");
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
            cout << "Ingrese el nombre de su Tabla a eliminar" << endl;
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
        case 0:
        {
            system("cls");
            cout << "Ingrese el nombre de la TABLA donde eliminara su COLUMNA" << endl;
            cin >> nombreTabla;
            cout << "Ingrese el nombre de la Columna a eliminar" << endl;
            cin >> eliminarColumna;
            break;
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
        case 0:
        {
            system("cls");
            cout << "..." << endl;
            sub_menu();
        }
        }
    } while (opcion != 0);
}*/

// find_first_of