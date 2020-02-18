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
        }
    }
};


#endif //PRACTICA1_PILA_H
