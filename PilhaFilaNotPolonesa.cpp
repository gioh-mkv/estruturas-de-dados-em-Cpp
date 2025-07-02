// ------------------------------------------------------------------------------------------------
// ---- Aplicação de Pilhas: Notação Polonesa e Polonesa Reversa ----------------------------------
// ------------------------------------------------------------------------------------------------
#include <iostream> //cout
#include <string>
#include <stack>
#include <queue>
using namespace std;

string expr_to_polonesa(string expr, bool rev);
string polonesa_to_expr(string expr, bool rev);




// ------------------------------------------------------------------------------------------------
// ---------- MAIN --------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
int main() {
    cout<<"expr: ((A*B)-(C/D)) => polo_rev: "<<expr_to_polonesa("((A*B)-(C/D))",1)<<endl;
    cout<<"expr: ((A*B)-(C/D)) => polonesa: "<<expr_to_polonesa("((A*B)-(C/D))",0)<<endl;
    cout<<"polo-rev: AB*CD/-   => expr: "<<polonesa_to_expr("AB*CD/-",1)<<endl;
    cout<<"polonesa: -*AB/CD   => expr: "<<polonesa_to_expr("-*AB/CD",0)<<endl;
    cout<<endl;
    cout<<"expr: (W+(X*(Y-Z))) => polo_rev: "<<expr_to_polonesa("(W+(X*(Y-Z)))",1)<<endl;
    cout<<"expr: (W+(X*(Y-Z))) => polonesa: "<<expr_to_polonesa("(W+(X*(Y-Z)))",0)<<endl;
    cout<<"polo-rev: WXYZ-*+   => expr: "<<polonesa_to_expr("WXYZ-*+",1)<<endl;
    cout<<"polonesa: +W*X-YZ   => expr: "<<polonesa_to_expr("+W*X-YZ",0)<<endl;
    cout<<endl;
    cout<<"expr: (((R+S)*T)-U) => polo_rev: "<<expr_to_polonesa("(((R+S)*T)-U)",1)<<endl;
    cout<<"expr: (((R+S)*T)-U) => polonesa: "<<expr_to_polonesa("(((R+S)*T)-U)",0)<<endl;
    cout<<"polo-rev: RS+T*U-   => expr: "<<polonesa_to_expr("RS+T*U-",1)<<endl;
    cout<<"polonesa: -*+RSTU   => expr: "<<polonesa_to_expr("-*+RSTU",0)<<endl;
    return 1;
}


// ------------------------------------------------------------------------------------------------
// ---- Algoritmos de CONVERSAO (POLONESA) --------------------------------------------------------
// ------------------------------------------------------------------------------------------------
string expr_to_polonesa(string expr, bool rev) {
    stack<string> P1, P2;
    int i = 0;
    while (true) {
        char c = expr[i++];
        if (c==0) break;
        string s(1,c);
        if ((c=='+')||(c=='-')||(c=='*')||(c=='/')) {
            P2.push(s);
        } else
        if (c==')') {
            string B  = P1.top(); P1.pop();
            string A  = P1.top(); P1.pop();
            string op = P2.top(); P2.pop();
            if ((A=="")||(B=="")||(op=="")) return "";

            string aux;
            if (rev) aux = A+B+op;
            else aux = op+A+B;
            P1.push(aux);
        } else if ((c!='(')&&(c!=' ')) {
            P1.push(s);
        }
    }
    string s = P1.top(); P1.pop();
    return s;
}


string polonesa_to_expr(string expr, bool rev) {
    int i;
    int N = expr.size();
    stack<string> P;
    if (rev) i=0; else i=N-1;
    while (true) {
        if ((i<0)||(i>=N)) break;
        char c = expr[i];
        string s(1,c);
        if (rev) i++; else i--;
        if ((c=='+')||(c=='-')||(c=='*')||(c=='/')) {
            string B = P.top(); P.pop();
            string A = P.top(); P.pop();
            if ((A=="")||(B=="")) return "";

            string aux;
            if (rev) aux = "("+A+c+B+")";
            else aux = "("+B+c+A+")";
            P.push(aux);
        } else
        if (c!=' ') {
            P.push(s);
        }
    }
    string s = P.top(); P.pop();
    return s;
}