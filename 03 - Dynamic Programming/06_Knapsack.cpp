#include <iostream>

using namespace std;

/*
    Implementación DP para el 0/1 Knapsack Problem.
*/
int knapsack(int K, int* V, int* W, int n){
    //Se crea la estructura de datos
    //Para este problema es necesaria una matriz:
    //  - Las filas corresponderán a los objetos.
    //  - Las columnas corresponderán a las posibles capacidades del knapsack.
    //  - Hay 1 fila y 1 columna extras para colocar los casos base.
    int M[n+1][K+1];

    //Se llena la primera columna con ceros
    //("Si no hay knapsack, no hay nada que colocar.")
    for(int i = 0; i <= n; ++i)
        M[i][0] = 0;

    //Se llena la primera fila con ceros
    //("Si no hay objetos, no hay valor en el knapsack.")
    for(int j = 1; j <= K; ++j) //Se inicia en la segunda columna
        M[0][j] = 0;

    //Se llena el resto de la matriz fila por fila y de izquierda a derecha
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= K; ++j)
            //Si el peso del objeto actual no sobrepasa la capacidad del knapsack,
            //se procede a evaluar su inclusión
            if( W[i-1] <= j )
                //Se determina qué da un valor mayor:
                //  - Utilizar el objeto actual más la respuesta
                //    para la capacidad restante.
                //  - No utilizar el objeto actual y utilizar
                //    la respuesta hasta el objeto anterior.
                M[i][j] = max( V[i-1] + M[i-1][j-W[i-1]] , M[i-1][j] );

            //Si el peso del objeto actual excede la capacidad del knapsack,
            //el objeto no puede colocarse y se utiliza la respuesta hasta el
            //objeto anterior.
            else
                M[i][j] = M[i-1][j];

    //La respuesta está en la última celda, es decir, en la esquina inferior
    //derecha de la matriz
    return M[n][K];
}

int main(void){
    int V[] = {60,100,120}, W[] = {10,20,30};
    int n = sizeof(V)/sizeof(int), K = 50;

    cout << "El valor máximo que se puede obtener es: " << knapsack(K, V, W, n) << ".\n";

    return 0;
}