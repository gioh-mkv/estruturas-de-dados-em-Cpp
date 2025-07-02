// ------------------------------------------------------------------------------------
// Secao 10.4 do Livro Algoritmos (de Cormen, Leiserson, Rivest, Stein) ---------------
// Implementacao de Arvores enraizadas (NAO-BINARIA) ----------------------------------
// ------------------------------------------------------------------------------------
#include <iostream>
#include <math.h>
#include <queue>
using namespace std;

struct node {
	char valor;
	node* pai;      // pai
	node* filhoesq; // filho esquerdo
	node* irmaodir; // irmao direito
};


class arvore {
    node* raiz;
    void apaga(node* p);
    void pre_ordem(node* p);
    void pos_ordem(node* p);
    node* sub_arvore(string &s, int &i);

public:
    arvore(string s); //construtor
    ~arvore();       //destrutor

    void apaga_tudo();
    void pre_ordem();
    void pos_ordem();
    void nivel_ordem();
};



// ------------------------------------------------------------------------------------
// ------- MAIN -----------------------------------------------------------------------
// ------------------------------------------------------------------------------------
int main()
{
    string s;
    //s = "(a     (b (e) (f))    (c (g (k)(l (m (n (o)(p)(q))))))     (d (h)(i)(j)))";
    //s = "(a (b)(c)(d) )";
    //s = "(a (b(d)(e)) (c(f)(g)) )";
    s  = "(R ";
    s += "(a (b (c)(d)(e)) (f (g)(h)(i)) (j (k)(l)(m)) )";
    s += "(n (o (p)(q)(r)) (s (t)(u)(v)) (w (x)(y)(z)) ))";
    arvore T (s);
    cout << "Pre-Ordem ----------------- "; T.pre_ordem();
    cout << "Pos-Ordem ----------------- "; T.pos_ordem();
    cout << "Nivel Ordem --------------- "; T.nivel_ordem();

    return 0;
}





// ------------------------------------------------------------------------------------
// ---- Algoritmos de ARVORES NORMAIS -------------------------------------------------
// ------------------------------------------------------------------------------------
arvore::arvore(string s) {
    int i = 0;
    raiz = sub_arvore(s,i);

    if (raiz!=NULL) {
        raiz->pai = NULL;
        raiz->irmaodir = NULL;
    }
}

node* arvore::sub_arvore(string &s, int &i) {
    while ((i<s.size()) && ((s[i]== '(') || (s[i]== ' ')) ) i++;
    if ((i>=s.size())||(s[i] == ')')) {
        i++;
        return NULL;
    }
    node* p = new node;
    p->valor = s[i++];

    node* q = sub_arvore(s,i);
    p->filhoesq = q;

    while(q != NULL) {
        q->pai = p;
        node* r = sub_arvore(s,i);
        q->irmaodir = r;
        q = r;
    }
    return p;
}



arvore::~arvore() {
    apaga_tudo();
}

// Deleta a arvore da memoria
void arvore::apaga_tudo() {
    apaga(raiz);
    raiz = NULL;
}

void arvore::apaga(node* p) {
    if (p==NULL) return;

    apaga(p->irmaodir);
    p->irmaodir = NULL;

    apaga(p->filhoesq);
    p->filhoesq = NULL;

    delete p;
}

// Lista os elementos em Pre-Ordem
void arvore::pre_ordem() {
    pre_ordem(raiz);
    cout << "\n";
}

void arvore::pre_ordem(node* p) {
    if (p==NULL) return;
    cout << p->valor << " ";
    node* noh = p->filhoesq;
    while (noh!=NULL) {
        pre_ordem(noh);
        noh = noh->irmaodir;
    }
}

// Lista os elementos em Pos-Ordem
void arvore::pos_ordem() {
    pos_ordem(raiz);
    cout << "\n";
}

void arvore::pos_ordem(node* p) {
    if (p==NULL) return;
    node* noh = p->filhoesq;
    while (noh!=NULL) {
        pos_ordem(noh);
        noh = noh->irmaodir;
    }
    cout << p->valor << " ";
}

// Lista os elementos por Nivel
void arvore::nivel_ordem() {
    if (raiz==NULL) return;

    queue<node*> Q;
    Q.push(raiz);

    while (!Q.empty()) {
        node* noh = Q.front();
        Q.pop();
        if (noh!=NULL) {
            cout << noh->valor << " ";
            noh = noh->filhoesq;
            while (noh!=NULL) {
                Q.push(noh);
                noh = noh->irmaodir;
            }
        }
    }
    cout << "\n";
}