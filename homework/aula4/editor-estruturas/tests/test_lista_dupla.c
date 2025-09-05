#include "structs.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

static void run_one(StrMode mode) {
    ListD L; ld_init(&L, mode);
    ld_insert(&L, "x", 0);
    ld_insert(&L, "y", 1);
    ld_insert(&L, "z", 2);
    assert(L.size == 3);
    /* delete tail */
    ld_delete(&L, 2);
    assert(L.size == 2 && L.tail && strcmp(L.tail->str, "y") == 0);
    /* insert in middle */
    ld_insert(&L, "m", 1);
    assert(L.size == 3);
    /* sequence x, m, y */
    NodeD *n = L.head;
    assert(strcmp(n->str, "x") == 0);
    assert(strcmp(n->next->str, "m") == 0);
    assert(strcmp(n->next->next->str, "y") == 0);
    ld_clear(&L);
    assert(L.size == 0 && L.head == NULL && L.tail == NULL);
}

int main(void) {
    run_one(STR_PTR);
    run_one(STR_FIXED);
    printf("test_lista_dupla OK\n");
    return 0;
}
