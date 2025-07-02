// ---------------------------------------------------------------------
// -- Livro Estruturas de Dados e Seus Algoritmos (Jayme Szwarcfiter) --
// ----------------------- Arvore AVL ----------------------------------
// ---------------------------------------------------------------------
#include <iostream>
#include <ctime>
using namespace std;


struct node {
    char valor;
    node* pai;
    node* esq;
    node* dir;
    int altura;// altura da subarvore com raiz no noh
    int tamanho;// tamanho da subarvore com raiz no noh

    node(char k) {//construtor
        pai=esq=dir=NULL;
        valor = k;
        tamanho=1;
    }
};

int altura(node* p) {
    if (p==NULL) return -1;
    return p->altura;
}

int tamanho(node* p) {
    if (p==NULL) return 0;
    return p->tamanho;
}

void embaralha(string& s) {
    //srand (time(NULL));
    for (int i=s.size()-1; i>=0; i--) {
        int k = rand()%(i+1);
        char c = s[i];
        s[i] = s[k];
        s[k] = c;
    }
}

void inverte(string& s) {
    int n = s.size();
    for (int i=0; i<=(n-1)/2; i++) {
        char c = s[i];
        s[i] = s[n-i-1];
        s[n-i-1] = c;
    }
}

// --------------------------------------------------------
// Classe de Arvores Binarias de Busca (Binary Search Tree)
// --------------------------------------------------------
class tree_avl {
    node* raiz;

    node* minimo(node* p);
    node* maximo(node* p);

    void apaga_tudo(node* p);
    void imprime_ordenado(node* p, int flag=0);
    void transplant(node* u, node* v);
    node* busca_rec(node* p, char c);

    void inserir(char c);
    void atualizar_alt_tam(node* p);
    int ordem(node* p, char c);
    node* selecao(node* p, int k);

    void Rotacao_Direita(node* p);
    void Rotacao_Esquerda(node* p);
    void Rotacao_Direita_Dupla(node* p);
    void Rotacao_Esquerda_Dupla(node* p);

public:
    tree_avl();  //construtor
    ~tree_avl(); //destrutor

    node* busca(char c);
    node* busca_rec(char c);

    //int tamanho();
    void apaga_tudo();
    void imprime_ordenado(int flag=0);

    node* minimo();
    node* maximo();
    node* sucessor(node* p);
    node* predecessor(node* p);

    void inserir(string s);
    void remover(node* z);

    int ordem(char c);
    node* selecao(int k);
};


// -----------------------------------------------------------------
// ------ MAIN -----------------------------------------------------
// -----------------------------------------------------------------
void roda_exemplo(string s);

int main() {

    cout << "---------------------------------------------------------------\n";
    string s = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    roda_exemplo(s);

    cout << "---------------------------------------------------------------\n";
    inverte(s);
    roda_exemplo(s);

    cout << "---------------------------------------------------------------\n";
    inverte(s);
    embaralha(s);
    roda_exemplo(s);

    return 0;
}

void roda_exemplo(string s) {
    cout << "Ordem em que as letras foram inseridas: " << s << "\n\n";
    tree_avl T;
    T.inserir(s);

    cout << "Aplicando os algoritmos de Selecao e de Ordem na Arvore AVL\n";
    for (int i=1; i<=s.size(); i++) {
        node* p = T.selecao(i);

        if (i>9) cout << " ";
        cout << p->valor << " ";
    }
    cout << "\n";

    string ord = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i=0; i<ord.size(); i++) {
        cout << T.ordem(ord[i]) << " ";
    }
    cout << "\n\n";


    cout << "Valores em ordem crescente, com suas alturas e tamanhos na Arvore AVL\n";
    cout << "Em seguida, removemos sucessivamente o maior elemento\n\n";

    T.imprime_ordenado();
    T.imprime_ordenado(1);
    T.imprime_ordenado(2);
    cout << "\n\n";



    node* p = T.maximo();
    while (p != NULL) {
        T.remover(p);
        T.imprime_ordenado();
        T.imprime_ordenado(1);
        T.imprime_ordenado(2);
        cout << "\n";
        p = T.maximo();
    }
}




