//
// Created by juanpa on 8/02/20.
//

#ifndef PRACTICA1_LISTASIMPLE_H
#define PRACTICA1_LISTASIMPLE_H
#include <string>
#include <cstring>

using namespace std;

class Palabras{
public:
    string palabraInicial;
    string palabraReemplazada;
    Palabras(string inicial, string remplazo){
        palabraInicial = inicial;
        palabraReemplazada = remplazo;
    }
    Palabras(){}
};

class NodoS{
public:
    Palabras dato;
    NodoS *next;
    NodoS(Palabras nuevo){
        dato = nuevo;
        next = NULL;
    }
};

class ListaSimple {
private:
    NodoS *cabeza;
    NodoS *cola;
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
        NodoS *nuevo = new NodoS(pal);

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
        NodoS *nuevo = new NodoS(pal);

        if(cabeza == NULL){
            cabeza = nuevo;
            cola = nuevo;
        } else {
            NodoS *aux = cabeza;
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
            NodoS *aux = cabeza;
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
            NodoS *aux = cabeza;
            NodoS *anterior;
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
            NodoS *anterior;
            NodoS *aux = cabeza;
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
            NodoS *nuevo = new NodoS(pal);
            NodoS *aux = cabeza;
            NodoS *ant;

            for (int i = 0; i < size; i++){
                ant = aux;
                aux = aux->next;
            }

            ant->next = nuevo;
            nuevo->next = aux;
            size++;
        }
    }

    void ordenarBuscadas(){
        if(!isEmpty() && size > 1){
            NodoS *aux = cabeza;
            Palabras datos[size];
            Palabras temp;
            int k = 0;
            while(aux!=NULL){
                datos[k] = aux->dato;
                aux = aux->next;
                k++;
            }
            for(int i = 0; i < size; i++){
                for(int j = 0; j < size-1; j++){
                    if(strcmp(datos[j].palabraInicial.c_str(), datos[j+1].palabraInicial.c_str()) > 0){
                        temp = datos[j];
                        datos[j] = datos[j+1];
                        datos[j+1] = temp;
                    }
                }
            }
            generarGrafo(datos);
        }
    }
    void ordenarReemplazadas(){
        if(!isEmpty() && size > 1){
            NodoS *aux = cabeza;
            Palabras datos[size];
            Palabras temp;
            int k = 0;
            while(aux!=NULL){
                datos[k] = aux->dato;
                aux = aux->next;
                k++;
            }
            for(int i = 0; i < size; i++){
                for(int j = 0; j < size-1; j++){
                    if(strcmp(datos[j].palabraReemplazada.c_str(), datos[j+1].palabraReemplazada.c_str()) > 0){
                        temp = datos[j];
                        datos[j] = datos[j+1];
                        datos[j+1] = temp;
                    }
                }
            }
            generarGrafoDos(datos);
        }
    }

    void generarGrafo(Palabras datos[]){
        if (!isEmpty()) {
            ofstream fs("busquedas.dot");
            fs << "digraph G {" << endl;
            fs << "rankdir = LR;" << endl;
            fs << "node [margin=0 shape=oval style=filled ];" << endl;
            for (int i = 0; i < size; i++) {
                fs << "A" << i + 1 << " [label=\"" << datos[i].palabraInicial << " reemplazada por: "<< datos[i].palabraReemplazada << "\"];" << endl;
            }
            fs << "C [label=\"null\"];" << endl;
            fs << "" << endl;
            for (int j = 1; j < size; j++) {
                fs << "A" << j << " -> A" << j + 1 << ";" << endl;
            }
            fs << "A" << size << " -> C;" << endl;
            fs << "}" << endl;
            fs.close();

            system("dot -Tpng busquedas.dot -o busquedas.png");
            system("display busquedas.png");
        }
    }
    void generarGrafoDos(Palabras datos[]){
        if (!isEmpty()) {
            ofstream fs("reemplazo.dot");
            fs << "digraph G {" << endl;
            fs << "rankdir = LR;" << endl;
            fs << "node [margin=0 shape=oval style=filled ];" << endl;
            for (int i = 0; i < size; i++) {
                fs << "A" << i + 1 << " [label=\"" << datos[i].palabraReemplazada << " reemplazo a: "<< datos[i].palabraInicial << "\"];" << endl;
            }
            fs << "C [label=\"null\"];" << endl;
            fs << "" << endl;
            for (int j = 1; j < size; j++) {
                fs << "A" << j << " -> A" << j + 1 << ";" << endl;
            }
            fs << "A" << size << " -> C;" << endl;
            fs << "}" << endl;
            fs.close();

            system("dot -Tpng reemplazo.dot -o reemplazo.png");
            system("display reemplazo.png");
        }
    }

    ~ListaSimple(){
        NodoS *sig;
        while(!isEmpty()){
            sig = cabeza->next;
            delete cabeza;
            cabeza = sig;
        }
    }
};


#endif //PRACTICA1_LISTASIMPLE_H
