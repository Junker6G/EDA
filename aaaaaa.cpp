#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <iomanip>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

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
            cout << "Encontre una tabla " << aux->nombreTabla << endl;
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
                cout << "Se ha creado " << nombreCol << endl;
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
            cout << "Se ha creado " << nombreCol << endl;
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
    unsigned int no_encontrado = -1;

    if (columnasTupla.find(limite) == no_encontrado)
    {
        cout << columnasTupla << " no cumple con las condiciones requeridas" << endl;
        return;
    }

    if (valoresTupla.find(limite) == no_encontrado)
    {
        cout << valoresTupla << " no cumple con las condiciones requeridas" << endl;
        return;
    }

    string columnasTuplaCopia = columnasTupla;
    string valoresTuplaCopia = valoresTupla;
    int cant_palabrasColumna = 0;
    int cant_palabrasTupla = 0;

    while (columnasTuplaCopia.find(limite) < 99999)
    {
        columnasTuplaCopia.erase(0, columnasTuplaCopia.find(limite) + 1);
        cant_palabrasColumna++;
        cout << "ANDAAA1" << endl;
    }

    while (valoresTuplaCopia.find(limite) < 99999)
    {
        valoresTuplaCopia.erase(0, valoresTuplaCopia.find(limite) + 1);
        cant_palabrasTupla++;
        cout << "ANDAAA2" << endl;
    }

    if (cant_palabrasColumna != cant_palabrasTupla)
    {
        cout << "La cantidad de palabras es distinta" << endl;
    }
    else
    {
        cout << "La cantidad de palabras es igual" << endl;
    }

    if (BD == NULL)
    {
        cout << "ERROR - NO HAY TABLAS EXISTENTES -" << endl;
        return;
    }
    Tabla aux = BD;
    while (aux != NULL)
    {
        if (aux->nombreTabla == nombreTabla)
        {
            if (aux->columna == NULL)
            {
                cout << "No existe ninguna columna" << endl;
                return;
            }
            columna aux1 = aux->columna;
            string nombreColumna;
            nombreColumna = columnasTupla.substr(0, columnasTupla.find(limite));
            cout<<"klslajdlaksjld"<<endl;
            cout <<aux1->nombreColumna<<endl;
            cout <<nombreColumna<<endl;
            if (aux1->nombreColumna == nombreColumna)
            {

                if (aux1->tipo_dato = true)
                {

                    string datoTupla;
                    datoTupla = valoresTuplaCopia.substr(0, valoresTuplaCopia.find(limite));
                    stringstream ss;
                    ss << datoTupla;
                    datoTupla = ss.str();
                    cout << "tupla de la dato" << endl;
                }
                else
                {
                    cout << "No coinicide las columnas a ingresar con las creadas" << endl;
                }

                // CASO QUE NO VEAN FILAS
                if (aux1->filas == NULL)
                {
                    filas nuevaFila = new nodoFilas;
                    aux1->filas = nuevaFila;
                    nuevaFila->sig = NULL;
                    nuevaFila->ant = NULL;
                    nuevaFila->arriba = NULL;
                    nuevaFila->abajo = NULL;
                    // ver los de nn
                    //  nuevaFila->dato_int= nn;
                    nuevaFila->dato_string = "";

                    // columnas apunta a filas
                    aux1->filas = nuevaFila;
                }
                filas aux2 = aux1->filas;

                while (aux2 != NULL && aux2->abajo != NULL)
                {

                    if (aux2->abajo->sig != NULL)
                    {
                        aux2 = aux2->abajo->sig;
                    }
                    if (aux2->abajo->ant != NULL)
                    {
                        aux2 = aux2->abajo->ant;
                    }
                    aux2 = aux2->abajo;
                }
                filas nuevaFila = new nodoFilas;
                aux1->filas = nuevaFila;
                nuevaFila->sig = NULL;
                nuevaFila->ant = NULL;
                nuevaFila->abajo = NULL;
                nuevaFila->arriba = aux2;
                aux2->abajo = nuevaFila;

                if (aux2->abajo->sig != NULL)
                {
                    aux2 = aux2->abajo->sig;
                }
                if (aux2->abajo->ant != NULL)
                {
                    aux2 = aux2->abajo->ant;
                }
            }

            while (aux1 != NULL)
            {
            }
            aux1 = aux1->sig;
        }
    }
    aux = aux->sig;
}

void deleteTupla(string nombreTabla, string condicionEliminar)
{
    if (BD == NULL)
    {
        cout << "ERROR - NO HAY TABLAS EXISTENTES -" << endl;
        return;
    }
    Tabla aux = BD;
    while (aux != NULL)
    {
        if (aux->nombreTabla == nombreTabla)
        {
            if (aux->columna == NULL)
            {
                cout << "No existe ninguna columna" << endl;
                return;
            }
            columna aux1 = aux->columna;

            while (aux1 != NULL)
            {
                filas aux2 = aux1->filas;

                while (aux2 != NULL && aux2->abajo != NULL)
                {

                    while (aux2->abajo->sig != NULL)
                    {
                        aux2 = aux2->abajo->sig;
                    }
                    while (aux2->abajo->ant != NULL)
                    {
                        aux2 = aux2->abajo->ant;
                    }
                    aux2 = aux2->abajo;
                }
                // ahora todos los punteros llegaron a NULL
                if (condicionEliminar == "")
                {
                    filas borrar = aux2;
                    // aux2 = aux2->abajo;
                    borrar->abajo = NULL;
                    borrar->arriba = NULL;
                    borrar->sig = NULL;
                    borrar->ant = NULL;
                    delete borrar;
                }
            }
            aux1 = aux1->sig;
        }
    }
    aux = aux->sig;
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
        cout << "-" << aux->nombreTabla << endl;

        if (aux->columna == NULL)
        {
            cout << "No existen columnas" << endl;
            return;
        }

        if (aux->nombreTabla == nombreTabla)
        {
            columna aux1 = aux->columna;
            do
            {
                cout << "|" << setw(20) << aux1->nombreColumna << "|" << endl;

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
            aux = aux->sig;
        }
        return;
    }
}

int main()
{
    system("cls");
    createTable("personas");
    createTable("tipo_arboles");
    createTable("pescados");
    // cout << "nombre de la tabla" << endl;

    createTable("hi");
    //  imprimir(BD);
    //  imprimir(BD);

    // addCol("alo", "queso", "", "");
    addCol("personas", "nombres", "int", "nn");
    addCol("personas", "apellidos", "int", "nn");
    addCol("personas", "cedula", "int", "primary_key");

   // addCol("pescados", "naranja", "", "primary_key");
    // addCol("alo", "soto", "int", "nn");
    // addCol("alo", "quiesoto", "int", "nn");
    // alterCol("alo", "quesoto", "", "primary_key", "sioto");
    insertInto("personas", "nombres:apellidos:cedula", "juan:soto:1");
    printTables(BD);
    // printMetadata("alo");
    //   dropTable("hi");addCol("alo", "qu
    //   esoto", "int", "primary_key");
    //   dropCol("alo", "quesoto");
    //   imprimir(BD);

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