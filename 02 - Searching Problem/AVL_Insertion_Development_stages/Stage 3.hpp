void insertion_rebalance(tree* n){
    tree *parent, *anchor;

    while(n->parent != NULL){
        parent = n->parent;

        if(check_position(n) == LEFT)
			if(parent->balance < 0){
				if(n->balance == 1) anchor = LR_rotation(parent, n);
				else anchor = LL_rotation(parent, n);
				break;
			}
			if(parent->balance == 0){
				parent->balance = -1;
				n = parent;
			}
			if(parent->balance > 0){
				parent->balance = 0;
				break;
			}
        else
			if(parent->balance < 0){
				parent->balance = 0;
				break;
			}
			if(parent->balance == 0){
				parent->balance = 1;
				n = parent;
			}
			if(parent->balance > 0){
				if(n->balance == -1) anchor = RL_rotation(parent, n);
				else anchor = RR_rotation(parent, n);
				break;
			}
    }
}
