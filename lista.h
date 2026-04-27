#ifndef LISTA_H
#define LISTA_H

/* ================================================================
 * lista.h — TAD Lista Duplamente Encadeada de Inteiros
 *
 * Evolução incremental — cada bloco de funções corresponde
 * a um exercício da lista.
 *
 * Nota sobre nomenclatura:
 *   'tamanho' é tanto o campo da struct (lista->tamanho) quanto
 *   o nome da função (tamanho(lista)). Em C isso é válido porque
 *   campos de struct e funções pertencem a espaços de nomes
 *   distintos — não há conflito.
 * ================================================================ */

#include "nodo.h"

typedef struct {
    Nodo *inicio;    /* HEAD — primeiro elemento */
    Nodo *fim;       /* TAIL — último  elemento  */
    int   tamanho;   /* contador de elementos    */
} Lista;

/* ── Exercício 2 — Estrutura base ─────────────────────────────── */
Lista* criar_lista(void);
int    esta_vazia(Lista *lista);
int    tamanho(Lista *lista);
void   destruir_lista(Lista *lista);

/* ── Exercício 3 — Inserção no início ─────────────────────────── */
int inserir_inicio(Lista *lista, int valor);

/* ── Exercício 4 — Inserção no fim ────────────────────────────── */
int inserir_fim(Lista *lista, int valor);

/* ── Exercício 5 — Impressão bidirecional ─────────────────────── */
void imprimir_inicio_fim(Lista *lista);
void imprimir_fim_inicio(Lista *lista);

/* ── Exercício 6 — Remoção do início ──────────────────────────── */
int remover_inicio(Lista *lista, int *valor_removido);

/* ── Exercício 7 — Remoção do fim ─────────────────────────────── */
int remover_fim(Lista *lista, int *valor_removido);

/* ── Exercício 8 — Busca por valor ────────────────────────────── */
Nodo* buscar(Lista *lista, int valor);

/* ── Exercício 9 — Inserção em posição específica ─────────────── */
int inserir_posicao(Lista *lista, int valor, int posicao);

/* ── Exercício 10 — Remoção por valor ─────────────────────────── */
int remover_valor(Lista *lista, int valor);

#endif /* LISTA_H */
