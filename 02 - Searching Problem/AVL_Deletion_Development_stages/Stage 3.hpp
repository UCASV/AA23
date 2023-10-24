void removal_rebalance(tree* n){
    tree *parent, *gramps, *sibling, *anchor;
    position parent_position;

    while(n->parent != NULL){
        parent = n->parent;

        if(check_position(n) == LEFT){
            if(parent->balance == -1){
                parent->balance = 0;
                n = parent;
            }
            if(parent->balance == 0){
                parent->balance = 1;
                
                break;
            }
            if(parent->balance == 1){
                sibling = parent->right;

                if(sibling->balance < 0) anchor = RL_rotation(parent, sibling);
                else anchor = RR_rotation(parent, sibling);

                break;
            }
        }else{
            if(parent->balance == -1){
                sibling = parent->right;

                if(sibling->balance > 0) anchor = LR_rotation(parent, sibling);
                else anchor = LL_rotation(parent, sibling);

                break;
            }
            if(parent->balance == 0){
                parent->balance = -1;
                
                break;
            }
            if(parent->balance == 1){
                parent->balance = 0;
                n = parent;
            }
        }
    }
}