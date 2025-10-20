#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define element char

typedef struct treeNode
{   
    element E;
    struct treeNode* left;
    struct treeNode* right;
    struct treeNode* parent;
    bool left_threaded;
    bool right_threaded;

}* tNode;

/**
*@brief 前序遍历线索化,仅线索化无输出
*
*@param tNode root 根结点指针
*
*@return void
*/ 
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

/**
*@brief 遍历输出前序线索化后的二叉树
*
*@param tNode root 根结点指针
*
*@return void
*/
void pre_order(tNode root) {
    while(root) {
        printf("%c", root->E);
        if(root->right_threaded) {
            root = root->right;
        }else if(root->right == NULL) {
            break;
        }else {
            root = root->left;
        }
    }
}

tNode in_pre = NULL;
/**
*@brief 中序遍历线索化,仅线索化无输出
*
*@param tNode root 根结点指针
*
*@return void
*/
void in_order_threaded(tNode root) {
    if(root == NULL) return;
    if(root->left_threaded == false) {
        in_order_threaded(root->left);
    }
    // 线索化
    if(root->left == NULL) {
        root->left = in_pre;
        root->left_threaded = true;
    }
    if(in_pre && in_pre->right == NULL) {
        in_pre->right = root;
        in_pre->right_threaded = true;
    }
    in_pre = root;
    if(root->right_threaded == false) {
        in_order_threaded(root->right);
    }
}

/**
*@brief 遍历输出中序线索化后的二叉树结点元素
*
*@param tNode root 根结点指针
*
*@return void
*/
void in_order(tNode root) {
    // 找到未线索化时的左边叶子结点
    while(root->left_threaded == false) {
        root = root->left;
    }
    // 通过线索化标志向右来进行索引遍历 --线索化后右边为后继结点
    while(root) {
        printf("%c", root->E);
        if(root->right_threaded || root->right) {
            root = root->right;
        }else {
            break;
        }
    }
}

tNode post_pre = NULL;
/**
*@brief 中序遍历线索化,仅线索化无输出
*
*@param tNode root 根结点指针
*
*@return void
*/
void post_order_threaded(tNode root) {
    if(root == NULL) return;
    if(root->left && root->left_threaded == false) {
        post_order_threaded(root->left);
        root->left->parent = root;
    }
    if(root->right && root->right_threaded == false) {
        post_order_threaded(root->right);
        root->right->parent = root;
    }
    // 线索化
    if(root->left == NULL) {
        root->left = post_pre;
        root->left_threaded = true;
    }
    if(post_pre && post_pre->right == NULL) {
        post_pre->right = root;
        post_pre->right_threaded = true;
    }
    post_pre = root;
}

/**
*@brief 遍历输出后序线索化后的二叉树结点元素
*
*@param tNode root 根结点指针
*
*@return void
*/
void post_order(tNode root) {
    // 记录二叉树根结点
    tNode root_tNode = root;
    // 找到未线索化时的左边叶子结点
    while(root->left_threaded == false) {
        root = root->left;
    }
    // 以线索化右标志和其兄弟结点为遍历索引
    while(root) {
        printf("%c", root->E);
        if(root->right_threaded == true) {
            root = root->right;
        }else if(root != root_tNode && root->parent->right) {
            root = root->parent->right;
        }else {
            break;
        }
    }
}

tNode create_node(element e) {
    tNode node = malloc(sizeof(struct treeNode));
    if(node == NULL) return NULL;
    node->E = e;
    node->left = node->right = node->parent = NULL;
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
    // tNode F = create_node('F');

    A->left = B;    
    A->right = C;
    B->left = D;    
    B->right = E;
    // C->right = F;

    // pre_order_threaded(A);
    // pre_order(A);
    // in_order_threaded(A);
    // in_order(A);
    post_order_threaded(A);
    post_order(A);

    return 0;
}

/**
*todo: 后序线索化存在问题, 加入F
*/ 