#include <stdio.h>
#include "nodo.h"
#include "lista.h"
#include "lista_aluno.h"

/* ================================================================
 * main.c — Suite de Testes: Lista Duplamente Encadeada
 *          Exercícios 1 a 10 + Desafio Extra
 * ================================================================ */

/* ── Helpers visuais ──────────────────────────────────────────── */
static void secao(int num, const char *titulo) {
    printf("\n+----------------------------------------------------------+\n");
    printf("|  EXERCICIO %-2d — %-41s|\n", num, titulo);
    printf("+----------------------------------------------------------+\n");
}

static void sub(const char *msg) {
    printf("\n  [>] %s\n", msg);
}

static void imprimir_lista_fmt(Lista *l, const char *label) {
    printf("  %-20s : ", label);
    imprimir_inicio_fim(l);
}

/* ================================================================
 * EXERCÍCIO 1 — TAD Nodo
 * ================================================================ */
static void teste_ex1(void) {
    secao(1, "TAD Nodo Duplo");

    sub("Criando nodo com valor 42...");
    Nodo *n = criar_nodo(42);
    printf("  Valor via getter   : %d\n", obter_valor(n));
    printf("  Anterior           : %s\n", obter_anterior(n) ? "existe" : "NULL");
    printf("  Proximo            : %s\n", obter_proximo(n)  ? "existe" : "NULL");

    sub("Alterando valor para 99 via setter...");
    definir_valor(n, 99);
    printf("  Novo valor         : %d\n", obter_valor(n));

    sub("Criando vizinhos e ligando manualmente...");
    Nodo *a = criar_nodo(10);
    Nodo *b = criar_nodo(20);
    definir_proximo(a, n);
    definir_anterior(n, a);
    definir_proximo(n, b);
    definir_anterior(b, n);

    printf("  Percurso a->n->b   : %d -> %d -> %d\n",
           obter_valor(a),
           obter_valor(obter_proximo(a)),
           obter_valor(obter_proximo(obter_proximo(a))));
    printf("  Percurso b->n->a   : %d -> %d -> %d\n",
           obter_valor(b),
           obter_valor(obter_anterior(b)),
           obter_valor(obter_anterior(obter_anterior(b))));

    destruir_nodo(a);
    destruir_nodo(n);
    destruir_nodo(b);
    printf("  Nodos destruidos com sucesso.\n");
}

/* ================================================================
 * EXERCÍCIO 2 — Estrutura base da Lista
 * ================================================================ */
static void teste_ex2(void) {
    secao(2, "Estrutura Base da Lista");

    Lista *l = criar_lista();
    printf("  Lista criada       : %s\n", l ? "OK" : "FALHA");
    printf("  esta_vazia()       : %d (esperado 1)\n", esta_vazia(l));
    printf("  tamanho()          : %d (esperado 0)\n", tamanho(l));
    destruir_lista(l);
    printf("  Lista destruida    : OK\n");
}

/* ================================================================
 * EXERCÍCIO 3 — Inserção no início
 * ================================================================ */
static void teste_ex3(void) {
    secao(3, "Insercao no Inicio");

    Lista *l = criar_lista();

    sub("Inserindo em lista vazia (valor 30)...");
    inserir_inicio(l, 30);
    imprimir_lista_fmt(l, "Apos inserir 30");

    sub("Inserindo 20 e 10 no inicio...");
    inserir_inicio(l, 20);
    inserir_inicio(l, 10);
    imprimir_lista_fmt(l, "10 -> 20 -> 30");
    printf("  tamanho()          : %d (esperado 3)\n", tamanho(l));

    destruir_lista(l);
}

/* ================================================================
 * EXERCÍCIO 4 — Inserção no fim
 * ================================================================ */
static void teste_ex4(void) {
    secao(4, "Insercao no Fim");

    Lista *l = criar_lista();

    sub("Inserindo 10, 20, 30 no fim (ordem natural)...");
    inserir_fim(l, 10);
    inserir_fim(l, 20);
    inserir_fim(l, 30);
    imprimir_lista_fmt(l, "10 -> 20 -> 30");

    sub("Misturando inicio e fim: inserir_inicio(5) + inserir_fim(40)...");
    inserir_inicio(l, 5);
    inserir_fim(l, 40);
    imprimir_lista_fmt(l, "5->10->20->30->40");
    printf("  tamanho()          : %d (esperado 5)\n", tamanho(l));

    destruir_lista(l);
}

/* ================================================================
 * EXERCÍCIO 5 — Impressão bidirecional
 * ================================================================ */