// ----------------------------------------------------------------
// -- Algoritmos de Arvore Binaria de Busca (BINARY SEARCH TREE) --
// ----------------------------------------------------------------
tree_avl::tree_avl() {
    raiz=NULL;
}
tree_avl::~tree_avl() {
    apaga_tudo();
}

//int tree_bs::tamanho() {return raiz->tamanho;}

// Apaga da memoria a arvore enraizada em p
void tree_avl::apaga_tudo() {
    apaga_tudo(raiz);
    raiz = NULL;
}
void tree_avl::apaga_tudo(node* p) {
    if (p==NULL) return;
    apaga_tudo(p->esq);
    apaga_tudo(p->dir);
    delete p;
}



// Imprime em ordem os valores da subarvore de p (EM-ORDER)
void tree_avl::imprime_ordenado(int flag) {
    imprime_ordenado(raiz,flag);
    cout << "\n";
}
void tree_avl::imprime_ordenado(node* p, int flag) {
    if (p==NULL) return;
    imprime_ordenado(p->esq, flag);

    if (flag==2) {
        cout << p->tamanho << " ";
    } else if (flag==1) {
        if (p->tamanho>9) cout << " ";
        cout << p->altura << " ";
    } else {
        if (p->tamanho>9) cout << " ";
        cout << p->valor << " ";
    }
    imprime_ordenado(p->dir, flag);
}



// Procura recursivamente um no com valor k na subarvore de p
node* tree_avl::busca_rec(char c) {
    return busca_rec(raiz, c);
}
node* tree_avl::busca_rec(node* p, char c) {
    if ((p==NULL)||(p->valor==c)) {
        return p;
    }
    if (c < p->valor) {
        return busca_rec(p->esq, c);
    } else {
        return busca_rec(p->dir, c);
    }
}

// Procura iterativamente um no com valor k na subarvore de p
node* tree_avl::busca(char c) {
    node* p = raiz;
    while ((p!=NULL) && (p->valor!=c)) {
        if (c < p->valor)
            p = p->esq;
        else
            p = p->dir;
    }
    return p;
}



// Retorna o no com valor minimo na subarvore de p
node* tree_avl::minimo() {
    if (raiz==NULL) return NULL;
    return minimo(raiz);
}

node* tree_avl::minimo(node* p) {
    while (p->esq != NULL) p = p->esq;
    return p;
}

// Retorna o no com valor maximo na subarvore de p
node* tree_avl::maximo() {
    if (raiz==NULL) return NULL;
    return maximo(raiz);
}

node* tree_avl::maximo(node* p) {
    while (p->dir!=NULL) p = p->dir;
    return p;
}

// Retorna o sucessor do node apontado por p
node* tree_avl::sucessor(node* p) {
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
node* tree_avl::predecessor(node* p) {
    if (p->esq!=NULL)
        return maximo(p->esq);

    node* pp = p->pai;
    while ((pp!=NULL) && (pp->dir!=p)) {
        p  = pp;
        pp = p->pai;
    }
    return pp;
}



// Insere um no com valor c
void tree_avl::inserir(string s) {
    for (int i=0; i<s.size(); i++)
        inserir(s[i]);
}

void tree_avl::inserir(char c) {
    node* z = new node(c);

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
    else //if (z->valor > pp->valor)
        pp->dir = z;
    //else if (rand()%2)
    //    pp->esq = z;
    //else
    //    pp->dir = z;



    atualizar_alt_tam(z);
}





// Remove no da arvore e a reorganiza
void tree_avl::remover(node* z) {
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
        suc->esq = z->esq;
        suc->esq->pai = suc;
        transplant(z, suc);
    }
    delete z;
}

