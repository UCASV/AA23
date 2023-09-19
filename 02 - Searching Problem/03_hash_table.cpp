#include <iostream>

using namespace std;

bool search(int* HT, int v){
    int n = sizeof(HT)/sizeof(int);
    int key = v % n;
    return HT[key] == v;
}

int main(int argc, char** argv){
    if( argc != 2 ){
        cout << "El programa debe ejecutarse colocando el tamaño del arreglo. >:|\n";
        exit(EXIT_FAILURE);
    }

    int n = atoi(argv[1]), value, key;
    int HT[n];

    srand(time(NULL));
    for(int i = 0; i < n; i++){
        value = rand() % 1000 + 1;
        key = value & n;
        HT[key] = value;
    }

    int v;
    cout << "Ingrese el número a buscar en el arreglo: ";
    cin >> v;

    if(search(HT, v)) cout << "El dato fue encontrado! :)\n";
    else cout << "El dato NO fue encontrado! :(\n";

    return 0;
}