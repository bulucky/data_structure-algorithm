#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 2025

// 键值对
typedef struct Pair
{
    int key;
    char* val;
} Pair;

// 节点 -- 链式处理哈希冲突
typedef struct Node
{
    Pair pair;
    struct Node* next;
} Node;

// 哈希表 元素为链式节点
typedef struct HashMap 
{
    Node* buckets[MAX_SIZE];
} HashMap;

/**
 * @brief 哈希表构造函数 -- 初始化
 * 
 * @details ...
 * 
 * @param[in] no
 * 
 * @return HashMap地址 (地址)        
 */
HashMap* new_hash_map() {
    bool new_hp_ok = false;
    HashMap* hash_map = malloc(sizeof(HashMap));
    if(hash_map == NULL) {
        printf("memory malloc failed! \n");
        // return false;
    }else {
        for(size_t i = 0; i < MAX_SIZE; ++i) {
            Node* node = malloc(sizeof(Node));
            if(node == NULL) {
                printf("memory malloc failed! \n");
                // return false;
            }else {
                Pair pair;
                pair.val = malloc(sizeof(char));
                if(pair.val == NULL) {
                    printf("memory malloc failed! \n");
                }else {
                    pair.key = -1;
                    strcpy(pair.val, "\0");
                    node->pair = pair;
                    node->next = NULL;
                    hash_map->buckets[i] = node;
                    new_hp_ok = true;
                }
            } 
        }
    }
    if(new_hp_ok) return hash_map;
    else return NULL;
}

/**
 * @brief 哈希表析构函数 -- 释放内存
 * 
 * @details ...
 * 
 * @param[in] hash_map地址
 * 
 * @return no        
 */
void del_hash_map(HashMap* hash_map) {
    for(size_t i = 0; i < MAX_SIZE; ++i) {
        if(hash_map->buckets[i]->next == NULL) {                // 链表仅存在首届点 -- 无元素
            free(hash_map->buckets[i]->pair.val);       // 释放键值对内存
            hash_map->buckets[i]->pair.val = NULL;  
            free(hash_map->buckets[i]);
            hash_map->buckets[i] = NULL;                        // 释放节点内存
        }else {                                                 // 链表存在除首节点外节点 -- 即认为存在元素
            Node* node_temp = hash_map->buckets[i];
            Node* node_temp_current = node_temp->next;
            while(node_temp_current != NULL) {
                Node* node_temp_current_next = node_temp_current->next;        // 暂存下一节点地址
                printf("free element: %d---%s \n", node_temp_current->pair.key, node_temp_current->pair.val);
                free(node_temp_current->pair.val);                // 释放当前地址
                node_temp_current->pair.val = NULL;
                free(node_temp_current);
                node_temp_current = node_temp_current_next;
            }
            hash_map->buckets[i]->next = NULL;
        }
    }
}

// 哈希函数
int hash_func(int key) {
    return key % MAX_SIZE;
}

/**
 * @brief 哈希表填加元素
 * 
 * @details ...
 * 
 * @param[in] hash_map 哈希表指针
 * @param[in] key 填加键值对(元素) 键       (值)
 * @param[in] val 填加键值对(元素) 值指针   (指针)
 * 
 * @return bool        
 */
bool hash_set(HashMap* hash_map, const int key, const char* val) {
    bool hash_set_ok = false;
    
    Node* node = malloc(sizeof(Node));
    if(node == NULL) {
        printf("memory malloc failed! \n");
    }else {
        Pair pair;
        pair.val = malloc(sizeof(*val));
        if(pair.val == NULL) {
            printf("memory malloc failed! \n");
        }else {
            pair.key = key;
            strcpy(pair.val, val);
            node->pair = pair;
            node->next = NULL;
            // pair.val = NULL;

            int hash_code = hash_func(key);
            Node* node_temp = hash_map->buckets[hash_code];
            while(node_temp->next) {
                node_temp = node_temp->next;
            }
            printf("set element: %d---%s \n", key, val);
            node_temp->next = node;
            hash_set_ok = true;
        }
    }   

    return hash_set_ok;
}   

/**
 * @brief 哈希表查找元素并打印
 * 
 * @details ...
 * 
 * @param[in] hash_map 哈希表指针
 * @param[in] key 填加键值对(元素) 键       (值)
 * 
 * @return bool        
 */
bool hash_find(HashMap* hash_map, const int key) {
    bool hash_find_ok = false;

    int hash_code = hash_func(key);
    if(hash_map->buckets[hash_code]->next == NULL) {
        printf("element not find! %d \n", key);
    }else {
        // 打印链表节点键值对 值内容
        Node* node_temp = hash_map->buckets[hash_code];
        while(node_temp->next) {
            printf("find element: %d---%s \n", key, node_temp->next->pair.val);
            node_temp = node_temp->next;
        }
        hash_find_ok = true;
    }

    return hash_find_ok;
}

/**
 * @brief 哈希表删除指定键值对
 * 
 * @details ...
 * 
 * @param[in] hash_map 哈希表指针
 * @param[in] key 填加键值对(元素) 键       (值)
 * 
 * @return bool        
 */
bool hash_del(HashMap* hash_map, const int key) {
    bool hash_del_ok = false;

    int hash_code = hash_func(key);
    if(hash_map->buckets[hash_code]->next == NULL) {
        printf("element not exist! \n");
    }else {
        // 存在除首节点外节点(元素) -- 释放内存 
        Node* node_temp = hash_map->buckets[hash_code];  // 头节点
        Node* node_temp_current = node_temp->next;       // 当前节点
        while(node_temp_current != NULL) {
            Node* node_temp_current_next = node_temp_current->next;                         // 暂存下一个节点地址(可能为空)
            printf("delete element: %d---%s \n", key, node_temp_current->pair.val);
            free(node_temp_current->pair.val);                                      // 释放当前节点值
            node_temp_current->pair.val = NULL;
            free(node_temp_current);                                                // 释放当前节点
            node_temp_current = node_temp_current_next;                                     // 处理下一个节点
        }
        hash_map->buckets[hash_code]->next = NULL;                                          // 恢复为初始头节点
        hash_del_ok = true;
    }

    return hash_del_ok;
}

int main(int argc, char const* argv[]) 
{   
    printf("hash_map_chaining \n");

    HashMap* hp = new_hash_map();
    hash_set(hp, 2025, "g");
    hash_set(hp, 2025, "rr");
    hash_set(hp, 2025, "ccc");
    hash_set(hp, 2026, "!!!!");

    hash_find(hp, 2025);
    hash_del(hp, 2025);
    hash_find(hp, 2025);

    del_hash_map(hp);
    
    return 0;
}