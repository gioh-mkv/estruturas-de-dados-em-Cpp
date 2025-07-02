// ------------------------------------------------------------
// ---- Livro Algoritmos (CORMEN): Capitulo 14 - Árvores B ----
// ------------------------------------------------------------
#include<iostream>
#include <ctime>
using namespace std;

const int M = 3;// Arvore B de ordem M

struct node {
    char valor[M];// vetor de tam no maximo M-1 (com uma casa a mais de folga)
    node* filho[M+1];// vetor de tam no maximo M (com uma casa a mais de folga)
    bool folha;
    int n;// numero de valores: menor ou igual a M-1 e maior ou igual a (M-1)/2

    node(bool f) {folha=f; n=0;}
};


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
// Classe de Arvores B de ordem M (grau maximo)
// --------------------------------------------------------
class tree_B {
    node* raiz;

    node* minimo(node* p);
    node* maximo(node* p);

    void apaga_tudo(node* p);
    void imprime_ordenado(node* p);
    void transplant(node* u, node* v);
    node* busca_rec(node* p, char k);

    void inserir(char c);
    void inserir(node* p, char c);
    void divide_filho(node* p, int i);

    void remover(node* p, char c, bool del_folha);
    void enche_filho(node* p, int i);
    void anterior_ajuda(node* p, int i);
    void posterior_ajuda(node* p, int i);
    void aglutina(node* p, int i);

public:
    tree_B();  //construtor
    ~tree_B(); //destrutor

    node* busca(char k);
    node* busca_rec(char k);

    //int tamanho();
    void apaga_tudo();
    void imprime_ordenado();

    node* minimo();
    node* maximo();

    void inserir(string s);
    void remover(char c);
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
    cout << "Abaixo listamos os valores em ordem na Arvore B\n";
    cout << "Em seguida, removemos sucessivamente o maior elemento\n\n";

    tree_B T;
    T.inserir(s);
    T.imprime_ordenado();

    string del = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    inverte(del);
    for (int i=0; i<del.size(); i++) {
        T.remover(del[i]);
        T.imprime_ordenado();
    }
}



// --------------------------------------------------------
// Algoritmos das Arvores B de ordem M (grau maximo)
// --------------------------------------------------------
tree_B::tree_B() {
    raiz=NULL;
}
tree_B::~tree_B() {
    apaga_tudo();
}

// Apaga da memoria a arvore enraizada em p
void tree_B::apaga_tudo() {
    apaga_tudo(raiz);
    raiz = NULL;
}
void tree_B::apaga_tudo(node* p) {
    if (p==NULL) return;
    if (! p->folha) {
        for (int i=0; i<=p->n; i++) {
            apaga_tudo(p->filho[i]);
        }
    }
    delete p;
}



// Imprime em ordem os valores da subarvore de p (EM-ORDER)
void tree_B::imprime_ordenado() {
    if (raiz==NULL) return;
    imprime_ordenado(raiz);
    cout << "          ------ raiz = ";
    for (int i=0; i<raiz->n; i++) cout << raiz->valor[i];
    cout << "\n";
}
void tree_B::imprime_ordenado(node* p) {
    if (p==NULL) return;

    if (!p->folha) imprime_ordenado(p->filho[0]);

    for (int i=0; i<p->n; i++) {
        cout << " " << p->valor[i] << " ";
        if (!p->folha) imprime_ordenado(p->filho[i+1]);
    }
}


// Procura recursivamente um no com valor k na subarvore de p
node* tree_B::busca_rec(char c) {
    return busca_rec(raiz, c);
}
node* tree_B::busca_rec(node* p, char c) {
    if (p==NULL) return NULL;
    int i, n = p->n;
    for (i=0; i<n; i++)
        if (c <= p->valor[i]) break;

    if ((i<n) && (c==p->valor[i])) return p;
    if (p->folha) return NULL;

    return busca_rec(p->filho[i], c);
}

// Procura iterativamente um no com valor k na subarvore de p
node* tree_B::busca(char c) {
    node* p = raiz;
    while (p!=NULL) {
        int i, n = p->n;
        for (i=0; i<n; i++)
           if (c <= p->valor[i]) break;

        if ((i<n) && (c==p->valor[i])) return p;
        else if (p->folha) return NULL;
        else p = p->filho[i];
    }
    return NULL;
}



// Retorna o no com valor minimo na subarvore de p
node* tree_B::minimo() {
    if (raiz==NULL) return NULL;
    return minimo(raiz);
}

node* tree_B::minimo(node* p) {
    while (!p->folha) p = p->filho[0];
    return p;
}

// Retorna o no com valor maximo na subarvore de p
node* tree_B::maximo() {
    if (raiz==NULL) return NULL;
    return maximo(raiz);
}

node* tree_B::maximo(node* p) {
    while (!p->folha) p = p->filho[ p->n ];
    return p;
}







// --------------------------------------------------------
// INSERIR UM ELEMENTO NA ARVORE
// --------------------------------------------------------
void tree_B::inserir(string s) {
    for (int i=0; i<s.size(); i++)
        inserir(s[i]);
}

