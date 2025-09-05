#include "structs.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

static void run_one(StrMode mode) {
    ListS L; ls_init(&L, mode);
    assert(L.size == 0);
    ls_insert(&L, "a", 0);
    ls_insert(&L, "b", 1);
    ls_insert(&L, "c", 2);
    assert(L.size == 3);
    ls_delete(&L, 1); /* remove "b" */
    assert(L.size == 2);
    /* check order a,c */
    NodeS *n = L.head;
    assert(strcmp(n->str, "a") == 0);
    assert(strcmp(n->next->str, "c") == 0);
    ls_clear(&L);
    assert(L.size == 0 && L.head == NULL);
}

int main(void) {
    run_one(STR_PTR);
    run_one(STR_FIXED);
    printf("test_lista_simples OK\n");
    return 0;
}
