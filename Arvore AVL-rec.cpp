// -----------------------------------------------------------
// ---- Livro Algoritmos (CORMEN): Capitulo 12 ---------------
// ---- Arvore de Busca Binaria (Binary Search Tree) ---------
// -----------------------------------------------------------
#include <iostream>
#include <ctime>
using namespace std;


struct node {
	char valor;
	node* esq;
	node* dir;
	int altura;// altura da subarvore com raiz no noh
	int tamanho;// tamanho da subarvore com raiz no noh

	node(char k) {//construtor
	    esq=dir=NULL;
	    valor = k;
	    altura =0;
	    tamanho=1;
    }
};

int alt(node* p) {
    if (p==NULL) return -1;
    return p->altura;
}

int tam(node* p) {
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
class tree_avl2 {
    node* raiz;

    node* minimo(node* p);
    node* maximo(node* p);

    void apaga_tudo(node* p);
    void imprime_ordenado(node* p, int flag=0);
    void transplant(node* u, node* v);
    node* busca_rec(node* p, char c);

    node* remover(char c, node* p);
    void inserir(char c, node* p);
    void atualiza(node* p);
    int ordem(node* p, char c);
    node* selecao(node* p, int k);

    void balanceamento(node* p, node* pp);
    void Rotacao_Direita(node* p, node* pp);
    void Rotacao_Esquerda(node* p, node* pp);
    void Rotacao_Direita_Dupla(node* p, node* pp);
    void Rotacao_Esquerda_Dupla(node* p, node* pp);

public:
    tree_avl2();  //construtor
    ~tree_avl2(); //destrutor

    node* busca(char c);
    node* busca_rec(char c);

    //int tamanho();
    void apaga_tudo();
    void imprime_ordenado(int flag=0);

    node* minimo();
    node* maximo();

    void inserir(string s);
    void remover(char c);

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
    tree_avl2 T;
    T.inserir(s);

    cout << "Aplicando os algoritmos de Selecao e de Ordem na Arvore Binaria de Busca modificada\n";
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


    cout << "Valores em ordem crescente, com suas alturas e tamanhos\n";
    cout << "Em seguida, removemos sucessivamente o maior elemento\n\n";




    T.imprime_ordenado();
    T.imprime_ordenado(1);
    T.imprime_ordenado(2);
    cout << "\n\n";



    node* p = T.maximo();
    while (p != NULL) {
        T.remover(p->valor);
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
tree_avl2::tree_avl2() {
    raiz=NULL;
}
tree_avl2::~tree_avl2() {
    apaga_tudo();
}

//int tree_bs::tamanho() {return raiz->tamanho;}

// Apaga da memoria a arvore enraizada em p
void tree_avl2::apaga_tudo() {
    apaga_tudo(raiz);
    raiz = NULL;
}
void tree_avl2::apaga_tudo(node* p) {
    if (p==NULL) return;
    apaga_tudo(p->esq);
    apaga_tudo(p->dir);
    delete p;
}



// Imprime em ordem os valores da subarvore de p (EM-ORDER)
void tree_avl2::imprime_ordenado(int flag) {
    imprime_ordenado(raiz,flag);
    cout << "\n";
}
void tree_avl2::imprime_ordenado(node* p, int flag) {
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
node* tree_avl2::busca_rec(char c) {
    return busca_rec(raiz, c);
}
node* tree_avl2::busca_rec(node* p, char c) {
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
node* tree_avl2::busca(char c) {
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
node* tree_avl2::minimo() {
    if (raiz==NULL) return NULL;
    return minimo(raiz);
}

node* tree_avl2::minimo(node* p) {
    while (p->esq != NULL) p = p->esq;
    return p;
}

// Retorna o no com valor maximo na subarvore de p
node* tree_avl2::maximo() {
    if (raiz==NULL) return NULL;
    return maximo(raiz);
}

node* tree_avl2::maximo(node* p) {
    while (p->dir!=NULL) p = p->dir;
    return p;
}






// Insere um no com valor c
void tree_avl2::inserir(string s) {
    for (int i=0; i<s.size(); i++) {
        inserir(s[i], raiz);
        balanceamento(raiz, NULL);
    }
}

void tree_avl2::inserir(char c, node* p) {

    if (raiz==NULL) {
        raiz = new node(c);
        return;
    }

    if (c < p->valor)
        if (p->esq == NULL)
            p->esq = new node(c);
        else
            inserir(c, p->esq);
    else
        if (p->dir == NULL)
            p->dir = new node(c);
        else
            inserir(c, p->dir);


    atualiza(p);
}





// Remove no da arvore com valor c
void tree_avl2::remover(char c) {
    raiz = remover(c, raiz);
}

node* tree_avl2::remover(char c, node* p) {
    node* r = p;
    if (p==NULL) return r;

    if (c == p->valor) {
        if ((p->esq!=NULL)&&(p->dir!=NULL)) {
            node* suc = minimo(p->dir);
            p->valor = suc->valor;
            p->dir = remover(suc->valor, p->dir);
        } else {
            r = NULL;
            if (p->esq!=NULL) r = p->esq; else
            if (p->dir!=NULL) r = p->dir;
            delete p;
        }
    }
    else   if (c < p->valor)
        p->esq = remover(c, p->esq);
    else //if (c > p->valor)
        p->dir = remover(c, p->dir);

    atualiza(r);
    return r;
}






node* tree_avl2::selecao(int k) {return selecao(raiz, k);}

node* tree_avl2::selecao(node* p, int k) {
    if (p==NULL) return NULL;
    if ( k < 1 ) return NULL;
    if ( k >= p->tamanho) return maximo(p);

    if (k == tam(p->esq)+1) return p;
    if (k <= tam(p->esq))
        return selecao(p->esq, k);

    return selecao(p->dir, k-1 - tam(p->esq));
}



int tree_avl2::ordem(char c) {return ordem(raiz, c);}

int tree_avl2::ordem(node* p, char c) {
    if (p==NULL) return -INT_MAX;

    if (c == p->valor) return tam(p->esq) + 1;
    if (c <  p->valor)
        return ordem(p->esq, c);

    return ordem(p->dir, c) + tam(p->esq) + 1;
}





void tree_avl2::atualiza(node* p) {
    if (p==NULL) return;

    balanceamento(p->esq, p);
    balanceamento(p->dir, p);

    p->altura  = 1 + max(alt(p->esq) , alt(p->dir));
    p->tamanho = 1 +     tam(p->esq) + tam(p->dir);
}


void tree_avl2::balanceamento(node* p, node* pp) {
    if (p==NULL) return;

    if (alt(p->esq) > alt(p->dir)+1)
        if (alt(p->esq->esq) >= alt(p->esq->dir))
            Rotacao_Direita(p, pp);
        else
            Rotacao_Direita_Dupla(p, pp);
    else
    if (alt(p->dir) > alt(p->esq)+1)
        if (alt(p->dir->dir) >= alt(p->dir->esq))
            Rotacao_Esquerda(p, pp);
        else
            Rotacao_Esquerda_Dupla(p, pp);

}



// ------------------------------------
// Algoritmos de Rotacoes de Nohs
// ------------------------------------
void tree_avl2::Rotacao_Direita(node* p, node* pp) {
    node* q = p->esq;
    p->esq = q->dir;

    if (pp==NULL) raiz = q;
    else if (p==pp->esq)
        pp->esq = q;
    else
        pp->dir = q;

    q->dir = p;

    p->altura  = 1 + max(alt(p->esq) , alt(p->dir));
    q->altura  = 1 + max(alt(q->esq) , alt(q->dir));
    p->tamanho = 1 +     tam(p->esq) + tam(p->dir);
    q->tamanho = 1 +     tam(q->esq) + tam(q->dir);
}

void tree_avl2::Rotacao_Esquerda(node* p, node* pp) {
    node* q = p->dir;
    p->dir = q->esq;

    if (pp==NULL) raiz = q;
    else if (p==pp->esq)
        pp->esq = q;
    else
        pp->dir = q;
    q->esq = p;

    p->altura  = 1 + max(alt(p->esq) , alt(p->dir));
    q->altura  = 1 + max(alt(q->esq) , alt(q->dir));
    p->tamanho = 1 +     tam(p->esq) + tam(p->dir);
    q->tamanho = 1 +     tam(q->esq) + tam(q->dir);
}

void tree_avl2::Rotacao_Direita_Dupla(node* p, node* pp) {
    Rotacao_Esquerda(p->esq, p);
    Rotacao_Direita(p, pp);
}

void tree_avl2::Rotacao_Esquerda_Dupla(node* p, node* pp) {
    Rotacao_Direita(p->dir, p);
    Rotacao_Esquerda(p, pp);
}