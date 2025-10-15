#include <stdio.h>
#include <stdlib.h>

#define element char

typedef struct treeNode 
{
    element E;
    struct treeNode* left;
    struct treeNode* right;

}* Node;


void pre_order(Node root) {
    if(root == NULL) return;
    printf("%c", root->E);
    pre_order(root->left);
    pre_order(root->right);
}


int main(int argc, char const* argv[])
{
    printf("binary tree \n");
    
    Node A = malloc(sizeof(struct treeNode));
    Node B = malloc(sizeof(struct treeNode));
    Node C = malloc(sizeof(struct treeNode));
    Node D = malloc(sizeof(struct treeNode));
    Node E = malloc(sizeof(struct treeNode));
    Node F = malloc(sizeof(struct treeNode));

    A->E = 'A';
    B->E = 'B';
    C->E = 'C';
    D->E = 'D';
    E->E = 'E';
    F->E = 'F';

    A->left = B;
    A->right = C;
    B->left = D;
    B->right = E;
    C->left = NULL;
    C->right = F;
    D->left = D->right = NULL;
    E->left = E->right = NULL;
    F->left = F->right = NULL;

    pre_order(A);

    return 0;
}