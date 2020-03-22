#include <stdio.h>

/*

           15
          / \
         /   \
        /     \
       13      11
      / \      / \    
     /   \    /   \
    10   12	 9     8
   / \      /     / \
  7   2    6     3	 1
*/

// variable to store maximum number of nodes
int complete_node = 15;

// array to store the tree
int tree[] = {-1, 15, 13, 11, 10, 12, 9, 8, 7, 2, -1, -1, 6, -1, 3, 1};

int get_right_child(int index)
{
    // node is not null
    // and the result must lie within the number of nodes for a complete binary tree
    if(tree[index]!= -1 && ((2*index)+1)<=complete_node)
        return (2*index)+1;
    // right child doesn't exist
    return -1;
}

int get_left_child(int index)
{
    // node is not null and the result must lie within the number of nodes for a complete binary tree
    if(tree[index]!= -1  && (2*index)<=complete_node)
        return 2*index;
    // left child doesn't exist
    return -1;
}


int Find_greater(int v){
	int count = 0;
	void preorder(int index){
		if(index>0 && tree[index]!= -1)
    	{
        	if(tree[index] > v){
        		count++;
        		preorder(get_left_child(index)); //visiting left subtree
        		preorder(get_right_child(index)); //visiting right subtree
    		}
    	}
	}
	preorder(1);
	return count;
}

int main()
{
    int x = Find_greater(8);
    printf("%d", x);
    return 0;
}
