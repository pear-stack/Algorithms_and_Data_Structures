#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "_hash_table.h"
#include "prime_number.h"

//Prime nubers used in hashing functions
#define HT_PRIME_NUMBER_1 173
#define HT_PRIME_NUMBER_2 257
//Hash table default size
#define HT_DEFAULT_BASE_SIZE 20
//Hash table load limits
#define HT_LOAD_LIMIT_UP 70
#define HT_LOAD_LIMIT_DOWN 10

//Deleted item struct to point at
static hash_table_item_t 
HT_DELETED_ITEM = {NULL, NULL};

/*Print hash table*/
void
ht_print(hash_table_t* ht)
{
    for(int i = 0; i < ht->size; i++)
    {
        if(ht->items[i] != NULL && ht->items[i] != &HT_DELETED_ITEM)
        {
            printf("Key: %s, Value: %s\n",ht->items[i]->key, ht->items[i]->value);
        }
    }
}

/*Create hash table item*/
static hash_table_item_t* 
ht_create_item(const char* key, const char* value) 
{
    //Alloc space for new hash table item
    hash_table_item_t* item = malloc(sizeof(hash_table_item_t));
    //Copy parameters to struct members
    item->key = strdup(key);
    item->value = strdup(value);
    //Return item address
    return item;
}

/*Initialise hash table*/
hash_table_t* 
ht_create_hash_table_sized(const int base_size) 
{
    //Alloc space for new hash table 
    hash_table_t* ht = malloc(sizeof(hash_table_t));
    ht->base_size = base_size;
    //Calculate items quantity
    ht->size = next_prime_number(ht->base_size);
    ht->count = 0;
    //Alloc space for hash table items
    ht->items = calloc((size_t)ht->size, sizeof(hash_table_item_t*));
    return ht;
}

hash_table_t* 
ht_create_hash_table() 
{
    //Create hash table with default size
    ht_create_hash_table_sized(HT_DEFAULT_BASE_SIZE);
}

/*Resize hash table*/
static void 
ht_resize(hash_table_t* ht, const int base_size) 
{
    //Don't resize if base size is smaller than default
    if (base_size < HT_DEFAULT_BASE_SIZE) 
    {
        return;
    }
    hash_table_t* new_ht = ht_create_hash_table_sized(base_size);
    //Insert all not empty items to new_ht
    for (int i = 0; i < ht->size; i++) 
    {
        hash_table_item_t* item = ht->items[i];
        if (item != NULL && item != &HT_DELETED_ITEM) 
        {
            ht_insert(new_ht, item->key, item->value);
        }
    }
    //Set ht attributes to new, based on created new_ht
    ht->base_size = new_ht->base_size;
    ht->count = new_ht->count;

    //Swap size and items and delete new_ht
    const int tmp_size = ht->size;
    ht->size = new_ht->size;
    new_ht->size = tmp_size;

    hash_table_item_t** tmp_items = ht->items;
    ht->items = new_ht->items;
    new_ht->items = tmp_items;

    ht_delete_hash_table(new_ht);
}

static void 
ht_resize_up(hash_table_t* ht) 
{
    //Set 2 at least times larger size
    const int new_size = ht->base_size * 2;
    ht_resize(ht, new_size);
}


static void 
ht_resize_down(hash_table_t* ht) 
{
    //Set 2 at least times smaller size
    const int new_size = ht->base_size / 2;
    ht_resize(ht, new_size);
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
    //Free all not empty items
    for (int i = 0; i < ht->size; i++) 
    {
        hash_table_item_t* item = ht->items[i];
        if (item != NULL && item != &HT_DELETED_ITEM) 
        {
            ht_delete_item(item);
        }
    }
    //Free items pointer
    free(ht->items);
    //Free hash table pointer
    free(ht);
}

/*string single hashing function*/
static int 
ht_hash(const char* string, const int seed, const int buckets_number) 
{
    long hash = 0;
    const int string_len = strlen(string);
    for (int i = 0; i < string_len; i++) 
    {
        //Convert string to large int
        hash += (long)pow(seed, string_len - (i+1)) * string[i];
        //Reduce size to fixed range
        hash = hash % buckets_number;
    }
    return (int)hash;
}

/*hashing function*/
static int 
ht_get_hash(const char* string, const int collisions, const int buckets_number) 
{
    const int hash_st = ht_hash(string, HT_PRIME_NUMBER_1, buckets_number);
    const int hash_nd = ht_hash(string, HT_PRIME_NUMBER_2, buckets_number);
    /*hash again if collisions != 0*/
    return (hash_st + (collisions * (hash_nd + 1))) % buckets_number;
}

/*API*/
void 
ht_insert(hash_table_t* ht, const char* key, const char* value) 
{
    //Resize if hash table load > HT_LOAD_LIMIT_UP
    const int load = ht->count * 100 / ht->size;
    if (load > HT_LOAD_LIMIT_UP) 
    {
        ht_resize_up(ht);
    }
    hash_table_item_t* item = ht_create_item(key, value);
    int index = ht_get_hash(item->key, 0, ht->size);
    hash_table_item_t* cur_item = ht->items[index];
    int i = 1;
    //If item isn't empty or deleted
    while (cur_item != NULL && cur_item != &HT_DELETED_ITEM) 
    {
        //Hash again till empty or deleted
        index = ht_get_hash(item->key, i, ht->size);
        cur_item = ht->items[index];
        i++;
    }
    //Insert item into hash table with specified index 
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
    //Resize if hash table load < HT_LOAD_LIMIT_DOWN
    const int load = ht->count * 100 / ht->size;
    if (load < HT_LOAD_LIMIT_DOWN) 
    {
        ht_resize_down(ht);
    }
    int index = ht_get_hash(key, 0, ht->size);
    hash_table_item_t* item = ht->items[index];
    //Return if theres no item with specified key
    int i = 1;
    while (item != NULL) 
    {
        if (item != &HT_DELETED_ITEM) 
        {
            //Compare keys
            if (strcmp(item->key, key) == 0) 
            {
                //Delete item
                ht_delete_item(item);
                //Mark that item was deleted
                ht->items[index] = &HT_DELETED_ITEM;
                ht->count--;
                return;
            }
        }
        //Hash again if item was deleted (in case of collision chain)
        index = ht_get_hash(key, i, ht->size);
        item = ht->items[index];
        i++;
    } 
}