#include "structs.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char *str_dup_heap(const char *s) {
    if (!s) return NULL;
    size_t n = strlen(s) + 1;
    char *p = (char*)malloc(n);
    if (p) memcpy(p, s, n);
    return p;
}

void str_assign(char **out_ptr, char buf[MAX_CHARS], const char *src, StrMode mode, uint8_t *uses_heap) {
    if (mode == STR_PTR) {
        char *h = str_dup_heap(src);
        *out_ptr = h;
        if (uses_heap) *uses_heap = 1;
    } else { /* STR_FIXED */
        if (!src) src = "";
        /* Copy up to MAX_CHARS-1 and ensure null-terminated */
        size_t n = strlen(src);
        if (n >= MAX_CHARS) n = MAX_CHARS - 1;
        memcpy(buf, src, n);
        buf[n] = '\0';
        *out_ptr = buf;
        if (uses_heap) *uses_heap = 0;
    }
}

/* =============== Singly List Implementation =============== */

void ls_init(ListS *list, StrMode mode) {
    list->head = NULL;
    list->size = 0;
    list->mode = mode;
}

static NodeS* ls_new_node(const char *text, StrMode mode) {
    NodeS *node = (NodeS*)malloc(sizeof(NodeS));
    if (!node) return NULL;
    node->next = NULL;
    node->heap_str = NULL;
    node->uses_heap = 0;
    str_assign(&node->str, node->buf, text, mode, &node->uses_heap);
    if (node->uses_heap) node->heap_str = node->str;
    return node;
}

static void ls_free_node(NodeS *node) {
    if (!node) return;
    if (node->uses_heap && node->heap_str) free(node->heap_str);
    free(node);
}

int ls_insert(ListS *list, const char *text, size_t pos) {
    if (!list) return -1;
    if (pos > list->size) pos = list->size; /* append if beyond end */
    NodeS *node = ls_new_node(text, list->mode);
    if (!node) return -2;

    if (pos == 0) {
        node->next = list->head;
        list->head = node;
    } else {
        NodeS *cur = list->head;
        for (size_t i = 0; i < pos - 1; ++i) cur = cur->next;
        node->next = cur->next;
        cur->next = node;
    }
    list->size++;
    return 0;
}

int ls_delete(ListS *list, size_t pos) {
    if (!list || list->size == 0) return -1;
    if (pos >= list->size) return -2;
    NodeS *to_del;
    if (pos == 0) {
        to_del = list->head;
        list->head = to_del->next;
    } else {
        NodeS *cur = list->head;
        for (size_t i = 0; i < pos - 1; ++i) cur = cur->next;
        to_del = cur->next;
        cur->next = to_del->next;
    }
    ls_free_node(to_del);
    list->size--;
    return 0;
}

void ls_print(const ListS *list) {
    printf("[Singly] size=%zu: ", list ? list->size : 0);
    if (!list || !list->head) { printf("(empty)\n"); return; }
    const NodeS *cur = list->head;
    size_t idx = 0;
    while (cur) {
        printf("(%zu:\"%s\")", idx, cur->str ? cur->str : "(null)");
        if (cur->next) printf(" -> ");
        cur = cur->next;
        idx++;
    }
    printf("\n");
}

void ls_clear(ListS *list) {
    if (!list) return;
    NodeS *cur = list->head;
    while (cur) {
        NodeS *nxt = cur->next;
        ls_free_node(cur);
        cur = nxt;
    }
    list->head = NULL;
    list->size = 0;
}

/* =============== Doubly List Implementation =============== */

void ld_init(ListD *list, StrMode mode) {
    list->head = list->tail = NULL;
    list->size = 0;
    list->mode = mode;
}

static NodeD* ld_new_node(const char *text, StrMode mode) {
    NodeD *node = (NodeD*)malloc(sizeof(NodeD));
    if (!node) return NULL;
    node->prev = node->next = NULL;
    node->heap_str = NULL;
    node->uses_heap = 0;
    str_assign(&node->str, node->buf, text, mode, &node->uses_heap);
    if (node->uses_heap) node->heap_str = node->str;
    return node;
}

static void ld_free_node(NodeD *node) {
    if (!node) return;
    if (node->uses_heap && node->heap_str) free(node->heap_str);
    free(node);
}

int ld_insert(ListD *list, const char *text, size_t pos) {
    if (!list) return -1;
    if (pos > list->size) pos = list->size;
    NodeD *node = ld_new_node(text, list->mode);
    if (!node) return -2;

    if (list->size == 0) {
        list->head = list->tail = node;
    } else if (pos == 0) {
        node->next = list->head;
        list->head->prev = node;
        list->head = node;
    } else if (pos == list->size) {
        node->prev = list->tail;
        list->tail->next = node;
        list->tail = node;
    } else {
        NodeD *cur = list->head;
        for (size_t i = 0; i < pos; ++i) cur = cur->next;
        node->prev = cur->prev;
        node->next = cur;
        cur->prev->next = node;
        cur->prev = node;
    }
    list->size++;
    return 0;
}