static void teste_ex5(void) {
    secao(5, "Impressao Bidirecional");

    Lista *l = criar_lista();
    inserir_fim(l, 10);
    inserir_fim(l, 20);
    inserir_fim(l, 30);
    inserir_fim(l, 40);

    printf("  Lista: ");
    imprimir_inicio_fim(l);

    sub("Inicio para fim:");
    printf("  ");
    imprimir_inicio_fim(l);

    sub("Fim para inicio:");
    printf("  ");
    imprimir_fim_inicio(l);

    sub("Lista vazia — ambas as funcoes:");
    Lista *vazia = criar_lista();
    printf("  inicio_fim : "); imprimir_inicio_fim(vazia);
    printf("  fim_inicio : "); imprimir_fim_inicio(vazia);
    destruir_lista(vazia);

    destruir_lista(l);
}

/* ================================================================
 * EXERCÍCIO 6 — Remoção do início
 * ================================================================ */
static void teste_ex6(void) {
    secao(6, "Remocao do Inicio");

    Lista *l = criar_lista();
    inserir_fim(l, 10);
    inserir_fim(l, 20);
    inserir_fim(l, 30);

    printf("  Inicial : "); imprimir_inicio_fim(l);

    int v;
    sub("Removendo do inicio 3 vezes...");
    while (remover_inicio(l, &v))
        printf("  Removido: %d | Restante: ", v), imprimir_inicio_fim(l);

    sub("Tentando remover de lista vazia...");
    remover_inicio(l, &v);

    destruir_lista(l);
}

/* ================================================================
 * EXERCÍCIO 7 — Remoção do fim
 * ================================================================ */
static void teste_ex7(void) {
    secao(7, "Remocao do Fim [O(1) via ponteiro ->anterior]");

    Lista *l = criar_lista();
    inserir_fim(l, 10);
    inserir_fim(l, 20);
    inserir_fim(l, 30);

    printf("  Inicial : "); imprimir_inicio_fim(l);

    int v;
    sub("Removendo do fim 3 vezes...");
    while (remover_fim(l, &v))
        printf("  Removido: %d | Restante: ", v), imprimir_inicio_fim(l);

    sub("Tentando remover de lista vazia...");
    remover_fim(l, &v);

    destruir_lista(l);
}

/* ================================================================
 * EXERCÍCIO 8 — Busca por valor
 * ================================================================ */
static void teste_ex8(void) {
    secao(8, "Busca por Valor");

    Lista *l = criar_lista();
    inserir_fim(l, 5);
    inserir_fim(l, 8);
    inserir_fim(l, 12);
    inserir_fim(l, 20);

    printf("  Lista   : "); imprimir_inicio_fim(l);

    sub("Buscando valores existentes...");
    Nodo *r;
    r = buscar(l, 12);
    printf("  buscar(12): %s (valor=%d)\n", r ? "ENCONTRADO" : "NULL", r ? obter_valor(r) : -1);
    r = buscar(l, 5);
    printf("  buscar(5) : %s (valor=%d, HEAD)\n", r ? "ENCONTRADO" : "NULL", r ? obter_valor(r) : -1);
    r = buscar(l, 20);
    printf("  buscar(20): %s (valor=%d, TAIL)\n", r ? "ENCONTRADO" : "NULL", r ? obter_valor(r) : -1);

    sub("Buscando valor inexistente (99)...");
    r = buscar(l, 99);
    printf("  buscar(99): %s (esperado NULL)\n", r ? "ENCONTRADO" : "NULL");

    destruir_lista(l);
}

/* ================================================================
 * EXERCÍCIO 9 — Inserção em posição específica
 * ================================================================ */
static void teste_ex9(void) {
    secao(9, "Insercao em Posicao Especifica");

    Lista *l = criar_lista();
    inserir_fim(l, 10);
    inserir_fim(l, 20);
    inserir_fim(l, 40);

    printf("  Inicial         : "); imprimir_inicio_fim(l);

    sub("inserir_posicao(30, 2) — no meio entre 20 e 40...");
    inserir_posicao(l, 30, 2);
    imprimir_lista_fmt(l, "10->20->30->40");

    sub("inserir_posicao(5, 0) — no inicio (posicao 0)...");
    inserir_posicao(l, 5, 0);
    imprimir_lista_fmt(l, "5->10->20->30->40");

    sub("inserir_posicao(50, 5) — no fim (posicao==tamanho)...");
    inserir_posicao(l, 50, 5);
    imprimir_lista_fmt(l, "5->10->20->30->40->50");

    sub("inserir_posicao(99, -1) — posicao invalida...");
    int ret = inserir_posicao(l, 99, -1);
    printf("  Retorno          : %d (esperado -1)\n", ret);
    ret = inserir_posicao(l, 99, 999);
    printf("  Retorno pos 999  : %d (esperado -1)\n", ret);

    printf("  Final           : "); imprimir_inicio_fim(l);
    printf("  Reverso         : "); imprimir_fim_inicio(l);

    destruir_lista(l);
}