void tree_avl::transplant(node* u, node* v) {
    if (u==NULL) return;
    if (u->pai==NULL) {
        raiz = v;
    } else if (u == u->pai->esq) {
        u->pai->esq = v;
    } else {
        u->pai->dir = v;
    }
    if (v!=NULL) v->pai = u->pai;



    if (v!=NULL) atualizar_alt_tam(v);
    else         atualizar_alt_tam(u->pai);
}





void tree_avl::atualizar_alt_tam(node* p) {
    if (p==NULL) return;

    /**/
    if (altura(p->esq) > altura(p->dir)+1)
        if (altura(p->esq->esq) >= altura(p->esq->dir))
            Rotacao_Direita(p);
        else
            Rotacao_Direita_Dupla(p);
    else
    if (altura(p->dir) > altura(p->esq)+1)
        if (altura(p->dir->dir) >= altura(p->dir->esq))
            Rotacao_Esquerda(p);
        else
            Rotacao_Esquerda_Dupla(p);
    /**/

    p->altura = 1 + max(altura(p->esq),altura(p->dir));
    p->tamanho = 1 + tamanho(p->esq) + tamanho(p->dir);

    atualizar_alt_tam(p->pai);
}




node* tree_avl::selecao(int k) {return selecao(raiz, k);}

node* tree_avl::selecao(node* p, int k) {
    if (p==NULL) return NULL;
    if ( k < 1 ) return NULL;
    if ( k >= p->tamanho) return maximo(p);

    if (k == tamanho(p->esq)+1) return p;
    if (k <= tamanho(p->esq))
        return selecao(p->esq, k);

    return selecao(p->dir, k-1 - tamanho(p->esq));
}


int tree_avl::ordem(char c) {return ordem(raiz, c);}

int tree_avl::ordem(node* p, char c) {
    if (p==NULL) return -INT_MAX;

    if (c == p->valor) return tamanho(p->esq) + 1;
    if (c <  p->valor)
        return ordem(p->esq, c);

    return ordem(p->dir, c) + tamanho(p->esq) + 1;
}





// ------------------------------------
// Algoritmos de Rotacoes de Nohs
// ------------------------------------
void tree_avl::Rotacao_Direita(node* p) {
    node* q = p->esq;
    p->esq = q->dir;
    if (p->esq!=NULL) p->esq->pai = p;

    if (p->pai==NULL) raiz = q;
    else if (p==p->pai->esq)
        p->pai->esq = q;
    else
        p->pai->dir = q;

    q->pai = p->pai;
    q->dir = p;
    p->pai = q;

    p->altura  = 1 + max( altura(p->esq) ,  altura(p->dir) );
    q->altura  = 1 + max( altura(q->esq) ,  altura(q->dir) );
    p->tamanho = 1 +     tamanho(p->esq) + tamanho(p->dir);
    q->tamanho = 1 +     tamanho(q->esq) + tamanho(q->dir);
}

void tree_avl::Rotacao_Esquerda(node* p) {
    node* q = p->dir;
    p->dir = q->esq;
    if (p->dir!=NULL) p->dir->pai = p;

    if (p->pai==NULL) raiz = q;
    else if (p==p->pai->esq)
        p->pai->esq = q;
    else
        p->pai->dir = q;
    q->pai = p->pai;
    q->esq = p;
    p->pai = q;

    p->altura  = 1 + max( altura(p->esq) ,  altura(p->dir) );
    q->altura  = 1 + max( altura(q->esq) ,  altura(q->dir) );
    p->tamanho = 1 +     tamanho(p->esq) + tamanho(p->dir);
    q->tamanho = 1 +     tamanho(q->esq) + tamanho(q->dir);
}

void tree_avl::Rotacao_Direita_Dupla(node* p) {
    Rotacao_Esquerda(p->esq);
    Rotacao_Direita(p);
}

void tree_avl::Rotacao_Esquerda_Dupla(node* p) {
    Rotacao_Direita(p->dir);
    Rotacao_Esquerda(p);
}