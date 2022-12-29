#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <_hash_table.h>

#define HT_PRIME_NUMBER_1 173
#define HT_PRIME_NUMBER_2 257

static hash_table_item_t 
HT_DELETED_ITEM = {NULL, NULL};

/*Initialise hash table item*/
static hash_table_item_t* 
ht_create_item(const char* key, const char* value) 
{
    hash_table_item_t* item = malloc(sizeof(hash_table_item_t));
    item->key = strdup(key);
    item->value = strdup(value);
    return item;
}

/*Initialise hash table*/
hash_table_t* 
ht_create_hash_table() 
{
    hash_table_t* ht = malloc(sizeof(hash_table_t));
    ht->size = 30;
    ht->count = 0;
    ht->items = calloc((size_t)ht->size, sizeof(hash_table_item_t*));
    return ht;
}

/*Delete hash table item*/
static void 
ht_delete_item(hash_table_item_t* item) 
{
    free(item->key);
    free(item->value);
    free(item);
}

/*Delete hash table*/
void 
ht_delete_hash_table(hash_table_t* ht) 
{
    for (int i = 0; i < ht->size; i++) 
    {
        hash_table_item_t* item = ht->items[i];
        if (item != NULL) 
        {
            ht_delete_item(item);
        }
    }
    free(ht->items);
    free(ht);
}

/*string hash function*/
static int 
ht_hash(const char* string, const int seed, const int buckets_number) 
{
    long hash = 0;
    const int string_len = strlen(string);
    for (int i = 0; i < string_len; i++) 
    {
        hash += (long)pow(seed, string_len - (i+1)) * string[i];
        hash = hash % buckets_number;
    }
    return (int)hash;
}

/*double hashing function*/
static int 
ht_get_hash(const char* string, const int collisions, const int buckets_number) 
{
    const int hash_st = ht_hash(string, HT_PRIME_NUMBER_1, buckets_number);
    const int hash_nd = ht_hash(string, HT_PRIME_NUMBER_2, buckets_number);
    /*hash second time if collisions != 0*/
    return (hash_st + (collisions * (hash_nd + 1))) % buckets_number;
}

/*API*/
void ht_insert
(hash_table_t* ht, const char* key, const char* value) 
{
    hash_table_item_t* item = ht_create_item(key, value);
    int index = ht_get_hash(item->key, 0, ht->size);
    hash_table_item_t* cur_item = ht->items[index];
    int i = 1;
    while (cur_item != NULL && cur_item != &HT_DELETED_ITEM) 
    {
        index = ht_get_hash(item->key, i, ht->size);
        cur_item = ht->items[index];
        i++;
    } 
    ht->items[index] = item;
    ht->count++;
}

/*TODO: fix search for dobuble hashed items*/
char* 
ht_search(hash_table_t* ht, const char* key) 
{
    int index = ht_get_hash(key, 0, ht->size);
    hash_table_item_t* item = ht->items[index];
    int i = 1;
    while (item != NULL) 
    {
        if (item != &HT_DELETED_ITEM) 
        { 
            if (strcmp(item->key, key) == 0) 
            {
                return item->value;
            }
        }
        index = ht_get_hash(key, ht->size, i);
        item = ht->items[index];
        i++;
    } 
    return NULL;
}

void 
ht_delete(hash_table_t* ht, const char* key) 
{
    int index = ht_get_hash(key, ht->size, 0);
    hash_table_item_t* item = ht->items[index];
    int i = 1;
    while (item != NULL) 
    {
        if (item != &HT_DELETED_ITEM) 
        {
            if (strcmp(item->key, key) == 0) 
            {
                ht_delete_item(item);
                ht->items[index] = &HT_DELETED_ITEM;
            }
        }
        index = ht_get_hash(key, ht->size, i);
        item = ht->items[index];
        i++;
    } 
    ht->count--;
}