void tree_B::inserir(char c) {
    int i;
    if (raiz==NULL) {
        raiz = new node(1);
        raiz->valor[0] = c;
        raiz->n = 1;
        return;
    }

    inserir(raiz, c);
    if (raiz->n < M) return;

    node* pp = new node(0);
    pp->filho[0] = raiz;
    raiz = pp;

    divide_filho(raiz, 0);
}

void tree_B::inserir(node* p, char c) {
    int i;
    if (p->folha)
    {
        for (i=p->n-1; i>=0; i--) {
            if (c > p->valor[i]) break;
            p->valor[i+1] = p->valor[i];
        }
        p->valor[i+1] = c;
        p->n++;
    }
    else
    {
        for (i=0; i < p->n; i++)
           if (c <= p->valor[i]) break;

        inserir(p->filho[i], c);

        if (p->filho[i]->n >= M)
            divide_filho(p, i);
    }
}

void tree_B::divide_filho(node* p, int i) {
    int k = (M-1)/2;

    node* f1 = p->filho[i];
    node* f2 = new node(f1->folha);

    for (int j=k+1; j < f1->n; j++) {
        f2->valor[j-k-1] = f1->valor[j];
    }
    if (! f1->folha) {
        for (int j=k+1; j <= f1->n; j++) {
            f2->filho[j-k-1] = f1->filho[j];
        }
    }
    f2->n = f1->n - (k+1);
    f1->n = k;

    for (int j=p->n; j>i; j--) {
        p->valor[ j ] = p->valor[j-1];
        p->filho[j+1] = p->filho[ j ];
    }
    p->valor[ i ] = f1->valor[k];
    p->filho[i+1] = f2;
    p->n++;
}






// --------------------------------------------------------
// REMOVER UM ELEMENTO DA ARVORE
// --------------------------------------------------------
void tree_B::remover(char c) {
    if (raiz==NULL) return;
    remover(raiz, c, 0);
    if (raiz->n==0) {
        node* r = raiz;
        if (raiz->folha)
            raiz = NULL;
        else
            raiz = raiz->filho[0];
        delete r;
    }
}

void tree_B::remover(node* p, char c, bool del_folha) {
    int i;
    for (i=0; i < p->n; i++)
        if (c <= p->valor[i]) break;

    if ((p->folha) && (i<p->n) && (c==p->valor[i])) {
        for (int j = i+1; j < p->n; j++)
            p->valor[j-1] = p->valor[j];

        p->n--;
        return;
    }
    if ((!del_folha) && (i<p->n) && (c==p->valor[i])) {
        node* q = maximo(p->filho[i]);
        c = q->valor[q->n-1];
        p->valor[i] = c;
        del_folha = true;
    }

    remover(p->filho[i], c, del_folha);

    int K = (M-1)/2;
    if (p->filho[i]->n < K) {
        enche_filho(p, i);
    }
}

void tree_B::enche_filho(node* p, int i) {
    int K = (M-1)/2;
    if ((i>0) && (p->filho[i-1]->n > K))
        anterior_ajuda(p, i);
    else if ((i<p->n-1) && (p->filho[i+1]->n > K))
        posterior_ajuda(p, i );
    else if (i==0)
        aglutina(p, i );
    else
        aglutina(p,i-1);
}

void tree_B::anterior_ajuda(node* p, int i) {
    node* f1 = p->filho[ i ];
    node* f2 = p->filho[i-1];

    for (int j = f1->n-1; j>=0; j--)
        f1->valor[j+1] = f1->valor[j];

    if (!f1->folha) {
        for (int j = f1->n; j>=0; j--)
            f1->filho[j+1] = f1->filho[j];
    }

    f1->valor[0] = p->valor[i-1];

    if (!f1->folha)
        f1->filho[0] = f2->filho[f2->n];

    p->valor[i-1] = f2->valor[f2->n-1];

    f1->n += 1;
    f2->n -= 1;
}

void tree_B::posterior_ajuda(node* p, int i) {
    node* f1 = p->filho[ i ];
    node* f2 = p->filho[i+1];

    f1->valor[f1->n] = p->valor[i];

    if (! f1->folha)
        f1->filho[f1->n+1] = f2->filho[0];

    p->valor[i] = f2->valor[0];

    for (int j=1; j<f2->n; j++)
        f2->valor[j-1] = f2->valor[j];

    if (!f2->folha) {
        for (int j=1; j<=f2->n; j++)
            f2->filho[j-1] = f2->filho[j];
    }

    f1->n += 1;
    f2->n -= 1;
}

void tree_B::aglutina(node* p, int i) {
    node* f1 = p->filho[ i ];
    node* f2 = p->filho[i+1];

    f1->valor[f1->n] = p->valor[i];

    for (int j=0; j<f2->n; j++)
        f1->valor[f1->n + j+1] = f2->valor[j];

    if (!f1->folha) {
        for (int j=0; j<=f2->n; j++)
            f1->filho[f1->n + j+1] = f2->filho[j];
    }

    for (int j=i+1; j<p->n; j++)
        p->valor[j-1] = p->valor[j];

    for (int j=i+2; j<=p->n; j++)
        p->filho[j-1] = p->filho[j];

    f1->n += f2->n + 1;
    p->n--;

    delete f2;
}