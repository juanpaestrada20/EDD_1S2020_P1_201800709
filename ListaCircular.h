//
// Created by juanpa on 9/02/20.
//

#ifndef PRACTICA1_LISTACIRCULAR_H
#define PRACTICA1_LISTACIRCULAR_H

#include <string>

using namespace std;

class NodoC {
public:
    string ruta;
    NodoC *next;

    NodoC(string _ruta) {
        ruta = _ruta;
        next = NULL;
    }
};

class ListaCircular {
private:
    NodoC *cabeza;
    NodoC *cola;
    int size;
public:
    ListaCircular() {
        cabeza = NULL;
        cola = NULL;
        size = 0;
    }

    bool isEmpty() {
        return (size == 0);
    }

    void agregarInicio(string ruta) {
        NodoC *nuevo = new NodoC(ruta);
        if (cabeza == NULL) {
            cabeza = nuevo;
            cabeza->next = cabeza;
        } else if (cabeza->next == cabeza) {
            cola = nuevo;
            cabeza->next = cola;
            cola->next = cabeza;
        } else {

            cola->next = nuevo;
            nuevo->next = cabeza;
            cola = nuevo;
        }
        size++;
    }

    void generarGrafo() {
        if (!isEmpty()) {
            int i;
            int j;
            NodoC *aux = cabeza;
            ofstream fs("archivos.dot");
            fs << "digraph G {" << endl;
            fs << "rankdir = LR;" << endl;
            fs << "node [margin=0 shape=oval style=filled ];" << endl;
            if (size == 1) {
                fs << "A1" << " [label=\"" << aux->ruta << "\"];" << endl;
                fs << "A1" << " -> A1;" << endl;
            }else{
                for(i = 0; i < size; i++){
                    fs << "A" << i+1 << " [label=\"" << aux->ruta << "\"];" << endl;
                    aux = aux->next;
                }
                fs << endl;
                aux = cabeza;
                for (j = 1; j < size; j++) {
                    fs << "A" << j << " -> A" << j + 1 << ";" << endl;
                    aux = aux->next;
                }
                fs << "A" << size << " -> A1;" << endl;
            }

            fs << "}" << endl;
            fs.close();

            system("dot -Tpng archivos.dot -o archivos.png");
            system("display archivos.png");
        }
    }
};


#endif //PRACTICA1_LISTACIRCULAR_H
