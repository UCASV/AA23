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
    short balance;
    struct node* left;
    struct node* right;
} tree;

//Puntero a la raíz del árbol
tree* root = NULL;

/*###################### Funciones de administración del árbol ######################*/
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
    tree* n = (tree*) malloc( sizeof(tree) );

    //Se inicializan los datos del nuevo nodo
    n->data = value;
    n->balance = 0;
    n->parent = n->left = n->right = NULL;

    return n;
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

/*###################### Funciones de Rotación de Nodos ######################*/
/*
    Función que rota a un nodo B junto a su padre A en el
    sentido opuesto al de las agujas del reloj.
*/
void L_rotation(tree* A, tree* B){
    //El hijo izquierdo de B queda huérfano
    tree* temp = B->left;

    //El nuevo hijo derecho de A será el nodo huérfano
    A->right = temp;
    //Si el huérfano no es nulo, se actualiza que su nuevo
    //padre es A
    if(temp != NULL) temp->parent = A;
    
    //El nuevo hijo izquierdo de B será A
    B->left = A;
    //El nuevo padre de A será B
    A->parent = B;

    //B es la nueva raíz del árbol local
}

/*
    Función que ejecuta el caso de Rotación RR: El nodo en desbalance
    lo está a causa de su hijo derecho, quién a su vez ha sido analizado
    por su derecha.
*/
tree* RR_rotation(tree* p, tree* n){
    //Se ejecuta una rotación hacia la izquierda entre p y n
    L_rotation(p, n);

    /*
        A continuación se verifica el balance original de n,
        de lo que dependen los nuevos valores de balance tanto
        de n como de p.
    */
    //n estaba originalmente neutral, la rotación se provocó
    //por un borrado en su hermano
    if(n->balance == 0){
        n->balance = -1;
        n->left->balance = 1;
    //Caso contrario, n estaba originalmente Right-Heavy, la
    //rotación se provocó por una inserción
    }else{
        n->balance = 0;
        n->left->balance = 0;
    }

    //Se retorna la dirección de la nueva raíz del árbol local
    return n;
}

/*
    Función que rota a un nodo A junto a su padre B en el
    sentido de las agujas del reloj.
*/
void R_rotation(tree* B, tree* A){
    //El hijo derecho de A queda huérfano
    tree* temp = A->right;

    //El nuevo hijo izquierdo de B será el nodo huérfano
    B->left = temp;
    //Si el huérfano no es nulo, se actualiza que su nuevo
    //padre es B
    if(temp != NULL) temp->parent = B;

    //El nuevo hijo derecho de A será B
    A->right = B;
    //El nuevo padre de B será A
    B->parent = A;

    //A es la nueva raíz del árbol local
}

/*
    Función que ejecuta el caso de Rotación LL: El nodo en desbalance
    lo está a causa de su hijo izquierdo, quién a su vez ha sido analizado
    por su izquierda.
*/
tree* LL_rotation(tree* parent, tree* T){
    //Se ejecuta una rotación hacia la derecha entre p y n
    R_rotation(parent, T);

    /*
        A continuación se verifica el balance original de n,
        de lo que dependen los nuevos valores de balance tanto
        de n como de p.
    */
    //n estaba originalmente neutral, la rotación se provocó
    //por un borrado en su hermano
    if(T->balance == 0){
        T->balance = 1;
        T->right->balance = -1;
    //Caso contrario, n estaba originalmente Left-Heavy, la
    //rotación se provocó por una inserción
    }else{
        T->balance = 0;
        T->right->balance = 0;
    }

    //Se retorna la dirección de la nueva raíz del árbol local
    return T;
}

