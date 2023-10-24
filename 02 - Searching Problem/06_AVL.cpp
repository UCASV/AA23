#include <iostream>
using namespace std;

enum order {IN,PRE,POST};
enum position {NONE,LEFT,RIGHT};

typedef struct node {
    struct node* parent;
    int data;
    short balance;
    struct node* left;
    struct node* right;
} tree;

tree* root = NULL;

bool is_empty_tree(tree* T){
    return T == NULL;
}

tree* create_node(int value){
    tree* n = (tree*) malloc( sizeof(tree) );

    n->data = value;
    n->balance = 0;
    n->parent = n->left = n->right = NULL;

    return n;
}

position check_position(tree* T){
    if(T->parent != NULL)
        if(T->parent->left == T)
            return LEFT;
        else
            return RIGHT;
    else return NONE;
}

void L_rotation(tree* parent, tree* T){
    tree* temp = T->left;

    parent->right = temp;
    if(temp != NULL) temp->parent = parent;
    
    T->left = parent;
    parent->parent = T;
}

tree* RR_rotation(tree* parent, tree* T){
    L_rotation(parent, T);

    if(T->balance == 0){
        T->balance = -1;
        T->left->balance = 1;
    }else{
        T->balance = 0;
        T->left->balance = 0;
    }

    return T;
}

void R_rotation(tree* parent, tree* T){
    tree* temp = T->right;

    parent->left = temp;
    if(temp != NULL) temp->parent = parent;

    T->right = parent;
    parent->parent = T;
}

tree* LL_rotation(tree* parent, tree* T){
    R_rotation(parent, T);

    if(T->balance == 0){
        T->balance = 1;
        T->right->balance = -1;
    }else{
        T->balance = 0;
        T->right->balance = 0;
    }

    return T;
}

tree* RL_rotation(tree* gramps, tree* parent){
    tree* pivot = parent->left;
    
    tree* temp = pivot->right;
    parent->left = temp;
    if(temp != NULL) temp->parent = parent;

    pivot->right = parent;
    parent->parent = pivot;

    L_rotation(gramps, pivot);
    
    switch(pivot->balance){
        case -1:
            pivot->left->balance = 0;
            pivot->right->balance = 1;
            break;

        case 0:
            pivot->left->balance = 0;
            pivot->right->balance = 0;
            break;
    
        case 1:
            pivot->left->balance = -1;
            pivot->right->balance = 0;
            break;
    }

    pivot->balance = 0;

    return pivot;
}

tree* LR_rotation(tree* gramps, tree* parent){
    tree* pivot = parent->right;

    tree* temp = pivot->left;
    parent->right = temp;
    if(temp != NULL) temp->parent = parent;

    pivot->left = parent;
    parent->parent = pivot;

    R_rotation(gramps, pivot);

    switch(pivot->balance){
        case -1:
            pivot->left->balance = 0;
            pivot->right->balance = 1;
            break;

        case 0:
            pivot->left->balance = 0;
            pivot->right->balance = 0;
            break;
    
        case 1:
            pivot->left->balance = -1;
            pivot->right->balance = 0;
            break;
    }

    pivot->balance = 0;

    return pivot;
}

void insertion_rebalance(tree* n){
    position parent_position;
    tree *parent, *gramps, *anchor;

    while(n->parent != NULL){
        parent = n->parent;

        if(check_position(n) == LEFT){
			if(parent->balance == -1){
				gramps = parent->parent;
				parent_position = check_position(parent);
				
				if(n->balance == 1) anchor = LR_rotation(parent, n);
				else anchor = LL_rotation(parent, n);
			}else{
				if(parent->balance == 0){
					parent->balance = -1;
					n = parent;
					continue;
				}

				parent->balance = 0;
				break;
			}
		}else{
			if(parent->balance == -1){
				parent->balance = 0;
				break;
			}else{
				if(parent->balance == 0){
					parent->balance = 1;
					n = parent;
					continue;
				}

				gramps = parent->parent;
				parent_position = check_position(parent);
				
				if(n->balance == -1) anchor = RL_rotation(parent, n);
				else anchor = RR_rotation(parent, n);
			}
		}
			
		anchor->parent = gramps;
		if(gramps != NULL)
			if(parent_position == LEFT) gramps->left = anchor;
			else gramps->right = anchor;
		else root = anchor;
		
		break;
    }
}

tree* insert_aux(tree* T, int value){
    if(value <= T->data)
        if(T->left == NULL){
            T->left = create_node(value);
            T->left->parent = T;

            return T->left;
        }else return insert_aux(T->left, value);
    else
        if(T->right == NULL){
            T->right = create_node(value);
            T->right->parent = T;

            return T->right;
        }else return insert_aux(T->right, value);
}

