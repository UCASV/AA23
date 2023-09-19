#include <iostream>

using namespace std;

bool linear_search(int* A, int v){
    bool ans = false;
    int n = sizeof(A)/sizeof(int);

    for(int i = 0; i < n; ++i)
        if(A[i] == v){
            ans = true;
            break;
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

    if(linear_search(A, v)) cout << "El dato fue encontrado! :)\n";
    else cout << "El dato NO fue encontrado! :(\n";

    return 0;
}