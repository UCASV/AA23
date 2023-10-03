#include <iostream>

using namespace std;

//Enumeración utilizada para los distintos recorridos del árbol
enum order {IN,PRE,POST};

//Estructura de un nodo del árbol
typedef struct node {
    int data;
    struct node* left;
    struct node* right;
} tree;

//Puntero a la raíz del árbol
tree* root = NULL;

/*
    Función para determinar su un árbol está vacío.
*/
bool is_empty_tree(tree* T){
    //El árbol está vacío si el puntero a la raíz apunta a NULL
    return T == NULL;
}

/*
    Función para crear un nuevo nodo en memoria dado un dato para su
    contenido, retorna la dirección de este nuevo nodo.
*/
tree* create_node(int value){
    //Se reserva memoria para el nodo
    tree* node = (tree*) malloc( sizeof(tree) );
    
    //Se inicializan los datos del nuevo nodo
    node->data = value;
    node->left = NULL;
    node->right = NULL;

    return node;
}

/*
    Funciones para insertar un nuevo nodo en el árbol
*/
//Función auxiliar para el proceso de inserción
void insert_aux(tree* T, int value){
    //Si el dato a ingresar es menor o igual al dato de la raíz actual,
    //debe ser ingresado en el subárbol izquierdo
    if(value <= T->data)
        //Si no hay subárbol izquierdo, el nuevo nodo será el hijo izquierdo
        //de la raíz actual
        if(T->left == NULL) T->left = create_node(value);
        //Si hay árbol izquierdo, se continúa en recursión
        else insert_aux(T->left, value);

    //Si el dato a ingresar es mayor al dato de la raíz actual,
    //debe ser ingresado en el subárbol derecho
    else
        //Si no hay subárbol derecho, el nuevo nodo será el hijo derecho
        //de la raíz actual
        if(T->right == NULL) T->right = create_node(value);
        //Si hay árbol derecho, se continúa en recursión
        else insert_aux(T->right, value);
}
//Función principal para el proceso de inserción
void insert(tree* T, int value){
    //Si el árbol está vacío, el nuevo nodo es la raíz
    if(is_empty_tree(T)) root = create_node(value);
    //De lo contrario, se utiliza la función auxiliar
    else insert_aux(T, value);
}

/*
    Funciones para mostrar el contenido del árbol
*/
//Función para mostar el árbol con recorrido Pre-Order
void show_pre_order(tree* T){
    if(T == NULL){
        cout << "- ";
        return;
    }
    cout << "[ ";
    cout << T->data << " ";
    show_pre_order(T->left);
    show_pre_order(T->right);
    cout << "] ";
}
//Función para mostar el árbol con recorrido In-Order
void show_in_order(tree* T){
    if(T == NULL){
        cout << "- ";
        return;
    }
    cout << "[ ";
    show_in_order(T->left);
    cout << T->data << " ";
    show_in_order(T->right);
    cout << "] ";
}
//Función para mostar el árbol con recorrido Post-Order
void show_post_order(tree* T){
    if(T == NULL){
        cout << "- ";
        return;
    }
    cout << "[ ";
    show_post_order(T->left);
    show_post_order(T->right);
    cout << T->data << " ";
    cout << "] ";
}
//Función principal para mostrar el árbol. Recibe un indicador del
//tipo de recorrido a ejecutar
void show(tree* T, order mode){
    switch(mode){
        case IN:
            show_in_order(T);
            break;
        case PRE:
            show_pre_order(T);
            break;
        case POST:
            show_post_order(T);
            break;
    }
    cout << "\n";
}

/*
    Función para determinar si un dato se encuentra o no en el árbol.
*/
bool find(tree* T, int value){
    //Si el árbol está vacío, no se encontró el dato.
    if(T == NULL) return false;

    //Si el dato de la raíz actual es el dato buscado, se ha encontrado! :^)
    if(value == T->data) return true;

    //Si el dato buscado es menor que el de la raíz actual, se continúa la
    //búsqueda en el subárbol izquierdo
    if(value < T->data) return find(T->left, value);
    //Si el dato buscado es mayor que el de la raíz actual, se continúa la
    //búsqueda en el subárbol derecho
    else return find(T->right, value);
}

/*
    Función para liberar toda la memoria asignada al árbol.
*/
void destroy(tree* T){
    //Si el árbol está vacío, no hay nada que hacer
    if(T == NULL) return;

    //Se libera el subárbol izquierdo
    destroy(T->left);

    //Se libera el subárbol derecho
    destroy(T->right);

    //Se libera la raíz
    free(T);
}

int main(void){
    //Arreglo de datos a ingresar al árbol
    int A[] = {58,18,95,7,45,85,97,2,24,46,63,86,23,42,47,87,27,56,39,32};
    //Se determina el tamaño del arreglo
    int n = sizeof(A) / sizeof(int);

    //Se recorre el arreglo, insertando los datos celda por celda
    for(int i = 0; i < n; ++i)
        insert(root, A[i]);

    cout << "Mostrando árbol en In-Order:\n";
    show(root, IN);

    cout << "\nMostrando árbol en Pre-Order:\n";
    show(root, PRE);

    cout << "\nMostrando árbol en Post-Order:\n";
    show(root, POST);

    cout << "\n";

    if(find(root,24)) cout << "Esto sí se va a imprimir.\n";
    else cout << "Esto no se va a imprimir ;)\n";

    if(find(root,43)) cout << "Esto no se va a imprimir ;)\n";
    else cout << "Esto sí se va a imprimir.\n";

    destroy(root);
    
    return 0;
}