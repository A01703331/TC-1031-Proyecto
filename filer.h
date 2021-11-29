/*
 *  filer.h
 *  Integral A
 *  José Sebastián Pedrero Jiménez
 *  A01703331
*/ 

#ifndef FILER_H
#define FILER_H

#include <string>
#include <sstream>
#include <math.h>

template <class T> class BSTree;

template <class T>
class Run {
private:
    Run();
	Run(std::string, unsigned int, std::string);
	Run(std::string, unsigned int, std::string, Run<T>*, Run<T>*);
	Run(const Run<T>&);
    unsigned int Tseconds, hours, minutes,seconds;
    std::string name, version;
	Run<T>* add(std::string, int, std::string);//
	Run<T> *faster, *slower, *previous, *next;
    void TotalTime(unsigned int, unsigned int, unsigned int);
	void removeChilds(); //
	void fromFastest(std::stringstream&) const;//
    int maxHeight(Run<T>*);//
    
public:
    std::string printTime() const;
	friend class BSTree<T>;
};

template <class T> //Constructor por default
Run<T>::Run(): name(""), Tseconds(0), version(""), slower(NULL), faster(NULL){
}

template <class T> //Constructor simple
Run<T>::Run(std::string nm, unsigned int secs, std::string ver): name(nm), Tseconds(secs), version(ver), slower(NULL), faster(NULL){
}

template <class T> //Constructor con nodos
Run<T>::Run(std::string nm, unsigned int secs, std::string ver, Run *slw, Run *fst) : name(nm), Tseconds(secs), version(ver), slower(slw), faster(fst){
}

template <class T>
void Run<T>::removeChilds() {
	if (faster != NULL) {
		faster->removeChilds();
		delete faster;
		faster = NULL;
	}
	if (slower != NULL) {
		slower->removeChilds();
		delete slower;
		slower = NULL;
	}
}

template <class T> //Agrega un nuevo Run al arbol
Run<T>* Run<T>::add(std::string nm, int secs, std::string ver) {
	if (secs < Tseconds) {
		if (faster != NULL) {
			return faster->add(nm, secs, ver);
		} else {
			return faster = new Run<T>(nm, secs, ver);
		}
	} else {
		if (slower != NULL) {
			return slower->add(nm, secs, ver);
		} else {
			return slower = new Run<T>(nm, secs, ver);
		}
	}
}

template <class T>
void Run<T>::TotalTime(unsigned int hrs, unsigned int mins, unsigned int secs) {
    Tseconds = hrs*3600 + mins*60 + secs;
}

template <class T>
std::string Run<T>::printTime() const {
	std::stringstream aux;
    seconds = Tseconds;
    minutes = floor(Tseconds/60);
    hours = floor(minutes/60);

    if (hours>0){
        aux << hours << ":";
    }
    aux << minutes%60 << ":";
    aux << seconds%60;
    return aux.str();
}

template <class T>
int Run<T>::maxHeight(Run<T> *segment){
	if (segment!=NULL){
		int L = maxHeight(segment->faster);
		int R = maxHeight(segment->slower);
		if (L>R) {
			return (L+1);
		} else{
			return (R+1);
		}
	} else {
		return 0;
	}
}

template <class T>
void Run<T>::fromFastest(std::stringstream &aux) const {
    if (faster != NULL) {
	    faster->fromFastest(aux);
	    aux << " ";
	}
    aux << name << ",";
	aux << printTime() << ",";
    aux << version;
	if (slower != NULL) {
        aux << " ";
	    slower->fromFastest(aux);
    }
}

template <class T>
class BSTree {
private:
	Run<T> *root, *head, *tail;
    unsigned int tamanio;

public:
	BSTree();
	~BSTree();
	bool empty() const;
	void add(std::string, int, std::string); //
	void addWR(std::string, int, std::string); //
	void remove(int);
	void removeAll();
	std::string fromFastest() const; //
    int size() const; //
	int height() const; //
};

template <class T> //Verifica si el arbol y la lista estan vacios
bool BSTree<T>::empty() const{
    return (head==NULL && root==NULL);
}

template <class T> //Agrega un nuevo Run al arbol y al final de la lista vinculada
void BSTree<T>::add(std::string nm, int secs, std::string ver){
    if (!empty){
        Run<T> *addition = root->add(nm,secs,ver);
	    tail->next = addition;
	    addition->previous = tail;
	    tail = addition;
        tamanio++;
    } else {
        root = new Run<T>(nm, secs, ver);
        head = root;
        tail = root;
        tamanio++;
    }
}

template <class T> //Agrega un nuevo Run al arbol y al principio de la lista vinculada
void BSTree<T>::addWR(std::string nm, int secs, std::string ver){
    if (!empty){
        Run<T> *wr = root->add(nm,secs,ver);
	    wr->next = head;
        head->previous = wr;
    	head = wr;
	    tamanio++;
    } else {
        root = new Run<T>(nm, secs, ver);
        head = root;
        tail = root;
        tamanio++;
    }
}

template <class T>
void BSTree<T>::removeAll() {
    Run<T> *p, *q;

	p = head;
	while (p != NULL){
		q = p->next;
		delete p;
		p = q;
	}
	if (root != NULL) {
		root->removeChilds();
	}
	delete root;
    head = NULL;
    tail = NULL;
	root = NULL;
    tamanio = 0;
}

template <class T>
std::string BSTree<T>::fromFastest() const{
    std::stringstream aux;
    aux << root->fromFastest(aux, 10);
    return aux.str();
}

template <class T>  // Regresa la altura del arbol
int BSTree<T>::height() const{
	if (!empty()){
		return root->maxHeight(root);
	} else {
		return 0;
	}
}

template <class T> //Regresa el tamanio de la lista vinculada
int BSTree<T>::size() const{
    return tamanio;
}

#endif