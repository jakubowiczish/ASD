#include <stdio.h>
#include <time.h>
#include <cstdlib>
/*
1. zaimplementowaæ funkcje sprawdzaj¹c¹ czy drzewo binarne jest drzewem BST
2. zaimplementowaæ funkcje sprawdzaj¹c¹ czy drzewo binarne jest drzewem AVL
3. Dane jest drzewo BST, napisaæ funkcjê zwracaj¹c¹ wskaŸnik do elementu bêd¹cego median¹
*/
typedef struct BSTnode{
    int val;
    struct BSTnode* right;
    struct BSTnode* left;
    struct BSTnode* parent;
} BSTnode;

void add_node(BSTnode* &root, int value){
    BSTnode* tmp = new BSTnode;
    tmp->val=value;
    tmp->left = NULL;
    tmp->right = NULL;
    tmp->parent = NULL;

    // If root is empty?
    if(root == NULL){
        root=tmp;
        return;
    }

    BSTnode* tmpRoot = root;
    BSTnode* prevRoot = NULL;

    // Find the father of a new node
    while(tmpRoot != NULL){
        prevRoot=tmpRoot;
        if(value < tmpRoot->val){
            tmpRoot=tmpRoot->left;
        }
        else{
            tmpRoot=tmpRoot->right;
        }
    }

    // Insert the new node
    if(value < prevRoot->val) {
        prevRoot->left=tmp;
    }
    else{
        prevRoot->right=tmp;
    }
    tmp->parent=prevRoot;

}

BSTnode* min(BSTnode* root){
    if(root->left == NULL) return root;
    while(root->left!=NULL){
        root=root->left;
    }
    return root;
}

BSTnode* max(BSTnode* root){
    if(root->right == NULL) return root;
    while(root->right!=NULL){
        root=root->right;
    }
    return root;
}

void free_BST(BSTnode* root){
    if(root == NULL){
        return;
    }
    if(root->left != NULL){
        free_BST(root->left);
    }
    if(root->right != NULL){
        free_BST(root->right);
    }
    delete root;
    return;
}

void in_order_tree_walk(BSTnode* node){
    if(node->left != NULL){
        in_order_tree_walk(node->left);
    }
    printf("%d\n", node->val);
    if(node->right != NULL){
        in_order_tree_walk(node->right);
    }
}
int get_size_of_subtree(BSTnode* node){
    if(node!=NULL){
        int size = 1;
        size += get_size_of_subtree(node->left);
        size += get_size_of_subtree(node->right);
        return size;
    }
    return 0;
}
int max(int w, int v){
    if(w>v)return w;
    return v;
}
int get_height_of_subtree(BSTnode* node){
    if(node!=NULL){
        int size = 1;
        size += max(get_height_of_subtree(node->left),get_height_of_subtree(node->right));
        return size;
    }
    return 0;
}
/// ZADANIE 1
bool is_BST_h(BSTnode *root, int minKey, int maxKey)
{
    if(root == nullptr)
        return true;
    if(root -> val < minKey || root -> val > maxKey)
        return false;
    return is_BST(root -> left, minKey, node -> val) && is_BST(node -> right, node -> val, maxKey);
}

bool is_BST(BSTnode *root)
{
    if(is_BST_h(root,INT_MIN,INT_MAX))
        return true;
    return false;
}
/// ZADANIE 2
bool is_AVL(BSTnode* tree){
    if(tree==NULL) return true;
    int diff = get_height_of_subtree(tree->left) - get_height_of_subtree(tree->right);
    if(diff<0)diff=-diff;
    if(diff>=2){
        printf("\n DIFF HEHE \n");
        return false;
    }
    else return is_AVL(tree->left) && is_AVL(tree->right);
}
bool is_AVL(BSTnode* tree, int &height){
    if(tree==NULL){
        height=0;
        return 1;
    }
    int left_height = 0;
    int right_height = 0;

    bool left_AVL = false;
    bool right_AVL = false;

    left_AVL = is_AVL(tree->left, left_height);
    right_AVL = is_AVL(tree->right, right_height);

    height = max(left_height, right_height) + 1; //wysokoœæ na której jest aktualny tree licz¹c od do³u i od 1

    int diff = left_height - right_height;
    if(diff<0)diff=-diff;
    if(diff>=2){
        return false;
    }
    return left_AVL && right_AVL;

}
void inorder(BSTnode* tree){
    if(tree!=NULL){
        inorder(tree->left);
        printf("%d \n", tree->val);
        inorder(tree->right);
    }
}

/// ZADANIE 3
BSTnode* kth_element(BSTnode* node, int &k){
    if(node!=NULL){
        BSTnode* tmp = kth_element(node->left,k);
        if(tmp!=NULL) return tmp;
        k--;
        if(k==0) return node;
        tmp = kth_element(node->right,k);
        if(tmp!=NULL) return tmp;
    }
    return NULL;
}
BSTnode* get_median(BSTnode* tree){
    int number_of_elements = get_size_of_subtree(tree);
    number_of_elements/=2;
    return kth_element(tree,number_of_elements);
}
int main(){
    BSTnode* tree = NULL;
    add_node(tree, 25);
    add_node(tree, 20);
    add_node(tree, 22);
    add_node(tree, 10);
    add_node(tree, 12);
    add_node(tree, 36);
    add_node(tree, 30);
    add_node(tree, 40);
    add_node(tree, 28);
    add_node(tree, 38);
    add_node(tree, 48);
    add_node(tree, 50);
    //add_node(tree, 51);

    in_order_tree_walk(tree);

    printf("\n SIEMA %d", get_height_of_subtree(tree->left));
    printf("\n SIEMA2 %d", get_height_of_subtree(tree));
    printf("\n SIEMA3 %d", is_AVL(tree));
    int height = 0;
    printf("\n SIEMA4 %d", is_AVL(tree,height));
    printf("\n");

    inorder(tree);

    int k = 5;
    printf("\n SIEMA5 %d", kth_element(tree,k)->val);
    printf("\n SIEMA6 %d", get_median(tree)->val);

}
