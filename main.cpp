#include <iostream>
#include <stdlib.h>
#include <ncurses.h>
#include "ListaDobleEnlazada.h"
using namespace std;

void crearArchivo();
void menu();

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

    while (wgetch(menu) != 52){
        for(int i = 0; i < 12; i++){
            if(i == highlight){
                wattron(menu, A_REVERSE);
            }
            wattroff(menu, A_REVERSE);
            if (i<8){
                mvwprintw(menu, i+1, 1, cabecera[i].c_str());
            }else {
                mvwprintw(menu, i+1, 1, opciones[i-8].c_str());
            }
        }

        option = wgetch(menu);
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
            default:
                break;
        }
        if(option == '1'){
            crearArchivo();
        }
    }
    wrefresh(menu);
    getch();
    delwin(menu);
    endwin();
}

void crearArchivo() {
    int y, x;
    getmaxyx(stdscr, y, x);

    WINDOW *archivo = newwin(20,x,0,0);
    box(archivo, 0,0);
    refresh();
    wrefresh(archivo);
    keypad(archivo, true);
}
