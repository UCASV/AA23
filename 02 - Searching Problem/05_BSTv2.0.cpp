#include <iostream>

using namespace std;

enum order {IN,PRE,POST};
enum position {NONE,LEFT,RIGHT};

typedef struct node {
    struct node* parent;
    int data;
    struct node* left;
    struct node* right;
} tree;

tree* root = NULL;

bool is_empty_tree(tree* T){
    return T == NULL;
}

tree* create_node(int value){
    tree* node = (tree*) malloc( sizeof(tree) );
    
    node->data = value;

    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;

    return node;
}

void insert_aux(tree* T, int value){
    if(value <= T->data)
        if(T->left == NULL){
            T->left = create_node(value);
            T->left->parent = T;
        }
        else insert_aux(T->left, value);
    else
        if(T->right == NULL){
            T->right = create_node(value);
            T->right->parent = T;
        }
        else insert_aux(T->right, value);
}

void insert(tree* T, int value){
    if(is_empty_tree(T)) root = create_node(value);
    else insert_aux(T, value);
}

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
    if(is_empty_tree(T)) return false;
    if(value == T->data) return true;
    if(value < T->data) return find(T->left, value);
    else return find(T->right, value);
}

tree* extract_node(tree* T, int value){
    if(value == T->data) return T;
    if(value < T->data) return extract_node(T->left, value);
    else return extract_node(T->right, value);
}

position check_position(tree* node){
    if(node->parent == NULL) return NONE;
    if(node->parent->left == node) return LEFT;
    else return RIGHT;
}

void patch_removal(tree* node, tree* child){
    switch(check_position(node)){
        case NONE:
            root = child;
            break;
        case LEFT:
            node->parent->left = child;
            break;
        case RIGHT:
            node->parent->right = child;
            break;
    }
}

tree* extract_in_order_successor(tree* T){
    if(T->left == NULL) return T;
    else return extract_in_order_successor(T->left);
}

void remove(tree* T, int value){
    if(find(T, value)){
        tree* node = extract_node(T, value);
        do{
            if(node->left == NULL && node->right == NULL){
                patch_removal(node, NULL);

                free(node);
                break;
            }

            if(node->right == NULL){
                node->left->parent = node->parent;
                
                patch_removal(node, node->left);

                free(node);
                break;
            }

            if(node->left == NULL){
                node->right->parent = node->parent;

                patch_removal(node, node->right);

                free(node);
                break;
            }

            tree* IOS = extract_in_order_successor(node->right);
            node->data = IOS->data;
            node = IOS;
        }while(true);
    }
    else cout << "El dato no se puede eliminar porque no se encuentra dentro del árbol.\n";
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

    cout << "\n";

    int B[] = {56,32,87,42,7,46,18,95,58};
    int m = sizeof(B) / sizeof(int);

    for(int i = 0; i < m; ++i){
        remove(root, B[i]);
        show(root, IN);
    }

    return 0;
}
