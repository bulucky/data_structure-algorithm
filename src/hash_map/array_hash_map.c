#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 2025

// 键值对
struct Pair
{
    int key;
    char* val;
};

// 哈希表
struct HashMap
{
    struct Pair* buckets[MAX_SIZE];
};

// 初始化哈希表 (构造函数)
struct HashMap* new_hash_map() {
    struct HashMap* hash_map = (struct HashMap*)malloc(sizeof(struct HashMap));
    if(hash_map == NULL) {
        printf("memory malloc failed! \n");
        return NULL;
    }else {
        for(size_t i = 0; i < MAX_SIZE; ++i) {
            hash_map->buckets[i] = NULL;
        }
        return hash_map;
    }
}

// (析构函数)
void del_hash_map(struct HashMap* hash_map) {
    for(size_t i = 0; i < MAX_SIZE; ++i) {
        if(hash_map->buckets[i] != NULL) {
            free(hash_map->buckets[i]->val);
            hash_map->buckets[i]->val = NULL;
            free(hash_map->buckets[i]);
            hash_map->buckets[i] = NULL;
        }
    }
    free(hash_map);
    hash_map = NULL;
}

// 哈希函数
int hash_func(int key) {
    return key % MAX_SIZE;
}

// 填加元素
bool hash_set(struct HashMap* hash_map, const int key, const char* val) {
    struct Pair* pair = malloc(sizeof(struct Pair));
    pair->key = key; 
    pair->val = malloc(sizeof(*val));               // 分配内存，大小为键值对中值大小
    if(pair->val == NULL) {                               // 内存分配失败
        printf("memory malloc failed! \n");
        return false;
    }else {
        strcpy(pair->val, val);              // 将值内容拷贝至上述分配内存中
        int hash_code = hash_func(pair->key);
        hash_map->buckets[hash_code] = pair;
        return true;
    }
}

// 查询元素
bool hash_find(struct HashMap* hash_map, int key) {
    int hash_code = hash_func(key);
    if(hash_map->buckets[hash_code] == NULL) {
        printf("element not find ! \n");
        return false;
    }else {
        printf("element find: %s \n", hash_map->buckets[hash_code]->val);
        return true;
    }
}

// 删除元素
bool hash_del(struct HashMap* hash_map, int key) {
    if(hash_find(hash_map, key)) {
        int hash_code = hash_func(key);
        free(hash_map->buckets[hash_code]->val);
        hash_map->buckets[hash_code]->val = NULL;
        free(hash_map->buckets[hash_code]);
        hash_map->buckets[hash_code] = NULL;
        return true;
    }else {
        printf("element not find, delete element failed! \n");
        return false;
    }
}

int main(int argc, char const* argv[]) 
{
    // int* a = (int*)malloc(sizeof(int));
    // printf("%p\n", a);
    // free(a);
    // printf("%p\n", a);
    // char s1[] = "hello";
    // char s2[] = {'h', 'e', 'l', 'l', 'o', '\0'};
    // printf("%zu size: %zu \n", strlen(s1), sizeof(s1));
    // printf("%zu size: %zu \n", strlen(s2), sizeof(s2));
    // char* s_ptr = "hello";
    // printf("%p\n", s_ptr);
    // printf("%c\n", *s_ptr);
    struct HashMap* hp = new_hash_map();
    printf("-----set element----- \n");
    hash_set(hp, 2025, "gg");
    hash_set(hp, 2026, "rr");
    hash_set(hp, 2027, "cc");
    hash_set(hp, 2028, "!!");
    
    printf("-----find element----- \n");
    hash_find(hp, 2025);
    hash_find(hp, 2021);
    hash_find(hp, 2028);
    
    printf("-----delete element----- \n");
    hash_del(hp, 2028);
    printf("%d \n", hash_find(hp, 2028));

    del_hash_map(hp);
    
    return 0;
}

