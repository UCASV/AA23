void insertion_rebalance(tree* n){
    tree *parent;

    while(n->parent != NULL){
        parent = n->parent;

        if(check_position(n) == LEFT){
			if(parent->balance == 0){
				parent->balance = -1;
				n = parent;
			}
			if(parent->balance == 1){
				parent->balance = 0;
				break;
			}
		}else{
			if(parent->balance == -1){
				parent->balance = 0;
				break;
			}
			if(parent->balance == 0){
				parent->balance = 1;
				n = parent;
			}
		}
    }
}
