#include <iostream>

using namespace std;

/*
    Implementación DP para calcular la Longest Common
    Subsequence entre dos cadenas proporcionadas.
*/
int LCS(string A, string B){ 
    //Se obtienen las longitudes de las dos cadenas
    int nA = A.length(), nB = B.length();

    //Se prepara la estructura de datos
    //Para este problema es necesaria una matriz:
    //  - Las filas corresponderán a los caracteres de la primera cadena.
    //  - Las columnas corresponderán a los caracteres de la segunda cadena.
    //  - Hay 1 fila y 1 columna extras para colocar los casos base.
    int M[nA+1][nB+1];

    //Se llena la primera columna con ceros
    //("Si la segunda cadena es nula, la LCS no existe")
    for(int i = 0; i <= nA; ++i)
        M[i][0] = 0;

    //Se llena la primera fila con ceros
    //("Si la primera cadena es nula, la LCS no existe")
    for(int j = 1; j <= nB; ++j) //Se inicia en la segunda columna
        M[0][j] = 0;

    //Se llena el resto de la matriz fila por fila y de izquierda a derecha
    for(int i = 1; i <= nA; ++i)
        for(int j = 1; j <= nB; ++j)
            //Si los caracteres actuales en ambas cadenas coinciden,
            //se procede a actualizar la longitud de la LCS
            if( A[i-1] == B[j-1] )
                //Se toma el resultado retrocediendo un caracter en ambas cadenas,
                //y se le suma 1 para incluir al caracter actual
                M[i][j] = 1 + M[i-1][j-1];

            //Si los caracteres actuales en ambas cadenas no coinciden,
            //se evalúan los resultados anteriores
            else
                //Se determina qué da una longitud mayor:
                //  - El resultado retrocediendo un caracter en la primera cadena.
                //  - El resultado retrocediendo un caracter en la segunda cadena.
                M[i][j] = max( M[i-1][j] , M[i][j-1] );

    //La respuesta está en la última celda, es decir, en la esquina inferior
    //derecha de la matriz
    return M[nA][nB];
}

int main(void){
    string S1 = "stone", S2 = "longest";

    cout << "La longitud de la Longest Common Subsequence es: " << LCS(S1, S2) << ".\n";

    return 0;
}