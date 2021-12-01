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

template <class T1, class T2, class T3> class BSTree;

template <class T1, class T2, class T3>
class Run {
private:
    unsigned int Tseconds, hours, minutes, seconds;
    std::string name, version;
    
public:
	Run(std::string, unsigned int, std::string);
	Run(std::string, unsigned int, std::string, Run<T1,T2,T3>*, Run<T1,T2,T3>*);
	Run(const Run<T1,T2,T3>&);
	Run<T1,T2,T3> *faster, *slower, *next;
    void TotalTime(unsigned int, unsigned int, unsigned int);
	Run<T1,T2,T3>* add(std::string, unsigned int, std::string);
	Run<T1,T2,T3>* succesor();
	void remove(std::string, unsigned int, std::string, std::vector<Run<T1,T2,T3>*>&);
	void removeChilds(); //
	void fromFastest(std::stringstream&);//
	void byName(std::stringstream&, std::string);
    int maxHeight(Run<T1,T2,T3>*);//
    std::string printTime();//
	void printLinkList(std::stringstream&);
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
void Run<T1,T2,T3>::remove(std::string nm, unsigned int secs, std::string ver, std::vector<Run<T1,T2,T3>*>&TimeList) {
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
				TimeList.erase(std::remove(TimeList.begin(), TimeList.end(), old), TimeList.end());
				delete old;
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
				TimeList.erase(std::remove(TimeList.begin(), TimeList.end(), old), TimeList.end());
				delete old;
			} else {
				slower->remove(nm, secs, ver, TimeList);
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
	if (next != NULL) {
		next->removeChilds();
		delete next;
		next = NULL;
	}
}

template <class T1, class T2, class T3>
void Run<T1,T2,T3>::TotalTime(unsigned int hrs, unsigned int mins, unsigned int secs) {
    Tseconds = hrs*3600 + mins*60 + secs;
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
void Run<T1,T2,T3>::printLinkList(std::stringstream &aux) {
    aux << name << ",";
	aux << printTime() << ",";
    aux << version;
	aux << "\n";
	if (next != NULL) {
	    next->printLinkList(aux);
	}
}

template <class T1, class T2, class T3>
class BSTree {
private:
	std::vector<Run<T1,T2,T3>*> TimeList;
	Run<T1,T2,T3> *root, *head, *tail;
    unsigned int tamanio;
	void mergeSplit(std::vector<Run<T1,T2,T3>*>&, int, int);
	void mergeArr(std::vector<Run<T1,T2,T3>*>&, int, int, int);
	void copyArr(std::vector<Run<T1,T2,T3>*>&, int, int);

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

template <class T1, class T2, class T3>
BSTree<T1,T2,T3>::BSTree() :root(0), tamanio(0) {
}

template <class T1, class T2, class T3>
BSTree<T1,T2,T3>::~BSTree() {
	removeAll();
}

template <class T1, class T2, class T3> //Verifica si el arbol y la lista estan vacios
bool BSTree<T1,T2,T3>::empty() const{
    return (root==NULL);
}

template <class T1, class T2, class T3> //Agrega un nuevo Run al arbol y al final de la lista vinculada
void BSTree<T1,T2,T3>::add(std::string nm, int secs, std::string ver){
    if (!empty()){
        Run<T1,T2,T3> *addition = root->add(nm,secs,ver);
		TimeList.push_back(addition);
        tamanio++;
    } else {
        root = new Run<T1,T2,T3>(nm, secs, ver);
		head = root;
		tail = root;
		TimeList.push_back(root);
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

template <class T1, class T2, class T3>
void BSTree<T1,T2,T3>::removeAll() {
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


template <class T1, class T2, class T3>
void BSTree<T1,T2,T3>::copyArr(std::vector<Run<T1,T2,T3>*> &B, int L, int H) {
	for (int i = L; i <= H; i++) {
		TimeList[i] = B[i];
	};
};


template <class T1, class T2, class T3>
void BSTree<T1,T2,T3>::mergeArr(std::vector<Run<T1,T2,T3>*> &B, int L, int hal, int H) {
	size_t i, j, k;

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

template <class T1, class T2, class T3>
void BSTree<T1,T2,T3>::mergeSplit(std::vector<Run<T1,T2,T3>*> &B, int L, int H) {
	if ((H - L) < 1) {
		return; // Verifica si ya no se puede separar en mitades
	}
	int hal = (H + L) / 2;
	mergeSplit(B, L, hal); // Agarra la primera mitad del array TimeList para ordenarlo en B
	mergeSplit(B, (hal + 1), H); // Agarra la segunda mitad del array TimeList para ordenarlo en B
	mergeArr(B, L, hal, H); // Combina los arrays 
	copyArr(B, L, H); // Copia los valores de B hacia TimeList
};

template <class T1, class T2, class T3>
void BSTree<T1,T2,T3>::sortMerge(){
    std::vector<Run<T1,T2,T3>*> tarr(tamanio);
    mergeSplit(tarr, 0, (tamanio - 1));
};


template <class T1, class T2, class T3>
void BSTree<T1,T2,T3>::linkTimes(){
	head = TimeList[0];
	tail = TimeList[tamanio-1];
	for (int i=0;i<tamanio;i++){
		TimeList[i]->next=TimeList[i+1];
		if (i==tamanio-1) {
			TimeList[i]->next=NULL;
		}
	}
}

template <class T1, class T2, class T3> // Imprime tiempos desde el mas rapido
std::string BSTree<T1,T2,T3>::printLinkList(){
    linkTimes();
	std::stringstream aux;
	head->printLinkList(aux);
    return aux.str();
}


#endif