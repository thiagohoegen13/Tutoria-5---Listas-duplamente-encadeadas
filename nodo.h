#ifndef NODO_H
#define NODO_H

/* ================================================================
 * nodo.h — TAD Nodo Duplo de Inteiros (Exercício 1)
 *
 * Encapsula a estrutura do nodo com navegação bidirecional.
 * O campo 'valor' e os ponteiros são acessados exclusivamente
 * pelas funções da interface — nunca diretamente.
 * ================================================================ */

typedef struct Nodo {
    int          valor;
    struct Nodo *anterior;   /* elo com o passado  */
    struct Nodo *proximo;    /* elo com o futuro   */
} Nodo;

/* Aloca e inicializa um nodo com o valor dado */
Nodo* criar_nodo(int valor);

/* Getters */
int   obter_valor(Nodo *nodo);
Nodo* obter_anterior(Nodo *nodo);
Nodo* obter_proximo(Nodo *nodo);

/* Setters */
void  definir_valor(Nodo *nodo, int valor);
void  definir_anterior(Nodo *nodo, Nodo *anterior);
void  definir_proximo(Nodo *nodo, Nodo *proximo);

/* Libera o nodo (não percorre vizinhos) */
void  destruir_nodo(Nodo *nodo);

#endif /* NODO_H */
