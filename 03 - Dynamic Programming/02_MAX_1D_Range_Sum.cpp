#include <iostream>

using namespace std;

/*
    Implementación con DP para obtener la Maximum
    1D Range Sum de una secuancia de datos dada.
*/
int max_1d_range_sum(int* A, int n){
    //Se crea la estructura de datos
    int M[n+1]; //Para este problema es suficiente un arreglo

    //Se inicializa la variable que llevará registro de la suma total
    int S = 0;

    //Se coloca el valor trivial
    M[0] = 0; //Antes de comenzar a recorrer los datos, la M1DRS es 0

    //Se recorre el resto del arreglo para irlo llenado
    for(int i = 1; i <= n; ++i){
        //Se determina qué da un resultado mayor:
        //  - La suma actual más el dato actual.
        //  - Reiniciar la suma con el dato actual.
        S = max( S + A[i-1], A[i-1] );

        //Para definir el resultado hasta el dato actual,
        //se determina qué da un resultado mayor:
        //  - La suma actual (cómo haya quedado después de la evaluación anterior).
        //  - El resultado anterior.
        M[i] = max( S, M[i-1] );
    }

    //La respuesta queda en la última celda
    return M[n];
}

int main(void){
    int A[] = {-2,1,-3,4,-1,2,1,-5,4};
    int n = sizeof(A)/sizeof(int);

    cout << "El resultado máximo es: " << max_1d_range_sum(A, n) << ".\n";

    return 0;
}