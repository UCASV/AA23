#include "test_array.hpp"

/*
    Función que implementa el algoritmo de
    Búsqueda Lineal
*/
bool linear_search(int* A, int n, int v){
    //Se prepara una variable bandera, por efecto "abajo"
    bool ans = false;

    //Se recorre el arreglo de izquierda a derecha
    for(int i = 0; i < n; ++i)
        //Se evalúa el dato actual
        if(A[i] == v){
            //Si se ha encontrado el dato, se "levanta" la bandera
            ans = true;
            //Ya no es necesario seguir buscando
            break;
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
    
    //Se busca el dato utilizando búsqueda lineal
    if(linear_search(A, n, v)) cout << "El dato fue encontrado! :)\n";
    else cout << "El dato NO fue encontrado! :(\n";

    return 0;
}
