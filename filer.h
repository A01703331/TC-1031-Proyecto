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
#include <vector>
#include <list>
#include <math.h>
#include <algorithm>

template <class Player, class Time, class Version> class BSTree;

template <class Player, class Time, class Version>
class Run {
private:
    unsigned int Tseconds, hours, minutes, seconds;
    std::string name, version;
    
public:
	Run(std::string, unsigned int, std::string);
	Run(std::string, unsigned int, std::string, Run<Player,Time,Version>*, Run<Player,Time,Version>*);
	Run(const Run<Player,Time,Version>&);
	Run<Player,Time,Version> *faster, *slower, *next, *previous;
    void TotalTime(unsigned int, unsigned int, unsigned int);
	Run<Player,Time,Version>* add(std::string, unsigned int, std::string);
	Run<Player,Time,Version>* succesor();
	void remove(std::string, unsigned int, std::string, std::vector<Run<Player,Time,Version>*>&);
	void removeChilds(); //
	void removeLinks();
	void fromFastest(std::stringstream&);//
	void byName(std::stringstream&, std::string);
    int maxHeight(Run<Player,Time,Version>*);//
    std::string printTime();//
	void printLinkList(std::stringstream&);
	friend class BSTree<Player,Time,Version>;
};

template <class Player, class Time, class Version> //Constructor simple
Run<Player,Time,Version>::Run(std::string nm, unsigned int secs, std::string ver): name(nm), Tseconds(secs), version(ver), slower(NULL), faster(NULL){
}

template <class Player, class Time, class Version> //Constructor con nodos
Run<Player,Time,Version>::Run(std::string nm, unsigned int secs, std::string ver, Run *slw, Run *fst) : name(nm), Tseconds(secs), version(ver), slower(slw), faster(fst){
}

template <class Player, class Time, class Version> //Agrega un nuevo Run al arbol
Run<Player,Time,Version>* Run<Player,Time,Version>::add(std::string nm, unsigned int secs, std::string ver) {
	if (secs < Tseconds) {
		if (faster != NULL) {
			return faster->add(nm, secs, ver);
		} else {
			return faster = new Run<Player,Time,Version>(nm, secs, ver);
		}
	} else {
		if (slower != NULL) {
			return slower->add(nm, secs, ver);
		} else {
			return slower = new Run<Player,Time,Version>(nm, secs, ver);
		}
	}
}


template <class Player, class Time, class Version> 
Run<Player,Time,Version>* Run<Player,Time,Version>::succesor() {
	Run<Player,Time,Version> *fs, *sl;

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

	Run<Player,Time,Version> *parent, *child;
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

template <class Player, class Time, class Version> 
void Run<Player,Time,Version>::remove(std::string nm, unsigned int secs, std::string ver, std::vector<Run<Player,Time,Version>*>&TimeList) {
	Run<Player,Time,Version> * succ, *old;
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
				TimeList.erase(std::remove(TimeList.begin(), TimeList.end(), old), TimeList.end());
			} else {
				faster->remove(nm, secs, ver, TimeList);
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
				TimeList.erase(std::remove(TimeList.begin(), TimeList.end(), old), TimeList.end());
			} else {
				slower->remove(nm, secs, ver, TimeList);
			}
		}
	}
}

