#ifndef STRUCTS_H
#define STRUCTS_H

#include <stddef.h>
#include <stdint.h>

#define MAX_CHARS 100

typedef enum {
    STR_PTR = 1,   // store strings with malloc'd char*
    STR_FIXED = 2  // store strings in fixed-size buffer inside node
} StrMode;

typedef enum {
    LIST_SINGLY = 1,
    LIST_DOUBLY = 2,
    LIST_CIRCULAR = 3
} ListType;

/* Shared helpers */
char *str_dup_heap(const char *s);
void str_assign(char **out_ptr, char buf[MAX_CHARS], const char *src, StrMode mode, uint8_t *uses_heap);

/* ================= Singly Linked List ================= */

typedef struct NodeS {
    char *str;                 /* points either to heap_str or buf */
    char  buf[MAX_CHARS];      /* storage when mode == STR_FIXED */
    uint8_t uses_heap;         /* 1 if str points to heap_str */
    char *heap_str;            /* pointer to malloc'd memory when uses_heap==1 */
    struct NodeS *next;
} NodeS;

typedef struct {
    NodeS *head;
    size_t size;
    StrMode mode;
} ListS;

void ls_init(ListS *list, StrMode mode);
void ls_clear(ListS *list);
int  ls_insert(ListS *list, const char *text, size_t pos);
int  ls_delete(ListS *list, size_t pos);
void ls_print(const ListS *list);

/* ================= Doubly Linked List ================= */

typedef struct NodeD {
    char *str;
    char  buf[MAX_CHARS];
    uint8_t uses_heap;
    char *heap_str;
    struct NodeD *prev;
    struct NodeD *next;
} NodeD;

typedef struct {
    NodeD *head;
    NodeD *tail;
    size_t size;
    StrMode mode;
} ListD;

void ld_init(ListD *list, StrMode mode);
void ld_clear(ListD *list);
int  ld_insert(ListD *list, const char *text, size_t pos);
int  ld_delete(ListD *list, size_t pos);
void ld_print(const ListD *list);

/* ================= Circular Singly Linked List ================= */

typedef struct NodeC {
    char *str;
    char  buf[MAX_CHARS];
    uint8_t uses_heap;
    char *heap_str;
    struct NodeC *next; /* last->next points to head (circular) */
} NodeC;

typedef struct {
    NodeC *head;   /* NULL if empty; otherwise points to first element */
    size_t size;
    StrMode mode;
} ListC;

void lc_init(ListC *list, StrMode mode);
void lc_clear(ListC *list);
int  lc_insert(ListC *list, const char *text, size_t pos);
int  lc_delete(ListC *list, size_t pos);
void lc_print(const ListC *list);

#endif /* STRUCTS_H */
