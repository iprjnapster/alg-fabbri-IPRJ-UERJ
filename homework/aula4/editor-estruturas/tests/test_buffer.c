#include "structs.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

static void run_one(StrMode mode) {
    ListC L; lc_init(&L, mode);
    lc_insert(&L, "uno", 0);
    lc_insert(&L, "dos", 1);
    lc_insert(&L, "tres", 2);
    assert(L.size == 3);
    /* head string should be "uno" */
    assert(strcmp(L.head->str, "uno") == 0);
    /* delete head (pos 0), new head should be "dos" */
    lc_delete(&L, 0);
    assert(L.size == 2);
    assert(strcmp(L.head->str, "dos") == 0);
    /* delete last remaining tail (pos 1) */
    lc_delete(&L, 1);
    assert(L.size == 1);
    lc_clear(&L);
    assert(L.size == 0 && L.head == NULL);
}

int main(void) {
    run_one(STR_PTR);
    run_one(STR_FIXED);
    printf("test_buffer OK\n");
    return 0;
}
