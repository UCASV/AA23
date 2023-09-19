#include <iostream>

using namespace std;

#include "../01 - Sorting Problem/08_comparison.hpp"

bool binary_search(int* A, int v){
    bool ans = false;
    int n = sizeof(A)/sizeof(int), p = 0, r = n - 1, middle;

    quicksort(A, p, r);

    while(p <= r){
        middle = (p+r)/2;
        if(v < A[middle]) r = middle-1;
        else
            if(v > A[middle]) p = middle+1;
            else{
                ans = true;
                break;
            }
    }

    return ans;
}

int main(int argc, char** argv){
    if( argc != 2 ){
        cout << "El programa debe ejecutarse colocando el tamaño del arreglo. >:|\n";
        exit(EXIT_FAILURE);
    }

    int n = atoi(argv[1]);
    int A[n];

    srand(time(NULL));
    for(int i = 0; i < n; i++){
        A[i] = rand() % 1000 + 1;
    }

    int v;
    cout << "Ingrese el número a buscar en el arreglo: ";
    cin >> v;

    if(binary_search(A, v)) cout << "El dato fue encontrado! :)\n";
    else cout << "El dato NO fue encontrado! :(\n";

    return 0;
}