/*
    Función que ejecuta el caso de Rotación RL: El nodo en desbalance
    lo está a causa de su hijo derecho, quién a su vez ha sido afectado
    por su hijo izquierdo.
*/
tree* RL_rotation(tree* p, tree* n){
    //Es necesario desglosar al hijo izquierdo de n
    tree* Y = n->left;
    
    /* Primera rotación: n y Y rotan hacia la derecha */
    R_rotation(n, Y);

    /* Segunda rotación: p y Y rotan hacia la izquierda */
    L_rotation(p, Y);
    
    /*
        A continuación se verifica el balance original de Y,
        de lo que dependen los nuevos valores de balance de
        n y p.
    */
    switch(Y->balance){
        //Y era originalmente Left-Heavy
        case -1:
            Y->left->balance = 0;  //p
            Y->right->balance = 1; //n
            break;

        //Y era originalmente Neutral
        /*
            Esto sólo es posible si en un borrado se
            escoge hacerlo por RL. En el contexto de la
            clase es un escenario que no usamos, está aquí
            por completitud.
        */
        case 0:
            Y->left->balance = 0;
            Y->right->balance = 0;
            break;

        //Y era originalmente Right-Heavy
        case 1:
            Y->left->balance = -1; //p
            Y->right->balance = 0; //n
            break;
    }

    //En todos los escenarios Y pasa a ser Neutral
    Y->balance = 0;

    //Se retorna la dirección de la nueva raíz del árbol local
    return Y;
}

/*
    Función que ejecuta el caso de Rotación LR: El nodo en desbalance
    lo está a causa de su hijo izquierdo, quién a su vez ha sido afectado
    por su hijo derecho.
*/
tree* LR_rotation(tree* p, tree* n){
    //Es necesario desglosar al hijo derecho de n
    tree* Y = n->right;

    /* Primera rotación: n y Y rotan hacia la izquierda */
    L_rotation(n, Y);

    /* Segunda rotación: p y Y rotan hacia la derecha */
    R_rotation(p, Y);

    /*
        A continuación se verifica el balance original de Y,
        de lo que dependen los nuevos valores de balance de
        n y p.
    */
    switch(Y->balance){
        //Y era originalmente Left-Heavy
        case -1:
            Y->left->balance = 0;  //n
            Y->right->balance = 1; //p
            break;

        //Y era originalmente Neutral
        /*
            Esto sólo es posible si en un borrado se
            escoge hacerlo por LR. En el contexto de la
            clase es un escenario que no usamos, está aquí
            por completitud.
        */
        case 0:
            Y->left->balance = 0;
            Y->right->balance = 0;
            break;

        //Y era originalmente Right-Heavy
        case 1:
            Y->left->balance = -1; //n
            Y->right->balance = 0; //p
            break;
    }

    //En todos los escenarios Y pasa a ser Neutral
    Y->balance = 0;

    //Se retorna la dirección de la nueva raíz del árbol local
    return Y;
}