template <class Player, class Time, class Version>
void Run<Player,Time,Version>::removeChilds() {
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

template <class Player, class Time, class Version>
void Run<Player,Time,Version>::removeLinks() {
	if (next!=NULL){
		if (previous!=NULL){
			previous = NULL;
		}
		next->removeLinks();
		return;
	}
	previous = NULL;
}

template <class Player, class Time, class Version>
void Run<Player,Time,Version>::TotalTime(unsigned int hrs, unsigned int mins, unsigned int secs) {
    Tseconds = hrs*3600 + mins*60 + secs;
}

template <class Player, class Time, class Version>
void Run<Player,Time,Version>::fromFastest(std::stringstream &aux) {
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

template <class Player, class Time, class Version>
void Run<Player,Time,Version>::byName(std::stringstream &aux, std::string nm) {
    if (faster != NULL) {
	    faster->byName(aux, nm);
	}
	if (name == nm){
	    aux << name << ",";
		aux << printTime() << ",";
    	aux << version;
	    aux << "\n";
	}
	if (slower != NULL) {
	    slower->byName(aux, nm);
    }
}

template <class Player, class Time, class Version>
int Run<Player,Time,Version>::maxHeight(Run<Player,Time,Version> *segment){
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

template <class Player, class Time, class Version>
std::string Run<Player,Time,Version>::printTime() {
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

template <class Player, class Time, class Version>
void Run<Player,Time,Version>::printLinkList(std::stringstream &aux) {
    aux << name << ",";
	aux << printTime() << ",";
    aux << version;
	aux << "\n";
	if (next != NULL) {
	    next->printLinkList(aux);
	}
}

template <class Player, class Time, class Version>
class BSTree {
private:
	std::vector<Run<Player,Time,Version>*> TimeList;
	Run<Player,Time,Version> *root, *head, *tail;
    unsigned int tamanio;
	void mergeSplit(std::vector<Run<Player,Time,Version>*>&, int, int);
	void mergeArr(std::vector<Run<Player,Time,Version>*>&, int, int, int);
	void copyArr(std::vector<Run<Player,Time,Version>*>&, int, int);

public:
	BSTree();//
	~BSTree();//
	bool empty() const;//
	void add(std::string, int, std::string); //
	void remove(std::string, int, std::string); //
	void removeAll();//
	std::string fromFastest(); //
    std::string byName(std::string); //
	int size() const; //
	int height(); //
	void linkTimes();//
	void sortMerge();
	std::string printLinkList();
};

template <class Player, class Time, class Version>
BSTree<Player,Time,Version>::BSTree() :root(0), tamanio(0) {
}

template <class Player, class Time, class Version>
BSTree<Player,Time,Version>::~BSTree() {
	removeAll();
}

template <class Player, class Time, class Version> //Verifica si el arbol y la lista estan vacios
bool BSTree<Player,Time,Version>::empty() const{
    return (root==NULL);
}

template <class Player, class Time, class Version> //Agrega un nuevo Run al arbol y al final de la lista vinculada
void BSTree<Player,Time,Version>::add(std::string nm, int secs, std::string ver){
    if (!empty()){
        Run<Player,Time,Version> *addition = root->add(nm,secs,ver);
		TimeList.push_back(addition);
        tamanio++;
    } else {
        root = new Run<Player,Time,Version>(nm, secs, ver);
		head = root;
		tail = root;
		TimeList.push_back(root);
        tamanio++;
    }
}

template <class Player, class Time, class Version>
void BSTree<Player,Time,Version>::remove(std::string nm, int secs, std::string ver) {
	if (root != NULL) {
		if (nm == root->name && secs == root->Tseconds && ver == root->version) {
			Run<Player,Time,Version> *succ = root->succesor();
			if (succ != NULL) {
				succ->faster = root->faster;
				succ->slower = root->slower;
			}
			TimeList.erase(std::remove(TimeList.begin(), TimeList.end(), root), TimeList.end());
			delete root;
			root = succ;
			tamanio--;
		} else {
			root->remove(nm, secs, ver, TimeList);
			tamanio--;
		}
	}
}

template <class Player, class Time, class Version>
void BSTree<Player,Time,Version>::removeAll() {
	if (root != NULL) {
		root->removeChilds();
	}
	delete root;
	root = NULL;
	head = NULL;
	tail = NULL;
	TimeList.clear();
    tamanio = 0;
}

template <class Player, class Time, class Version> // Imprime tiempos desde el mas rapido
std::string BSTree<Player,Time,Version>::fromFastest(){
    std::stringstream aux;
	root->fromFastest(aux);
    return aux.str();
}

template <class Player, class Time, class Version> // Imprime tiempos de una persona en especifico	
std::string BSTree<Player,Time,Version>::byName(std::string nm){
    std::stringstream aux;
	root->byName(aux, nm);
    return aux.str();
}

template <class Player, class Time, class Version>  // Regresa la altura del arbol
int BSTree<Player,Time,Version>::height(){
	if (!empty()){
		return root->maxHeight(root);
	} else {
		return 0;
	}
}

template <class Player, class Time, class Version> //Regresa el tamanio de la lista vinculada
int BSTree<Player,Time,Version>::size() const{
    return tamanio;
}

template <class Player, class Time, class Version>
void BSTree<Player,Time,Version>::copyArr(std::vector<Run<Player,Time,Version>*> &B, int L, int H) {
	for (int i = L; i <= H; i++) {
		TimeList[i] = B[i];
	};
};


template <class Player, class Time, class Version>
void BSTree<Player,Time,Version>::mergeArr(std::vector<Run<Player,Time,Version>*> &B, int L, int hal, int H) {
	int i, j, k;

	i = L;
	j = hal + 1;
	k = L;
	while (i <= hal && j<=H) {
		if (TimeList[i]->Tseconds < TimeList[j]->Tseconds) {
			B[k] = TimeList[i];
			i++;
		} else {
			B[k] = TimeList[j];
			j++;
		}
		k++;
	}
	if (i > hal) {
		for (; j <= H; j++) {
			B[k++] = TimeList[j];
		};
	} else {
		for (; i <= hal; i++) {
			B[k++] = TimeList[i];
		};
	};
};

template <class Player, class Time, class Version>
void BSTree<Player,Time,Version>::mergeSplit(std::vector<Run<Player,Time,Version>*> &B, int L, int H) {
	if ((H - L) < 1) {
		return; // Verifica si ya no se puede separar en mitades
	}
	int hal = (H + L) / 2;
	mergeSplit(B, L, hal); // Agarra la primera mitad del array TimeList para ordenarlo en B
	mergeSplit(B, (hal + 1), H); // Agarra la segunda mitad del array TimeList para ordenarlo en B
	mergeArr(B, L, hal, H); // Combina los arrays 
	copyArr(B, L, H); // Copia los valores de B hacia TimeList
};

template <class Player, class Time, class Version>
void BSTree<Player,Time,Version>::sortMerge(){
    std::vector<Run<Player,Time,Version>*> tarr(tamanio);
    mergeSplit(tarr, 0, (tamanio - 1));
};

template <class Player, class Time, class Version>
void BSTree<Player,Time,Version>::linkTimes(){
	head = TimeList[0];
	tail = TimeList[tamanio-1];
	head->previous = NULL;
	for (int i=0;i<tamanio;i++){
		if (i==tamanio-1) {
			TimeList[i]->next=NULL;
			return;
		}
		TimeList[i]->next=TimeList[i+1];
		TimeList[i+1]->previous=TimeList[i];
		
	}
}

template <class Player, class Time, class Version> // Imprime tiempos desde el mas rapido
std::string BSTree<Player,Time,Version>::printLinkList(){
    linkTimes();
	std::stringstream aux;
	head->printLinkList(aux);
    return aux.str();
}

#endif