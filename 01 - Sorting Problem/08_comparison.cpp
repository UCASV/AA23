#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#include <chrono>

using namespace std;

#include "08_comparison.hpp"

int main(int argc, char** argv){
    //Se verifica que se haya invocado el programa proporcionando la cantidad de datos a ordenar
    if( argc != 2 ){
        cout << "El programa debe ejecutarse colocando el tamaño del arreglo a ordenar. >:|\n";
        exit(EXIT_FAILURE);
    }

    //Se extrae la cantidad de datos del segundo parámetro de entrada al programa
    int n = atoi(argv[1]);
    //Preparamos un arreglo para cada algoritmo
    int A[n], B[n], C[n], D[n], E[n], F[n];

    //Se establece la semilla para generación de datos aleatorios
    srand(time(NULL));
    //Se generan los datos aleatorios
    for(int i = 0; i < n; i++){
        A[i] = rand() % 1000 + 1; //Se restringe a que sean números entre 1 y 1000
        F[i] = E[i] = D[i] = C[i] = B[i] = A[i];
    }

    //Se preparan variables para medición del tiempo
    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<double> time_insertion, time_selection, time_bubble, time_merge, time_heap, time_quick;

    /*****************************************************************************************/
    /*
        Para cada algoritmo, se toma el tiempo antes y después de su ejecución para determinar
        su tiempo de ejecución.
    */

    start = std::chrono::system_clock::now();
    insertion_sort(A, n);
    end = std::chrono::system_clock::now();
    time_insertion = end - start;

    start = std::chrono::system_clock::now();
    selection_sort(B, n);
    end = std::chrono::system_clock::now();
    time_selection = end - start;

    start = std::chrono::system_clock::now();
    bubble_sort(C, n);
    end = std::chrono::system_clock::now();
    time_bubble = end - start;

    start = std::chrono::system_clock::now();
    merge_sort(D, 0, n-1);
    end = std::chrono::system_clock::now();
    time_merge = end - start;

    start = std::chrono::system_clock::now();
    heapsort(E, n);
    end = std::chrono::system_clock::now();
    time_heap = end - start;

    start = std::chrono::system_clock::now();
    quicksort(F, 0, n-1);
    end = std::chrono::system_clock::now();
    time_quick = end - start;

    //Se informan los resultados
    cout << "Insertion Sort se tardó: " << time_insertion.count() << " segundos\n";
    cout << "Selection Sort se tardó: " << time_selection.count() << " segundos\n";
    cout << "Bubble Sort se tardó: \t " << time_bubble.count() << " segundos\n";
    cout << "Merge Sort se tardó: \t " << time_merge.count() << " segundos\n";
    cout << "Heapsort se tardó: \t " << time_heap.count() << " segundos\n";
    cout << "Quicksort se tardó: \t " << time_quick.count() << " segundos\n";

    return 0;
}
