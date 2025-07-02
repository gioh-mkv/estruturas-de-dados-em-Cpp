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
class tree_bs3 {
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

public:
    tree_bs3();  //construtor
    ~tree_bs3(); //destrutor

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
    tree_bs3 T;
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
tree_bs3::tree_bs3() {
    raiz=NULL;
}
tree_bs3::~tree_bs3() {
    apaga_tudo();
}

//int tree_bs::tamanho() {return raiz->tamanho;}

// Apaga da memoria a arvore enraizada em p
void tree_bs3::apaga_tudo() {
    apaga_tudo(raiz);
    raiz = NULL;
}
void tree_bs3::apaga_tudo(node* p) {
    if (p==NULL) return;
    apaga_tudo(p->esq);
    apaga_tudo(p->dir);
    delete p;
}



// Imprime em ordem os valores da subarvore de p (EM-ORDER)
void tree_bs3::imprime_ordenado(int flag) {
    imprime_ordenado(raiz,flag);
    cout << "\n";
}
void tree_bs3::imprime_ordenado(node* p, int flag) {
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
node* tree_bs3::busca_rec(char c) {
    return busca_rec(raiz, c);
}
node* tree_bs3::busca_rec(node* p, char c) {
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
node* tree_bs3::busca(char c) {
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
node* tree_bs3::minimo() {
    if (raiz==NULL) return NULL;
    return minimo(raiz);
}

node* tree_bs3::minimo(node* p) {
    while (p->esq != NULL) p = p->esq;
    return p;
}

// Retorna o no com valor maximo na subarvore de p
node* tree_bs3::maximo() {
    if (raiz==NULL) return NULL;
    return maximo(raiz);
}

node* tree_bs3::maximo(node* p) {
    while (p->dir!=NULL) p = p->dir;
    return p;
}






// Insere um no com valor c
void tree_bs3::inserir(string s) {
    for (int i=0; i<s.size(); i++)
        inserir(s[i], raiz);
}

void tree_bs3::inserir(char c, node* p) {

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
void tree_bs3::remover(char c) {
    raiz = remover(c, raiz);
}

node* tree_bs3::remover(char c, node* p) {
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



void tree_bs3::atualiza(node* p) {
    if (p==NULL) return;

    p->altura  = 1 + max(alt(p->esq) , alt(p->dir));
    p->tamanho = 1 +     tam(p->esq) + tam(p->dir);
}



node* tree_bs3::selecao(int k) {return selecao(raiz, k);}

node* tree_bs3::selecao(node* p, int k) {
    if (p==NULL) return NULL;
    if ( k < 1 ) return NULL;
    if ( k >= p->tamanho) return maximo(p);

    if (k == tam(p->esq)+1) return p;
    if (k <= tam(p->esq))
        return selecao(p->esq, k);

    return selecao(p->dir, k-1 - tam(p->esq));
}



int tree_bs3::ordem(char c) {return ordem(raiz, c);}

int tree_bs3::ordem(node* p, char c) {
    if (p==NULL) return -INT_MAX;

    if (c == p->valor) return tam(p->esq) + 1;
    if (c <  p->valor)
        return ordem(p->esq, c);

    return ordem(p->dir, c) + tam(p->esq) + 1;
}