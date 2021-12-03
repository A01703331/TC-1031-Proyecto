/*
 *  main.cpp
 *  Integral A
 *  José Sebastián Pedrero Jiménez
 *  A01703331
*/ 

#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <sstream>
#include <utility>
#include "filer.h" 

using namespace std;

int main(int argc, char* argv[]) {
    BSTree<std::string, int, std::string> Tanooki;
    std::ofstream Runs("SMO-test.csv"); // Toma un archivo de salida
    Runs << "Player,Time,Version" << "\n";
    unsigned int option;
    cout << "Bienvenido al organizador de datos de SMO, este programa escribe los datos a un archivo, elija una opcion:" << "\n";
    cout << "1: Agregar un run" << "\n";
    cout << "2: Quitar un run" << "\n";
    cout << "3: Verificar si no hay runs" << "\n";
    cout << "4: Verificar size de arreglo" << "\n";
    cout << "5: Imprimir tiempos por más rápido" << "\n";
    cout << "6: Imprimir tiempos por orden de agregación" << "\n";
    cout << "7: Ordenar lista e imprimir" << "\n";
    cout << "Otro valor: salir" << "\n";
    cin >> option;
    
    while (option>0 && option<8){
        if (option==1){
            std::string Player, Version;
            unsigned int Time = 0;
            cout << "Ingrese el nombre del jugador:" << "\n";
            cin >> Player;
            cout << "Ingrese el tiempo en segundos:" << "\n";
            cin >> Time;
            while (Time < 1){
                cout << "Ingrese el tiempo en segundos (solo numeros positivos):" << "\n";
                cin >> Time;
            }
            cout << "Ingrese la version del juego:" << "\n";
            cin >> Version;
            Tanooki.add(Player,Time,Version);
            cout << "1: Agregar un run" << "\n";
            cout << "2: Quitar un run" << "\n";
            cout << "3: Verificar si no hay runs" << "\n";
            cout << "4: Verificar size de arreglo" << "\n";
            cout << "5: Imprimir tiempos por más rápido" << "\n";
            cout << "6: Imprimir tiempos por orden de agregación" << "\n";
            cout << "7: Ordenar lista e imprimir" << "\n";
            cout << "Otro valor: salir" << "\n";
            cin >> option;
        } else if (option == 2){
            std::string Player, Version;
            unsigned int Time = 0;
            cout << "Ingrese el nombre del jugador:" << "\n";
            cin >> Player;
            cout << "Ingrese el tiempo en segundos:" << "\n";
            cin >> Time;
            while (Time < 1){
                cout << "Ingrese el tiempo en segundos (solo numeros positivos):" << "\n";
                cin >> Time;
            }
            cout << "Ingrese la version del juego:" << "\n";
            cin >> Version;
            Tanooki.remove(Player,Time,Version);
            cout << "1: Agregar un run" << "\n";
            cout << "2: Quitar un run" << "\n";
            cout << "3: Verificar si no hay runs" << "\n";
            cout << "4: Verificar size de arreglo" << "\n";
            cout << "5: Imprimir tiempos por más rápido" << "\n";
            cout << "6: Imprimir tiempos por orden de agregación" << "\n";
            cout << "7: Ordenar lista e imprimir" << "\n";
            cout << "Otro valor: salir" << "\n";
            cin >> option;
        } else if (option == 3){
            if (Tanooki.empty()){
                cout << "No hay runs guardados" << "\n";
            } else {
                cout << "Hay runs guardados" << "\n";
            }
            cout << "1: Agregar un run" << "\n";
            cout << "2: Quitar un run" << "\n";
            cout << "3: Verificar si no hay runs" << "\n";
            cout << "4: Verificar size de arreglo" << "\n";
            cout << "5: Imprimir tiempos por más rápido" << "\n";
            cout << "6: Imprimir tiempos por orden de agregación" << "\n";
            cout << "7: Ordenar lista e imprimir" << "\n";
            cout << "Otro valor: salir" << "\n";
            cin >> option;
        } else if (option == 4){
            cout << "Actualmente hay " << Tanooki.size() << " runs guardados" << "\n";
            cout << "1: Agregar un run" << "\n";
            cout << "2: Quitar un run" << "\n";
            cout << "3: Verificar si no hay runs" << "\n";
            cout << "4: Verificar size de arreglo" << "\n";
            cout << "5: Imprimir tiempos en archivo por más rápido" << "\n";
            cout << "6: Imprimir tiempos por orden de agregación" << "\n";
            cout << "7: Ordenar lista e imprimir" << "\n";
            cout << "Otro valor: salir" << "\n";
        }  else if (option == 5){
            Runs << Tanooki.fromFastest();
            cout << "Los tiempos se han impreso en el archivo SMO-test.csv" << "\n";
            Runs.close();
            return 0;
        }  else if (option == 6){
            Runs << Tanooki.printLinkList();
            cout << "Los tiempos se han impreso en el archivo SMO-test.csv" << "\n";
            Runs.close();
            return 0;
        } else if (option == 7) { 
            Tanooki.sortMerge();
            Runs << Tanooki.printLinkList();
            cout << "Los tiempos se han impreso en el archivo SMO-test.csv" << "\n";
            Runs.close();
            return 0;

        }
    }
    return 0;
}