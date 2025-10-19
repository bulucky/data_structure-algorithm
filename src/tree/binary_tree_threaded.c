#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define element char

typedef struct treeNode
{   
    element E;
    struct treeNode* left;
    struct treeNode* right;
    bool left_threaded;
    bool right_threaded;

}* tNode;

tNode pre = NULL;
void pre_order_threaded(tNode root) {
    if(root == NULL) return;
    // 结点线索化
    if(root->left == NULL) {
        root->left = pre;
        root->left_threaded = true;
    }
    if(pre && pre->right == NULL) {
        pre->right = root;
        pre->right_threaded = true;
    }

    pre = root;
    if(root->left_threaded == false)
        pre_order_threaded(root->left);
    if(root->right_threaded == false)
        pre_order_threaded(root->right);
}


tNode create_node(element e) {
    tNode node = malloc(sizeof(struct treeNode));
    if(node == NULL) return NULL;
    node->E = e;
    node->left = node->right = NULL;
    node->left_threaded = node->right_threaded = false;
    
    return node;
}

int main(int argc, char const* argv[])
{
    tNode A = create_node('A');
    tNode B = create_node('B');
    tNode C = create_node('C');
    tNode D = create_node('D');
    tNode E = create_node('E');

    A->left = B;    
    A->right = C;
    B->left = D;    
    B->right = E;

    pre_order_threaded(A);

    return 0;
}