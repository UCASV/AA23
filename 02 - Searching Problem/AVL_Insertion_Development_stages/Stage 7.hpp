void insertion_rebalance(tree* n){
    position parent_position;
    tree *parent, *gramps, *anchor;

    while(n->parent != NULL){
        parent = n->parent;
        parent_position = check_position(parent);

        if(check_position(n) == LEFT)
            if(parent->balance < 0){
                gramps = parent->parent;

                if(n->balance > 0) anchor = LR_rotation(parent, n);
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
        else
            if(parent->balance < 0){
                    parent->balance = 0;

                    break;
            }else{
                if(parent->balance == 0){
                    parent->balance = 1;
                    n = parent;

                    continue;
                }
                
                gramps = parent->parent;

                if(n->balance < 0) anchor = RL_rotation(parent, n);
                else anchor = RR_rotation(parent, n);
            }

        anchor->parent = gramps;
        if(gramps != NULL)
            if(parent_position == LEFT) gramps->left = anchor;
            else gramps->right = anchor;
        else root = anchor;

        break;
    }
}