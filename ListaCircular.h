//
// Created by juanpa on 9/02/20.
//

#ifndef PRACTICA1_LISTACIRCULAR_H
#define PRACTICA1_LISTACIRCULAR_H

#include <string>
using namespace std;

class Nodo{
public:
    string ruta;
    Nodo *next;
    Nodo(string ruta){
        this->ruta = ruta;
        next = NULL;
        prev = NULL;
    }
};

class ListaCircular {
private:
    Nodo *cabeza;
    Nodo *cola;
    int size;
public:
    ListaCircular(){
        cabeza = NULL;
        cola = NULL;
        size = 0;
    }
    bool isEmpty(){
        return (cabeza == NULL);
    }
    void agregarInicio(string ruta){
        Nodo *nuevo = new Nodo(ruta);

        if(isEmpty())
            return;
        else if(cabeza == NULL){
            cabeza = nuevo;
            cabeza->next=cabeza;
        } else if(cabeza->next == cabeza){
            cola = nuevo;
            cabeza->next=cola;
            cola->next=cabeza;
        }else {
            Nodo *aux = new Nodo(ruta);

            cola->next = nuevo;
            nuevo->next = cabeza;
            cabeza = aux;
        }
        size++;
    }
};


#endif //PRACTICA1_LISTACIRCULAR_H
