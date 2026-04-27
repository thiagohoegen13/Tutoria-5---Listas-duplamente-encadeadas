#include <stdio.h>
#include <stdlib.h>
#include "lista_aluno.h"

/* ================================================================
 * lista_aluno.c — Implementação do TAD Lista de Alunos
 * ================================================================ */

/* ── Utilitário interno ─────────────────────────────────────────── */
static NodoAluno *alocar_nodo_aluno(Aluno aluno) {
    NodoAluno *novo = (NodoAluno *) malloc(sizeof(NodoAluno));
    if (novo == NULL) {
        fprintf(stderr, "[ERRO] alocar_nodo_aluno: memoria insuficiente.\n");
        return NULL;
    }
    novo->dado     = aluno;
    novo->anterior = NULL;
    novo->proximo  = NULL;
    return novo;
}

/* ── Ciclo de vida ─────────────────────────────────────────────── */

ListaAluno* criar_lista_aluno(void) {
    ListaAluno *l = (ListaAluno *) malloc(sizeof(ListaAluno));
    if (l == NULL) {
        fprintf(stderr, "[ERRO] criar_lista_aluno: memoria insuficiente.\n");
        return NULL;
    }
    l->inicio  = NULL;
    l->fim     = NULL;
    l->tamanho = 0;
    return l;
}

void destruir_lista_aluno(ListaAluno *lista) {
    if (lista == NULL) return;
    NodoAluno *atual = lista->inicio;
    while (atual != NULL) {
        NodoAluno *temp = atual->proximo;
        free(atual);
        atual = temp;
    }
    free(lista);
}

/* ── Inserções — O(1) ─────────────────────────────────────────── */

int inserir_aluno_inicio(ListaAluno *lista, Aluno aluno) {
    if (lista == NULL) return 0;
    NodoAluno *novo = alocar_nodo_aluno(aluno);
    if (novo == NULL) return 0;

    if (lista->inicio == NULL) {
        lista->inicio = novo;
        lista->fim    = novo;
    } else {
        novo->proximo           = lista->inicio;
        lista->inicio->anterior = novo;
        lista->inicio           = novo;
    }
    lista->tamanho++;
    return 1;
}

int inserir_aluno_fim(ListaAluno *lista, Aluno aluno) {
    if (lista == NULL) return 0;
    NodoAluno *novo = alocar_nodo_aluno(aluno);
    if (novo == NULL) return 0;

    if (lista->fim == NULL) {
        lista->inicio = novo;
        lista->fim    = novo;
    } else {
        novo->anterior    = lista->fim;
        lista->fim->proximo = novo;
        lista->fim          = novo;
    }
    lista->tamanho++;
    return 1;
}

/* ── Busca — O(n) ─────────────────────────────────────────────── */

NodoAluno* buscar_por_matricula(ListaAluno *lista, int matricula) {
    if (lista == NULL) return NULL;
    NodoAluno *atual = lista->inicio;
    while (atual != NULL) {
        if (atual->dado.matricula == matricula)
            return atual;
        atual = atual->proximo;
    }
    return NULL;
}

/* ── Remoção — O(n) busca + O(1) remoção ─────────────────────── */

int remover_por_matricula(ListaAluno *lista, int matricula) {
    NodoAluno *alvo = buscar_por_matricula(lista, matricula);
    if (alvo == NULL) {
        fprintf(stderr, "[AVISO] Matricula %d nao encontrada.\n", matricula);
        return 0;
    }

    /* Religar vizinhos */
    if (alvo->anterior != NULL) {
        alvo->anterior->proximo = alvo->proximo;
    } else {
        lista->inicio = alvo->proximo;   /* alvo era o HEAD */
    }

    if (alvo->proximo != NULL) {
        alvo->proximo->anterior = alvo->anterior;
    } else {
        lista->fim = alvo->anterior;     /* alvo era o TAIL */
    }

    alvo->anterior = NULL;
    alvo->proximo  = NULL;
    free(alvo);
    lista->tamanho--;
    return 1;
}

/* ── Impressão filtrada ───────────────────────────────────────── */

void imprimir_aprovados(ListaAluno *lista) {
    printf("  >> APROVADOS (media >= %.1f):\n", MEDIA_APROVACAO);
    if (lista == NULL || lista->inicio == NULL) {
        printf("     (nenhum)\n");
        return;
    }
    int achou = 0;
    NodoAluno *atual = lista->inicio;
    while (atual != NULL) {
        if (aluno_aprovado(&atual->dado)) {
            printf("     Mat: %5d | %-30s | Media: %.1f\n",
                   atual->dado.matricula,
                   atual->dado.nome,
                   atual->dado.media);
            achou = 1;
        }
        atual = atual->proximo;
    }
    if (!achou) printf("     (nenhum)\n");
}

void imprimir_reprovados(ListaAluno *lista) {
    printf("  >> REPROVADOS (media < %.1f):\n", MEDIA_APROVACAO);
    if (lista == NULL || lista->inicio == NULL) {
        printf("     (nenhum)\n");
        return;
    }
    int achou = 0;
    NodoAluno *atual = lista->inicio;
    while (atual != NULL) {
        if (!aluno_aprovado(&atual->dado)) {
            printf("     Mat: %5d | %-30s | Media: %.1f\n",
                   atual->dado.matricula,
                   atual->dado.nome,
                   atual->dado.media);
            achou = 1;
        }
        atual = atual->proximo;
    }
    if (!achou) printf("     (nenhum)\n");
}

void imprimir_lista_aluno(ListaAluno *lista) {
    if (lista == NULL || lista->inicio == NULL) {
        printf("  (lista de alunos vazia)\n");
        return;
    }
    NodoAluno *atual = lista->inicio;
    int pos = 1;
    while (atual != NULL) {
        printf("  [%2d] Mat: %5d | %-30s | Media: %4.1f | %s\n",
               pos++,
               atual->dado.matricula,
               atual->dado.nome,
               atual->dado.media,
               aluno_aprovado(&atual->dado) ? "APROVADO" : "REPROVADO");
        atual = atual->proximo;
    }
}
