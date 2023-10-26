#include <iostream>

using namespace std;

/*
    Implementación con DP para obtener el n-ésimo término
    de la Sucesión de Fibonacci.
*/
int fibonacci(int n){
    //Se crea la estructura de datos
    int A[n+1]; //Para Fibonacci es suficiente un arreglo
    
    //Se colocan los casos base
    A[0] = 1;
    A[1] = 1;

    //Se llena el resto de la estructura
    for(int i = 2; i <= n; ++i)
        A[i] = A[i-1] + A[i-2];
    
    //El valor solicitado se encuentra en la última celda
    return A[n];
}

int main(int argc, char* argv[]){
    if(argc != 2){
        cout << "El programa debe ejecutarse con el siguiente formato: fibonacci_dp <posición requerida>\n";
        exit(EXIT_FAILURE);
    }
    int n = atoi(argv[1]);
    if(n <= 0){
        cout << "La posición requerida debe ser mayor a 0.\n";
        exit(EXIT_FAILURE);
    }

    cout << "El n-ésimo término de la sucesión de Fibonacci es: " << fibonacci(n) << "\n";

    return 0;
}