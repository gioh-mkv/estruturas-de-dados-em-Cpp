// ------------------------------------------------------------------------------------------------
// Secao 10.4 do Livro Algoritmos (de Cormen, Leiserson, Rivest, Stein)
// Implementacao de Arvores enraizadas (BINARIA)
// ------------------------------------------------------------------------------------------------
#include <iostream> //cout
#include <queue>
#include <stack>
#include <vector>
using namespace std;

struct node {
    int valor;
    node* pai;  // node pai
    node* fesq; // filho esquerdo
    node* fdir; // filho direito
};


class arvore_bin {
    node* raiz;
    void pre_ordem(node* p);
    void pos_ordem(node* p);
    void  em_ordem(node* p);
    void apaga(node* p);

public:
    arvore_bin(int N); //construtor
    ~arvore_bin();    //destrutor

    void reconstroi(int N);
    void apaga_tudo();

    void pre_ordem();
    void pos_ordem();
    void  em_ordem();
    void pre_ordem_nao_rec();
    void nivel_ordem();
};


// ------------------------------------------------------------------------------------------------
// ---------- MAIN --------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
int main() {
    int N = 7;
    arvore_bin T(N);

    //cout<<"Arvore binaria completa com "<<h<<" niveis preenchida em Pre-Ordem";
    cout << "------------------------------------------------------------\n";
    cout << "Arvore binaria com "<<N<<" elementos (preenchida por niveis)\n";
    cout << "------------------------------------------------------------\n\n";

    cout<<"Pre-Ordem (busca em profundidade):\n";
    T.pre_ordem();
    cout<<"\n\n\n";

    cout<<"Pos-Ordem:\n";
    T.pos_ordem();
    cout<<"\n\n\n";

    cout<<"Em-Ordem:\n";
    T.em_ordem();
    cout<<"\n\n\n";

    cout<<"Ordem por Nivel (busca em largura):\n";
    T.nivel_ordem();
    cout<<"\n\n\n";

    cout<<"Pre-Ordem NAO-recursiva (usando Pilha):\n";
    T.pre_ordem_nao_rec();
    cout<<"\n\n\n";


    // ---------------------------------------------------------------------
    // Recomeca tudo de novo
    // ---------------------------------------------------------------------
    N = 31;
    T.reconstroi(N);

    cout << "------------------------------------------------------------\n";
    cout << "Arvore binaria com "<<N<<" elementos (preenchida por niveis)\n";
    cout << "------------------------------------------------------------\n\n";

    cout<<"Pre-Ordem (busca em profundidade):\n";
    T.pre_ordem();
    cout<<"\n\n\n";

    cout<<"Pos-Ordem:\n";
    T.pos_ordem();
    cout<<"\n\n\n";

    cout<<"Em-Ordem:\n";
    T.em_ordem();
    cout<<"\n\n\n";

    cout<<"Ordem por Nivel (busca em largura):\n";
    T.nivel_ordem();
    cout<<"\n\n\n";

    cout<<"Pre-Ordem NAO-recursiva (usando Pilha):\n";
    T.pre_ordem_nao_rec();
    cout<<"\n\n\n";

    return 0;
}



// ------------------------------------------------------------------------------------------------
// ---- Algoritmos de ARVORES BINARIAS ------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
arvore_bin::arvore_bin(int N) {
    raiz = NULL;
    reconstroi(N);
}

arvore_bin::~arvore_bin() {
    apaga_tudo();
}

void arvore_bin::apaga_tudo() {
    apaga(raiz);
    raiz = NULL;
}

// Deleta a arvore da memoria
void arvore_bin::apaga(node* p) {
    if (p==NULL) return;

    apaga(p->fesq);
    p->fesq = NULL;

    apaga(p->fdir);
    p->fdir = NULL;

    delete p;
}


void arvore_bin::reconstroi(int N) {
    apaga_tudo();
    if (N<=0) {raiz = NULL; return;}

    vector<node*> vet(N+1, NULL);
    vet[0] = NULL;
    for (int i=1; i<=N; i++) {
        vet[i] = new node;
        vet[i]->valor = i;
        vet[i]->pai = vet[i/2];
        vet[i]->fesq = NULL;
        vet[i]->fdir = NULL;
        if (i==1) continue;
        if (i%2==0)
             vet[i]->pai->fesq = vet[i];
        else vet[i]->pai->fdir = vet[i];
    }
    raiz = vet[1];
}

// Lista os elementos em PRE-Ordem
void arvore_bin::pre_ordem() {pre_ordem(raiz);}
void arvore_bin::pre_ordem(node* p) {
    if (p==NULL) return;
    cout << p->valor << " ";
    pre_ordem(p->fesq);
    pre_ordem(p->fdir);
}

// Lista os elementos em POS-Ordem
void arvore_bin::pos_ordem() {pos_ordem(raiz);}
void arvore_bin::pos_ordem(node* p) {
    if (p==NULL) return;
    pos_ordem(p->fesq);
    pos_ordem(p->fdir);
    cout << p->valor << " ";
}

// Lista os elementos em EM-Ordem
void arvore_bin::em_ordem() {em_ordem(raiz);}
void arvore_bin::em_ordem(node* p) {
    if (p==NULL) return;
    em_ordem(p->fesq);
    cout << p->valor << " ";
    em_ordem(p->fdir);
}

// Lista os elementos por Nivel
void arvore_bin::nivel_ordem() {
    if (raiz==NULL) return;

    queue<node*> Q;
    Q.push(raiz);

    while (!Q.empty()) {
        node* noh = Q.front();
        Q.pop();
        if (noh!=NULL) {
            cout << noh->valor << " ";
            if (noh->fesq!=NULL) Q.push(noh->fesq);
            if (noh->fdir!=NULL) Q.push(noh->fdir);
        }
    }
}


// Lista os elementos em Pre-Ordem usando Pilha (Nao recursivo)
void arvore_bin::pre_ordem_nao_rec() {
    if (raiz==NULL) return;

    stack<node*> Q;
    Q.push(raiz);

    while (!Q.empty()) {
        node* noh = Q.top();
        Q.pop();
        if (noh!=NULL) {
            cout << noh->valor << " ";
            if (noh->fdir!=NULL) Q.push(noh->fdir);
            if (noh->fesq!=NULL) Q.push(noh->fesq);
        }
    }
}