//
// Created by juanp on 7/02/2020.
//

#ifndef PRACTICA1_LISTADOBLEENLAZADA_H
#define PRACTICA1_LISTADOBLEENLAZADA_H

#include <fstream>

using namespace std;

class Nodo {
public:
    char letra;
    Nodo *next;
    Nodo *prev;

    Nodo(char dato) {
        letra = dato;
        next = NULL;
        prev = NULL;
    }
};

class ListaDobleEnlazada {
private:
    Nodo *cabeza;
    Nodo *cola;
    int size;
public:
    ListaDobleEnlazada() {
        cabeza = NULL;
        cola = NULL;
        size = 0;
    }

    int getSize() {
        return size;
    }

    void agregarFin(char letra) {
        Nodo *nuevo = new Nodo(letra);

        if (cabeza == NULL) {
            cabeza = nuevo;
            cola = nuevo;
        } else {
            cola->next = nuevo;
            nuevo->prev = cola;
            cola = nuevo;
        }
        size++;
    }

    void agregarInicio(char letra) {
        Nodo *nuevo = new Nodo(letra);

        if (cabeza == NULL) {
            cabeza = nuevo;
            cola = nuevo;
        } else {
            cabeza->prev = nuevo;
            nuevo->next = cabeza;
            cabeza = nuevo;
        }
        size++;
    }

    void agregarPosicion(char letra, int pos) {

        if (pos < 0 || pos > (size + 1))
            return;
        else if (pos == 0)
            agregarInicio(letra);
        else if (pos == size + 1)
            agregarFin(letra);
        else if (cabeza != NULL) {
            Nodo *nuevo = new Nodo(letra);
            Nodo *aux = cabeza;
            for (int i = 0; i < pos; i++) {
                aux = aux->next;
            }

            aux->prev->next = nuevo;
            nuevo->prev = aux->prev;
            nuevo->next = aux;
            aux->prev = nuevo;

        }

        size++;
    }

    void eliminarPrimero() {
        if (cabeza->next == NULL) {
            delete cabeza;
            cabeza = NULL;
            cola = NULL;
            size--;
        } else if (cabeza != NULL) {
            cabeza = cabeza->next;
            delete cabeza->prev;
            cabeza->prev = NULL;
            size--;
        }

    }

    void eliminarUltimo() {
        if (cabeza->next == NULL) {
            delete cabeza;
            cabeza = NULL;
            cola = NULL;
        } else if (cabeza != NULL) {
            cola = cola->prev;
            delete cola->next;
            cola->next = NULL;
            size--;
        }
    }

    void eliminarPosicion(int pos) {
        if (pos < 0 || pos > size)
            return;
        else if (pos == 0)
            eliminarPrimero();
        else if (pos == size)
            eliminarUltimo();
        else if (cabeza != NULL) {
            Nodo *aux = cabeza;
            for (int i = 1; i < pos; i++)
                aux = aux->next;

            aux->prev->next = aux->next;
            aux->next->prev = aux->prev;
            delete aux;
            size--;
        }
    }

    bool isEmpty() {
        return (cabeza == NULL);
    }

    void mostrarDatos() {
        if (isEmpty()) {
            return;
        } else {
            Nodo *aux = cabeza;
            for (int i = 0; i < size; i++) {
                cout << aux->letra;
            }

        }
    }

    void limpiarLista() {
        while (!isEmpty()) {
            eliminarPrimero();
        }
    }

    void generarGrafo() {
        if (!isEmpty()) {
            Nodo *aux = cabeza;
            char letras[size];
            ofstream fs("letras.dot");
            fs << "digraph G {" << endl;
            fs << "rankdir = LR;" << endl;
            fs << "node [margin=0 shape=oval style=filled ];" << endl;
            fs << "B [label=\"null\"];" << endl;
            for (int i = 0; i < size; i++) {
                fs << "A" << i + 1 << " [label=\"" << aux->letra << "\"];" << endl;
                aux = aux->next;
            }
            fs << "C [label=\"null\"];" << endl;
            fs << "" << endl;
            aux = cabeza;
            if (aux == cabeza && aux->next != NULL) {
                fs << "A1 -> B;" << endl;
            }
            for (int j = 1; j < size; j++) {
                fs << "A" << j << " -> A" << j + 1 << " [dir=both];" << endl;
                aux = aux->next;
            }
            fs << "A" << size << " -> C;" << endl;
            fs << "}" << endl;
            fs.close();

            system("dot -Tpng letras.dot -o letras.png");
            system("display letras.png");
        }
    }

    void buscarPalabra(string palabra, string intercambio) {
        Nodo *aux = cabeza;
        int contador = 0;
        bool palabraEncontrada = false;
        string buscando = "";
        int pos = 0;
        while (aux != NULL) {
            if (aux->letra == palabra[contador]) {
                buscando += aux->letra;
                contador++;
            }
            if (buscando == palabra && aux->next->letra == ' ') {
                pos = pos + 2 - buscando.length();
                for (int i = 0; i < palabra.length(); i++) {
                    eliminarPosicion(pos);
                }
                for (int j = 0; j < intercambio.size(); j++) {
                    agregarPosicion(intercambio[j], pos);
                    pos++;
                }

            }
            if (aux->letra == ' ') {
                buscando = "";
                contador = 0;
            }
            pos++;
            aux = aux->next;
        }

    }
    void guardarArchivo(string nombre){
        if (!isEmpty()) {
            Nodo *aux = cabeza;
            ofstream fs(nombre);
            for (int i = 0; i < size; i++) {
                if(aux->letra == 10){
                    fs << endl;
                }else{
                    fs << aux->letra;
                }
                aux = aux->next;
            }

            fs.close();
        }
    }
};


#endif //PRACTICA1_LISTADOBLEENLAZADA_H
