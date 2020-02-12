#include <iostream>
#include <stdlib.h>
#include <ncurses.h>
#include "ListaDobleEnlazada.h"
using namespace std;

void crearArchivo();
void menu();

static ListaDobleEnlazada *listaCaracteres = new ListaDobleEnlazada();

int main() {
    menu();
    return 0;
}

void menu(){
    initscr();
    noecho();
    cbreak();

    int y, x;
    getmaxyx(stdscr, y, x);

    WINDOW *menu = newwin(20,x,0,0);
    box(menu, 0,0);
    refresh();
    wrefresh(menu);
    keypad(menu, true);

    string opciones[4] = {"1. Crear Archivo", "2. Abrir Archivo", "3. Archivos Recientes", "4. Salir"};
    string cabecera[8] = {"UNIVERSIDAD SAN CARLOS DE GUATEMALA", "FACULTAD DE INGENIERIA", "ESTRUCTURAS DE DATOS", "PARCTICA 1",
                          "JUAN PABLO ESTRADA ALEMAN", "2018000709", "", "MENU"};

    int option;
    int highlight = 8;

    for(int i = 0; i < 12; i++){
        if(i == highlight){
            wattron(menu, A_STANDOUT);
        }
        wattroff(menu, A_STANDOUT);
        if (i<8){
            mvwprintw(menu, i+1, 1, cabecera[i].c_str());
        }else {
            mvwprintw(menu, i+1, 1, opciones[i-8].c_str());
        }
    }
    while (wgetch(menu) != '4'){

        option = getch();
        switch (option){
            case KEY_UP:
                highlight = highlight - 1;
                if (highlight == 7){
                    highlight=12;
                }
                break;
            case KEY_DOWN:
                highlight = highlight + 1;
                if(highlight == 13){
                    highlight=8;
                }
                break;
        }
        if(option == '1'){
            clear();
            crearArchivo();
        }
    }
    delwin(menu);
    endwin();
}

void crearArchivo() {
    initscr();
    echo();
    cbreak();

    int y, x;
    getmaxyx(stdscr, y, x);

    WINDOW *archivo = newwin(20,x,0,0);
    box(archivo, 0,0);
    refresh();
    wrefresh(archivo);
    keypad(archivo, true);
    string instrucciones = "^w (Buscar y Remplazar)   ^c(Reportes)    ^s (Salir)";
    mvwprintw(archivo, 21, x, "%c", instrucciones.c_str());
    refresh();

    int columna = 1;
    int fila = 1;

    int contCaracteres = 0;
    move(fila, columna);
    //^X
    while (wgetch(archivo) != 24){
        int acsii = wgetch();
        char letra = acsii;
        switch (acsii){
            case KEY_UP:
            case KEY_DOWN:
            case 27:
                listaCaracteres->generarGrafo();
                break;
            case 13:
                fila++;
                move(fila, columna);
            default:
                listaCaracteres->agregarFin(letra);
                mvwprintw(archivo, fila, columna, "%c", letra);

                columna++;
        }
    }

    delwin(archivo);
    endwin();
    menu();
}
