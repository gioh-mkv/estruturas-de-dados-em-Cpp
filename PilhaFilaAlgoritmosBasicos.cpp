// ------------------------------------------------------------------------------------------------
// ---- Livro Algoritmos (de Cormen, Leiserson, Rivest, Stein) ------------------------------------
// ---- Implementação de Pilhas e Filas em Vetores (Capítulo 10, Seção 10.1) ----------------------
// ------------------------------------------------------------------------------------------------
#include <iostream> //cout
#include <ctime>   //time
using namespace std;



class pilha {
    int* vet;  //os valores da pilha ficam sobre um vetor
    int topo; //topo da pilha
    int tam; //tamanho da pilha

public:
    pilha(int N); //construtor
    ~pilha();    //destrutor

    bool push(int x);
    int  pop();
    bool vazia();
    bool cheia();
};




class fila {
    int* vet;   //os valores da fila ficam sobre um vetor
    int ini;   // inicio da fila
    int fim;  // fim da fila
    int tam; // tamanho da fila

public:
    fila(int N); // construtor
    ~fila();    // destrutor

    bool enqueue(int x);
    int  dequeue();
    bool vazia();
    bool cheia();
};



// ------------------------------------------------------------------------------------------------
// ---------- MAIN --------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
int main() {
    srand (time(NULL));
    int i;

    pilha P(10);
    cout <<"Numeros postos  na PILHA com PUSH: ";
    while (! P.cheia()) {
        int x = rand()%100;
        cout << x << " ";
        P.push(x);
    }
    cout << endl;
    cout <<"Numeros tirados da PILHA com POP : ";
    while (! P.vazia()) cout << P.pop() << " ";



    cout << endl << endl;
    fila F(10);
    cout <<"Numeros postos  na FILA com ENQUEUE: ";
    while (! F.cheia()) {
        int x = rand()%100;
        cout << x << " ";
        F.enqueue(x);
    }
    cout << endl;
    cout <<"Numeros tirados da FILA com DEQUEUE: ";
    while (! F.vazia()) cout << F.dequeue() << " ";
    cout << endl;
    return 0;
}



// ------------------------------------------------------------------------------------------------
// ---- Algoritmos de PILHA -----------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
pilha::pilha(int N) {
    vet = NULL;
    tam = 0;
    topo = -1;
    if (N<=0) return;
    tam = N;
    vet = new int [N];
}

pilha::~pilha() {
    if (vet==NULL) return;
    delete [] vet;
    vet = NULL;
    tam = 0;
    topo = -1;
}

bool pilha::push(int x) {
    if (cheia()) return false;
    vet[++topo] = x;
    return true;
}

int pilha::pop() {
    if (vazia()) {
        cout << "Pilha Vazia (estouro negativo)" << endl;
        return -1;
    }
    return vet[topo--];
}

bool pilha::vazia() {
    if (topo<0) return true;
    return false;
}

bool pilha::cheia() {
    if (topo>=tam-1) return true;
    return false;
}



// ------------------------------------------------------------------------------------------------
// ---- Algoritmos de FILA -----------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
fila::fila(int N) {
    vet = NULL;
    if (N<=0) return;
    vet = new int [N];
    tam = 0;
    ini = 0;
    fim = 0;
    tam = N;
}

fila::~fila() {
    if (vet==NULL) return;
    delete [] vet;
    vet = NULL;
    tam = 0;
    ini = 0;
    fim = 0;
}

bool fila::enqueue(int x) {
    if (cheia()) return false;
    vet[fim] = x;
    if (fim==tam-1) {
        fim = 0;
    } else {
        fim++;
    }
    return true;
}


int fila::dequeue() {
    if (vazia()) {
        cout << "Fila Vazia (estouro negativo)" << endl;
        return -1;
    }
    int x = vet[ini];
    if (ini==tam-1) {
        ini = 0;
    } else {
        ini++;
    }
    return x;
}

bool fila::vazia() {
    if (ini==fim) return true;
    return false;
}

bool fila::cheia() {
    if (ini==fim+1) return true;
    if ((ini==0)&&(fim==tam-1)) return true;
    return false;
}