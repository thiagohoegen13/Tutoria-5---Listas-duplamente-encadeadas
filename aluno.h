#ifndef ALUNO_H
#define ALUNO_H

/* ================================================================
 * aluno.h — Entidade Aluno para o Desafio Extra
 * ================================================================ */

#define MEDIA_APROVACAO 7.0f

typedef struct {
    int   matricula;
    char  nome[50];
    float media;
} Aluno;

/* Retorna 1 se aprovado, 0 se reprovado */
static inline int aluno_aprovado(const Aluno *a) {
    return (a->media >= MEDIA_APROVACAO);
}

#endif /* ALUNO_H */
