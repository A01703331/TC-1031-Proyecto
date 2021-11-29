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

template <class T1, class T2, class T3> class BSTree;

template <class T1, class T2, class T3>
class Run {
private:
    unsigned int Tseconds, hours, minutes,seconds;
    std::string name, version;
    
public:
	Run(std::string, unsigned int, std::string);
	Run(std::string, unsigned int, std::string, Run<T1,T2,T3>*, Run<T1,T2,T3>*);
	Run(const Run<T1,T2,T3>&);
	Run<T1,T2,T3> *faster, *slower, *previous, *next;
    void TotalTime(unsigned int, unsigned int, unsigned int);
	Run<T1,T2,T3>* add(std::string, unsigned int, std::string);
	Run<T1,T2,T3>* succesor();
	void remove(std::string, unsigned int, std::string);
	void removeChilds(); //
	void fromFastest(std::stringstream&);//
	void byName(std::stringstream&, std::string);
    int maxHeight(Run<T1,T2,T3>*);//
    std::string printTime();
	friend class BSTree<T1,T2,T3>;
};

template <class T1, class T2, class T3> //Constructor simple
Run<T1,T2,T3>::Run(std::string nm, unsigned int secs, std::string ver): name(nm), Tseconds(secs), version(ver), slower(NULL), faster(NULL){
}

template <class T1, class T2, class T3> //Constructor con nodos
Run<T1,T2,T3>::Run(std::string nm, unsigned int secs, std::string ver, Run *slw, Run *fst) : name(nm), Tseconds(secs), version(ver), slower(slw), faster(fst){
}

template <class T1, class T2, class T3> //Agrega un nuevo Run al arbol
Run<T1,T2,T3>* Run<T1,T2,T3>::add(std::string nm, unsigned int secs, std::string ver) {
	if (secs < Tseconds) {
		if (faster != NULL) {
			return faster->add(nm, secs, ver);
		} else {
			return faster = new Run<T1,T2,T3>(nm, secs, ver);
		}
	} else {
		if (slower != NULL) {
			return slower->add(nm, secs, ver);
		} else {
			return slower = new Run<T1,T2,T3>(nm, secs, ver);
		}
	}
}


template <class T1, class T2, class T3> 
Run<T1,T2,T3>* Run<T1,T2,T3>::succesor() {
	Run<T1,T2,T3> *fs, *sl;

	fs = faster;
	sl = slower;

	if (faster == NULL) {
		if (slower != NULL) {
			slower = NULL;
		}
		return sl;
	}

	if (faster->slower == NULL) {
		faster = faster->faster;
		fs->faster = NULL;
		return fs;
	}

	Run<T1,T2,T3> *parent, *child;
	parent = faster;
	child = faster->slower;
	while (child->slower != NULL) {
		parent = child;
		child = child->slower;
	}
	parent->slower = child->faster;
	child->faster = NULL;
	return child;
}

template <class T1, class T2, class T3> 
void Run<T1,T2,T3>::remove(std::string nm, unsigned int secs, std::string ver) {
	Run<T1,T2,T3> * succ, *old;
	if (secs < Tseconds) {
		if (faster != NULL) {
			if (faster->Tseconds == secs) {
				old = faster;
				succ = faster->succesor();
				if (succ != NULL) {
					succ->faster = old->faster;
					succ->slower = old->slower;
				}
				faster = succ;
				delete old;
			} else {
				faster->remove(nm, secs, ver);
			}
		}
	} else if (secs > Tseconds) {
		if (slower != NULL) {
			if (slower->Tseconds == secs) {
				old = slower;
				succ = slower->succesor();
				if (succ != NULL) {
					succ->faster = old->faster;
					succ->slower = old->slower;
				}
				slower = succ;
				delete old;
			} else {
				slower->remove(nm, secs, ver);
			}
		}
	}
}

