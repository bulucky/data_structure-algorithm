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

/*****************queue******************/

#define qElement Node

typedef struct queueNode
{
    qElement E;
    struct queueNode* next;
}* qNode;

typedef struct queue
{
    struct queueNode* front;
    struct queueNode* rear;
}* queue;

/** 
*@brief 初始化队列
*
*@param queue queue 队列指针
*
*@return bool       是否成功
*/
bool init_queue(queue queue) {
    qNode node = malloc(sizeof(struct queueNode));  // 前驱节点
    if(node == NULL) return true;
    queue->front = queue->rear = node;
    
    return true;
}

/** 
*@brief 判断队列是否为空
*
*@param queue queue 队列指针
*
*@return bool       是否为空
*/
bool is_empty(queue queue) {
    return queue->front == queue->rear;
}

/** 
*@brief 入列操作
*
*@param queue queue 队列指针
*@param qElement e  队列节点元素
*
*@return bool       是否成功
*/
bool push_queue(queue queue, qElement e) {
    qNode node = malloc(sizeof(struct queueNode));
    if(node == NULL) return false;
    node->E = e;
    queue->rear->next = node;
    queue->rear = node;

    return true;
}

/** 
*@brief 出列操作
*
*@param queue queue 队列指针
*
*@return qElement   队列节点元素指针
*/
qElement pop_queue(queue queue) {
    if(is_empty(queue)) return NULL;
    qNode node = queue->front->next;
    qElement e = node->E;
    queue->front->next = node->next;
    if(node == queue->rear) queue->front = queue->rear;

    return e;
}

/*****************queue******************/

void level_order(Node root) {
    struct queue queue;
    init_queue(&queue);
    push_queue(&queue, root);
    
    while(!is_empty(&queue)) {
        qElement node = pop_queue(&queue);
        printf("%c", node->E);
        if(node->left != NULL) push_queue(&queue, node->left);
        if(node->right != NULL) push_queue(&queue, node->right);
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

    level_order(A);

    return 0;
}