/* ================================================================
 * EXERCÍCIO 10 — Remoção por valor
 * ================================================================ */
static void teste_ex10(void) {
    secao(10, "Remocao por Valor");

    Lista *l = criar_lista();
    inserir_fim(l, 10);
    inserir_fim(l, 20);
    inserir_fim(l, 30);
    inserir_fim(l, 40);

    printf("  Inicial         : "); imprimir_inicio_fim(l);

    sub("Removendo do MEIO (valor 30)...");
    remover_valor(l, 30);
    imprimir_lista_fmt(l, "10->20->40");

    sub("Removendo do INICIO (valor 10)...");
    remover_valor(l, 10);
    imprimir_lista_fmt(l, "20->40");

    sub("Removendo do FIM (valor 40)...");
    remover_valor(l, 40);
    imprimir_lista_fmt(l, "20");

    sub("Removendo ELEMENTO UNICO (valor 20)...");
    remover_valor(l, 20);
    imprimir_lista_fmt(l, "vazia");
    printf("  inicio=NULL: %s | fim=NULL: %s\n",
           l->inicio == NULL ? "OK" : "ERRO",
           l->fim    == NULL ? "OK" : "ERRO");

    sub("Tentando remover valor inexistente (99)...");
    remover_valor(l, 99);

    destruir_lista(l);
}

/* ================================================================
 * DESAFIO EXTRA — Lista de Alunos
 * ================================================================ */
static void teste_bonus(void) {
    secao(0, "DESAFIO EXTRA — Lista de Alunos");

    ListaAluno *la = criar_lista_aluno();

    /* Dados de teste */
    Aluno alunos[] = {
        {1001, "Ana Carolina Ferreira",  8.5f},
        {1002, "Bruno Henrique Leal",    5.0f},
        {1003, "Camila Duarte Vieira",   9.0f},
        {1004, "Diego Santos Lima",      6.8f},
        {1005, "Elena Souza Marques",    7.0f},
        {1006, "Felipe Andrade Rocha",   4.5f},
        {1007, "Giulia Tavares Moura",   10.0f},
    };
    int n = (int)(sizeof(alunos) / sizeof(alunos[0]));

    sub("Inserindo alunos no fim...");
    for (int i = 0; i < n; i++)
        inserir_aluno_fim(la, alunos[i]);

    imprimir_lista_aluno(la);

    sub("inserir_aluno_inicio: Vitor Nunes (Mat:9001, Media:3.0)...");
    Aluno novo = {9001, "Vitor Nunes Prado", 3.0f};
    inserir_aluno_inicio(la, novo);
    imprimir_lista_aluno(la);

    sub("buscar_por_matricula(1003)...");
    NodoAluno *r = buscar_por_matricula(la, 1003);
    printf("  Resultado: %s\n", r ? r->dado.nome : "NULL (nao encontrado)");

    sub("buscar_por_matricula(9999) — inexistente...");
    r = buscar_por_matricula(la, 9999);
    printf("  Resultado: %s (esperado NULL)\n", r ? r->dado.nome : "NULL");

    sub("remover_por_matricula(1002) — reprovado Bruno...");
    remover_por_matricula(la, 1002);
    imprimir_lista_aluno(la);

    sub("Filtrando aprovados e reprovados...");
    imprimir_aprovados(la);
    imprimir_reprovados(la);

    destruir_lista_aluno(la);
    printf("\n  Memoria liberada com sucesso.\n");
}

/* ================================================================
 * MAIN
 * ================================================================ */
int main(void) {
    printf("\n");
    printf("  ================================================\n");
    printf("  Lista Duplamente Encadeada — Exercicios 1 a 10\n");
    printf("  + Desafio Extra: Lista de Alunos\n");
    printf("  ================================================\n");

    teste_ex1();
    teste_ex2();
    teste_ex3();
    teste_ex4();
    teste_ex5();
    teste_ex6();
    teste_ex7();
    teste_ex8();
    teste_ex9();
    teste_ex10();
    teste_bonus();

    printf("\n  ================================================\n");
    printf("  Todos os testes concluidos.\n");
    printf("  ================================================\n\n");

    return 0;
}
