#include <iostream>

using namespace std;

enum order {IN,PRE,POST};

typedef struct node {
    //struct node* parent;
    int data;
    struct node* left;
    struct node* right;
} tree;

tree* root = NULL;

/*
    TODO:
    - Insertar
    - Eliminar
    - Buscar
    - Modificar nodo
    - Mostrar (In - Pre - Post)
    - Vacío
*/

bool is_empty_tree(tree* T){
    return T == NULL;
}

tree* create_node(int value){
    tree* node = (tree*) malloc( sizeof(tree) );
    
    node->data = value;
    node->left = NULL;
    node->right = NULL;

    return node;
}

void insert_aux(tree* T, int value){
    if(value <= T->data)
        if(T->left == NULL) T->left = create_node(value);
        else insert_aux(T->left, value);
    else
        if(T->right == NULL) T->right = create_node(value);
        else insert_aux(T->right, value);
}

void insert(tree* T, int value){
    if(is_empty_tree(T)) root = create_node(value);
    else insert_aux(T, value);
}

void show_in_order(tree* T){
    if(T == NULL){
        cout << "- ";
        return;
    }
    cout << "[ ";
    cout << T->data << " ";
    show_in_order(T->left);
    show_in_order(T->right);
    cout << "] ";
}

void show_pre_order(tree* T){
    if(T == NULL){
        cout << "- ";
        return;
    }
    cout << "[ ";
    show_pre_order(T->left);
    cout << T->data << " ";
    show_pre_order(T->right);
    cout << "] ";
}

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

bool find(tree* T, int value){
    if(T == NULL) return false;
    if(value == T->data) return true;
    if(value < T->data) return find(T->left, value);
    else return find(T->right, value);
}

int main(void){
    int A[] = {58,18,95,7,45,85,97,2,24,46,63,86,23,42,47,87,27,56,39,32};
    int n = sizeof(A) / sizeof(int);

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

    return 0;
}