template <class T1, class T2, class T3>
void Run<T1,T2,T3>::removeChilds() {
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

template <class T1, class T2, class T3>
void Run<T1,T2,T3>::TotalTime(unsigned int hrs, unsigned int mins, unsigned int secs) {
    Tseconds = hrs*3600 + mins*60 + secs;
}

template <class T1, class T2, class T3>
std::string Run<T1,T2,T3>::printTime() {
	std::stringstream aux;
    seconds = Tseconds;
    minutes = floor(Tseconds/60);
    hours = floor(minutes/60);

    if (hours>0){
        aux << hours << ":";
    }
	if (minutes%60 < 10){
		aux << "0";
	}
    aux << minutes%60 << ":";
	if (seconds%60 < 10){
		aux << "0";
	}
    aux << seconds%60;
    return aux.str();
}

template <class T1, class T2, class T3>
int Run<T1,T2,T3>::maxHeight(Run<T1,T2,T3> *segment){
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

template <class T1, class T2, class T3>
void Run<T1,T2,T3>::fromFastest(std::stringstream &aux) {
    if (faster != NULL) {
	    faster->fromFastest(aux);
	    aux << "\n";
	}
    aux << name << ",";
	aux << printTime() << ",";
    aux << version;
	if (slower != NULL) {
        aux << "\n";
	    slower->fromFastest(aux);
    }
}

template <class T1, class T2, class T3>
void Run<T1,T2,T3>::byName(std::stringstream &aux, std::string nm) {
	if (faster != NULL) {
	    faster->byName(aux, nm);
	}
	if (nm == name) {
    	aux << name << ",";
		aux << printTime() << ",";
    	aux << version;
	    aux << "\n";
	}
	if (slower != NULL) {
	    slower->byName(aux, nm);
    }
}

template <class T1, class T2, class T3>
class BSTree {
private:
	Run<T1,T2,T3> *root, *head, *tail;
    unsigned int tamanio;

public:
	BSTree();//
	~BSTree();//
	bool empty() const;//
	void add(std::string, int, std::string); //
	void addWR(std::string, int, std::string); //
	void remove(std::string, int, std::string);
	void removeAll();//
	std::string fromFastest(); //
    std::string byName(std::string); //
	int size() const; //
	int height(); //
};

template <class T1, class T2, class T3>
BSTree<T1,T2,T3>::BSTree() :head(0), tail(0), root(0), tamanio(0) {
}

template <class T1, class T2, class T3>
BSTree<T1,T2,T3>::~BSTree() {
	removeAll();
}

template <class T1, class T2, class T3> //Verifica si el arbol y la lista estan vacios
bool BSTree<T1,T2,T3>::empty() const{
    return ((head==NULL && tail==NULL) && tail==NULL);
}

template <class T1, class T2, class T3> //Agrega un nuevo Run al arbol y al final de la lista vinculada
void BSTree<T1,T2,T3>::add(std::string nm, int secs, std::string ver){
    if (!empty()){
        Run<T1,T2,T3> *addition = root->add(nm,secs,ver);
	    tail->next = addition;
	    addition->previous = tail;
	    tail = addition;
        tamanio++;
    } else {
        root = new Run<T1,T2,T3>(nm, secs, ver);
        head = root;
        tail = root;
        tamanio++;
    }
}

template <class T1, class T2, class T3> //Agrega un nuevo Run al arbol y al principio de la lista vinculada
void BSTree<T1,T2,T3>::addWR(std::string nm, int secs, std::string ver){
    if (!empty()){
        Run<T1,T2,T3> *wr = root->add(nm,secs,ver);
	    wr->next = head;
        head->previous = wr;
    	head = wr;
	    tamanio++;
    } else {
        root = new Run<T1,T2,T3>(nm, secs, ver);
        head = root;
        tail = root;
        tamanio++;
    }
}

template <class T1, class T2, class T3>
void BSTree<T1,T2,T3>::remove(std::string nm, int secs, std::string ver) {
	if (root != NULL) {
		if (nm == root->name && secs == root->Tseconds && ver == root->version) {
			Run<T1,T2,T3> *succ = root->succesor();
			if (succ != NULL) {
				succ->faster = root->faster;
				succ->slower = root->slower;
			}
			delete root;
			root = succ;
			tamanio--;
		} else {
			root->remove(nm, secs, ver);
			tamanio--;
		}
	}
}

template <class T1, class T2, class T3>
void BSTree<T1,T2,T3>::removeAll() {
    Run<T1,T2,T3> *p, *q;

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

template <class T1, class T2, class T3> // Imprime tiempos desde el mas rapido
std::string BSTree<T1,T2,T3>::fromFastest(){
    std::stringstream aux;
	root->fromFastest(aux);
    return aux.str();
}

template <class T1, class T2, class T3> // Imprime tiempos de una persona en especifico	
std::string BSTree<T1,T2,T3>::byName(std::string nm){
    std::stringstream aux;
	root->byName(aux, nm);
    return aux.str();
}

template <class T1, class T2, class T3>  // Regresa la altura del arbol
int BSTree<T1,T2,T3>::height(){
	if (!empty()){
		return root->maxHeight(root);
	} else {
		return 0;
	}
}

template <class T1, class T2, class T3> //Regresa el tamanio de la lista vinculada
int BSTree<T1,T2,T3>::size() const{
    return tamanio;
}

#endif