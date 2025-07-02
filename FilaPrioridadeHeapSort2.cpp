// ------------------------------------------------------------------------------------
// ---- Secao 6.5 do Livro Algoritmos (de Cormen, Leiserson, Rivest, Stein) -----------
// ---- Usando Heaps para Ordenar (Heap-Sort) -----------------------------------------
// ------------------------------------------------------------------------------------
#include <iostream> //cout
#include <math.h>  //floor
#include <ctime>  //time
#include <vector>
#include <queue>
using namespace std;

void HeapSort(double* vetor, int N);



class heap {
    vector<double> v;
    void   min_heapify(int i);

public:
    void push(double valor);// Insere um novo valor no heap
    double extract_min();  // Retorna o minimo e remove do heap
    double minimo();      // Retorna o minimo sem remover do heap
    bool vazio();        // Retorna se o heap estah vazio ou nao
};

// ------------------------------------------------------------------------------------
// --------- MAIN ---------------------------------------------------------------------
// ------------------------------------------------------------------------------------
int main() {
    vector<double> vet;
    int i, N=100;
    srand (time(NULL));
    cout << "----------------------------------------------------------------------\n";
    cout << "--- Valores do Vetor Original ----------------------------------------\n";
    cout << "----------------------------------------------------------------------\n";
    for (i=0;i<N;i++) {
        double valor = (double) rand()/RAND_MAX;
        vet.push_back(valor);
        cout << valor << " ";
    }
    cout << "\n\n\n\n";
    cout << "----------------------------------------------------------------------\n";
    cout << "--- Valores Ordenados usando o Heap-Sort tradicional sobre o vetor ---\n";
    cout << "----------------------------------------------------------------------\n";

    double* vet2 = new double[N];
    for (i=0;i<N;i++) vet2[i] = vet[i];
    HeapSort(vet2,N);
    for (i=0;i<N;i++) cout << vet2[i] << " ";
    delete vet2;

    cout << "\n\n\n\n";
    cout << "----------------------------------------------------------------------\n";
    cout << "--- Valores Ordenados usando o nosso Heap ----------------------------\n";
    cout << "----------------------------------------------------------------------\n";
    heap H;
    for (i=0;i<N;i++) {
        H.push(vet[i]);
    }
    while (!H.vazio()) {
        double valor = H.extract_min();
        cout << valor << " ";
    }
    cout << "\n\n\n\n";
    cout << "----------------------------------------------------------------------\n";
    cout << "--- Valores Ordenados usando o Heap do C++ (priority_queue) ----------\n";
    cout << "----------------------------------------------------------------------\n";
    priority_queue<double> Q;
    for (i=0;i<N;i++) {
        Q.push(vet[i]);
    }
    i = N;
    while (!Q.empty()) {
        vet[--i] = Q.top();
        Q.pop();
    }
    for (i=0;i<N;i++) {
        cout << vet[i] << " ";
    }
    cout << "\n\n\n\n";

    return 0;
}



// ------------------------------------------------------------------------------------
// ---- Algoritmos da nossa Estrutura de Dados HEAP -----------------------------------
// ------------------------------------------------------------------------------------
bool heap::vazio() {
    if (v.size() <= 0) return true;
    return false;
}

// Retorna o menor valor do heap sem remover do heap
double heap::minimo() {
    if (vazio()) {
        cout << "ERRO: Heap Vazio !!\n\n";
        return -1; // ERRO
    }
    return v[0];
}

// Retorna o menor valor do heap e remove do heap
double heap::extract_min() {
    if (vazio()) {
        cout << "ERRO: Heap Vazio !!\n\n";
        return -1; // ERRO
    }
    int N = v.size();
    double x = v[0];
    v[0] = v[N-1];
    v.pop_back();
    min_heapify(0);
    return x;
}

void heap::push(double valor) {
    v.push_back(valor);
    int N = v.size();
    int i = N-1;
    int p = floor((i-1)/2.0); //pai

    while ((p>=0) && (v[p]>v[i])) {
        double z = v[i];
        v[i] = v[p];    v[p] = z;
        i = p;
        p = floor((p-1)/2.0);
    }
}

void heap::min_heapify(int i) {
    int N = v.size();
    int m = i;
    int esq = 2*i+1;
    int dir = esq+1;
    if ((esq < N) && (v[esq] < v[m])) m = esq;
    if ((dir < N) && (v[dir] < v[m])) m = dir;
    if (m != i) {
        double z = v[i];
        v[i] = v[m];
        v[m] = z;
        min_heapify(m);
    }
}

// ------------------------------------------------------------------------------------
// ---- Algoritmo HEAPSORT TRADICIONAL ------------------------------------------------
// ------------------------------------------------------------------------------------
void trocar(double& x, double& y) {double z = x; x = y; y = z;}

void maxheapify(double* vetor, int i, int N) {
    int m = i;
    int esq = 2*i + 1;
    int dir = 2*i + 2;
    if ((esq<N)&&(vetor[esq]>vetor[i])) m = esq;
    if ((dir<N)&&(vetor[dir]>vetor[m])) m = dir;
    if (m != i) {
        trocar(vetor[i], vetor[m]);
        maxheapify(vetor,m,N);
    }
}

void HeapSort(double* vetor, int N) {
    int i;
    for (i=N/2 - 1; i>=0; i--) {
        maxheapify(vetor,i,N);
    }
    for (i=N-1;i>0;i--) {
        trocar(vetor[0], vetor[i]);
        N = N-1;
        maxheapify(vetor,0,N);
    }
}
