//
// Created by juanpa on 8/02/20.
//

#ifndef PRACTICA1_LISTASIMPLE_H
#define PRACTICA1_LISTASIMPLE_H
#include <string>

using namespace std;

class Palabras{
public:
    Palabras(long i) {
    }
    string palabraInicial;
    string palabraReemplazada;
    Palabras(string palabraInicial, string palabraReemplazada){
        this->palabraInicial = palabraInicial;
        this->palabraReemplazada = palabraReemplazada;
    }
    Palabras(){}
};

class Nodo{
public:
    Palabras dato;
    Nodo *next;
    Nodo(Palabras dato){
        this->dato = NULL;
        next = NULL;
    }
};

class ListaSimple {
private:
    Nodo *cabeza;
    Nodo *cola;
    int size;
public:
    ListaSimple(){
        cabeza = NULL;
        cola = NULL;
        size = 0;
    }
    int getSize(){
        return size;
    }
    void agregarFinal(Palabras pal){
        Nodo *nuevo = new Nodo(pal);

        if(cabeza == NULL){
            cabeza = nuevo;
            cola = nuevo;
        }else{
            cola->next = nuevo;
            cola = nuevo;
        }
        size++;
    }
    void agregarInicio(Palabras pal){
        Nodo *nuevo = new Nodo(pal);

        if(cabeza == NULL){
            cabeza = nuevo;
            cola = nuevo;
        } else {
            Nodo *aux = cabeza;
            cabeza = nuevo;
            nuevo->next = aux;
        }
        size++;
    }
    bool isEmpty(){
        return (cabeza == NULL);
    }
    void eliminarPrimero(){
        if(cabeza == NULL)
            return;
        else{
            Nodo *aux = cabeza;
            cabeza = aux->next;
            delete aux;
            size--;
        }
    }
    void eliminarUltimo(){
        if(cabeza == NULL)
            return;
        else if ( cabeza->next == NULL)
            eliminarPrimero();
        else if ( cabeza != NULL){
            Nodo *aux = cabeza;
            Nodo *anterior;
            while ( aux->next != NULL){
                anterior = aux;
                aux = aux->next;
            }
            cola = anterior;
            anterior->next = NULL;
            delete aux;
            size--;
        }
    }
    void eliminarPosicion(int pos){
        if(pos < 1 || pos > size)
            return;
        else if (pos == 1)
            eliminarPrimero();
        else if(pos == size)
            eliminarUltimo();
        else if (cabeza != NULL){
            Nodo *anterior;
            Nodo *aux = cabeza;
            for(int i = 0; i < pos; i++){
                anterior = aux;
                aux = aux->next;
            }
            anterior->next = NULL;
            delete aux;
            size--;
        }
    }
    void agregarPosicion(Palabras pal, int pos){
        if(pos < 1 || pos > size + 1)
            return;
        else if(pos==1)
            agregarInicio(pal);
        else if(pos == size + 1)
            agregarFinal(pal);
        else if (cabeza != NULL){
            Nodo *nuevo = new Nodo(pal);
            Nodo *aux = cabeza;
            Nodo *ant;

            for (int i = 0; i < size; i++){
                ant = aux;
                aux = aux->next;
            }

            ant->next = nuevo;
            nuevo->next = aux;
            size++;
        }
    }
    ~ListaSimple(){
        Nodo *sig;
        while(!isEmpty()){
            sig = cabeza->next;
            delete cabeza;
            cabeza = sig;
        }
    }
};


#endif //PRACTICA1_LISTASIMPLE_H
