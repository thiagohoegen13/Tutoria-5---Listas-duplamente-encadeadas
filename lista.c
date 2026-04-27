#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

/* ================================================================
 * lista.c — Implementação do TAD Lista Duplamente Encadeada
 *           Exercícios 2 a 10
 * ================================================================ */

/* ────────────────────────────────────────────────────────────────
 * EXERCÍCIO 2 — Estrutura base
 * ──────────────────────────────────────────────────────────────── */

Lista* criar_lista(void) {
    Lista *l = (Lista *) malloc(sizeof(Lista));
    if (l == NULL) {
        fprintf(stderr, "[ERRO] criar_lista: falha ao alocar memoria.\n");
        return NULL;
    }
    l->inicio   = NULL;
    l->fim      = NULL;
    l->tamanho  = 0;
    return l;
}

int esta_vazia(Lista *lista) {
    return (lista == NULL || lista->inicio == NULL);
}

/* Retorna o campo tamanho sem percorrer a lista — O(1) */
int tamanho(Lista *lista) {
    if (lista == NULL) return 0;
    return lista->tamanho;
}

void destruir_lista(Lista *lista) {
    if (lista == NULL) return;

    Nodo *atual = lista->inicio;
    while (atual != NULL) {
        Nodo *temp = atual->proximo;
        destruir_nodo(atual);   /* libera via TAD Nodo */
        atual = temp;
    }
    free(lista);
}

/* ────────────────────────────────────────────────────────────────
 * EXERCÍCIO 3 — Inserção no início — O(1)
 *
 * Casos:
 *   (a) Lista vazia    → inicio e fim apontam para o novo nodo
 *   (b) Não-vazia      → novo->proximo = antigo inicio
 *                        antigo_inicio->anterior = novo
 *                        inicio = novo
 *   (c) malloc falhou  → retorna 0
 * ──────────────────────────────────────────────────────────────── */
int inserir_inicio(Lista *lista, int valor) {
    if (lista == NULL) return 0;

    Nodo *novo = criar_nodo(valor);
    if (novo == NULL) return 0;

    if (esta_vazia(lista)) {
        lista->inicio = novo;
        lista->fim    = novo;
    } else {
        definir_proximo(novo, lista->inicio);     /* novo olha para frente    */
        definir_anterior(lista->inicio, novo);    /* antigo inicio olha atrás */
        lista->inicio = novo;
    }

    lista->tamanho++;
    return 1;
}

/* ────────────────────────────────────────────────────────────────
 * EXERCÍCIO 4 — Inserção no fim — O(1)
 *
 * Acesso direto via lista->fim sem percorrer a lista.
 * Mesmos três casos do exercício 3, sentido oposto.
 * ──────────────────────────────────────────────────────────────── */
int inserir_fim(Lista *lista, int valor) {
    if (lista == NULL) return 0;

    Nodo *novo = criar_nodo(valor);
    if (novo == NULL) return 0;

    if (esta_vazia(lista)) {
        lista->inicio = novo;
        lista->fim    = novo;
    } else {
        definir_anterior(novo, lista->fim);       /* novo olha para trás  */
        definir_proximo(lista->fim, novo);        /* antigo fim olha frente */
        lista->fim = novo;
    }

    lista->tamanho++;
    return 1;
}

/* ────────────────────────────────────────────────────────────────
 * EXERCÍCIO 5 — Impressão nos dois sentidos
 *
 * inicio_fim: percorre via ->proximo   (sentido natural)
 * fim_inicio: percorre via ->anterior  (sentido reverso — principal
 *             vantagem da lista duplamente encadeada)
 * ──────────────────────────────────────────────────────────────── */
void imprimir_inicio_fim(Lista *lista) {
    if (esta_vazia(lista)) {
        printf("[ lista vazia ]\n");
        return;
    }
    Nodo *atual = lista->inicio;
    while (atual != NULL) {
        printf("%d", obter_valor(atual));
        if (obter_proximo(atual) != NULL) printf(" -> ");
        atual = obter_proximo(atual);
    }
    printf("\n");
}

void imprimir_fim_inicio(Lista *lista) {
    if (esta_vazia(lista)) {
        printf("[ lista vazia ]\n");
        return;
    }
    Nodo *atual = lista->fim;
    while (atual != NULL) {
        printf("%d", obter_valor(atual));
        if (obter_anterior(atual) != NULL) printf(" -> ");
        atual = obter_anterior(atual);
    }
    printf("\n");
}

/* ────────────────────────────────────────────────────────────────
 * EXERCÍCIO 6 — Remoção do início — O(1)
 *
 * Casos:
 *   (a) Lista vazia          → retorna 0
 *   (b) Único elemento       → inicio = fim = NULL
 *   (c) Vários elementos     → novo inicio->anterior = NULL
 * ──────────────────────────────────────────────────────────────── */
int remover_inicio(Lista *lista, int *valor_removido) {
    if (esta_vazia(lista)) {
        fprintf(stderr, "[AVISO] remover_inicio: lista vazia.\n");
        return 0;
    }

    Nodo *removido    = lista->inicio;
    *valor_removido   = obter_valor(removido);

    lista->inicio = obter_proximo(removido);

    if (lista->inicio != NULL) {
        definir_anterior(lista->inicio, NULL);  /* novo HEAD não tem passado */
    } else {
        lista->fim = NULL;                       /* lista ficou vazia         */
    }

    /* Isola antes de liberar */
    definir_proximo(removido, NULL);
    destruir_nodo(removido);

    lista->tamanho--;
    return 1;
}