/*###################### Funciones para la Inserción de Nodos ######################*/
/*
    Función que recibe la dirección de un nuevo insertado, actualiza los balances
    de todos los nodos involucrados, y corrige desbalances si son detectados.
*/
void insertion_rebalance(tree* n){
    //Variables auxiliares para el proceso
    position parent_position;
    tree *p, *g, *anchor;

    /*
        Ciclo que ejecuta un proceso de recorrido desde n hacia
        arriba, terminando ya sea al llegar a la raíz o hasta que
        ya no sea necesario continuar.
    */
    //El proceso sigue potencialmente mientras no se haya llegado
    //a la raíz del árbol
    while(n->parent != NULL){
        //Se extrae la dirección del padre del nodo actual
        p = n->parent;

        //El proceso se bifurca dependiendo de la posición de
        //n con respecto a su padre
        if(check_position(n) == LEFT){ //n es hijo izquierdo de p
			//El proceso se bifurca nuevamente dependiendo del
            //balance original de p
            if(p->balance == -1){ //p era Left-Heavy
                //p pasaría a ser Left-Heavier, hay desbalance y
                //debe ser corregido

                //Se rescata la dirección del abuelo antes de las rotaciones
				g = p->parent;
                //Se rescata la posición de p con respecto a g antes de las rotaciones
				parent_position = check_position(p);
				
                //El caso de rotación depende del balance de n
                //anchor almacena la raíz del nuevo árbol local después de las rotaciones
                //Si n creció por la derecha, se aplica LR
				if(n->balance == 1) anchor = LR_rotation(p, n);
                //Si n creció por la izquierda, se aplica LL
				else anchor = LL_rotation(p, n);
			}else{
				if(p->balance == 0){ //p era Neutral
                    //p pasa a ser Left-Heavy
					p->balance = -1;

                    //No hay desbalance local, pero la altura local creció,
                    //es necesario recorrer hacia arriba
					n = p;

					continue; //El resto del while ya no es necesario
				}

                //Si ninguno de los dos if anteriores se cumplió,
                //entonces p era Right-Heavy

                //p pasa a ser Neutral
				p->balance = 0;

				break; //El resto del while ya no es necesario
			}
		}else{ //n es hijo derecho de p
            //El proceso se bifurca nuevamente dependiendo del
            //balance original de p
			if(p->balance == -1){ //p era Left-Heavy
                //p pasa a ser Neutral
				p->balance = 0;

				break; //El resto del while ya no es necesario
			}else{
				if(p->balance == 0){ //p era Neutral
                    //p pasa a ser Right-Heavy
					p->balance = 1;

                    //No hay desbalance local, pero la altura local creció,
                    //es necesario recorrer hacia arriba
					n = p;

					continue; //El resto del while ya no es necesario
				}

                //Si ninguno de los dos if anteriores se cumplió,
                //entonces p era Right-Heavy

                //p pasaría a ser Right-Heavier, hay desbalance y
                //debe ser corregido

				//Se rescata la dirección del abuelo antes de las rotaciones
                g = p->parent;
                //Se rescata la posición de p con respecto a g antes de las rotaciones
				parent_position = check_position(p);
				
                //El caso de rotación depende del balance de n
                //anchor almacena la raíz del nuevo árbol local después de las rotaciones
                //Si n creció por la izquierda, se aplica RL
				if(n->balance == -1) anchor = RL_rotation(p, n);
                //Si n creció por la derecha, se aplica RR
				else anchor = RR_rotation(p, n);
			}
		}
		
        //Lo siguiente es común a, y se ejecutará solo para, las situaciones en
        //las que se ha ejecutado un caso de rotación

        //El nuevo padre de anchor será g
		anchor->parent = g;
        //Si g no es nulo, debe actualizarse uno de sus hijos
		if(g != NULL)
            //Si p estaba a la izquierda de g, debe actualizarse su hijo izquierdo
			if(parent_position == LEFT) g->left = anchor;
            //Si p estaba a la derecha de g, debe actualizarse su hijo derecho
			else g->right = anchor;
        //Si g es nulo, anchor es la nueva raíz de todo el árbol, y debe actualizarse root
		else root = anchor;
		
		break; //No es necesario continuar recorriendo el árbol hacia arriba
    }
}

//Función auxiliar para el proceso de inserción
tree* insert_aux(tree* T, int value){
    //Si el dato a ingresar es menor o igual al dato de la raíz actual,
    //debe ser ingresado en el subárbol izquierdo
    if(value <= T->data)
        //Si no hay subárbol izquierdo, el nuevo nodo será el hijo izquierdo
        //de la raíz actual
        if(T->left == NULL){
            T->left = create_node(value);
            //Se especifica que el padre del nuevo nodo es la raíz actual
            T->left->parent = T;

            //Se retorna la dirección del nuevo nodo
            return T->left;
        }
        //Si hay árbol izquierdo, se continúa en recursión
        else return insert_aux(T->left, value);
    
    //Si el dato a ingresar es mayor al dato de la raíz actual,
    //debe ser ingresado en el subárbol derecho
    else
        //Si no hay subárbol derecho, el nuevo nodo será el hijo derecho
        //de la raíz actual
        if(T->right == NULL){
            T->right = create_node(value);
            //Se especifica que el padre del nuevo nodo es la raíz actual
            T->right->parent = T;

            //Se retorna la dirección del nuevo nodo
            return T->right;
        }
        //Si hay árbol derecho, se continúa en recursión
        else return insert_aux(T->right, value);
}

//Función principal para el proceso de inserción
void insert(tree* T, int value){
    //Si el árbol está vacío, el nuevo nodo es la raíz
    if(is_empty_tree(T)) root = create_node(value);
    //De lo contrario, se utiliza la función auxiliar
    else{
        //Se recibe la dirección del nuevo nodo insertado
        tree* n = insert_aux(T, value);

        //Se procede a evaluar, actualizar, y posiblemente corregir el AVL
        insertion_rebalance(n);
    }
}

/*###################### Funciones utilitarias para búsqueda en el árbol ######################*/
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

/*###################### Funciones para el Borrado de Nodos ######################*/
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
    Función que recibe ya sea la dirección del padre del nodo borrado (Caso 1)
    o la dirección del nodo que ha sustituido al nodo borrado (Caso 2), y actualiza
    los balances de todos los nodos involucrados, y corrige desbalances si son detectados.
