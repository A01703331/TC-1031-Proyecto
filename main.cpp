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
    Runs << "Name,Time,Version" << "\n";
    
    if (Tanooki.empty()){  
        cout << "El arbol y la lista estan vacios" << "\n";
    } else {
        cout << "El arbol y la lista no estan vacios" << "\n";
    }
        
    Tanooki.add("ML",4381,"1.3.0");
    Tanooki.add("Trop",5012,"1.2.0");
    Tanooki.add("Ren",8429,"1.0.0");
    Tanooki.add("ML",4294,"1.3.0");
    Tanooki.add("Goro",4203,"1.3.1");
    Tanooki.add("ML",4223,"1.3.0");
    Tanooki.add("Tari",5231,"1.0.0");
    Tanooki.add("Saber",4932,"1.2.0");
    Tanooki.add("NecoArc",4423,"1.2.0");
    Tanooki.add("Pringle",3523,"1.2.0");
    cout << Tanooki.fromFastest() << "\n";
    cout << "La lista tiene " << Tanooki.size() << " nodos.\n";
    cout << "El arbol tiene una altura de " << Tanooki.height() << ".\n";
 
    if (Tanooki.empty()){  
        cout << "El arbol y la lista estan vacios." << "\n";
    } else {
        cout << "El arbol y la lista no estan vacios." << "\n";
    }
    Tanooki.remove("NecoArc",4423,"1.2.0");
    cout << "Impreso por arbol:" << "\n";
    cout << Tanooki.fromFastest() << "\n";
    cout << "La lista tiene " << Tanooki.size() << " nodos.\n";
    cout << "El arbol tiene una altura de " << Tanooki.height() << ".\n";   
    cout << "Los Runs de ML son:\n" << Tanooki.byName("ML");
    cout << "Lista desordenada:" << "\n";
    cout << Tanooki.printLinkList();
    Tanooki.sortMerge();
    cout << "Lista ordenada:" << "\n";
    cout << Tanooki.printLinkList();
    Runs << Tanooki.printLinkList();
    Runs.close();

    return 0;
}