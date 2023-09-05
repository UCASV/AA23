#include <iostream>
#include <climits>

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
  Funciones para ordenar un arreglo de enteros utilizando el
  Quicksort
*/
//Función que calcula el punto de partición en el arreglo
int partition(int* A, int p, int r){
    int temp; //Variable auxiliar
    //Se toma como pivote el último dato
    int pivot = A[r];
    //Se toma como primera posición de referencia una antes
    //del primer dato
    int i = p-1;

    /* Recorrido de los datos */
    //Desde el inicio y hasta la penúltima posición
    for(int j = p; j < r; ++j)
        //Si el dato actual es más pequeño que el pivote,
        //se mueve hacia la izquierda y se actualiza la
        //posición de referencia
        if(A[j] <= pivot){
            ++i;
            temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
    
    //Se mueve el pivote a su nueva posición (a la derecha
    //de la última posición de referencia)
    temp = A[r];
    A[r] = A[i+1];
    A[i+1] = temp;

    //Se retorna la posición a la derecha de la última referencia
    //como el punto de corte
    return i+1;
}

//Función principal del método
void quicksort(int* A, int p, int r){
    //Se verifica que el arreglo tenga al menos
    //2 datos para poder proceder.
    //Si p == r, solo hay un dato.
    //Si p > r, es un arreglo no válido.
    if(p < r){
        //Se calcula el punto de corte
        int q = partition(A, p, r);

        //Se ordena la mitad izquierda
        quicksort(A, p, q-1);
        //Se ordena la mitad derecha
        quicksort(A, q+1, r);
    }
}

int main(void){
    //Arreglo de prueba
    int size = 8, A[size] = {5,2,4,6,1,3,9,7};

    cout << "Arreglo antes de ordenar: ";
    show_array(A,size);

    //Se ejecuta el ordenamiento
    quicksort(A,0,size-1);
    
    cout << "Arreglo después de ordenar: ";
    show_array(A,size);

    return 0;
}
