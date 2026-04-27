#include <stdio.h>
#include <stdlib.h>
#include "nodo.h"

/* ================================================================
 * nodo.c — Implementação do TAD Nodo Duplo (Exercício 1)
 * ================================================================ */

Nodo* criar_nodo(int valor) {
    Nodo *novo = (Nodo *) malloc(sizeof(Nodo));
    if (novo == NULL) {
        fprintf(stderr, "[ERRO] criar_nodo: falha ao alocar memoria.\n");
        return NULL;
    }
    novo->valor    = valor;
    novo->anterior = NULL;
    novo->proximo  = NULL;
    return novo;
}

int obter_valor(Nodo *nodo) {
    if (nodo == NULL) {
        fprintf(stderr, "[ERRO] obter_valor: nodo nulo.\n");
        return 0;
    }
    return nodo->valor;
}

Nodo* obter_anterior(Nodo *nodo) {
    return nodo ? nodo->anterior : NULL;
}

Nodo* obter_proximo(Nodo *nodo) {
    return nodo ? nodo->proximo : NULL;
}

void definir_valor(Nodo *nodo, int valor) {
    if (nodo != NULL) nodo->valor = valor;
}

void definir_anterior(Nodo *nodo, Nodo *anterior) {
    if (nodo != NULL) nodo->anterior = anterior;
}

void definir_proximo(Nodo *nodo, Nodo *proximo) {
    if (nodo != NULL) nodo->proximo = proximo;
}

void destruir_nodo(Nodo *nodo) {
    /* Apenas libera este nodo; os vizinhos continuam intactos */
    free(nodo);
}
