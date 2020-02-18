#include <iostream>
#include <ncurses.h>
#include "ListaDobleEnlazada.h"
#include "Pila.h"
#include "ListaCircular.h"


using namespace std;

void crearArchivo();

void guardarArchivo();

void menu();

static ListaCircular *recientes = new ListaCircular();
static Pila *cambios = new Pila();
static ListaDobleEnlazada *listaCaracteres = new ListaDobleEnlazada();

int main() {
    menu();
    return 0;
}

void menu() {
    initscr();
    noecho();
    cbreak();

    int y, x;
    getmaxyx(stdscr, y, x);

    WINDOW *menu = newwin(y, x, 0, 0);
    box(menu, 0, 0);
    refresh();
    wrefresh(menu);
    keypad(menu, true);

    string opciones[4] = {"1. Crear Archivo", "2. Abrir Archivo", "3. Archivos Recientes", "4. Salir"};
    string cabecera[8] = {"UNIVERSIDAD SAN CARLOS DE GUATEMALA", "FACULTAD DE INGENIERIA", "ESTRUCTURAS DE DATOS",
                          "PARCTICA 1",
                          "JUAN PABLO ESTRADA ALEMAN", "2018000709", "", "MENU"};

    int option;
    while (1) {
        for (int i = 0; i < 12; i++) {
            if (i < 8) {
                mvprintw(i + 1, 1, cabecera[i].c_str());
            } else {
                mvprintw(i + 1, 1, opciones[i - 8].c_str());
            }
            refresh();
        }
        if (getch() == '4') {
            break;
        }
        option = getch();
        if (option == '1') {
            clear();
            crearArchivo();
        }
        refresh();
    }
    delwin(menu);
    endwin();
}

void crearArchivo() {
    initscr();
    noecho();
    raw();
    box(stdscr, 0, 0);

    int y, x;
    getmaxyx(stdscr, y, x);
    keypad(stdscr, true);
    string instrucciones = "^w (Buscar y Remplazar)   ^c(Reportes)    ^s (Guardar)";
    refresh();
    mvprintw(y - 1, 12, instrucciones.c_str());


    int columna = 1;
    int fila = 1;

    int contCaracteres = 0;
    move(fila, columna);
    while (1) {
        char letra = getch();
        if (letra == 24) {
            listaCaracteres->limpiarLista();
            break;
        }
        switch ((unsigned int) letra) {
            case 1:
            case 2:
            case 4:
            case 5:
            case 6:
            case 9:
            case 13:
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
            case 27:
            case 28:
            case 29:
            case 30:
            case 31:
            case KEY_UP:
            case KEY_DOWN:
                break;
            case 3:
                //Reportes ctrl+c
                listaCaracteres->generarGrafo();
                cambios->generarGrafo();
                break;
            case 8:
            case 7:
            case 127:
                //borrar
            {
                if (columna > 1 && columna < x - 1) {
                    listaCaracteres->eliminarUltimo();
                    mvprintw(fila, columna - 1, " ");
                    refresh();
                    columna--;
                    move(fila, columna);
                    refresh();
                } else if (columna == 1 && fila > 1) {
                    listaCaracteres->eliminarUltimo();
                    fila--;
                    columna = x - 1;
                    move(fila, columna);
                }
                break;
            }
            case 10: {
                if (fila < (y - 2)) {
                    //enter
                    fila++;
                    columna = 1;
                    listaCaracteres->agregarFin(10);
                    move(fila, columna);
                    refresh();
                    break;
                }
            }
            case 19:
                //ctrl + s
                guardarArchivo();
                listaCaracteres->limpiarLista();
                break;
            case 25:
                //ctrl + Y
                break;
            case 26:
                //ctrl + Z
                break;
            case 23:
                //busqueda
            {
                string remplazo = "";
                int posy = y - 2;
                int posx = 29;
                mvprintw(posy, 1, "Escriba palabra a remplazar:");
                refresh();
                while (1) {
                    char letraR = getch();
                    if (letraR == 24) {
                        move(y - 2, 0);
                        clrtoeol();
                        move(fila, columna);
                        break;
                    } else if (letraR == 10) {
                        string anterior = "";
                        int i;
                        for (i = 0; i < remplazo.length(); i++) {
                            if (remplazo[i] == ';') {
                                i++;
                                break;
                            } else {
                                anterior += remplazo[i];
                            }
                        }
                        string nuevaP = "";
                        while (i < remplazo.length()) {
                            nuevaP += remplazo[i];
                            i++;
                        }
                        move(y - 2, 0);
                        clrtoeol();
                        move(fila, columna);
                        listaCaracteres->buscarPalabra(anterior, nuevaP);
                        break;
                    } else if (letraR == 8) {
                        if (posx > 29 && posx < x - 1) {
                            mvprintw(posy, posx - 1, " ");
                            refresh();
                            posx--;
                            move(fila, columna);
                            refresh();
                        }
                    } else if (letraR > 19 && letraR < 126) {
                        mvaddch(posy, posx, letraR);
                        remplazo += letraR;
                        posx++;
                        refresh();
                    }
                }
                break;
            }
            default:
                if (columna == (x - 1)) {
                    fila++;
                    columna = 1;
                    listaCaracteres->agregarFin(' ');
                    move(fila, columna);
                    refresh();
                }
                mvaddch(fila, columna, letra);
                listaCaracteres->agregarFin(letra);
                cambios->agregarCambio(*new Cambio("", "", false, "", contCaracteres));
                columna++;
                contCaracteres++;
                refresh();
                break;
        }
        refresh();
    }

    clear();
    listaCaracteres->limpiarLista();
    endwin();
    menu();
}

void guardarArchivo() {

    string nombreArchivo = "";
    int columna = 1;
    int y, x;
    getmaxyx(stdscr, y, x);
    int fila = y-2;
    move(fila+1, columna);
    clrtoeol();
    box(stdscr, 0, 0);
    bool fin = false;
    string instrucciones = "^x(Cancelar)    Enter(Guardar)";
    refresh();
    mvprintw(y - 1, 20, instrucciones.c_str());
    mvprintw(fila, columna, "Ingrese nombre del archivo: ");
    columna = 29;
    refresh();

    while (1) {
        char letra = getch();
        if (letra == 24) {
            break;
        }
        switch (letra) {
            case 0 -5:
            case 6:
            case 9:
            case 11 - 23:
            case 25 - 31:
                break;
            case 7-8:
                //borrar
            {
                if (columna > 29 && columna < x - 1) {
                    nombreArchivo.erase(nombreArchivo.length());
                    mvprintw(fila, columna - 1, " ");
                    refresh();
                    columna--;
                    move(fila, columna);
                    refresh();
                }
                break;
            }
            case 10:
                //enter
                if (nombreArchivo != "") {
                    nombreArchivo += ".txt";
                    listaCaracteres->guardarArchivo(nombreArchivo);
                    move(y-2, 0);
                    clrtoeol();
                    nombreArchivo = "";
                    fin = true;
                }
                break;
            default:
                if (columna < x - 1) {
                    nombreArchivo += letra;
                    mvaddch(fila, columna,letra);
                    refresh();
                    columna++;
                }
                break;
        }
        if(fin){
            move(fila+1, columna);
            clrtoeol();
            box(stdscr, 0, 0);
            string instrucciones2 = "^w (Buscar y Remplazar)   ^c(Reportes)    ^s (Guardar)";
            mvprintw(y - 1, 12, instrucciones2.c_str());
            refresh();
            break;
        }
    }
}
