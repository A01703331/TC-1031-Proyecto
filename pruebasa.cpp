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
    string scheck;
    
    cout << "\n" <<"1.- Esperada: " << 1 << "\nPrograma: " << Tanooki.empty() << "\n";
	cout <<	(1 == Tanooki.empty() ? "success\n" : "fail\n");
    
    Tanooki.add("ML",4381,"1.3.0");
    Tanooki.add("Trop",5012,"1.2.0");
    Tanooki.add("Ren",8429,"1.0.0");
    Tanooki.add("ML",4294,"1.3.0");
    Tanooki.add("Goro",4203,"1.3.1");

    scheck = "Goro,1:10:03,1.3.1\nML,1:11:34,1.3.0\nML,1:13:01,1.3.0\nTrop,1:23:32,1.2.0\nRen,2:20:29,1.0.0";
	cout << "\n" <<"2.- Esperada:\n" << scheck << "\nPrograma:\n" << Tanooki.fromFastest() << "\n";
	cout <<	(!scheck.compare(Tanooki.fromFastest()) ? "success\n" : "fail\n");

	cout << "\n" <<"3.- Esperada: " << 5 << "\nPrograma: " << Tanooki.size() << "\n";
	cout <<	(5 == Tanooki.size() ? "success\n" : "fail\n");
    
	cout << "\n" <<"4.- Esperada: " << 3 << "\nPrograma: " << Tanooki.height() << "\n";
	cout <<	(3 == Tanooki.height()  ? "success\n" : "fail\n");

    cout << "\n" <<"5.- Esperada: " << 0 << "\nPrograma: " << Tanooki.empty() << "\n";
	cout <<	(0 == Tanooki.empty() ? "success\n" : "fail\n");

    
    scheck = "ML,1:13:01,1.3.0\nTrop,1:23:32,1.2.0\nRen,2:20:29,1.0.0\nML,1:11:34,1.3.0\nGoro,1:10:03,1.3.1\n";
	cout << "\n" <<"6.- Esperada:\n" << scheck << "\nPrograma:\n" << Tanooki.printLinkList() << "\n";
	cout <<	(!scheck.compare(Tanooki.printLinkList()) ? "success\n" : "fail\n");
    Tanooki.remove("ML",4381,"1.3.0");
    scheck = "Trop,1:23:32,1.2.0\nRen,2:20:29,1.0.0\nML,1:11:34,1.3.0\nGoro,1:10:03,1.3.1\n";
	cout << "\n" <<"6.- Esperada:\n" << scheck << "\nPrograma:\n" << Tanooki.printLinkList() << "\n";
	cout <<	(!scheck.compare(Tanooki.printLinkList()) ? "success\n" : "fail\n");
    Tanooki.remove("NecoArc",234235,"1.3.0");
    scheck = "Trop,1:23:32,1.2.0\nRen,2:20:29,1.0.0\nML,1:11:34,1.3.0\nGoro,1:10:03,1.3.1\n";
	cout << "\n" <<"7.- Esperada:\n" << scheck << "\nPrograma:\n" << Tanooki.printLinkList() << "\n";
	cout <<	(!scheck.compare(Tanooki.printLinkList()) ? "success\n" : "fail\n");

    Tanooki.sortMerge();
    scheck = "Goro,1:10:03,1.3.1\nML,1:11:34,1.3.0\nTrop,1:23:32,1.2.0\nRen,2:20:29,1.0.0\n";
	cout << "\n" <<"8.- Esperada:\n" << scheck << "\nPrograma:\n" << Tanooki.printLinkList() << "\n";
	cout <<	(!scheck.compare(Tanooki.printLinkList()) ? "success\n" : "fail\n");

	cout << "\n" <<"9.- Esperada: " << 4 << "\nPrograma: " << Tanooki.size() << "\n";
	cout <<	(4 == Tanooki.size() ? "success\n" : "fail\n");
    
	cout << "\n" <<"10.- Esperada: " << 3 << "\nPrograma: " << Tanooki.height() << "\n";
	cout <<	(3 == Tanooki.height()  ? "success\n" : "fail\n");
    
    Tanooki.add("ML",3854,"1.3.0");
    scheck = "Goro,1:10:03,1.3.1\nML,1:11:34,1.3.0\nTrop,1:23:32,1.2.0\nRen,2:20:29,1.0.0\nML,1:04:14,1.3.0\n";
	cout << "\n" <<"11.- Esperada:\n" << scheck << "\nPrograma:\n" << Tanooki.printLinkList() << "\n";
	cout <<	(!scheck.compare(Tanooki.printLinkList()) ? "success\n" : "fail\n");

    Tanooki.add("ML",3425,"1.3.0");
    Tanooki.add("ML",4294,"1.3.0");
    scheck = "ML,57:05,1.3.0\nML,1:04:14,1.3.0\nML,1:11:34,1.3.0\nML,1:11:34,1.3.0\n";
	cout << "\n" <<"12.- Esperada: " << scheck << "\nPrograma:\n" << Tanooki.byName("ML") << "\n";
	cout <<	(!scheck.compare(Tanooki.byName("ML")) ? "success\n" : "fail\n");

    
    Tanooki.sortMerge();
    Runs << Tanooki.fromFastest();

    Runs.close();

    return 0;
}