int ld_delete(ListD *list, size_t pos) {
    if (!list || list->size == 0) return -1;
    if (pos >= list->size) return -2;
    NodeD *del;
    if (list->size == 1) {
        del = list->head;
        list->head = list->tail = NULL;
    } else if (pos == 0) {
        del = list->head;
        list->head = del->next;
        list->head->prev = NULL;
    } else if (pos == list->size - 1) {
        del = list->tail;
        list->tail = del->prev;
        list->tail->next = NULL;
    } else {
        NodeD *cur = list->head;
        for (size_t i = 0; i < pos; ++i) cur = cur->next;
        del = cur;
        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;
    }
    ld_free_node(del);
    list->size--;
    return 0;
}

void ld_print(const ListD *list) {
    printf("[Doubly] size=%zu: ", list ? list->size : 0);
    if (!list || !list->head) { printf("(empty)\n"); return; }
    const NodeD *cur = list->head;
    size_t idx = 0;
    while (cur) {
        printf("(%zu:\"%s\")", idx, cur->str ? cur->str : "(null)");
        if (cur->next) printf(" <-> ");
        cur = cur->next;
        idx++;
    }
    printf("\n");
}

void ld_clear(ListD *list) {
    if (!list) return;
    NodeD *cur = list->head;
    while (cur) {
        NodeD *nxt = cur->next;
        ld_free_node(cur);
        cur = nxt;
    }
    list->head = list->tail = NULL;
    list->size = 0;
}

/* =============== Circular Singly List Implementation =============== */

void lc_init(ListC *list, StrMode mode) {
    list->head = NULL;
    list->size = 0;
    list->mode = mode;
}

static NodeC* lc_new_node(const char *text, StrMode mode) {
    NodeC *node = (NodeC*)malloc(sizeof(NodeC));
    if (!node) return NULL;
    node->next = NULL;
    node->heap_str = NULL;
    node->uses_heap = 0;
    str_assign(&node->str, node->buf, text, mode, &node->uses_heap);
    if (node->uses_heap) node->heap_str = node->str;
    return node;
}

static void lc_free_node(NodeC *node) {
    if (!node) return;
    if (node->uses_heap && node->heap_str) free(node->heap_str);
    free(node);
}

int lc_insert(ListC *list, const char *text, size_t pos) {
    if (!list) return -1;
    if (pos > list->size) pos = list->size;
    NodeC *node = lc_new_node(text, list->mode);
    if (!node) return -2;

    if (list->size == 0) {
        node->next = node; /* points to itself */
        list->head = node;
    } else if (pos == 0) {
        /* insert before head: need tail to link new node */
        NodeC *tail = list->head;
        for (size_t i = 0; i < list->size - 1; ++i) tail = tail->next;
        node->next = list->head;
        tail->next = node;
        list->head = node;
    } else {
        NodeC *cur = list->head;
        for (size_t i = 0; i < pos - 1; ++i) cur = cur->next;
        node->next = cur->next;
        cur->next = node;
    }
    list->size++;
    return 0;
}

int lc_delete(ListC *list, size_t pos) {
    if (!list || list->size == 0) return -1;
    if (pos >= list->size) return -2;

    NodeC *to_del;
    if (list->size == 1) {
        to_del = list->head;
        list->head = NULL;
    } else if (pos == 0) {
        NodeC *tail = list->head;
        for (size_t i = 0; i < list->size - 1; ++i) tail = tail->next;
        to_del = list->head;
        list->head = to_del->next;
        tail->next = list->head;
    } else {
        NodeC *cur = list->head;
        for (size_t i = 0; i < pos - 1; ++i) cur = cur->next;
        to_del = cur->next;
        cur->next = to_del->next;
    }
    lc_free_node(to_del);
    list->size--;
    return 0;
}

void lc_print(const ListC *list) {
    printf("[Circular] size=%zu: ", list ? list->size : 0);
    if (!list || !list->head) { printf("(empty)\n"); return; }
    const NodeC *cur = list->head;
    size_t idx = 0;
    do {
        printf("(%zu:\"%s\")", idx, cur->str ? cur->str : "(null)");
        cur = cur->next;
        if (idx + 1 < list->size) printf(" -> ");
        idx++;
    } while (cur != list->head && idx < list->size);
    printf(" -> (back to head)\n");
}

void lc_clear(ListC *list) {
    if (!list || list->size == 0) { if (list){list->head=NULL;list->size=0;} return; }
    /* Break the circle to reuse linear freeing */
    NodeC *cur = list->head->next;
    list->head->next = NULL;
    cur = list->head;
    while (cur) {
        NodeC *nxt = cur->next;
        lc_free_node(cur);
        cur = nxt;
    }
    list->head = NULL;
    list->size = 0;
}
