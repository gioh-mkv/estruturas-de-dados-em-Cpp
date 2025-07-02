// -----------------------------------------------------------
// ---- Livro Algoritmos (CORMEN): Capitulo 12 ---------------
// ---- Arvore de Busca Binaria (Binary Search Tree) ---------
// -----------------------------------------------------------
#include <iostream>
#include <ctime>
using namespace std;


struct node {
	double valor;
	node* pai;
	node* esq;
	node* dir;

	node(double k) {//construtor
	    pai=esq=dir=NULL;
	    valor = k;
    }
};

// --------------------------------------------------------
// Classe de Arvores Binarias de Busca (Binary Search Tree)
// --------------------------------------------------------
class tree_bs {
    node* raiz;
    int N; //numero de elementos

    node* minimo(node* p);
    node* maximo(node* p);

    node* sucessor(node* p);
    node* predecessor(node* p);

    void apaga_tudo(node* p);
    void imprime_ordenado(node* p);
    void transplant(node* u, node* v);
    node* busca_rec(node* p, double k);

public:
    tree_bs();  //construtor
    ~tree_bs(); //destrutor

    node* busca(double k);
    node* busca_rec(double k);

    void apaga_tudo();
    void imprime_ordenado();
    void inserir(double k);
    void remover(node* z);
    int tamanho();
};


// -----------------------------------------------------------------
// ------ MAIN -----------------------------------------------------
// -----------------------------------------------------------------
int main() {
    tree_bs T;

    int N = 20;

    srand (time(NULL));
    cout.precision(2);
    for (int i=0;i<N;i++) {
        double valor = (double) rand()/RAND_MAX;
        T.inserir(valor);
    }
    T.imprime_ordenado();

    T.apaga_tudo();
    cout << endl;

    T.inserir(4);
    T.inserir(2);
    T.inserir(1);
    T.inserir(3);
    T.inserir(6);
    T.inserir(5);
    T.inserir(7);
    T.imprime_ordenado();

    cout << endl;
    T.remover(T.busca(4));
    T.imprime_ordenado();

    return 0;
}



// ------------------------------------------------------------------------------------------------
// ---- Algoritmos de Arvore Binaria de Busca (BINARY SEARCH TREE) --------------------------------
// ------------------------------------------------------------------------------------------------
tree_bs::tree_bs() {
    raiz=NULL;
    N=0;
}
tree_bs::~tree_bs() {
    apaga_tudo();
}

int tree_bs::tamanho() {
    return N;
}

// Apaga da memoria a arvore enraizada em p
void tree_bs::apaga_tudo() {
    apaga_tudo(raiz);
    raiz = NULL;
    N = 0;
}
void tree_bs::apaga_tudo(node* p) {
    if (p==NULL) return;
    apaga_tudo(p->esq);
    apaga_tudo(p->dir);
    delete p;
}

// Imprime em ordem os valores da subarvore de p (EM-ORDER)
void tree_bs::imprime_ordenado() {
    imprime_ordenado(raiz);
}
void tree_bs::imprime_ordenado(node* p) {
    if (p==NULL) return;
    imprime_ordenado(p->esq);
    cout << p->valor << " ";
    imprime_ordenado(p->dir);
}

// Procura recursivamente um no com valor k na subarvore de p
node* tree_bs::busca_rec(double k) {
    return busca_rec(raiz,k);
}
node* tree_bs::busca_rec(node* p, double k) {
    if ((p==NULL)||(p->valor==k)) {
        return p;
    }
    if (k < p->valor) {
        return busca_rec(p->esq, k);
    } else {
        return busca_rec(p->dir, k);
    }
}

// Procura iterativamente um no com valor k na subarvore de p
node* tree_bs::busca(double k) {
    node* p = raiz;
    while ((p!=NULL) && (p->valor!=k)) {
        if (k < p->valor)
            p = p->esq;
        else
            p = p->dir;
    }
    return p;
}

// Retorna o no com valor minimo na subarvore de p
node* tree_bs::minimo(node* p) {
    while (p->esq != NULL)
        p = p->esq;

    return p;
}

// Retorna o no com valor maximo na subarvore de p
node* tree_bs::maximo(node* p) {
    while (p->dir!=NULL)
        p = p->dir;

    return p;
}

// Retorna o sucessor do node apontado por p
node* tree_bs::sucessor(node* p) {
    if (p->dir!=NULL)
        return minimo(p->dir);

    node* pp = p->pai;
    while ((pp!=NULL) && (pp->esq!=p)) {
        p  = pp;
        pp = p->pai;
    }
    return pp;
}

// Retorna o predecessor do node apontado por p
node* tree_bs::predecessor(node* p) {
    if (p->esq!=NULL)
        return maximo(p->esq);

    node* pp = p->pai;
    while ((pp!=NULL) && (pp->dir!=p)) {
        p  = pp;
        pp = p->pai;
    }
    return pp;
}

// Insere um no com valor k
void tree_bs::inserir(double k) {
    node* z = new node(k);
    N++;

    node* pp = NULL;
    node* p  = raiz;
    while (p!=NULL) {
        pp = p;
        if (z->valor < p->valor)
             p = p->esq;
        else p = p->dir;
    }
    z->pai = pp;
    if (pp==NULL) raiz = z;
    else if (z->valor < pp->valor)
         pp->esq = z;
    else pp->dir = z;
}





// Remove no da arvore e a reorganiza
void tree_bs::transplant(node* u, node* v) {
    if (u==NULL) return;
    if (u->pai==NULL) {
        raiz = v;
    } else if (u == u->pai->esq) {
        u->pai->esq = v;
    } else {
        u->pai->dir = v;
    }
    if (v!=NULL) v->pai = u->pai;
}

void tree_bs::remover(node* z) {
    if (z==NULL) return;
    if (z->esq==NULL) {
        transplant(z, z->dir);
    } else if (z->dir==NULL) {
        transplant(z, z->esq);
    } else {
        node* suc = sucessor(z);
        if (suc->pai!=z) {
            transplant(suc, suc->dir);
            suc->dir = z->dir;
            suc->dir->pai = suc;
        }
        transplant(z, suc);
        suc->esq = z->esq;
        suc->esq->pai = suc;
    }
    N--;
    delete z;
}