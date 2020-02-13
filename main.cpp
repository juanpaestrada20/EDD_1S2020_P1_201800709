#include <iostream>
#include <stdio.h>
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
    noecho();
    raw();

    int y, x;
    getmaxyx(stdscr, y, x);
    keypad(stdscr, true);
    string instrucciones = "^w (Buscar y Remplazar)   ^c(Reportes)    ^s (Salir)";
    refresh();

    printw(instrucciones.c_str());
    for (int line = 0; line < x; line++){
        mvprintw(1,line,"_");
        refresh();
    }

    int columna = 0;
    int fila = 3;

    int contCaracteres = 0;
    move(fila, columna);
    while (1){
        //int acsii = getch();
        char letra = getch();
        if(letra==19){
            listaCaracteres->limpiarLista();
            break;
        }
        switch (letra){
            case 1:
            case 2:
            case 4:
            case 5:
            case 6:
            case 7:
            case 9:
            case 10:
            case 11:
            case 12:
            case 14:
            case 15:
            case 16:
            case 17:
            case 18:
            case 20:
            case 21:
            case 22:
            case 24:
            case 27:
            case 28:
            case 29:
            case 30:
            case 31:
                break;
            case 3:
                //Reportes ctrl+c
                listaCaracteres->generarGrafo();
                break;
            case 8:
                //borrar
                break;
            case 13:
                //enter
                fila++;
                move(fila,columna);
                refresh();
                break;
            case 25:
                //ctrl + Y
                break;
            case 26:
                //ctrl + Z
                break;
            case 23:
                //busqueda
                break;
            default:
                addch(letra);
                listaCaracteres->agregarFin(letra);
                columna++;
                move(fila, columna);
                refresh();
                break;
        }
        refresh();
    }

    clear();
    listaCaracteres->limpiarLista();
    menu();
}
