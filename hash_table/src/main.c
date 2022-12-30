#include <stdio.h>
#include <_hash_table.h>

int main(){
    hash_table_t *ht = ht_create_hash_table();
    ht_insert(ht, "a", "we");
    ht_insert(ht, "a", "wa");
    ht_print(ht);
    ht_delete(ht,"a");
    printf("\n");
    ht_print(ht);
    ht_delete_hash_table(ht);
    return 0;
}