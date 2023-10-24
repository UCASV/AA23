#include <iostream>
#include <string>

using namespace std;

typedef struct{
    int min_value;
    string min_combi;
} Answer;

Answer minimum_coin_change(int V, int* C, int n){
    int M[n+1][V+1];
    string S[n+1][V+1];

    for(int i = 0; i <= n; i++){
        M[i][0] = 0;
        S[i][0] = "";
    }

    for(int j = 1; j <= V; j++){
        M[0][j] = 9999;
        S[0][j] = "";
    }

    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= V; j++)
            if( C[i-1] <= j && ( 1 + M[i][j-C[i-1]] < M[i-1][j] ) ){
                M[i][j] = 1 + M[i][j-C[i-1]];
                S[i][j] = S[i][j-C[i-1]] + ((S[i][j-C[i-1]]=="")?"":",") + to_string(C[i-1]);
            }else{
                M[i][j] = M[i-1][j];
                S[i][j] = S[i-1][j];
            }

    Answer res;
    res.min_value = M[n][V];
    res.min_combi = S[n][V];
    return res;
}

int main(void){
    int n = 4, V = 18;
    int C[n] = {1,3,5,7};

    Answer respuesta = minimum_coin_change(V, C, n);

    cout << "El valor máximo que se puede obtener es: " << respuesta.min_value << ", y la combinación de objetos es: [" << respuesta.min_combi << "].\n";

    return 0;
}