*/
void removal_rebalance(tree* n){
    //Variables auxiliares para el proceso
    position parent_position;
    tree *p, *g, *sibling, *anchor;

    /*
        Ciclo que ejecuta un proceso de recorrido desde n hacia
        arriba, terminando ya sea al llegar a la raíz o hasta que
        ya no sea necesario continuar.
    */
    //El proceso sigue potencialmente mientras no se haya llegado
    //a la raíz del árbol
    while(n->parent != NULL){
        //Se extrae la dirección del padre del nodo actual
        p = n->parent;

        //El proceso se bifurca dependiendo de la posición de
        //n con respecto a su padre
        if(check_position(n) == LEFT){ //n es hijo izquierdo de p
            //El proceso se bifurca nuevamente dependiendo del
            //balance original de p
            if(p->balance == -1){ //p era Left-Heavy
                //p pasa a ser Neutral
                p->balance = 0;

                //No hay desbalance local, pero la altura local decreció,
                //es necesario recorrer hacia arriba
                n = p;

                continue; //El resto del while ya no es necesario
            }
            else{
                if(p->balance == 0){ //p era Neutral
                    //p pasa a ser Right-Heavy
                    p->balance = 1;
                    
                    break; //El resto del while ya no es necesario
                }

                //Si ninguno de los dos if anteriores se cumplió,
                //entonces p era Right-Heavy

                //p pasaría a ser Right-Heavier, hay desbalance y
                //debe ser corregido

				//Se rescata la dirección del abuelo antes de las rotaciones
                g = p->parent;
                //Se rescata la posición de p con respecto a g antes de las rotaciones
                parent_position = check_position(p);

                //Se obtiene la dirección del hermano de n
                sibling = p->right;

                //El caso de rotación depende del balance del hermano
                //anchor almacena la raíz del nuevo árbol local después de las rotaciones
                //Si el hermano es Left-Heavy, se aplica RL
                if(sibling->balance < 0) anchor = RL_rotation(p, sibling);
                //Si el hermano es Neutra o Right-Heavy, se aplica RR
                else anchor = RR_rotation(p, sibling);
            }
        }else{ //n es hijo derecho de p
            //El proceso se bifurca nuevamente dependiendo del
            //balance original de p
            if(p->balance == -1){ //p era Left-Heavy
                //p pasaría a ser Left-Heavier, hay desbalance y
                //debe ser corregido

				//Se rescata la dirección del abuelo antes de las rotaciones
                g = p->parent;
                //Se rescata la posición de p con respecto a g antes de las rotaciones
                parent_position = check_position(p);

                //Se obtiene la dirección del hermano de n                
                sibling = p->left;

                //El caso de rotación depende del balance del hermano
                //anchor almacena la raíz del nuevo árbol local después de las rotaciones
                //Si el hermano es Right-Heavy, se aplica LR
                if(sibling->balance > 0) anchor = LR_rotation(p, sibling);
                //Si el hermano es Neutral o Left-Heavy, se aplica LL
                else anchor = LL_rotation(p, sibling);
            }else{
                if(p->balance == 0){ //p era Neutral
                    //p pasa a ser Left-Heavy
                    p->balance = -1;
                    
                    break; //El resto del while ya no es necesario
                }

                //Si ninguno de los dos if anteriores se cumplió,
                //entonces p era Right-Heavy

                //p pasa a ser Neutral
                p->balance = 0;

                //No hay desbalance local, pero la altura local decreció,
                //es necesario recorrer hacia arriba
                n = p;

                continue; //El resto del while ya no es necesario
            }
        }

        //Lo siguiente es común a, y se ejecutará solo para, las situaciones en
        //las que se ha ejecutado un caso de rotación

        //El nuevo padre de anchor será g
        anchor->parent = g;
        //Si g no es nulo, debe actualizarse uno de sus hijos
        if(g != NULL)
        //Si p estaba a la izquierda de g, debe actualizarse su hijo izquierdo
            if(parent_position == LEFT) g->left = anchor;
            //Si p estaba a la derecha de g, debe actualizarse su hijo derecho
            else g->right = anchor;
        //Si g es nulo, anchor es la nueva raíz de todo el árbol, y debe actualizarse root
        else root = anchor;

        break; //No es necesario continuar recorriendo el árbol hacia arriba
    }
}

