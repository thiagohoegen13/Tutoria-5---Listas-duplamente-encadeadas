#ifndef LISTA_ALUNO_H
#define LISTA_ALUNO_H

/* ================================================================
 * lista_aluno.h — TAD Lista Duplamente Encadeada de Alunos
 *                 (Desafio Extra)
 *
 * TAD independente: não reutiliza Nodo<int> para manter
 * coesão de tipos e encapsulamento correto.
 * ================================================================ */

#include "aluno.h"

/* ── Nodo interno ─────────────────────────────────────────────── */
typedef struct NodoAluno {
    Aluno             dado;
    struct NodoAluno *anterior;
    struct NodoAluno *proximo;
} NodoAluno;

/* ── Gerenciador ──────────────────────────────────────────────── */
typedef struct {
    NodoAluno *inicio;
    NodoAluno *fim;
    int        tamanho;
} ListaAluno;

/* Ciclo de vida */
ListaAluno* criar_lista_aluno(void);
void        destruir_lista_aluno(ListaAluno *lista);

/* Inserções */
int inserir_aluno_inicio(ListaAluno *lista, Aluno aluno);
int inserir_aluno_fim(ListaAluno *lista, Aluno aluno);

/* Busca */
NodoAluno* buscar_por_matricula(ListaAluno *lista, int matricula);

/* Remoção */
int remover_por_matricula(ListaAluno *lista, int matricula);

/* Impressão filtrada */
void imprimir_aprovados(ListaAluno *lista);
void imprimir_reprovados(ListaAluno *lista);

/* Impressão geral */
void imprimir_lista_aluno(ListaAluno *lista);

#endif /* LISTA_ALUNO_H */
