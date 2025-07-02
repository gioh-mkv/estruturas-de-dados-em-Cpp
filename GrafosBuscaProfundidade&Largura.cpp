// ---------------------------------------------------------------------------------
// ---- GRAFOS - BUSCA EM PROFUNDIDADE E BUSCA EM LARGURA --------------------------
// ---------------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <vector>
using namespace std;


class grafo {

public:
    int N;// numero de vertices
    int M;// numero de arestas
    vector<vector<int>> adjL;

    grafo();//construtor

    void busca_largura (int s);
    void busca_profund (bool rec = true);

private:
    void busca_prof_recur (int x, vector<int>& achou);// busca em profundidade recursiva
    void busca_prof_pilha (int x, vector<int>& achou);// busca em profundidade com pilha
};



// ---------------------------------------------------------------------------------
// ------ MAIN ---------------------------------------------------------------------
// ---------------------------------------------------------------------------------
int main() {
    grafo G;
    if (G.N==0) {cout<<"Arquivo do grafo com erro ou inexistente\n"; return -1;}

    cout<<"Busca em Largura, partindo do vertice 0";
    G.busca_largura(0);

    cout<<"Busca em Profundidade (original, recursiva)";
    G.busca_profund();

    cout<<"Busca em Profundidade (com pilha)";
    G.busca_profund(0);

    cout << "\n\n\n";
    return 0;
}




// ---------------------------------------------------------------------------------
// ---- ALGORITMOS DA CLASSE GRAFO -------------------------------------------------
// ---------------------------------------------------------------------------------

// Construtor da classe
// Faz a leitura do arquivo "grafo.txt"
// Ver o arquivo para entender o formato de entrada, similar a lista de adjacencias
grafo::grafo() {
    N = M = 0;
    ifstream arq;
    int x, y, grau;
    arq.open("grafo.txt");
    if (arq.fail()) return;
    arq >> N;
    adjL.resize(N);

    for (x=0; x<N; x++) {
        arq >> grau;
        M += grau;
        for (int k=0; k<grau; k++) {
            arq >> y;
            adjL[x].push_back(y);
        }
    }
    arq.close();
}



// Busca em largura
void grafo::busca_largura(int s) {
    vector<int> achou(N,0);
    vector<int> dist(N,-1);
    vector<int> pai(N,-1);
    achou[s] = 1;
    dist[s] = 0;

    queue<int> Fila;
    Fila.push(s);

    int distancia_atual = -1;
    while (! Fila.empty()) {
        int x = Fila.front();  Fila.pop();
        if (distancia_atual != dist[x]) {
            distancia_atual = dist[x];
            cout << "\n Distancia " << distancia_atual << ":  ";
        }
        cout << x << " ";
        for (int i=0; i<adjL[x].size(); ++i) {
            int y = adjL[x][i];
            if (! achou[y]) {
                achou[y] = 1;
                dist[y] = dist[x] + 1;
                pai[y] = x;
                Fila.push(y);
            }
        }
    }
    cout << "\n\n\n";
}


// Busca em profundidade
void grafo::busca_profund(bool rec) {
    vector<int> achou(N,0);

    for (int i=0; i<N; i++) {
        if (! achou[i]) {
            cout << "\n";
            if (rec) busca_prof_recur(i, achou);
            else     busca_prof_pilha(i, achou);
        }
    }
    cout << "\n\n\n";
}


// Busca em profundidade (original, recursiva)
void grafo::busca_prof_recur(int x, vector<int>& achou) {

    achou[x] = 1;
    cout << x << " ";
    for (int i=0; i<adjL[x].size(); ++i) {
        int y = adjL[x][i];
        if (! achou[y])
            busca_prof_recur(y, achou);
    }
    achou[x] = 2;
}

// Busca em profundidade (com pilha)
void grafo::busca_prof_pilha(int x, vector<int>& achou) {
    stack<int> Pilha;
    Pilha.push(x);
    while (! Pilha.empty()) {
        x = Pilha.top();  Pilha.pop();
        if (achou[x]) continue;

        achou[x] = 1;
        cout << x << " ";
        for (int i=adjL[x].size()-1; i>=0; --i) {
            int y = adjL[x][i];
            if (! achou[y])
                Pilha.push(y);
        }
        achou[x] = 2;
    }
}