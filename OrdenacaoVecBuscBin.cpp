// ------------------------------------------------------------------------------------------------
// ---- Livro Algoritmos (de Cormen, Leiserson, Rivest, Stein) ------------------------------------
// ---- Algoritmos de Ordenação (MergeSort, HeapSort, QuickSort, InsertionSort) -------------------
// ------------------------------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <climits>
#include <windows.h>
using namespace std;


void HeapSort(int* vetor, int p, int r);
void HeapSort_min(int* vetor, int p, int r);
void QuickSort(int* vetor, int p, int r);
void MergeSort(int* vetor, int p, int r);

void InsertionSort(int* vetor, int p, int r);
void BubbleSort(int* vetor, int p, int r);


int Busca_Binaria(int* vetor, int elemento, int p, int r);
int Busca_Binaria_Rec(int* vetor, int elemento, int p, int r);


void imprimir_vetor(int* vetor, int N, string filename);

int main() {
	// Cria um vetor
	int N = 2000000;
	int* vetor = new int [N];
	srand(time(NULL));
	for (int i = 0; i<N; i++) vetor[i] = rand() % 10000;

	imprimir_vetor(vetor, N, "entrada.txt");
	int* vetor2 = new int [N];
	int* vetor3 = new int [N];
	for (int i = 0; i<N; i++) { vetor2[i] = vetor[i]; vetor3[i] = vetor[i]; }
	int t1 = GetTickCount();



	//InsertionSort(vetor,0,N-1);
	//BubbleSort(vetor,0,N-1);

	HeapSort(vetor, 0, N - 1);
	int t2 = GetTickCount();

	//HeapSort_min(vetor,0,N-1);
	//int t2 = GetTickCount();

	QuickSort(vetor2, 0, N - 1);
	int t3 = GetTickCount();

	MergeSort(vetor3, 0, N - 1);
	int t4 = GetTickCount();


	//cout << "InsertionSort " << (t2 - t1) << "miliseg" << endl;
	//cout << "BubbleSort " << (t3 - t2) << "miliseg" << endl;
	cout << "HeapSort " << (t2 - t1) << "miliseg" << endl;
	cout << "QuickSort " << (t3 - t2) << "miliseg" << endl;
	cout << "MergeSort " << (t4 - t3) << "miliseg" << endl;

	imprimir_vetor(vetor, N, "saida_heap.txt");
	imprimir_vetor(vetor2, N, "saida_quick.txt");
	imprimir_vetor(vetor3, N, "saida_merge.txt");



	t1 = GetTickCount();
	Busca_Binaria(vetor, -1, 0, N - 1);

	t2 = GetTickCount();
	Busca_Binaria_Rec(vetor, -1, 0, N - 1);


	t3 = GetTickCount();
	cout << "Busca binaria " << (t2 - t1) << "miliseg" << endl;
	cout << "Busca binaria recursiva " << (t3 - t2) << "miliseg" << endl;

	delete [] vetor;
	delete [] vetor2;
	delete [] vetor3;
	return 0;
}




// ------------------------------------------------------------------------------------------------
// ---- Algoritmo HEAPSORT ------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
void trocar(int& x, int& y) {int z = x; x = y; y = z;}

void maxheapify(int* vetor, int i, int p, int r) {
    int m = i;
    int esq = p+2*(i-p)+1;
    int dir = p+2*(i-p)+2;
    if ((esq<=r)&&(vetor[esq]>vetor[i])) m = esq;
    if ((dir<=r)&&(vetor[dir]>vetor[m])) m = dir;
    if (m != i) {
        trocar(vetor[i], vetor[m]);
        maxheapify(vetor,m,p,r);
    }
}

void HeapSort(int* vetor, int p, int r) {
    int i;
    for (i=(r+p-1)/2; i>=p; i--) {
        maxheapify(vetor,i,p,r);
    }
    for (i=r;i>p;i--) {
        trocar(vetor[p], vetor[i]);
        r = r-1;
        maxheapify(vetor,p,p,r);
    }
}


// ------------------------------------------------------------------------------------------------
// ---- Algoritmo QUICK-SORT ----------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
int Particione_original(int* vetor, int p, int r) {
    int pivo = vetor[r];
    int i=p-1;
    for (int j=p; j<r; j++) {
        if (vetor[j] <= pivo) {
            i++;
            trocar(vetor[i], vetor[j]);
        }
    }
    trocar(vetor[i+1], vetor[r]);
    return i+1;
}

