// -------------------------------------------------------------
// ---- Livro Algoritmos (CORMEN): Capitulo 13 -----------------
// ---- Arvore Vermelho-Preto (ou Rubro-Negra ou Red-Black) ----
// -------------------------------------------------------------
#include <iostream>
#include <cmath>
#include <ctime>
#include <cfloat>
using namespace std;

struct node {
	double valor;
	struct node* pai;
	struct node* esq;
	struct node* dir;
	string cor;// "red", "black"
};


class tree_rb {
    node* nil;
    int N; //numero de elementos

    node* busca_rec(node* no, double k);
    node* busca_iter(node* no, double k);
    node* Minimo(node* no);
    node* Maximo(node* no);
    void apaga_tudo(node* no);
    void imprime_ordenado(node* no, int altura);
    void LeftRotate(node* x);
    void RightRotate(node* y);
    void InsertFixup(node* z);
    void Transplant(node* u, node* v);
    void DeleteFixup(node* x);

public:
    node* raiz;

    tree_rb();
    ~tree_rb();

    bool vazia();
    void imprime_ordenado();
    void apaga_tudo();
    node* busca_rec(double k);
    node* busca_iter(double k);
    node* Minimo();
    node* Maximo();
    node* Sucessor(node* no);
    node* Predecessor(node* no);
    void Insert(double k);
    void Delete(node* z);
};



// ------------------------------------------------------------
// --- MAIN ---------------------------------------------------
// ------------------------------------------------------------
int main() {
    tree_rb T;

    int i,j;
    int N = 20;
    srand (time(NULL));

    for (i=0;i<N;i++) {
        double k = (double) rand()/RAND_MAX;
        T.Insert(k);
    }

    while (! T.vazia()) {
        T.imprime_ordenado();
        T.Delete(T.raiz);
        cout << "\n-------------------------------- Remove Raiz ----\n";
    }
    return 0;
}



// ------------------------------------------------------------
// --- MANUTENCAO DE ARVORE VERMELHO-PRETO
// ------------------------------------------------------------
bool tree_rb::vazia() {
    if (raiz==nil) return true;
    return false;
}
tree_rb::tree_rb() {
    N = 0;
    nil = new node;
    raiz = nil;
    nil->pai = nil;
    nil->esq = nil;
    nil->dir = nil;
    nil->cor = 1;
    nil->valor = -DBL_MAX;
}
// ------------------------------------
// Apaga a arvore da memoria
// ------------------------------------
tree_rb::~tree_rb() {
    apaga_tudo();
    delete nil;
    nil = NULL;
}
// ------------------------------------
// Apaga da memoria a subarvore enraizada em no
// ------------------------------------
void tree_rb::apaga_tudo() {
    apaga_tudo(raiz);
    raiz=NULL;   N=0;
}
void tree_rb::apaga_tudo(node* no) {
    if ((no==NULL)||(no==nil)) return;
    apaga_tudo(no->esq);
    apaga_tudo(no->dir);
    delete no;
}

// ------------------------------------
// Imprime em ordem os valores da subarvore de no
// ------------------------------------
void tree_rb::imprime_ordenado() {
    imprime_ordenado(raiz,0);
}
void tree_rb::imprime_ordenado(node* no, int altura) {
    if (no==nil) return;
    imprime_ordenado(no->esq, altura+1);
    cout<<no->valor<<" , "<<no->cor<<" , "<<altura<<endl;
    imprime_ordenado(no->dir, altura+1);
}

// ------------------------------------
// Procura recursivamente um no com valor k na subarvore de no
// ------------------------------------
node* tree_rb::busca_rec(double k) {
    return busca_rec(raiz,k);
}
node* tree_rb::busca_rec(node* no, double k) {
    if ((no==nil)||(no->valor==k)) {
        return no;
    }
    if (k < no->valor) {
        return busca_rec(no->esq, k);
    } else {
        return busca_rec(no->dir, k);
    }
}

// ------------------------------------
// Procura iterativamente um no com valor k na subarvore de no
// ------------------------------------
node* tree_rb::busca_iter(double k) {
    return busca_iter(raiz,k);
}
node* tree_rb::busca_iter(node* no, double k) {
    while ((no!=nil)&&(no->valor!=k)) {
        if (k < no->valor)
            no = no->esq;
        else
            no = no->dir;
    }
    return no;
}

// ------------------------------------
// Retorna o no com valor minimo na subarvoore de no
// ------------------------------------
node* tree_rb::Minimo() {
    return Minimo(raiz);
}
node* tree_rb::Minimo(node* no) {
    while (no->esq != nil) {
        no = no->esq;
    }
    return no;
}

// ------------------------------------
// Retorna o no com valor maximo na subarvoore de no
// ------------------------------------
node* tree_rb::Maximo() {
    return Maximo(raiz);
}
node* tree_rb::Maximo(node* no) {
    while (no->dir!=nil) {
        no = no->dir;
    }
    return no;
}

// ------------------------------------
// Retorna o sucessor de no
// ------------------------------------
node* tree_rb::Sucessor(node* no) {
    if (no->dir != nil) {
        return Minimo(no->dir);
    }
    node* pai = no->pai;
    while ((pai != nil)&&(pai->esq!=no)) {
        no = pai;
        pai = pai->pai;
    }
    return pai;
}

// ------------------------------------
// Retorna o predecessor de no
// ------------------------------------
node* tree_rb::Predecessor(node* no) {
    if (no->esq != nil) {
        return Maximo(no->esq);
    }
    node* pai = no->pai;
    while ((pai!=nil)&&(pai->dir!=no)) {
        no = pai;
        pai = pai->pai;
    }
    return pai;
}


