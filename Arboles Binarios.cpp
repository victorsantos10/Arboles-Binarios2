#include<iostream>
#include<conio.h>
#include <windows.h>
#include <stdlib.h>


using namespace std;


int numNodos = 0;

struct Nodo {
    int dato;
    Nodo* der;
    Nodo* izq;
    Nodo* padre;

};
// Propototipos
void menu();
Nodo* crearNodo(int, Nodo*);
void InsertarNodo(Nodo*&, int, Nodo*);
void mostrarArbol(Nodo*, int);
bool buscarNodo(Nodo*, int);
void recorrerArbol(Nodo*);
Nodo* minimo(Nodo*);
void BorrarNodo(Nodo*&, Nodo*&);
void Borrado_UnHijo(Nodo*&, Nodo*&, Nodo*&);
void Borrado_SinHijos(Nodo*&, Nodo*&);
void Borrado_DosHijos(Nodo*&, Nodo*&);
void Suprimir(Nodo*&);
bool EsHijoDerecho(Nodo*&);
Nodo* BuscarNodo(Nodo*&, int);
Nodo* arbol = NULL;

int main()
{
    menu();
}

Nodo* crearNodo(int n, Nodo* padre) { // Crea los Nodos 
    Nodo* nuevoNodo = new Nodo();
    nuevoNodo->dato = n;
    nuevoNodo->der = NULL;
    nuevoNodo->izq = NULL;
    nuevoNodo->padre = padre;
    return nuevoNodo;
}

void InsertarNodo(Nodo*& arbol, int n, Nodo* padre) { // Inserta los Nodos 
    if (arbol == NULL) {
        Nodo* nuevoNodo = crearNodo(n, padre);
        arbol = nuevoNodo;
    }
    else {
        int valorRaiz = arbol->dato;
        if (n < valorRaiz) {
            InsertarNodo(arbol->izq, n, arbol);
        }
        else {
            InsertarNodo(arbol->der, n, arbol);
        }
    }

}

void mostrarArbol(Nodo* arbol, int contador) {
    if (arbol == NULL)
        return;
    mostrarArbol(arbol->der, contador + 1);

    for (int i = 0; i < contador; i++)
        cout << "   ";

    numNodos++;

    cout << arbol->dato << endl;
    mostrarArbol(arbol->izq, contador + 1);
}

bool buscarNodo(Nodo* arbol, int n) {
    if (arbol == NULL) {
        return false;
    }
    else if (arbol->dato == n) {
        return true;
    }
    else {
        return false;
    }
    if (n < arbol->dato) {
        return buscarNodo(arbol->izq, n);
    }
    else {
        return buscarNodo(arbol->der, n);
    }
}

void recorrerArbol(Nodo* arbol) { //recorrido en preorden
    if (arbol == NULL) {
        return;

    }
    else {
        cout << arbol->dato << "-";
        recorrerArbol(arbol->izq);
        recorrerArbol(arbol->der);
    }
}

Nodo* minimo(Nodo* arbol) { // para determinar el nodo mas izquierdo
    if (arbol == NULL) {
        return NULL;
    }
    if (arbol->izq) {
        return minimo(arbol->izq);
    }
    else {
        return arbol;
    }
}

void BorrarNodo(Nodo*& suprimido, Nodo*& raiz) {
    if (suprimido->der == NULL and suprimido->izq == NULL) {//si tiene ningun hijo
        Borrado_SinHijos(suprimido, raiz);
    }

    else if (suprimido->der != NULL and suprimido->izq != NULL) {//si tiene dos hijos
        Borrado_DosHijos(suprimido, raiz);
    }

    else if (suprimido->der != NULL) {//si tiene solo el hijo derecho
        Borrado_UnHijo(suprimido, suprimido->der, raiz);
    }

    else if (suprimido->izq != NULL) {//si tiene solo el hijo izquierdo
        Borrado_UnHijo(suprimido, suprimido->izq, raiz);
    }
}

