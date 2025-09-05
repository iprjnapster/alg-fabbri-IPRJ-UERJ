#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void read_line(char *buf, size_t cap) {
    if (!fgets(buf, (int)cap, stdin)) { buf[0] = '\0'; return; }
    size_t n = strlen(buf);
    if (n && buf[n-1] == '\n') buf[n-1] = '\0';
}

static size_t read_pos(void) {
    char line[64];
    read_line(line, sizeof(line));
    char *end = NULL;
    long v = strtol(line, &end, 10);
    if (end == line || v < 0) return 0;
    return (size_t)v;
}

static StrMode ask_str_mode(void) {
    printf("Escolha representacao de string: (1) char* (heap/malloc) (2) char name[%d]: ", MAX_CHARS);
    fflush(stdout);
    char line[16]; read_line(line, sizeof(line));
    int opt = atoi(line);
    return (opt == 2) ? STR_FIXED : STR_PTR;
}

static void menu_loop(void) {
    printf("Digite o tipo de implementacao de lista: (1) Encadeada (2) Duplamente encadeada (3) Buffer circular\n> ");
    fflush(stdout);
    char line[16]; read_line(line, sizeof(line));
    int tipo = atoi(line);
    if (tipo < 1 || tipo > 3) tipo = 1;

    StrMode mode = ask_str_mode();

    printf("Comandos: (i) inserir  (d) deletar  (p) imprimir  (q) sair\n");

    if (tipo == 1) {
        ListS L; ls_init(&L, mode);
        for (;;) {
            printf("[Singly] op> "); fflush(stdout);
            char op[8]; read_line(op, sizeof(op));
            if (op[0] == 'q') { ls_clear(&L); break; }
            else if (op[0] == 'p') { ls_print(&L); }
            else if (op[0] == 'i') {
                printf("posicao para inserir: "); size_t pos = read_pos();
                printf("texto: "); char txt[256]; read_line(txt, sizeof(txt));
                int r = ls_insert(&L, txt, pos);
                if (r != 0) printf("Falha ao inserir (codigo %d)\n", r);
            } else if (op[0] == 'd') {
                printf("posicao para deletar: "); size_t pos = read_pos();
                int r = ls_delete(&L, pos);
                if (r != 0) printf("Falha ao deletar (codigo %d)\n", r);
            }
        }
    } else if (tipo == 2) {
        ListD L; ld_init(&L, mode);
        for (;;) {
            printf("[Doubly] op> "); fflush(stdout);
            char op[8]; read_line(op, sizeof(op));
            if (op[0] == 'q') { ld_clear(&L); break; }
            else if (op[0] == 'p') { ld_print(&L); }
            else if (op[0] == 'i') {
                printf("posicao para inserir: "); size_t pos = read_pos();
                printf("texto: "); char txt[256]; read_line(txt, sizeof(txt));
                int r = ld_insert(&L, txt, pos);
                if (r != 0) printf("Falha ao inserir (codigo %d)\n", r);
            } else if (op[0] == 'd') {
                printf("posicao para deletar: "); size_t pos = read_pos();
                int r = ld_delete(&L, pos);
                if (r != 0) printf("Falha ao deletar (codigo %d)\n", r);
            }
        }
    } else {
        ListC L; lc_init(&L, mode);
        for (;;) {
            printf("[Circular] op> "); fflush(stdout);
            char op[8]; read_line(op, sizeof(op));
            if (op[0] == 'q') { lc_clear(&L); break; }
            else if (op[0] == 'p') { lc_print(&L); }
            else if (op[0] == 'i') {
                printf("posicao para inserir: "); size_t pos = read_pos();
                printf("texto: "); char txt[256]; read_line(txt, sizeof(txt));
                int r = lc_insert(&L, txt, pos);
                if (r != 0) printf("Falha ao inserir (codigo %d)\n", r);
            } else if (op[0] == 'd') {
                printf("posicao para deletar: "); size_t pos = read_pos();
                int r = lc_delete(&L, pos);
                if (r != 0) printf("Falha ao deletar (codigo %d)\n", r);
            }
        }
    }
}

int main(void) {
    menu_loop();
    return 0;
}
