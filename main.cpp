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

int main() {
    std::ofstream Runs("SMO-test.csv"); // Toma un archivo de salida
    Runs << "Welcome New Galaxy!";
    
    Runs.close(); // Cierra el archivo
    
    return 0;
}