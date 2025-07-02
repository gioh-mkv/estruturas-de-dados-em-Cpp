// ------------------------------------------------------------------------------------------------
// Secao 10.2 do Livro Algoritmos (de Cormen, Leiserson, Rivest, Stein)
// Implementacao de Listas Duplamente Ligadas com Sentinelas
// ------------------------------------------------------------------------------------------------
#include <iostream> //cout
using namespace std;

struct node {
    int valor;
    node* prox;
    node* ant;
};



class lista_dupla {
    node* Nulo; //sentinela: indica o inicio e o fim da lista

public:
    lista_dupla();  //construtor
    ~lista_dupla(); //destrutor

    void insere_na_posicao_a_frente(node* p, int k);
    void insere_no_inicio(int k);
    void insere_no_fim(int k);
    void apaga_noh(node* p);
    void apaga_tudo();
    node* busca(int k);
    void imprime();
    bool vazia();
    void inverte_lista();

    void push(int k);
    int pop();

    void enqueue(int k);
    int dequeue();
};


// ------------------------------------------------------------------------------------------------
// ---------- MAIN --------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
int main()
{
    lista_dupla L;

    cout << "-----------------------------------\n";
    cout << "Inserindo no fim:\n";
    for (int i=0;i<10;i++) {
        L.insere_no_fim(i);
    }
    L.imprime();

    cout << "Inserindo no inicio:\n";
    for (int i=10;i<20;i++) {
        L.insere_no_inicio(i);
    }
    L.imprime();

    cout << "Invertendo a Lista:\n";
    L.inverte_lista();
    L.imprime();


    cout << "\n\n\n";
    cout << "Apagando tudo e Colocando Novos Elementos:\n\n\n";
    L.apaga_tudo();

    // pilha usando listas
    cout << "-----------------------------------\n";
    cout << "Implementando PILHAS usando LISTAS:\n";
    cout << "-----------------------------------\n";
    for (int i=0;i<40;i++) L.push(i);
    for (int i=0;i<40;i++) L.pop();
    cout << "\n\n";

    // fila usando listas
    cout << "-----------------------------------\n";
    cout << "Implementando FILAS usando LISTAS:\n";
    cout << "-----------------------------------\n";
    for (int i=0;i<40;i++) L.enqueue(i);
    for (int i=0;i<40;i++) L.dequeue();


    cout << "\n\n";
}



// ------------------------------------------------------------------------------------------------
// ---- Algoritmos de LISTAS DUPLAMENTE LIGADAS com Sentinela -------------------------------------
// ------------------------------------------------------------------------------------------------
lista_dupla::lista_dupla() {
    Nulo = new node;
    Nulo->prox = Nulo;
    Nulo->ant  = Nulo;
    Nulo->valor = 0; // irrelevante, ja que o valor de Nulo nao interessa
}

lista_dupla::~lista_dupla() {
    apaga_tudo();

    delete Nulo;
    Nulo = NULL;
}

void lista_dupla::insere_na_posicao_a_frente(node* p, int k) {
    node* q = new node;
    q->valor = k;
    q->ant   = p;
    q->prox  = q->ant->prox;
    q->ant->prox = q;
    q->prox->ant = q;
}

void lista_dupla::insere_no_inicio(int k) {
    insere_na_posicao_a_frente(Nulo, k);
}

void lista_dupla::insere_no_fim(int k) {
    insere_na_posicao_a_frente(Nulo->ant, k);
}

void lista_dupla::apaga_noh(node* p) {
    if (p==Nulo) return;
    p->ant->prox = p->prox;
    p->prox->ant = p->ant;
    delete p;
}

void lista_dupla::apaga_tudo() {
    while (Nulo->prox != Nulo) {
        apaga_noh(Nulo->prox);
    }
}

node* lista_dupla::busca(int k) {
    node* p = Nulo->prox;
    while (p!=Nulo) {
        if (p->valor==k) return p;
        p = p->prox;
    }
    return Nulo;
}

void lista_dupla::imprime() {
    node* p = Nulo->prox;
    while (p!=Nulo) {
        cout << p->valor << " ";
        p = p->prox;
    }
    cout << "\n\n";
}

bool lista_dupla::vazia() {
    if (Nulo->prox == Nulo) return true;
    return false;
}


void lista_dupla::inverte_lista() {
    if (Nulo->prox == Nulo->ant) return;

    node* p = Nulo;
    do {
        node* q = p->prox;
        p->prox  = p->ant;
        p->ant = q;
        p = q;
    } while (p!=Nulo);
}



void lista_dupla::push(int k) {
    insere_no_inicio(k);
}
int lista_dupla::pop() {
    if (vazia()) {cout<<"Pilha/Lista vazia\n"; return -1;}
    int k = Nulo->prox->valor;
    apaga_noh(Nulo->prox);
    cout << k << " ";
    return k;
}



void lista_dupla::enqueue(int k) {
    insere_no_fim(k);
}
int lista_dupla::dequeue() {
    if (vazia()) {cout<<"Fila/Lista vazia\n"; return -1;}
    int k = Nulo->prox->valor;
    apaga_noh(Nulo->prox);
    cout << k << " ";
    return k;
}