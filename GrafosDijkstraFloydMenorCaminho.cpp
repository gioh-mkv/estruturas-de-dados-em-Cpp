// -------------------------------------------------------------
// ---- ALGORITMOS DE MENOR CAMINHO (DIJKSTRA E FLOYD) ---------
// -------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <cfloat>
#include <stack>
#include <vector>
using namespace std;


class grafo2 {

public:
    int N;// numero de vertices
    int M;// numero de arestas
    vector<vector < int >> adjL;
    vector<vector<double>> peso;

    grafo2();//construtor


    void dijkstra(int s);
    void floyd();

private:
    void imprime_matriz(vector<vector<double>>& d, int m, int n);
};



// ---------------------------------------------------------------------------------
// --- MAIN ------------------------------------------------------------------------
// ---------------------------------------------------------------------------------
int main() {
    grafo2 G;

    cout << "-----------------------------------------------------------\n";
    cout << "Algoritmo de Dijkstra (distancias do vertice 4 p/ demais): \n";
    cout << "-----------------------------------------------------------\n";
    G.dijkstra(4);

    cout << "\n\n\n";

    cout << "-----------------------------------------------------------\n";
    cout << "Algoritmo de Floyd: \n";
    cout << "-----------------------------------------------------------\n";
    G.floyd();


    cout << "\n\n\n";
    return 0;
}


// ---------------------------------------------------------------------------------
// ---- ALGORITMOS DA CLASSE GRAFO2 ------------------------------------------------
// ---------------------------------------------------------------------------------

// Construtor da classe
// Faz a leitura do arquivo "grafo2.txt"
// Ver o arquivo para entender o formato de entrada, similar a lista de adjacencias
grafo2::grafo2() {
    N = M = 0;
    ifstream arq;
    int x, y, grau;
    double p;
    arq.open("grafo2.txt");
    if (arq.fail()) return;
    arq >> N;
    adjL.resize(N);
    peso.resize(N);

    for (x=0; x<N; x++) {
        arq >> grau;
        M += grau;
        for (int k=0; k<grau; k++) {
            arq >> y;
            arq >> p;
            adjL[x].push_back(y);
            peso[x].push_back(p);
        }
    }
    arq.close();
}


// Algoritmo de Dijkstra
void grafo2::dijkstra(int s) {
    if (N<=0) return;

    int x, y, i, j;
    vector < int >  pai (N, s);
    vector < int >  ok (N, 0);
    vector<double> dist(N, DBL_MAX);
    dist[s] = 0;

    for (i=1; i<=N; i++) {
        double d_min = DBL_MAX;
        for (y=0; y<N; y++) {
            if ((!ok[y])&&(d_min >= dist[y])) {
                d_min = dist[y];
                x = y;
            }
        }
        ok[x] = 1;
        for (j=0; j<adjL[x].size(); j++) {
            y = adjL[x][j];
            double p = peso[x][j];
            if ((!ok[y]) && (dist[y] > p + dist[x])) {
                dist[y] = p + dist[x];
                pai[y] = x;
            }
        }
    }

    cout << "Vertices:  ";
    for (x=0; x<N; x++) cout << x << " ";
    cout << "\n";

    cout << "Distancia: ";
    for (x=0; x<N; x++) cout << dist[x] << " ";
    cout << "\n";
}


// Algoritmo de Floyd
void grafo2::floyd() {
    int x,y,z,i;
    vector<vector<double>> dist;
    vector<vector<int>> pi;

    vector<double> g(N, DBL_MAX);
    vector < int > h(N, -1);
    for (i=0; i<N; i++) {
        dist.push_back(g);
        pi.push_back(h);
    }
    for (x=0; x<N; x++) dist[x][x] = 0;

    for (x=0; x<N; x++) {
        for (i=0; i<adjL[x].size(); i++) {
                    y  = adjL[x][i];
            dist[x][y] = peso[x][i];
        }
    }

    for (z=0; z<N; z++) {
        for (x=0; x<N; x++) {
            if (dist[x][z] >= DBL_MAX) continue;
            for (y=0; y<N; y++) {
                if (dist[z][y] >= DBL_MAX) continue;
                if (dist[x][y] > dist[x][z]+dist[z][y]) {
                    dist[x][y] = dist[x][z]+dist[z][y];
                    pi[x][y] = z;
                }
            }
        }
    }
    imprime_matriz (dist,N,N);
}



// ------------------------------------
// ------------------------------------
void grafo2::imprime_matriz(vector<vector<double>>& d, int m, int n) {
    int i,j;
    for (i=0; i<m; i++) {
        for (j=0; j<n; j++) {
            if (d[i][j]<DBL_MAX)
                cout<<d[i][j]<<"      ";
            else
                cout<<"inf    ";
        }
        cout<<"\n";
    }
}