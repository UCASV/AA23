#include "test_array.hpp"

/*
    Implementación de una Hash Table utilizando únicamente
    números enteros y una Hash Function sencilla.
*/
int hash_function(int n){
    //En nuestro ejemplo, sabemos que el dato más grande es 5000
    //La Hash Function es una simple operación de módulo
    return n % 5000;
}

//Búsqueda en la Hash Table
bool search_hash_table(int* A, int v){
    //Se calcula el hash para valor buscado
    int hash = hash_function(v);

    //Se verifica su existencia en la Hash Table
    return A[hash] == v;
}

int main(int argc, char** argv){
    //Se verifica que se haya invocado el programa proporcionando el dato a buscar
    if( argc != 2 ){
        cout << "El programa debe ejecutarse colocando el dato a buscar. >:|\n";
        exit(EXIT_FAILURE);
    }

    //Se extrae el dato a buscar del segundo argumento
    int v = atoi(argv[1]);

    //Se prepara la Hash Table para un máximo de <nmax> valores
    int HT[nmax];

    //Se colocan los datos en la Hash Table utilizando la Hash Function
    for(int i = 0; i < n; i++)
        HT[ hash_function(A[i]) ] = v;

    //Si el dato a buscar no excede a <nmax>, se busca en la Hash Table
    if(v <= nmax && search_hash_table(HT, v)) cout << "El dato fue encontrado! :)\n";
    else cout << "El dato NO fue encontrado! :(\n";

    return 0;
}