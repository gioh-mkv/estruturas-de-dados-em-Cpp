// ------------------------------------------------------------------------------------
// Secao 10.4 do Livro Algoritmos (de Cormen, Leiserson, Rivest, Stein) ---------------
// Implementacao de Arvores enraizadas (NAO-BINARIA) com vetor de filhos --------------
// ------------------------------------------------------------------------------------
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>

using namespace std;

struct node{
    char valor;
    node* pai;
    vector<node*> filho;
};

class ARVORE{
    node* raiz;
    void pre_ordem(node* p);
    void pos_ordem(node* p);
    void apaga(node* p);
    node* sub_arvore(string &s,int &i);
public:
    ARVORE(string s); //construtor
    ~ARVORE();       //destrutor

    void apaga_tudo();
    void pre_ordem();
    void pos_ordem();
    void nivel_ordem();
    void pre_ordem_naorec();
};



// ------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------
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
    ARVORE T (s);
    cout << "Pre-Ordem nao recursiva --- "; T.pre_ordem_naorec();
    cout << "Pre-Ordem ----------------- "; T.pre_ordem();
    cout << "Pos-Ordem ----------------- "; T.pos_ordem();
    cout << "Nivel Ordem --------------- "; T.nivel_ordem();
}





// ------------------------------------------------------------------------------------
// ---- Algoritmos de ARVORES NORMAIS com vetor de filhos -----------------------------
// ------------------------------------------------------------------------------------
ARVORE::~ARVORE(){
    apaga_tudo();
}

void ARVORE::apaga_tudo(){
    apaga(raiz);
    raiz = NULL;
}

void ARVORE::apaga(node* p){
    if (p==NULL) return;
    for (int i = 0; i < p->filho.size(); i++){
        apaga(p->filho[i]);
    }
    delete p;
}

void ARVORE:: pre_ordem(node* p){
    if (p == NULL) return;
    cout << p->valor << " ";
    for (int i =0; i < p->filho.size(); i++){
        pre_ordem(p->filho[i]);
    }
}

void ARVORE::pre_ordem(){
    pre_ordem(raiz);
    cout << "\n";
}

void ARVORE::pos_ordem(node* p){
    if (p==NULL) return;
    for(int i = 0; i < p->filho.size(); i++){
        pos_ordem(p->filho[i]);
    }
    cout << p->valor << " ";
}

void ARVORE::pos_ordem(){
    pos_ordem(raiz);
    cout << "\n";
}

void ARVORE::nivel_ordem(){
    if (raiz== NULL) return;
    queue<node*> Q;
    Q.push(raiz);

    while(!Q.empty()){
        node* p = Q.front();
        Q.pop();
        if (p==NULL) continue;
        cout << p->valor << " ";
        for (int i = 0; i < p->filho.size(); i++){
            if (p->filho[i] != NULL) Q.push(p->filho[i]);
        }
    }
    cout << "\n";
}

void ARVORE::pre_ordem_naorec(){
    if (raiz== NULL) return;
    stack<node*> Q;
    Q.push(raiz);
    while (!Q.empty()){
        node* p = Q.top();
        Q.pop();
        if(p==NULL) continue;
        cout << p->valor << " ";
        for(int i= p->filho.size()-1; i>=0; i--){
            if (p->filho[i]!= NULL){
                Q.push(p->filho[i]);
            }
        }
    }
    cout << "\n";
}

ARVORE::ARVORE(string s){
    int i = 0;
    raiz = sub_arvore(s,i);

    if (raiz!=NULL) raiz->pai = NULL;
}

node* ARVORE::sub_arvore(string &s, int &i){
    while ((i<s.size()) && ((s[i]== '(') || (s[i]== ' ')) ) i++;
    if ((i>=s.size())||(s[i] == ')')) {
        i++;
        return NULL;
    }
    node* p = new node;
    p->valor = s[i++];

    while(true) {
        node* q = NULL;
        q = sub_arvore(s,i);
        if (q== NULL) break;
        p->filho.push_back(q);
        q->pai = p;
    }
    return p;
}
