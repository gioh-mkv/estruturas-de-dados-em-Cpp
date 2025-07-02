// ------------------------------------------------------------------------------------------------
// ---- ESTRUTURAS DE DADOS BASICAS do C++ --------------------------------------------------------
// ------------------------------------------------------------------------------------------------
#include <iostream> //cout
#include <vector>
#include <stack>
#include <queue>
using namespace std;




void Execucao(int exec) {
    vector<string> V;

    if (exec==1) {
        string S;
        for (int i=0; i<5; i++) {
            S = S + "a";
            V.push_back(S);
        }
    } else if (exec==2) {
        V.push_back("dddd");
        V.push_back("aaaaaaa");
        V.push_back("ccccc");
        V.push_back("bbbbbb");
        V.push_back("eee");
    }




    cout << "---------------------------------------\n";
    cout << "Elementos do Vetor:\n";
    cout << "---------------------------------------\n";


    stack<string> P;
    queue<string> Q;
    priority_queue<string> H;


    for (int i =0; i<V.size(); i++) {
        P.push(V[i]);
        Q.push(V[i]);
        H.push(V[i]);
        cout << V[i] << "\n";
    }
    cout << "\n\n";

    cout << "---------------------------------------\n";
    cout << "Elementos da Fila: \n";
    cout << "---------------------------------------\n";
    while (! Q.empty()) {
        string X = Q.front();
        Q.pop();
        cout << X << "\n";
    }
    cout << "\n\n";

    cout << "---------------------------------------\n";
    cout << "Elementos da Pilha:\n";
    cout << "---------------------------------------\n";
    while (! P.empty()) {
        string X = P.top();
        P.pop();
        cout << X << "\n";
    }
    cout << "\n\n";
    cout << "---------------------------------------\n";
    cout << "Elementos do Heap (Fila de Prioridade):\n";
    cout << "---------------------------------------\n";
    while (! H.empty()) {
        string X = H.top();
        H.pop();
        cout << X << "\n";
    }
    cout << "\n\n";
}

// ------------------------------------------------------------------------------------------
// ------ MAIN ------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------
int main() {

    cout << "Mostrando funcionamento de Estruturas de Dados Basicas jah prontas no C++\n\n";

    int exec = 2;
    Execucao(exec);

    return 0;
}