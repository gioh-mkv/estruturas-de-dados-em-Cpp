// ------------------------------------------------------------------------------------
// ---- CONJUNTOS --- Implementacao simples com vetor ordenado ------------------------
// ------------------------------------------------------------------------------------
#include <iostream> //cout
#include <math.h>  //floor
#include <ctime>  //time
#include <vector>
using namespace std;

// ---------------------------------------------
// Conjunto --- implementado como vetor ordenado
// ---------------------------------------------
class conjunto {
    vector<int> v;
    int busca_binaria(int x);

public:
    bool push(int valor);     // Insere um novo valor no conjunto, caso ainda nao pertenca
    bool pertence(int valor); // Retorna se um elemento pertence ao conjunto
    bool vazio();             // Retorna se o conjunto estah vazio ou nao
    int tamanho();            // Retorna o tamanho do conjunto
    void imprime();           // Imprime os valores do conjunto
    void apaga_tudo();        // apaga todos os elementos do conjunto

    void uniao     (conjunto& C1, conjunto& C2);// O conjunto vira a uniao de outros dois
    void intersecao(conjunto& C1, conjunto& C2);// O conjunto vira a intersecao de outros dois
    void diferenca (conjunto& C1, conjunto& C2);// O conjunto vira a diferenca de outros dois
};

// ------------------------------------------------------------------------------------
// --------- MAIN ---------------------------------------------------------------------
// ------------------------------------------------------------------------------------
int main() {
    conjunto C1, C2;

    int i;
    srand (time(NULL));
    for (i=0;i<10;i++) {
        C1.push( rand() % 20 );
        C2.push( rand() % 20 );
    }
    cout << "---------- VALORES DOS DOIS CONJUNTOS -----------\n";
    cout << "C1 :  "; C1.imprime();
    cout << "C2 :  "; C2.imprime();

    cout << "\n\n\n";
    cout << "------------------- UNIAO -----------------------\n";
    conjunto C;
    C.uniao(C1,C2);
    cout << "C1 uniao C2 :  ";
    C.imprime();


    cout << "\n\n\n";
    cout << "----------------- INTERSECAO --------------------\n";
    C.intersecao(C1,C2);
    cout << "C1 intersecao C2 :  ";
    C.imprime();


    cout << "\n\n\n";
    cout << "------------------ DIFERENCA --------------------\n";
    C.diferenca(C1,C2);
    cout << "C1 menos C2 :  ";
    C.imprime();

    C.diferenca(C2,C1);
    cout << "C2 menos C1 :  ";
    C.imprime();

    cout << "\n\n\n\n";
    return 0;
}



// ------------------------------------------------------------------------------------
// ---- Algoritmos da nossa Estrutura de Dados CONJUNTO -------------------------------
// ------------------------------------------------------------------------------------
bool conjunto::vazio() {
    if (v.size() <= 0) return true;
    return false;
}

int conjunto::tamanho() {
    return v.size();
}

void conjunto::imprime() {
    cout << "{ ";
    for (int i=0; i<v.size(); i++) {
        cout << v[i] << " ";
        if (i<v.size()-1) cout << ", ";
    }
    cout << "}\n\n";
}

bool conjunto::push(int valor) {
    if (pertence(valor)) return false;

    int i = v.size()-1;
    v.push_back(valor);

    while ((i>=0) && (v[i]>valor)) {
        v[i+1] = v[i];
        i--;
    }
    v[i+1] = valor;
    return true;
}

int conjunto::busca_binaria(int x) {
    int p = 0;
    int r = v.size()-1;
    while (p<=r) {
        int q = (p+r)/2;
        if (v[q]< x) p = q+1; else
        if (v[q]> x) r = q-1; else
        if (v[q]==x) return q;
    }
    return -1;
}

bool conjunto::pertence(int valor) {
    if (busca_binaria(valor)<0) return false;
    return true;
}

void conjunto::apaga_tudo() {
    v.clear();
}

void conjunto::uniao(conjunto& C1, conjunto& C2) {
    apaga_tudo();
    int i,j;
    int n1 = C1.tamanho();
    int n2 = C2.tamanho();
    int N =  n1 + n2;
    if (n1==0) {
        for (j=0; j<n2; j++) v.push_back(C2.v[j]);
        return;
    }
    if (n2==0) {
        for (i=0; i<n1; i++) v.push_back(C1.v[i]);
        return;
    }
    i = j = 0;
    int ultimo = min(C1.v[0],C2.v[0]);
    if (ultimo==C1.v[0]) i++; else j++;
    v.push_back(ultimo);

    while ((i<n1)||(j<n2)) {
        if ((j>=n2) ||  ((i<n1) && (C1.v[i]<=C2.v[j]))) {
            if (C1.v[i]>ultimo) {v.push_back(C1.v[i]); ultimo=C1.v[i];}
            i++;
        } else {
            if (C2.v[j]>ultimo) {v.push_back(C2.v[j]); ultimo=C2.v[j];}
            j++;
        }
    }
}

void conjunto::intersecao(conjunto& C1, conjunto& C2) {
    if (C1.tamanho() > C2.tamanho()) {
        intersecao(C2,C1);
        return;
    }
    apaga_tudo();
    for (int i=0; i<C1.tamanho(); i++) {
        if (C2.pertence(C1.v[i])) v.push_back(C1.v[i]);
    }
}

void conjunto::diferenca(conjunto& C1, conjunto& C2) {
    apaga_tudo();
    for (int i=0; i<C1.tamanho(); i++) {
        if (! C2.pertence(C1.v[i])) v.push_back(C1.v[i]);
    }
}