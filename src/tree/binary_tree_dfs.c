#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define element char

typedef struct treeNode 
{
    element E;
    struct treeNode* left;
    struct treeNode* right;
    int flag;

}* Node;

/****************stack*****************/

#define sElement Node

typedef struct stackNode
{
    sElement E;                 // 元素
    struct stackNode* next;     // 下一节点指针

}* sNode;

/** 
*@brief 初始化栈
*
*@param sNode head  头节点(不存储数据,仅指向栈顶(存储栈顶地址))
*
*@return void
*/
void init_stack(sNode head) {
    head->E = NULL;
    head->next = NULL;
}

bool is_empty(sNode head) {
    if(head->next) return true;
    else return false;
}

/** 
*@brief 入栈操作
*
*@param sNode head 指针
*@param sElement e 元素
*
*@return bool      是否成功
*/
bool push_stack(sNode head, sElement e) {
    sNode s_node = malloc(sizeof(struct stackNode));
    if(!s_node) return false;
    s_node->E = e;
    s_node->next = head->next;
    head->next = s_node;
    
    return true;
}

/** 
*@brief 出栈操作
*
*@param sNode head  指针
*
*@return sElement   出栈元素 --二叉树结点类型
*/
sElement pop_stack(sNode head) {
    sNode head_next = head->next;
    head->next = head->next->next;
    sElement e = head_next->E;
    free(head_next);
    
    return e;
}

/** 
*@brief 返回栈顶元素指针
*
*@param sNode head  指针
*
*@return sElement   栈顶元素指针
*/
sElement peek_stack(sNode haed) {
    return haed->next->E;
}

/****************stack*****************/

void pre_order(Node root) {
    if(root == NULL) return;
    printf("%c", root->E);
    pre_order(root->left);
    pre_order(root->right);
}

void pre_order_stack(Node root) {
    struct stackNode stack;
    init_stack(&stack);                                   // 声明并初始化栈 
    while(root || is_empty(&stack)) {            
        while(root) {                                          // 从根结点开始, 所有左结点入栈
            push_stack(&stack, root);         
            printf("%c", root->E);
            root = root->left;
        }                                             
        Node node = pop_stack(&stack);                   // 查看右结点 （如果当前结点为叶子结点, 则出栈该结点, 查看其父节点及兄弟结点(若存在)
        root = node->right;
    }
}

/**
*@brief 中序遍历
*   结点访问顺序在中间(父结点、左子结点、右子结点)
*   例: B、D、E, 访问顺序为D、B、E
*@param Node root 根节点指针
*/ 
void in_order(Node root) {
    if(root == NULL) return;
    in_order(root->left);
    printf("%c", root->E);
    in_order(root->right);
}

void in_order_stack(Node root) {
    struct stackNode stack;
    init_stack(&stack);                                   
    while(root || is_empty(&stack)) {            
        while(root) {                                          
            push_stack(&stack, root);         
            root = root->left;
        }                                             
        Node node = pop_stack(&stack);
        printf("%c", node->E);                   
        root = node->right;
    }
}

/**
*@brief 后序遍历
*   结点访问顺序在最后(父结点、左子结点、右子结点)
*   例: B、D、E, 访问顺序为D、E、B
*@param Node root 根节点指针
*/
void post_order(Node root) {
    if(root == NULL) return;
    post_order(root->left);
    post_order(root->right);
    printf("%c", root->E);
}

void post_order_stack(Node root) {
    struct stackNode stack;
    init_stack(&stack);
    while(root || is_empty(&stack)) {
        while(root) {
            push_stack(&stack, root);
            root->flag = 0;
            root = root->left;   
        }
        root = peek_stack(&stack);
        if(root->flag == 0) {
            root->flag = 1;
            root = root->right;
        }else {
            printf("%c", root->E);
            pop_stack(&stack);
            root = NULL;
        }
    }
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

    // pre_order(A);
    // pre_order_stack(A);
    in_order(A);
    // post_order(A);
    // post_order_stack(A);

    return 0;
}