/*
    Función para eliminar un dato del árbol.
*/
void remove(tree* T, int value){
    //Se verifica que el dato a borrar efectivamente esté en el árbol
    if(find(T,value)){
        //Variable para almacenar el nodo a ser enviado al proceso de rebalance
        tree* n;
        //Se extrae la dirección del nodo que contiene el dato a borrar
        tree* temp = extract_node(T, value);

        //Se inicia el proceso de borrado.
        //Si es el Caso 1 o el Caso 2, el do-while terminará inmediatamente.
        //Si ocurre el Caso 3, se hará 1, y solo 1, iteración adicional.
        do{
            //Caso 1: El nodo a borrar no tiene hijos
            if(temp->left == NULL && temp->right == NULL){
                //El padre del nodo a eliminar (o root) apuntará ahora a NULL
                patch_removal(temp, NULL);

                //El nodo a enviar al rebalance es el padre del nodo a eliminar
                n = temp->parent;

                //Se elimina el nodo y se libera su memoria
                free(temp);

                //Se procede a evaluar, actualizar, y posiblemente corregir el AVL
                removal_rebalance(n);

                break; //Se termina el proceso
            }
            
            //Caso 2: El nodo solo tiene un hijo
            if(temp->left == NULL || temp->right == NULL){
                //Caso 2a: El nodo solo tiene hijo izquierdo
                if(temp->right == NULL){
                    //El nodo a enviar al rebalance será el hijo del nodo a eliminar
                    n = temp->left;

                    //El padre del nodo a eliminar (o root) apuntará ahora al hijo izquierdo
                    patch_removal(temp, temp->left);
                    //El nuevo padre del hijo izquierdo será el padre del nodo a eliminar
                    temp->left->parent = temp->parent;
                }
                //Caso 2b: El nodo solo tiene hijo derecho
                if(temp->left == NULL){
                    //El nodo a enviar al rebalance será el hijo del nodo a eliminar
                    n = temp->right;

                    //El padre del nodo a eliminar (o root) apuntará ahora al hijo derecho
                    patch_removal(temp, temp->right);
                    //El nuevo padre del hijo derecho será el padre del nodo a eliminar
                    temp->right->parent = temp->parent;
                }
                
                //Se elimina el nodo y se libera su memoria
                free(temp);

                //Se procede a evaluar, actualizar, y posiblemente corregir el AVL
                removal_rebalance(n);

                break; //Se termina el proceso
            }

            //Caso 3: El nodo tiene dos hijos

            //Se encuentra el In-Order-Successor del nodo actual
            tree* IOS = extract_in_order_successor(temp->right);
            //Se sobreescribe el dato del nodo actual con el In-Order Successor encontrado
            temp->data = IOS->data;

            //El nuevo nodo a eliminar, es el que contiene el In-Order-Succesor
            temp = IOS;
        }while(true);
    }
    else cout << "El dato no se puede eliminar porque no se encuentra dentro del árbol.\n";
}

/*###################### Funciones para Mostrar datos del árbol ######################*/
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

//Función para mostar los balances del árbol en Pre-Order
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

//Función para mostar los balances del árbol en In-Order
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

//Función para mostar los balances del árbol en Post-Order
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

//Función principal para mostrar los balance del árbol. Recibe un indicador del
//tipo de recorrido a ejecutar
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

/*###########################################################*/
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

/*########################### Main ##############################*/
int main(void){
    //Datos para probar los procesos de Inserción
    int A[] = {80,70,96,97,99,20,10,90,95,73,77,50,30,60,40,98,85};
    int n = sizeof(A)/sizeof(int);

    //Datos para probar los procesos de Borrado
    int B[] = {10,90,80};
    int m = sizeof(B)/sizeof(int);

    //Se insertan los datos en el AVL Tree uno por uno y se van mostrando los resultados
    for(int i = 0; i < n; ++i){
        insert(root,A[i]);

        show(root, PRE); cout << "\n";
        show_balances(root, PRE); cout << "\n\n";
    }

    //Se borran datos en el AVL Tree uno por uno y se van mostrando los resultados
    for(int i = 0; i < m; ++i){
        remove(root,B[i]);
        show(root, PRE); cout << "\n";
        show_balances(root, PRE); cout << "\n\n";
    }

    //Se libera la memoria utilizada por el árbol
    destroy(root);

    return 0;
}