// ------------------------------------
// LEFT-ROTATE
// ------------------------------------
void tree_rb::LeftRotate(node* x) {
    node* y = x->dir;
    x->dir = y->esq;
    if (y->esq!=nil) y->esq->pai = x;
    y->pai = x->pai;
    if (x->pai==nil) raiz = y;
    else if (x==x->pai->esq)
        x->pai->esq = y;
    else
        x->pai->dir = y;
    y->esq = x;
    x->pai = y;
}

// ------------------------------------
// RIGHT-ROTATE
// ------------------------------------
void tree_rb::RightRotate(node* y) {
    node* x = y->esq;
    y->esq = x->dir;
    if (x->dir!=nil) x->dir->pai = y;
    x->pai = y->pai;
    if (y->pai==nil) raiz = x;
    else if (y==y->pai->dir)
        y->pai->dir = x;
    else
        y->pai->esq = x;
    x->dir = y;
    y->pai = x;
}

// ------------------------------------
// Corrige a arvore apos uma insercao
// ------------------------------------
void tree_rb::InsertFixup(node* z) {
    while (z->pai->cor=="red") {
        if (z->pai == z->pai->pai->esq) {
            node* y = z->pai->pai->dir;
            if (y->cor=="red") {
                z->pai->cor = "black";
                y->cor = "black";
                z->pai->pai->cor = "red";
                z = z->pai->pai;
            } else {
                if (z==z->pai->dir) {
                    z = z->pai;
                    LeftRotate(z);
                }
                z->pai->cor = "black";
                z->pai->pai->cor = "red";
                RightRotate(z->pai->pai);
            }
        } else {
            node* y = z->pai->pai->esq;
            if (y->cor=="red") {
                z->pai->cor = "black";
                y->cor = "black";
                z->pai->pai->cor = "red";
                z = z->pai->pai;
            } else {
                if (z==z->pai->esq) {
                    z = z->pai;
                    RightRotate(z);
                }
                z->pai->cor = "black";
                z->pai->pai->cor = "red";
                LeftRotate(z->pai->pai);
            }
        }
    }
    raiz->cor = "black";
}

// ------------------------------------
// Insere um no alocado na memoria
// ------------------------------------
void tree_rb::Insert(double k) {
    node* z = new node;
    z->pai = nil;
    z->esq = nil;
    z->dir = nil;
    z->valor = k;

    node* y = nil;
    node* x = raiz;
    while (x!=nil) {
        y = x;
        if (z->valor < x->valor)
             x = x->esq;
        else x = x->dir;
    }
    z->pai = y;
    if (y==nil) raiz = z;
    else if (z->valor < y->valor)
         y->esq = z;
    else y->dir = z;
    z->esq = nil;
    z->dir = nil;
    z->cor = "red";
    InsertFixup(z);
}





// ------------------------------------
// Transplanta o no v no lugar do no u
// ------------------------------------
void tree_rb::Transplant(node* u, node* v) {
    if (u==nil) return;
    if (u->pai==nil) {
        raiz = v;
    } else if (u==u->pai->esq) {
        u->pai->esq = v;
    } else {
        u->pai->dir = v;
    }
    v->pai = u->pai;
}
// ------------------------------------
// Reorganiza a arvore apos uma remocao
// ------------------------------------
void tree_rb::DeleteFixup(node* x) {
    while ((x!=raiz)&&(x->cor=="black")) {
        if (x==x->pai->esq) {
            node* w = x->pai->dir;
            if (w->cor=="red") {
                w->cor = "black";
                x->pai->cor = "red";
                LeftRotate(x->pai);
                w = x->pai->dir;
            }
            if ((w->esq->cor=="black")&&(w->dir->cor=="black")) {
                w->cor = "red";
                x = x->pai;
            } else {
                if (w->dir->cor=="black") {
                    w->esq->cor = "black";
                    w->cor = "red";
                    RightRotate(w);
                    w = x->pai->dir;
                }
                w->cor = x->pai->cor;
                x->pai->cor = "black";
                w->dir->cor = "black";
                LeftRotate(x->pai);
                x = raiz;
            }
        } else {
            node* w = x->pai->esq;
            if (w->cor=="red") {
                w->cor = "black";
                x->pai->cor = "red";
                RightRotate(x->pai);
                w = x->pai->esq;
            }
            if ((w->dir->cor=="black")&&(w->esq->cor=="black")) {
                w->cor = "red";
                x = x->pai;
            } else {
                if (w->esq->cor=="black") {
                    w->dir->cor = "black";
                    w->cor = "red";
                    LeftRotate(w);
                    w = x->pai->esq;
                }
                w->cor = x->pai->cor;
                x->pai->cor = "black";
                w->esq->cor = "black";
                RightRotate(x->pai);
                x = raiz;
            }
        }
    }
}
// ------------------------------------
// Remove um no da arvore
// ------------------------------------
void tree_rb::Delete(node* z) {
    if (z==nil) return;
    node* x;
    node* suc = z;
    string suc_cor_original = suc->cor;
    if (z->esq==nil) {
        x = z->dir;
        Transplant(z,x);
    } else if (z->dir==nil) {
        x = z->esq;
        Transplant(z,x);
    } else {
        suc = Sucessor(z);
        suc_cor_original = suc->cor;
        x = suc->dir;
        if (suc->pai!=z) {
            Transplant(suc,x);
            suc->dir = z->dir;
            suc->dir->pai = suc;
        } else {
            x->pai = suc;
        }
        Transplant(z,suc);
        suc->esq = z->esq;
        suc->esq->pai = suc;
        suc->cor = z->cor;
    }
    if (suc_cor_original=="black") DeleteFixup(x);
}