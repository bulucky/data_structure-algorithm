#include <stdio.h>
#include <stdlib.h>

#define E int

typedef struct treeNode
{
    E element;
    struct treeNode* left;
    struct treeNode* right;
}* tNode;

tNode create_node(E element) {
    tNode node = malloc(sizeof(struct treeNode));
    if(node == NULL) return NULL;
    node->element = element;
    node->left = node->right = NULL;

    return node;
}

tNode insert_node(tNode root, E element) {
    if(root) {
        if(element < root->element) root->left = insert_node(root->left, element);
        else if(element > root->element) root->right = insert_node(root->right, element); 
    }else {
        root = create_node(element);
    }

    return root;
}

tNode find_node(tNode root, E element) {
    while(root) {
        if(element < root->element) root = root->left;
        else if(element > root->element) root = root->right;
        else return root;
    }

    return NULL;
}

tNode find_max(tNode root) {
    while(root && root->right) {
        root = root->right;
    }

    return root;
}

tNode delete_node(tNode root, E element) {
    if(root == NULL) return NULL;
    if(element < root->element) {
        root->left = delete_node(root->left, element);
    }else if(element > root->element) {
        root->right = delete_node(root->right, element);
    }else {
        if(root->left && root->right) {
            tNode sub_max = find_max(root->left);
            root->element = sub_max->element;
            root->left = delete_node(root->left, root->element);
        }else {
            tNode free_temp = root;
            if(root->left) root = root->left;
            else if(root->right) root = root->right;
            free(free_temp);
        }
    }

    return root;
}

void in_order(tNode root) {
    if(root == NULL) return;
    in_order(root->left);
    printf("%d ", root->element);
    in_order(root->right);
}


int main(int argc, char const* argv[])
{
    tNode root = NULL;
    root = insert_node(root, 18);
    insert_node(root, 10);
    // insert_node(root, 20);
    insert_node(root, 7);
    insert_node(root, 15);
    insert_node(root, 22);
    insert_node(root, 9);
    // insert_node(root, 8);

    in_order(root);
    delete_node(root, 10);
    printf("\n");
    in_order(root);
    // tNode f_node = find_node(root, 18);
    // printf("%d", f_node->element); 
    return 0;
}