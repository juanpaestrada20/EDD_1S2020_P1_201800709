#include <iostream>
using namespace std;

void menu();

int main() {
    menu();
    return 0;
}

void menu() {
    int opcion;
    do{
        cout << "\tUNIVERSIDAD SAN CARLOS DE GUATEMALA" << endl;
        cout << "\tFACULTAD DE INGENIERIA" << endl;
        cout << "\tESTRUCTURAS DE DATOS" << endl;
        cout << "\tPRACTICA 1" << endl;
        cout << "\tJUAN PABLO ESTRADA ALEMAN" << endl;
        cout << "\t201800709" << endl;
        cout << "\n" << endl;
        cout << "\t\tMENU" << endl;
        cout << "1. Crear Archivo" << endl;
        cout << "2. Abrir Archivo" << endl;
        cout << "3. Archivos Recientes" << endl;
        cout << "4. Salir" << endl;

        cin >> opcion;

    }while (opcion != 4);
}
