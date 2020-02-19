//
// Created by juanpa on 8/02/20.
//

#ifndef PRACTICA1_PILA_H
#define PRACTICA1_PILA_H
#include <string>
using namespace std;

class Cambio {
public:
    string palabraBuscada;
    string palabraReemplazada;
    bool estado;
    string palabra;
    int posicion;
    Cambio(string buscada, string remplazo, bool state, string word, int pos){
        palabraBuscada = buscada;
        palabraReemplazada = remplazo;
        estado = state;
        palabra = word;
        posicion = pos;
    }
    Cambio (){}
};

class NodoP{
public:
    Cambio cambio;
    NodoP *siguiente;

    NodoP(Cambio change){
        cambio = change;
        siguiente = NULL;
    }
};

class Pila {
private:
    NodoP *top;
    int size;
public:
    Pila (){
        top = NULL;
        size = 0;
    }
    bool isEmpty(){
        return (top == NULL);
    }
    void agregarCambio(Cambio dato){
        NodoP *nuevo = new NodoP(dato);
        if(top == NULL)
            top = nuevo;
        else {
            nuevo->siguiente = top;
            top = nuevo;
        }
        size++;
    }
    Cambio sacarCambio(){
            Cambio temp = top->cambio;
            NodoP *aux = top;

            top = top->siguiente;
            delete aux;
            size--;
            return temp;
    }
    int getSize(){
        return size;
    }
    void vaciarPila(){
        while(!isEmpty())
            sacarCambio();
    }
    Pila girarPila(){
        Pila *auxPila = new Pila();
        auxPila->agregarCambio(sacarCambio());
        return *auxPila;
    }
    void generarGrafo(){
        if(!isEmpty()){
            int i = 1;
            Pila aux = girarPila();
            Pila aux3 = girarPila();
            Cambio aux2;
            Cambio aux4;
            ofstream fs("cambios.dot");
            fs << "digraph G {" << endl;
            fs << "rankdir = DU;" << endl;
            fs << "node [margin=0 shape=oval style=filled ];" << endl;
            while (!aux.isEmpty()) {
                aux2 = aux.sacarCambio();
                fs << "A" << i  << " [label=\"Palabra Buscada: " << aux2.palabraBuscada << "\nReemplazada por: ";
                fs << aux2.palabraReemplazada << "\nEstado: ";
                if(!aux2.estado){
                    fs << "No revertido";
                }else{
                    fs << "Revertido";
                }
                fs << "\nPalabra: " << aux2.palabra;
                fs << "\nPosicion: " << aux2.posicion << "\"];" << endl;
            }
            fs  << endl;
            for (int j = 1; j < size; j++) {
                fs << "A" << j << " -> A" << j + 1 << ";" << endl;
            }
            fs << "}" << endl;
            fs.close();

            system("dot -Tpng cambios.dot -o cambios.png");
            system("display cambios.png");
        }
    }
    void generarReversiones(){
        if(!isEmpty()) {
            int i = 1;
            Pila aux = girarPila();
            Pila aux3 = girarPila();
            Cambio aux2;
            Cambio aux4;
            ofstream fs("reversiones.dot");
            fs << "digraph G {" << endl;
            fs << "rankdir = DU;" << endl;
            fs << "node [margin=0 shape=oval style=filled ];" << endl;
            while (!aux.isEmpty()) {
                aux2 = aux.sacarCambio();
                fs << "A" << i << " [label=\"Palabra Buscada: " << aux2.palabraBuscada << "\nReemplazada por: ";
                fs << aux2.palabraReemplazada << "\nEstado: ";
                if (!aux2.estado) {
                    fs << "No revertido";
                } else {
                    fs << "Revertido";
                }
                fs << "\nPalabra: " << aux2.palabra;
                fs << "\nPosicion: " << aux2.posicion << "\"];" << endl;
            }
            fs << endl;
            for (int j = 1; j < size; j++) {
                fs << "A" << j << " -> A" << j + 1 << ";" << endl;
            }
            fs << "}" << endl;
            fs.close();

            system("dot -Tpng reversiones.dot -o reversiones.png");
            system("display reversiones.png");
        }
    }
};


#endif //PRACTICA1_PILA_H
