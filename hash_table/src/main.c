#include <stdio.h>
#include <_hash_table.h>

int main(){
    hash_table_t *ht = ht_create_hash_table();
    ht_delete_hash_table(ht);
    return 0;
}