void Borrado_UnHijo(Nodo*& suprimido, Nodo*& hijo, Nodo*& raiz) {

    if (suprimido->padre != NULL) {//si el nodo a borrar tiene padre

        hijo->padre = suprimido->padre;//al nodo hijo le asignamos como nuevo padre a su "abuelo"

        if (EsHijoDerecho(suprimido)) {//si es hijo derecho
            suprimido->padre->der = hijo;//al nodo padre le asignamos como nuevo hijo a su "nieto" 
        }
        else {//si es hijo izquierdo
            suprimido->padre->izq = hijo;//al nodo padre le asignamos como nuevo hijo a su "nieto"
        }

    }
    else if (raiz == suprimido) {//si el nodo a borrar es la raiz
        arbol = hijo;//intercambiamos lugares entre raiz/suprimido con hijo
        arbol->padre = NULL;//le ponemos null apadre para convertirlo un una raiz completa(recordemos que estas no tienen padre)
    }

    Suprimir(suprimido);

}

void Borrado_SinHijos(Nodo*& suprimido, Nodo*& raiz) {
    if (suprimido->padre != NULL) {
        if (EsHijoDerecho(suprimido)) {
            suprimido->padre->der = NULL;
        }
        else {
            suprimido->padre->izq = NULL;
        }
    }
    else if (raiz == suprimido) {
        raiz = NULL;
    }
    Suprimir(suprimido);
}

void Borrado_DosHijos(Nodo*& suprimido, Nodo*& raiz) {

    Nodo* min = minimo(suprimido->der);//buscamos el valor mas cercano al dato a borrar
    suprimido->dato = min->dato;//copiamos el valor encontrado por la funcion minimo hacia el dato que deseamos borrar
    BorrarNodo(min, raiz);//borramos minimo

}

void Suprimir(Nodo*& suprimido) {
    suprimido->der = NULL;
    suprimido->izq = NULL;
    suprimido->padre = NULL;
    delete suprimido;
    suprimido = NULL;

}

bool EsHijoDerecho(Nodo*& hijo) {
    if (hijo->padre->der == hijo) {
        return true;
    }
    return false;

}

Nodo* BuscarNodo(Nodo*& arbol, int buscado) {

    if (arbol == NULL or arbol->dato == buscado) {
        return arbol;
    }
    if (buscado < arbol->dato) {
        cout << "Izquierda ->";
        BuscarNodo(arbol->izq, buscado);
    }
    else {
        cout << "Derecha -> ";
        BuscarNodo(arbol->der, buscado);
    }

}

void menu() {
    int opcion, dato, contador = 0, n;
    do {
        cout << "\tArboles Binarios: ." << endl;
        cout << "\t1.- Insertar un nodo" << endl;
        cout << "\t2.- Mostrar el arbol" << endl;
        cout << "\t3.- Buscar un nodo" << endl;
        cout << "\t4.- Recorrer el arbol" << endl;
        cout << "\t5.- Borrar un nodo" << endl;
        cout << "\t6.- Salir" << endl;
        cin >> opcion;
        switch (opcion)
        {
        case 1:
            cout << "Coloque un numero: ";
            cin >> dato;
            InsertarNodo(arbol, dato, NULL);
            cout << "\n";
            system("pause");
            break;
        case 2:
            cout << "\nMostrando el arbol completo:\n\n";
            if (arbol == NULL && contador == NULL) {
                cout << "No hay datos";
            }
            else {
                mostrarArbol(arbol, contador);
            }
            cout << "\n";
            system("pause");
            break;
        case 3:
            cout << "\nIngresar elemento a buscar: ";
            cin >> dato;
            if (buscarNodo(arbol, dato) == true) {
                cout << "\nElemento " << dato << " esta en el arbol\n";
            }
            else {
                cout << "\n El elemento no esta en el arbol";
            }
            cout << "\n";
            system("pause");
            break;
        case 4:
            cout << "\n Mostrando recorrido del arbol:\n\n";
            if (arbol == NULL) {
                cout << "No hay datos";
            }
            else {
                recorrerArbol(arbol);
            }
            cout << "\n\n";
            system("pause");
            break;
        case 5:
            if (arbol == NULL) {
                cout << "---Arbol Vacio---" << endl << endl;
            }
            else {
                cout << "Dame el dato que deseas eliminar: "; cin >> dato;
                Nodo* a_borrar = BuscarNodo(arbol, dato);
                system("cls");
                if (a_borrar == NULL) {
                    cout << "---Elemento no encontrado---" << endl << endl;
                    system("pause");
                }
                else {
                    BorrarNodo(a_borrar, arbol);
                    cout << "---Elemento " << dato << " Borrado correctamente---" << endl << endl;
                    system("pause");
                }

            }
            break;
        case 6:
            exit(EXIT_SUCCESS);
        }


        system("cls");
    } while (opcion != 6);
}