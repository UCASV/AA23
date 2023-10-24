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