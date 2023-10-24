void removal_rebalance(tree* n){
    tree *parent;

    while(n->parent != NULL){
        parent = n->parent;

        if(check_position(n) == LEFT){
            if(parent->balance == -1){
                parent->balance = 0;
                n = parent;
            }
        }else{
            if(parent->balance == 1){
                parent->balance = 0;
                n = parent;
            }
        }
    }
}