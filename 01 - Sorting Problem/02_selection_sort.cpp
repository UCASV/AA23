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
  Método de Selección
*/
void selection_sort(int* A, int n){
    //Se prepara variable auxiliar
    int min;

    /* Recorrido Principal */
    //Se recorre el arreglo de izquierda a derecha desde la
    //primera posición hasta la penúltima
    for(int i = 0; i < n-1; ++i){
        //Se asume que el dato en la posición actual es el
        //más pequeño desde acá hasta el final
        min = i;
        
        /* Recorrido Secundario*/
        //Se recorre desde una posición después de la actual
        //y hasta el final
        for(int j = i+1; j < n; ++j){
            //Si se encuentra un dato más pequeño que el que
            //está al inicio, se actualiza la posición del dato
            //mínimo
            if(A[j] < A[min])
                min = j;
        }

        //Si después del recorrido secundario la posición actual
        //no tiene el dato mínimo, se hace un swap entre la posición
        //actual y la posición dónde está el dato mínimo
        if(min != i){
            int temp = A[i];
            A[i] = A[min];
            A[min] = temp;
        }
    }
}

int main(void){
    //Arreglo de prueba
    int size = 6, A[size] = {5,2,4,6,1,3};

    cout << "Arreglo antes de ordenar: ";
    show_array(A,size);

    //Se ejecuta el ordenamiento
    selection_sort(A,size);
    
    cout << "Arreglo después de ordenar: ";
    show_array(A,size);

    return 0;
}
