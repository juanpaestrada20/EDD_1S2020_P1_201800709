//
// Created by juanpa on 8/02/20.
//

#ifndef PRACTICA1_PILA_H
#define PRACTICA1_PILA_H
#include <string>
using namespace std;

class Cambio{
public:
    Cambio(long i) {

    }

    string palabraBuscada;
    string palabraReemplazada;
    bool estado;
    string palabra;
    int posicion;
    Cambio(string palabraBuscada, string palabraReemplazada, bool estado, string palabra, int posicion){
        this->palabraBuscada = palabraBuscada;
        this->palabraReemplazada = palabraReemplazada;
        this->estado = estado;
        this->palabra = palabra;
        this->posicion = posicion;
    }
    Cambio (){}
};

class Nodo{
public:
    Cambio cambio;
    Nodo *siguiente;
    Nodo(Cambio change){
        cambio = change;
        siguiente = NULL;
    }
};

class Pila {
private:
    Nodo *top;
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
        Nodo *nuevo = new Nodo(dato);
        if(top == NULL)
            top = nuevo;
        else {
            nuevo->siguiente = top;
            top = nuevo;
        }
        size++;
    }
    Cambio sacarCambio(){
        if(isEmpty()) {
            return NULL;
        }
        else{
            Cambio temp = top->cambio;
            Nodo *aux = top;

            top = top->siguiente;
            delete aux;
            size--;
            return temp;
        }
    }
    int getSize(){
        return size;
    }
    void vaciarPila(){
        while(!isEmpty())
            sacarCambio();
    }
};


#endif //PRACTICA1_PILA_H
