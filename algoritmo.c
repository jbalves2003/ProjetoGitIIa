#include "algoritmo.h"
#include <stdlib.h>
#include "funcao.h"
#include "utils.h"
#include <stdio.h>

// Gera um vizinho
void gera_vizinho(int a[], int b[], int n) {
    for (int i = 0; i < n; i++)
        b[i] = a[i];

    // Permitir até 3 mudanças por vez, aumentando a diversidade
    int num_mudancas = random_l_h(1, 3);
    for (int i = 0; i < num_mudancas; i++) {
        int pos = random_l_h(0, n - 1);
        int operacao = random_l_h(0, 1); // 0: remover moeda, 1: adicionar moeda

        if (operacao == 0 && b[pos] > 0) {
            b[pos]--;
        } else {
            b[pos]++;
        }
    }
}

// Trepa-colinas
int trepa_colinas(int sol[], float *valores_moedas, int n_moedas, float valor_objetivo, int num_iter) {
    int *nova_sol = malloc(sizeof(int) * n_moedas);
    if (nova_sol == NULL) {
        printf("Erro na alocação de memória\n");
        exit(1);
    }

    int custo = calcula_fit(sol, valores_moedas, n_moedas, valor_objetivo);
    for (int i = 0; i < num_iter; i++) {
        gera_vizinho(sol, nova_sol, n_moedas);
        int custo_viz = calcula_fit(nova_sol, valores_moedas, n_moedas, valor_objetivo);

        if (custo_viz < custo) {
            substitui(sol, nova_sol, n_moedas);
            custo = custo_viz;
        }
    }
    free(nova_sol);
    return custo;
}