int Particione_aleat(int* vetor, int p, int r) {
    srand (time(NULL));
    int pos_pivo = p + rand()%(r-p+1);
    trocar(vetor[pos_pivo], vetor[r]);
    return Particione_original(vetor,p,r);
}

void QuickSort(int* vetor, int p, int r) {
    if (p>=r) return;
    int q = Particione_aleat(vetor,p,r);
    QuickSort(vetor,p,q-1);
    QuickSort(vetor,q+1,r);
}



// ------------------------------------------------------------------------------------------------
// ---- Algoritmo MERGE-SORT ----------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
void Merge(int* vetor, int p, int q, int r) {
    int infinito = INT_MAX;
    int N1 = q-p+1;
    int N2 = r-q;
    int* esq = new int [N1+1];
    int* dir = new int[N2+1];
    for (int i=0; i<N1; i++) esq[i]=vetor[p+i];
    for (int j=0; j<N2; j++) dir[j]=vetor[q+j+1];
    esq[N1] = infinito;
    dir[N2] = infinito;

    int i=0;
    int j=0;
    for (int k=p; k<=r; k++) {
        if (esq[i]<=dir[j])
             vetor[k] = esq[i++];
        else vetor[k] = dir[j++];
    }
    delete[] esq;
    delete[] dir;
}

void MergeSort(int* vetor, int p, int r) {
    if (p>=r) return;
    int q = (p+r)/2;
    MergeSort(vetor,p,q);
    MergeSort(vetor,q+1,r);
    Merge(vetor,p,q,r);
}

// ------------------------------------------------------------------------------------------------
// ---- Algoritmo INSERTION-SORT ------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
void InsertionSort(int* vetor, int p, int r) {
    int i,j,carta;
    for (j=p+1;j<=r;j++) {
        carta = vetor[j];
        i = j-1;
        while ((i>=p)&&(vetor[i]>carta)) {
            vetor[i+1] = vetor[i];
            i--;
        }
        vetor[i+1] = carta;
    }
}


// ------------------------------------------------------------------------------------------------
// ---- Algoritmo BUBBLESORT ----------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
void BubbleSort(int* vetor, int p, int r) {
    int i;
    while (true) {
        bool stop = true;
        for (i=p;i<r;i++) {
            if (vetor[i]>vetor[i+1]) {
                trocar(vetor[i], vetor[i+1]);
                stop = false;
            }
        }
        if (stop) break;
    }
}



// ------------------------------------------------------------------------------------------------
// ---- Busca Binaria -----------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
int Busca_Binaria(int* vetor, int elemento, int p, int r) {
    while (p<=r) {
        int q = (p+r)/2;
        if (vetor[q]< elemento) p = q+1; else
        if (vetor[q]> elemento) r = q-1; else
        if (vetor[q]==elemento) return q;
    }
    return -1;
}

int Busca_Binaria_Rec(int* vetor, int elemento, int p, int r) {
    if (p>r) return -1;
    int q = (p+r)/2;
    if (elemento<vetor[q]) return Busca_Binaria_Rec(vetor,elemento,p,q-1);
    if (elemento>vetor[q]) return Busca_Binaria_Rec(vetor,elemento,q+1,r);
    return q;
}

// ------------------------------------------------------------------------------------------------
// ---- Imprimir vetor em arquivo -----------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
void imprimir_vetor(int* vetor, int N, string filename) {
    if (filename=="") filename="saida.txt";
	ofstream arq;
	arq.open(filename.c_str());
    for (int i=0;i<N;i++) arq<<vetor[i]<<" ";
	arq.close();
}





// ------------------------------------------------------------------------------------------------
// ---- Algoritmo MIN_HEAPSORT --------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// Usa heap mínimo enraizado na última posição do vetor
// ------------------------------------------------------------------------------------------------
void min_heapify(int* vetor, int i, int p, int r) {
    int m = i;
    int esq = 2*i-r-1;
    int dir = esq-1;
    if ((esq>=p)&&(vetor[esq]<vetor[i])) m = esq;
    if ((dir>=p)&&(vetor[dir]<vetor[m])) m = dir;
    if (m != i) {
        trocar(vetor[i], vetor[m]);
        min_heapify(vetor,m,p,r);
    }
}

void HeapSort_min(int* vetor, int p, int r) {
    int i;
    for (i=(r+p+2)/2; i<=r; i++) {
        min_heapify(vetor,i,p,r);
    }
    for (i=p;i<r;i++) {
        trocar(vetor[r], vetor[i]);
        p = p+1;
        min_heapify(vetor,r,p,r);
    }
}