#include "algoritmo.h"
#include <stdlib.h>
#include "funcao.h"
#include "utils.h"
#include <stdio.h>
#include <math.h>



// Gera um vizinho
void gera_vizinho(int a[], int b[], int n) {
    for (int i = 0; i < n; i++) {
        b[i] = a[i];
    }
    int num_mudancas = random_l_h(1, 3); // Faz até 3 mudanças
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

// Inicializa a população com soluções aleatórias
pchrom init_pop(struct info d) {
    pchrom pop = malloc(sizeof(chrom) * d.popsize);
    if (!pop) {
        printf("Erro na alocação de memória para a população\n");
        exit(1);
    }

    for (int i = 0; i < d.popsize; i++) {
        pop[i].p = (int *)malloc(sizeof(int) * d.numGenes); // Adicionado casting para int*
        if (!pop[i].p) {
            printf("Erro na alocação de memória para os genes\n");
            exit(1);
        }
        for (int j = 0; j < d.numGenes; j++) {
            pop[i].p[j] = random_l_h(0, 1); // 0 ou 1 para a presença de cada item
        }
        pop[i].fitness = 0;
        pop[i].valido = 1;
    }
    return pop;
}

// Avalia a população, calculando o fitness de cada indivíduo
void evaluate(pchrom pop, struct info d, float *valores_moedas, float *pesos, float valor_objetivo, float capacidade) {
    for (int i = 0; i < d.popsize; i++) {
        pop[i].fitness = calcula_fit_mochila(pop[i].p, valores_moedas, pesos, d.numGenes, capacidade);
    }
}

// Retorna o melhor indivíduo da população
chrom get_best(pchrom pop, struct info d, chrom best) {
    best.fitness = INFINITY; // Inicialização
    for (int i = 0; i < d.popsize; i++) {
        if (pop[i].fitness < best.fitness) { // Minimizando o custo
            best = pop[i];
        }
    }
    return best;
}

// Realiza um torneio binário para selecionar os pais
void tournament(pchrom pop, struct info d, pchrom parents) {
    for (int i = 0; i < d.popsize; i++) {
        int x1 = random_l_h(0, d.popsize - 1);
        int x2;
        do {
            x2 = random_l_h(0, d.popsize - 1);
        } while (x1 == x2);

        // Torneio: seleciona o melhor entre x1 e x2
        if (pop[x1].fitness < pop[x2].fitness) {
            parents[i] = pop[x1];
        } else {
            parents[i] = pop[x2];
        }
    }
}

// Realiza a recombinação entre os pais para gerar filhos
void genetic_operators(pchrom parents, struct info d, pchrom offspring) {
    for (int i = 0; i < d.popsize; i += 2) {
        crossover(parents, d, offspring);
        mutation(offspring, d);
    }
}

// Operador de crossover
void crossover(pchrom parents, struct info d, pchrom offspring) {
    int point;
    for (int i = 0; i < d.popsize; i += 2) {
        if (rand_01() < d.pr) {
            point = random_l_h(0, d.numGenes - 1);
            for (int j = 0; j < point; j++) {
                offspring[i].p[j] = parents[i].p[j];
                offspring[i + 1].p[j] = parents[i + 1].p[j];
            }
            for (int j = point; j < d.numGenes; j++) {
                offspring[i].p[j] = parents[i + 1].p[j];
                offspring[i + 1].p[j] = parents[i].p[j];
            }
        }
    }
}

// Operador de mutação
void mutation(pchrom offspring, struct info d) {
    for (int i = 0; i < d.popsize; i++) {
        for (int j = 0; j < d.numGenes; j++) {
            if (rand_01() < d.pm) {
                offspring[i].p[j] = !(offspring[i].p[j]);
            }
        }
    }
}

// Escreve o melhor indivíduo encontrado
void write_best(chrom x, struct info d) {
    printf("Melhor solucao encontrada: ");
    for (int i = 0; i < d.numGenes; i++) {
        printf("%d ", x.p[i]);
    }
    printf("\nFitness: %.2f\n", x.fitness);
}

// Trepa-Colinas
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

// Executa Trepa-Colinas
void executa_trepa_colinas(int runs, float *valores_moedas, int n_moedas, float valor_objetivo) {
    int *sol = malloc(sizeof(int) * n_moedas);
    int *best = malloc(sizeof(int) * n_moedas);
    int custo, best_custo;
    float mbf = 0.0;

    if (sol == NULL || best == NULL) {
        printf("Erro na alocação de memória\n");
        exit(1);
    }

    for (int k = 0; k < runs; k++) {
        gera_sol_inicial(sol, n_moedas, valores_moedas);
        printf("\nRepeticao %d:\n", k + 1);
        escreve_sol(sol, n_moedas, valores_moedas, "Solucao Inicial: ");

        custo = trepa_colinas(sol, valores_moedas, n_moedas, valor_objetivo, 1000000);
        escreve_sol(sol, n_moedas, valores_moedas, "Solucao Final: ");
        printf("Custo final: %d\n", custo);

        mbf += custo;
        if (k == 0 || best_custo > custo) {
            best_custo = custo;
            substitui(best, sol, n_moedas);
        }
    }

    printf("\n\nMBF: %f\n", mbf / runs);
    escreve_sol(best, n_moedas, valores_moedas, "Melhor solucao encontrada:");
    printf("Custo final: %2d\n", best_custo);

    free(sol);
    free(best);
}

// Executa Algoritmo Evolutivo
void executa_evolutivo(struct info d, float *valores_moedas, float *pesos, float valor_objetivo, float capacidade) {
    pchrom pop, offspring;
    chrom best;

    pop = init_pop(d);
    evaluate(pop, d, valores_moedas, pesos, valor_objetivo, capacidade);
    best = get_best(pop, d, best);

    offspring = malloc(sizeof(chrom) * d.popsize);
    if (!offspring) {
        printf("Erro na alocação de memória para offspring\n");
        exit(1);
    }

    for (int g = 0; g < d.numGenerations; g++) {
        tournament(pop, d, offspring);
        genetic_operators(offspring, d, pop);
        evaluate(pop, d, valores_moedas, pesos, valor_objetivo, capacidade);
        best = get_best(pop, d, best);

        printf("Geracao %d:\n", g + 1);
        write_best(best, d);
    }

    free(offspring);
    free(pop);
}