void insert(tree* T, int value){
    if(is_empty_tree(T)) root = create_node(value);
    else{
        tree* n = insert_aux(T, value);

        insertion_rebalance(n);
    }
}

bool find(tree* T, int value){
    if(T == NULL) return false;
    if(T->data == value) return true;
    if(value < T->data) return find(T->left, value);
    else return find(T->right, value);
}

tree* extract_node(tree* T, int value){
    if(T->data == value) return T;
    if(value < T->data) return extract_node(T->left, value);
    else return extract_node(T->right, value);
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

void removal_rebalance(tree* n){
    tree *parent, *gramps, *sibling, *anchor;
    position parent_position;

    while(n->parent != NULL){
        parent = n->parent;

        if(check_position(n) == LEFT){
            if(parent->balance == -1){
                parent->balance = 0;
                n = parent;

                continue;
            }
            else{
                if(parent->balance == 0){
                    parent->balance = 1;
                    
                    break;
                }

                gramps = parent->parent;
                parent_position = check_position(parent);
                sibling = parent->right;

                if(sibling->balance < 0) anchor = RL_rotation(parent, sibling);
                else anchor = RR_rotation(parent, sibling);
            }
        }else{
            if(parent->balance == -1){
                gramps = parent->parent;
                parent_position = check_position(parent);
                sibling = parent->right;

                if(sibling->balance > 0) anchor = LR_rotation(parent, sibling);
                else anchor = LL_rotation(parent, sibling);
            }else{
                if(parent->balance == 0){
                    parent->balance = -1;
                    
                    break;
                }

                parent->balance = 0;
                n = parent;

                continue;
            }
        }

        anchor->parent = gramps;
        if(gramps != NULL)
            if(parent_position == LEFT) gramps->left = anchor;
            else gramps->right = anchor;
        else root = anchor;

        break;
    }
}

void remove(tree* T, int value){
    if(find(T,value)){
        tree* n;
        tree* temp = extract_node(T, value);

        do{
            
            if(temp->left == NULL && temp->right == NULL){
                patch_removal(temp, NULL);

                n = temp->parent;
                free(temp);
                removal_rebalance(n);

                break;
            }
            
            if(temp->left == NULL || temp->right == NULL){
                if(temp->right == NULL){
                    n = temp->left;
                    patch_removal(temp, temp->left);
                    temp->left->parent = temp->parent;
                }
                if(temp->left == NULL){
                    n = temp->right;
                    patch_removal(temp, temp->right);
                    temp->right->parent = temp->parent;
                }
                
                free(temp);
                removal_rebalance(n);

                break;
            }

            tree* IOS = extract_in_order_successor(temp->right);
            temp->data = IOS->data;
            temp = IOS;
        }while(true);
    }
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

void show_balances_pre_order(tree* T){
    if(is_empty_tree(T)){
        cout << "- ";
        return;
    }
    cout << "[ ";
    cout << T->balance << " ";
    show_balances_pre_order(T->left);
    show_balances_pre_order(T->right);
    cout << "] ";
}

void show_balances_in_order(tree* T){
    if(is_empty_tree(T)){
        cout << "- ";
        return;
    }
    cout << "[ ";
    show_balances_in_order(T->left);
    cout << T->balance << " ";
    show_balances_in_order(T->right);
    cout << "] ";
}

void show_balances_post_order(tree* T){
    if(is_empty_tree(T)){
        cout << "- ";
        return;
    }
    cout << "[ ";
    show_balances_post_order(T->left);
    show_balances_post_order(T->right);
    cout << T->balance << " ";
    cout << "] ";
}

void show_balances(tree* T, order mode){
    switch(mode){
        case IN:
            show_balances_in_order(T);
            break;
        case PRE:
            show_balances_pre_order(T);
            break;
        case POST:
            show_balances_post_order(T);
            break;
    }
    cout << "\n";
}

void destroy(tree* T){
    if(T == NULL) return;
    destroy(T->left);
    destroy(T->right);
    free(T);
}

int main(void){
    int A[] = {80,70,96,97,99,20,10,90,95,73,77,50,30,60,40,98,85};
    int n = sizeof(A)/sizeof(int);

    int B[] = {10,90,80};
    int m = sizeof(B)/sizeof(int);

    for(int i = 0; i < n; ++i){
        insert(root,A[i]);

        show(root, PRE); cout << "\n";
        show_balances(root, PRE); cout << "\n\n";
    }
    for(int i = 0; i < m; ++i){
        remove(root,B[i]);
        show(root, PRE); cout << "\n";
        show_balances(root, PRE); cout << "\n\n";
    }

    destroy(root);

    return 0;
}