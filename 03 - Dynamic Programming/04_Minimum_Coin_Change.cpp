#include <iostream>

using namespace std;

int minimum_coin_change(int V, int* C, int n){
    int M[n+1][V+1];

    for(int i = 0; i <= n; i++)
        M[i][0] = 0;
    for(int j = 1; j <= V; j++)
        M[0][j] = 9999;

    for(int i = 1; i <= n; i++)     //O(n) ----> O( n*V ) ~= O( n^2 ) ???
        for(int j = 1; j <= V; j++) //O(V)
            if( C[i-1] <= j )
                M[i][j] = min( 1 + M[i][j-C[i-1]] , M[i-1][j] );
            else
                M[i][j] = M[i-1][j];
    
    return M[n][V];
}

int main(void){
    int n = 4, V = 18;
    int C[n] = {1,3,5,7};

    cout << "El valor máximo que se puede obtener es: " << minimum_coin_change(V, C, n) << ".\n";

    return 0;
}