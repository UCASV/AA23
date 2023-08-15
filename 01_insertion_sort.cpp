#include <iostream>

using namespace std;

/*
  Función para mostrar el contenido de un arreglo de enteros
*/
void show_array(int* A, int n){
    //Se abre un bracket para el arreglo
    cout << "[ ";
    //Se recorre el arreglo
    for(int i = 0; i < n; i++)
        //Se imprime la posición actual seguida de un espacio
        cout << A[i] << " ";
    //Se cierra el bracket del arreglo
    cout << "]\n";
}

/*
  Función para ordenar un arreglo de enteros utilizando el
  Método de Inserción
*/
void insertion_sort(int* A, int n){
    //Se preparan variables auxiliares
    int key, i;

    /* Recorrido Principal */
    //Se recorre el arreglo de izquierda a derecha a partir
    //de la segunda posición
    for(int j = 1; j < n; j++){
        //Se copia la celda actual del recorrido principal
        key = A[j];
        
        /* Recorrido Secundario hacia Atrás*/
        //El recorrido comienza en el dato anterior al actual
        i = j - 1;
        //Mientras no hayamos llegado al tope, y mientras el
        //dato encontrado sea más grande que el dato almacenado,
        //se continúa el recorrido hacia atrás
        while( i >= 0 && A[i] > key ){
            //El dato encontrado es más grande que el almacenado,
            //por lo que debe moverse a la derecha
            A[i+1] = A[i];
            //Se avanza hacia atrás
            i--;
        }

        //Cuando acabe el recorrido secundario es porque se encontró
        //un dato más pequeño que el almacenado, o porque se llegó
        //al tope en la izquierda, en ambos casos el dato almacenado
        //debe insertarse a la derecha de donde se detuvo el recorrido
        A[i+1]=key;
    }
}

int main(void){
    //Arreglo de prueba
    int size = 6, A[size] = {5,2,4,6,1,3};

    cout << "Arreglo antes de ordenar: ";
    show_array(A,size);
    //Se ejecuta el ordenamiento
    insertion_sort(A,size);
    cout << "Arreglo después de ordenar: ";
    show_array(A,size);

    return 0;
}
