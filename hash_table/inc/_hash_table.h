#ifndef __HASH_TABLE_H
#define __HASH_TABLE_H

/*Hash table item struct*/
typedef struct {
    char* key;
    char* value;
} hash_table_item_t;


/*Hash table struct*/
typedef struct {
    int size;
    int base_size;
    int count;
    hash_table_item_t** items;
} hash_table_t;


/*API*/
hash_table_t* ht_create_hash_table(); 
hash_table_t* ht_create_hash_table(); 
void ht_delete_hash_table(hash_table_t* ht);

void ht_print(hash_table_t* ht);
void ht_insert(hash_table_t* ht, const char* key, const char* value);
char* ht_search(hash_table_t* ht, const char* key);
void ht_delete(hash_table_t* h, const char* key); 

#endif