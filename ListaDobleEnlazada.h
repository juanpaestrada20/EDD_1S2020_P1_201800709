//
// Created by juanp on 7/02/2020.
//

#ifndef PRACTICA1_LISTADOBLEENLAZADA_H
#define PRACTICA1_LISTADOBLEENLAZADA_H

class Nodo{
public:
    char letra;
    Nodo *next;
    Nodo *prev;
    Nodo (char dato){
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
    ListaDobleEnlazada(){
        cabeza = NULL;
        cola = NULL;
        size = 0;
    }
    int getSize(){
        return size;
    }
    void agregarFin(char letra){
        Nodo *nuevo = new Nodo(letra);

        if(cabeza==NULL){
            cabeza = nuevo;
            cola = nuevo;
        }
        else {
            cola->next = nuevo;
            nuevo->prev = cola;
            cola = nuevo;
        }
        size++;
    }
    void agregarInicio(char letra){
        Nodo *nuevo = new Nodo(letra);

        if(cabeza==NULL){
            cabeza = nuevo;
            cola = nuevo;
        }
        else {
            cabeza->prev = nuevo;
            nuevo->next = cabeza;
            cabeza = nuevo;
        }
        size++;
    }
    void agregarPosicion(char letra, int pos){

        if(pos < 1 || pos > (size + 1))
            return;
        else if(pos == 1)
            agregarInicio(letra);
        else if(pos == size+1)
            agregarFin(letra);
        else if(cabeza != NULL){
            Nodo *nuevo = new Nodo(letra);
            Nodo *aux = cabeza;
            for(int i = 0; i < pos; i++)
                aux = aux->next;

            aux->prev->next = nuevo;
            nuevo->prev = aux->prev;
            nuevo->next = aux->next;
            aux->prev = nuevo;

        }

        size++;
    }
    void eliminarPrimero(){
        if(cabeza->next == NULL){
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
    void eliminarUltimo(){
        if(cabeza->next == NULL){
            delete cabeza;
            cabeza = NULL;
            cola = NULL;
        } else if (cabeza != NULL){
            cola = cola->prev;
            delete cola->next;
            cola->next = NULL;
            size--;
        }
    }
    void eliminarPosicion(int pos){
        if (pos < 1 || pos > size)
            return;
        else if(pos == 1)
            eliminarPrimero();
        else if(pos == size)
            eliminarUltimo();
        else if(cabeza != NULL){
            Nodo *aux = cabeza;
            for(int i = 1; i < pos; i++)
                aux = aux->next;

            aux->prev->next = aux->next;
            aux->next->prev = aux->prev;
            delete aux;
            size--;
        }
    }
    bool isEmpty(){
        return (cabeza == NULL);
    }
};


#endif //PRACTICA1_LISTADOBLEENLAZADA_H
