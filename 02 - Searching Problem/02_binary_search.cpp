#include "test_array.hpp"
#include "../01 - Sorting Problem/08_comparison.hpp"

/*
    Función que implementa el algoritmo de
    Búsqueda Binaria
*/
bool binary_search(int* A, int n, int v){
    //Se prepara una variable bandera, por efecto "abajo"
    bool ans = false;
    //Se preparan las variables del algoritmo:
    //  - Posición inicial
    //  - Posición final
    //  - Posición de la celda al medio
    int p = 0, r = n - 1, middle;

    //Si el arreglo no está ordenado, debe ordenarse primero
    quicksort(A, 0, n-1); //Esta línea no es parte del algoritmo

    //Mientras quede al menos un dato a evaluar, se continúa el proceso
    while(p <= r){
        //Se calcula la celda al medio
        middle = (p + r) / 2; //El floor se ejecuta automáticamente

        //Se compara el dato al medio con el buscado
        if(A[middle] == v){
            //Si se ha encontrado el dato, se "levanta" la bandera
            ans = true;
            //Ya no es necesario seguir buscando
            break;
        }else
            //Si el dato es menor que el del medio, se continúa buscando
            //a su izquierda
            if(v < A[middle]) r = middle - 1; //Se ajusta la posición final
            //Si el dato es mayor que el del medio, se continúa buscando
            //a su derecha
            else p = middle + 1; //Se ajusta la posición inicial
    }

    //Se retorna el resultado del proceso
    return ans;
}

int main(int argc, char** argv){
    //Se verifica que se haya invocado el programa proporcionando el dato a buscar
    if( argc != 2 ){
        cout << "El programa debe ejecutarse colocando el dato a buscar. >:|\n";
        exit(EXIT_FAILURE);
    }

    //Se extrae el dato a buscar del segundo argumento
    int v = atoi(argv[1]);
    
    //Se busca el dato utilizando búsqueda binaria
    if(binary_search(A, n, v)) cout << "El dato fue encontrado! :)\n";
    else cout << "El dato NO fue encontrado! :(\n";

    return 0;
}