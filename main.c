#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algoritmo.h"
#include "utils.h"

#define DEFAULT_RUNS 10

int main(int argc, char *argv[]) {
    char nome_fich[100];
    int n_moedas, escolha, runs;
    float *valores_moedas, *pesos, valor_objetivo, capacidade;
    struct info d;

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
    if (runs <= 0) return 0;

    init_rand();

    // Lê os dados do problema e ajusta dependendo do tipo de arquivo
    if (strstr(nome_fich, "file4") != NULL) {
        // Dados para o Trepa-Colinas
        valores_moedas = ler_moedas_trepa(nome_fich, &n_moedas, &valor_objetivo);
        printf("Arquivo para Trepa-Colinas lido com sucesso.\n");
        executa_trepa_colinas(runs, valores_moedas, n_moedas, valor_objetivo);
    } else {
        // Dados para o algoritmo evolutivo
        valores_moedas = ler_moedas(nome_fich, &n_moedas, &valor_objetivo);
        pesos = malloc(sizeof(float) * n_moedas);
        ler_pesos(nome_fich, pesos, n_moedas);

        printf("Numero de moedas: %d\nValor objetivo: %.2f\n", n_moedas, valor_objetivo);

        // Configuração do algoritmo evolutivo
        d.numGenes = n_moedas;
        d.popsize = 100; // Tamanho da população
        d.pm = 0.01;
        d.pr = 0.3;
        d.numGenerations = 2500;
        capacidade = 250.0; // Capacidade da mochila

        printf("\nEscolha o algoritmo:\n");
        printf("1. Trepa-colinas\n");
        printf("2. Evolutivo\n");
        printf("Opção: ");
        scanf("%d", &escolha);

        if (escolha == 1) {
            executa_trepa_colinas(runs, valores_moedas, n_moedas, valor_objetivo);
        } else if (escolha == 2) {
            executa_evolutivo(d, valores_moedas, pesos, valor_objetivo, capacidade);
        } else {
            printf("\nOpção inválida. Terminando o programa.\n");
        }

        free(pesos);
    }

    free(valores_moedas);
    return 0;
}
