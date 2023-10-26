#include <iostream>

using namespace std;

/*
    Implementación DP para resolver el Minimum Coin Change
    Problem para un conjunto de monedas dado y un "vuelto"
    a entregar.
*/
int minimum_coin_change(int V, int* C, int n){
    //Se crea la estructura de datos
    //Para este problema es necesaria una matriz:
    //  - Las filas corresponderán a las posibles monedas.
    //  - Las columnas corresponderán con todos los posibles "vueltos".
    //  - Hay 1 fila y 1 columna extras para colocar los casos base
    int M[n+1][V+1];

    //Se llena la primera columna con ceros
    //("Para un vuelto de 0 no es necesario utilizar ninguna moneda")
    for(int i = 0; i <= n; ++i)
        M[i][0] = 0;

    //Se llena la primera fila con datos que no pueden ser un mínimo
    //("No debe tomarse en cuenta una denominación de moneda que no existe")
    for(int j = 1; j <= V; ++j) //Se comienza en la segunda columna
        M[0][j] = 9999;

    //Se llena el resto de la matriz fila por fila y de izquierda a derecha
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= V; ++j)
            //Si la denominación actual es menor o igual al "vuelto" a entregar,
            //puede pasarse a evaluar su utilización
            if( C[i-1] <= j )
                //Se determina qué da una cantidad menor:
                //  - Utilizar 1 moneda de la denominación actual más la respuesta
                //    para el vuelto restante.
                //  - No utilizar la moneda de la denominación actual y utilizar
                //    la respuesta hasta la denominación anterior.
                M[i][j] = min( 1 + M[i][j-C[i-1]] , M[i-1][j] );

            //Si la denominación actual es mayor que el "vuelto" a entregar,
            //la moneda no puede usarse y se utiliza la respuesta obtenida hasta
            //la denominación anterior
            else
                M[i][j] = M[i-1][j];
    
    //La respuesta está en la última celda, es decir, en la esquina inferior
    //derecha de la matriz
    return M[n][V];
}

int main(void){
    int C[] = {1,3,5,7};
    int n = sizeof(C)/sizeof(int), V = 18;

    cout << "El número mínimo de monedas que se pueden usar es: " << minimum_coin_change(V, C, n) << ".\n";

    return 0;
}