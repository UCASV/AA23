#include <iostream>

using namespace std;

//Enumeración utilizada para los distintos recorridos del árbol
enum order {IN,PRE,POST};
//Enumeración utilizada para la posición de un nodo con respecto a su padre
enum position {NONE,LEFT,RIGHT};

//Estructura de un nodo del árbol
typedef struct node {
    struct node* parent;
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
    node->parent = NULL;
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
        if(T->left == NULL){
            T->left = create_node(value);
            //Se especifica que el padre del nuevo nodo es la raíz actual
            T->left->parent = T;
        }
        //Si hay árbol izquierdo, se continúa en recursión
        else insert_aux(T->left, value);

    //Si el dato a ingresar es mayor al dato de la raíz actual,
    //debe ser ingresado en el subárbol derecho
    else
        //Si no hay subárbol derecho, el nuevo nodo será el hijo derecho
        //de la raíz actual
        if(T->right == NULL){
            T->right = create_node(value);
            //Se especifica que el padre del nuevo nodo es la raíz actual
            T->right->parent = T;
        }
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
    if(is_empty_tree(T)){
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
    if(is_empty_tree(T)){
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
    if(is_empty_tree(T)){
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
    Función para extraer la dirección del nodo que contiene un dato especificado.
    Esta función asume que el dato sí se encuentra dentro del árbol.
*/
tree* extract_node(tree* T, int value){
    //Si el dato de la raíz actual es el dato buscado, se retorna la dirección de la raíz actual.
    if(value == T->data) return T;

    //Si el dato buscado es menor que el de la raíz actual, se continúa la
    //búsqueda en el subárbol izquierdo
    if(value < T->data) return extract_node(T->left, value);
    //Si el dato buscado es mayor que el de la raíz actual, se continúa la
    //búsqueda en el subárbol derecho
    else return extract_node(T->right, value);
}

/*
    Función para determinar la posición de un nodo con respecto a su padre.
*/
position check_position(tree* node){
    //Si el nodo actual no tiene padre, entonces se informa que el nodo actual
    //es la raíz actual
    if(node->parent == NULL) return NONE;

    //Se verifica si la dirección del nodo actual está almacenada como el hijo
    //izquierdo de su padre o si se encuentra almacenada como su hijo derecho
    if(node->parent->left == node) return LEFT;
    else return RIGHT;
}

/*
    Función para redirigir, dado un nodo, los punteros de su padre a uno de sus hijos,
    y además establecerlo como el nuevo padre de dicho hijo.
*/
void patch_removal(tree* node, tree* child){
    //Se determina la posición del nodo con respecto a su padre
    switch(check_position(node)){
        case NONE:
            //Si no hay padre, el nodo actual es la raíz del árbol,
            //y el hijo será la nueva raíz
            root = child;
            break;
        case LEFT:
            //Si el nodo es hijo izquierdo de su padre, su hijo será el nuevo
            //hijo izquierdo del padre
            node->parent->left = child;
            break;
        case RIGHT:
            //Si el nodo es hijo derecho de su padre, su hijo será el nuevo
            //hijo derecho del padre
            node->parent->right = child;
            break;
    }
}

/*
    Función para extraer el In-Order-Successor de un subárbol derecho dado.
    La función asume que efectivamente el proceso recorre el subárbol derecho
    de algún nodo de interés.
*/
tree* extract_in_order_successor(tree* T){
    //Si ya no hay subárbol izquierdo, el nodo actual es el In-Order-Successor
    if(T->left == NULL) return T;

    //De lo contrario, se continúa buscando por la izquierda
    else return extract_in_order_successor(T->left);
}

/*
    Función para eliminar un dato del árbol.
*/
void remove(tree* T, int value){
    //Se verifica que el dato a borrar efectivamente esté en el árbol
    if(find(T, value)){
        //Se extrae la dirección del nodo que contiene el dato a borrar
        tree* node = extract_node(T, value);

        //Se inicia el proceso de borrado.
        //Si es el Caso 1 o el Caso 2, el do-while terminará inmediatamente.
        //Si ocurre el Caso 3, se hará 1, y solo 1, iteración adicional.
        do{
            //Caso 1: El nodo a borrar no tiene hijos
            if(node->left == NULL && node->right == NULL){
                //El padre del nodo a eliminar (o root) apuntará ahora a NULL
                patch_removal(node, NULL);

                //Se elimina el nodo y se libera su memoria
                free(node);
                break; //Se termina el proceso
            }

            //Caso 2a: El nodo solo tiene hijo izquierdo
            if(node->right == NULL){ //Basta esta condición, ya que el primer if ha filtrado el caso de los dos hijos nulos
                //El nuevo padre del hijo izquierdo será el padre del nodo a eliminar
                node->left->parent = node->parent;
                
                //El padre del nodo a eliminar (o root) apuntará ahora al hijo izquierdo
                patch_removal(node, node->left);

                //Se elimina el nodo y se libera su memoria
                free(node);
                break; //Se termina el proceso
            }

            //Caso 2b: El nodo solo tiene hijo derecho
            if(node->left == NULL){ //Basta esta condición, ya que el primer if ha filtrado el caso de los dos hijos nulos
                //El nuevo padre del hijo derecho será el padre del nodo a eliminar
                node->right->parent = node->parent;

                //El padre del nodo a eliminar (o root) apuntará ahora al hijo derecho
                patch_removal(node, node->right);

                //Se elimina el nodo y se libera su memoria
                free(node);
                break; //Se termina el proceso
            }

            //Caso 3: El nodo tiene dos hijos

            //Se encuentra el In-Order-Successor del nodo actual
            tree* IOS = extract_in_order_successor(node->right);
            //Se sobreescribe el dato del nodo actual con el In-Order Successor encontrado
            node->data = IOS->data;

            //El nuevo nodo a eliminar, es el que contiene el In-Order-Succesor
            node = IOS;

            //Se reinicia el proceso, con garantía que se ejecutará ya sea el Caso 1 o el Caso 2
        }while(true);
    }
    else cout << "El dato no se puede eliminar porque no se encuentra dentro del árbol.\n";
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

    cout << "\n";

    //Arreglo de datos a ser eliminados del arreglo
    int B[] = {56,32,87,42,7,46,18,95,58};
    //Se determina el tamaño del arreglo
    int m = sizeof(B) / sizeof(int);

    //Se recorre el arreglo, eliminando los datos celda por celda
    for(int i = 0; i < m; ++i){
        remove(root, B[i]);
        show(root, IN); //Se muestra el árbol después de cada eliminación
    }

    destroy(root);

    return 0;
}
