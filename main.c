#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algoritmo.h"
#include "utils.h"

#define DEFAULT_RUNS 1000

int main(int argc, char *argv[]) {
    char nome_fich[100];
    int n_moedas, num_iter, k, runs, custo, best_custo;
    float *valores_moedas, valor_objetivo;
    int *sol, *best;
    float mbf = 0.0;

    if (argc == 3) {
        runs = atoi(argv[2]);
        strcpy(nome_fich, argv[1]);
    } else if (argc == 2) {
        runs = DEFAULT_RUNS;
        strcpy(nome_fich, argv[1]);
    } else {
        runs = DEFAULT_RUNS;
        printf("Nome do Ficheiro: ");
        gets(nome_fich);
    }
    if (runs <= 0)
        return 0;

    init_rand();
    // Lê dados do problema
    valores_moedas = ler_moedas(nome_fich, &n_moedas, &valor_objetivo);
    printf("Numero de moedas: %d\nValor objetivo: %.2f\n", n_moedas, valor_objetivo);

    num_iter = 1000000; // Número de iterações ajustado para exploração completa
    sol = malloc(sizeof(int) * n_moedas);
    best = malloc(sizeof(int) * n_moedas);
    if (sol == NULL || best == NULL) {
        printf("Erro na alocação de memória\n");
        exit(1);
    }

    int estagnado = 0;

    for (k = 0; k < runs; k++) {
        // Geração e exibição da solução inicial
        gera_sol_inicial(sol, n_moedas, valores_moedas);
        printf("\nRepeticao %d:\n", k + 1);
        escreve_sol(sol, n_moedas, valores_moedas, "Solucao Inicial: ");  // Passa título como argumento

        // Execução do algoritmo
        custo = trepa_colinas(sol, valores_moedas, n_moedas, valor_objetivo, num_iter);

        // Exibição da solução final
        escreve_sol(sol, n_moedas, valores_moedas, "Solucao Final: ");  // Passa título como argumento
        printf("Custo final: %d\n", custo);

        // Atualização de métricas globais
        mbf += custo;
        if (k == 0 || best_custo > custo) {
            best_custo = custo;
            substitui(best, sol, n_moedas);
        }

        // Controle de estagnação
        if (k > 0 && custo == best_custo) {
            estagnado++;
        } else {
            estagnado = 0;
        }

        if (estagnado > 500) {
            printf("\nComflito detectada. Reiniciando...\n");
            gera_sol_inicial(sol, n_moedas, valores_moedas);  // Reinicia para explorar mais
            estagnado = 0;
        }
    }

    // Exibe a melhor solução encontrada
    printf("\n\nMBF: %f\n", mbf / k);
    printf("\nMelhor solucao encontrada:");
    escreve_sol(best, n_moedas, valores_moedas, "Melhor solucao encontrada:");  // Passa título como argumento
    printf("Custo final: %2d\n", best_custo);

    free(valores_moedas);
    free(sol);
    free(best);
    return 0;
}
