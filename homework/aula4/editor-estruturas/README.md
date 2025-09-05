# Editor de Estruturas Básicas (C)

Implementa três variações de listas de strings sem usar STL, manipulando memória com `malloc/free`:
1. Lista encadeada simples
2. Lista duplamente encadeada
3. Lista encadeada circular (buffer circular)

## Compilar e executar

```bash
make           # compila
make run       # roda o app interativo
make test      # executa os testes
make clean     # limpa
```

## Modo de armazenamento de string
Ao iniciar, escolha entre:
- `char*` (heap): armazena cada string em memória dinâmica (liberada ao remover).
- `char name[MAX_CHARS]`: armazena um buffer fixo dentro de cada nó.

## Operações
- `i`: inserir na posição
- `d`: deletar na posição
- `p`: imprimir a estrutura
- `q`: sair

## Organização
- Código-fonte em `src/`
- Testes em `tests/`