/* ────────────────────────────────────────────────────────────────
 * EXERCÍCIO 7 — Remoção do fim — O(1)
 *
 * O ponteiro ->anterior permite chegar ao penúltimo elemento
 * diretamente via lista->fim->anterior, sem percorrer a lista.
 *
 * Casos idênticos ao exercício 6, sentido oposto.
 * ──────────────────────────────────────────────────────────────── */
int remover_fim(Lista *lista, int *valor_removido) {
    if (esta_vazia(lista)) {
        fprintf(stderr, "[AVISO] remover_fim: lista vazia.\n");
        return 0;
    }

    Nodo *removido  = lista->fim;
    *valor_removido = obter_valor(removido);

    lista->fim = obter_anterior(removido);

    if (lista->fim != NULL) {
        definir_proximo(lista->fim, NULL);   /* novo TAIL não tem futuro */
    } else {
        lista->inicio = NULL;                /* lista ficou vazia         */
    }

    definir_anterior(removido, NULL);
    destruir_nodo(removido);

    lista->tamanho--;
    return 1;
}

/* ────────────────────────────────────────────────────────────────
 * EXERCÍCIO 8 — Busca por valor — O(n)
 *
 * Percurso sequencial do inicio para o fim.
 * Retorna o ponteiro do primeiro nodo com o valor, ou NULL.
 * ──────────────────────────────────────────────────────────────── */
Nodo* buscar(Lista *lista, int valor) {
    if (lista == NULL) return NULL;

    Nodo *atual = lista->inicio;
    while (atual != NULL) {
        if (obter_valor(atual) == valor)
            return atual;
        atual = obter_proximo(atual);
    }
    return NULL; /* não encontrado */
}

/* ────────────────────────────────────────────────────────────────
 * EXERCÍCIO 9 — Inserção em posição específica — O(n)
 *
 * Posição 0          → delega para inserir_inicio  (O(1))
 * Posição == tamanho → delega para inserir_fim     (O(1))
 * Posição inválida   → retorna -1
 * Posição do meio    → ajuste dos 4 ponteiros:
 *
 *   Antes:  ... ⟺ [CURSOR] ⟺ [CURSOR->proximo] ⟺ ...
 *   Depois: ... ⟺ [CURSOR] ⟺ [NOVO] ⟺ [CURSOR->proximo] ⟺ ...
 *
 *   Passo 1: novo->anterior       = cursor
 *   Passo 2: novo->proximo        = cursor->proximo
 *   Passo 3: cursor->proximo->anterior = novo
 *   Passo 4: cursor->proximo      = novo
 * ──────────────────────────────────────────────────────────────── */
int inserir_posicao(Lista *lista, int valor, int posicao) {
    if (lista == NULL)                          return -1;
    if (posicao < 0 || posicao > lista->tamanho) return -1;

    if (posicao == 0)               return inserir_inicio(lista, valor);
    if (posicao == lista->tamanho)  return inserir_fim(lista, valor);

    Nodo *novo = criar_nodo(valor);
    if (novo == NULL) return 0;

    /* Percorre até a posição anterior ao ponto de inserção */
    Nodo *cursor = lista->inicio;
    for (int i = 0; i < posicao - 1; i++)
        cursor = obter_proximo(cursor);

    /* ── 4 ponteiros ── */
    Nodo *depois = obter_proximo(cursor);

    definir_anterior(novo, cursor);            /* passo 1 */
    definir_proximo(novo, depois);             /* passo 2 */
    definir_anterior(depois, novo);            /* passo 3 */
    definir_proximo(cursor, novo);             /* passo 4 */

    lista->tamanho++;
    return 1;
}

/* ────────────────────────────────────────────────────────────────
 * EXERCÍCIO 10 — Remoção por valor — O(n) busca + O(1) remoção
 *
 * Combina buscar() com a lógica de remoção dos exercícios 6 e 7.
 *
 * Casos:
 *   (a) Valor não encontrado → retorna 0
 *   (b) Valor no início      → delega para remover_inicio
 *   (c) Valor no fim         → delega para remover_fim
 *   (d) Valor no meio        → dança dos 4 ponteiros
 * ──────────────────────────────────────────────────────────────── */
int remover_valor(Lista *lista, int valor) {
    Nodo *alvo = buscar(lista, valor);

    if (alvo == NULL) {
        fprintf(stderr, "[AVISO] remover_valor: valor %d nao encontrado.\n", valor);
        return 0;
    }

    int descartado;

    /* Delegação para casos de borda */
    if (alvo == lista->inicio) return remover_inicio(lista, &descartado);
    if (alvo == lista->fim)    return remover_fim(lista, &descartado);

    /* ── Caso do meio: dança dos 4 ponteiros ── */
    Nodo *antes  = obter_anterior(alvo);
    Nodo *depois = obter_proximo(alvo);

    definir_proximo(antes, depois);      /* passo 1: antes pula o alvo  */
    definir_anterior(depois, antes);     /* passo 2: depois pula o alvo */
    definir_anterior(alvo, NULL);        /* passo 3: isola o alvo       */
    definir_proximo(alvo, NULL);         /* passo 4: isola o alvo       */

    destruir_nodo(alvo);
    lista->tamanho--;
    return 1;
}
