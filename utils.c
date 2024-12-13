#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <process.h>
#include "utils.h"

// Escreve a solução no formato requerido
void escreve_sol(int *sol, int n_moedas, float *valores_moedas, const char* titulo) {
    int primeiro = 1;
    printf("%s", titulo);
    for (int i = 0; i < n_moedas; i++) {
        if (sol[i] > 0) {  // Exibe apenas as moedas usadas
            if (!primeiro) {
                printf(" + ");
            }
            printf("%d*%.2f", sol[i], valores_moedas[i]);
            primeiro = 0;
        }
    }
    if (primeiro) {
        printf("Nenhuma moeda usada");
    }
    printf("\n");
}

// Lê os dados do arquivo de entrada (usado para o algoritmo evolutivo)
float* ler_moedas(char *nome_ficheiro, int *n_moedas, float *valor_objetivo) {
    FILE *f = fopen(nome_ficheiro, "r");
    if (!f) {
        printf("Erro ao abrir o ficheiro\n");
        exit(1);
    }

    fscanf(f, "%d %f", n_moedas, valor_objetivo);
    float *valores_moedas = malloc(sizeof(float) * (*n_moedas));

    for (int i = 0; i < *n_moedas; i++) {
        fscanf(f, "%f", &valores_moedas[i]);
    }

    fclose(f);
    return valores_moedas;
}

// Lê os pesos dos itens (usado no algoritmo evolutivo)
void ler_pesos(char *nome_ficheiro, float *pesos, int n_moedas) {
    FILE *f = fopen(nome_ficheiro, "r");
    if (!f) {
        printf("Erro ao abrir o ficheiro de pesos\n");
        exit(1);
    }

    // Lê os pesos do arquivo
    for (int i = 0; i < n_moedas; i++) {
        fscanf(f, "%f", &pesos[i]);
    }

    fclose(f);
}

// Função para ler os dados do arquivo de Trepa-Colinas (file4.txt)
float* ler_moedas_trepa(char *nome_ficheiro, int *n_moedas, float *valor_objetivo) {
    FILE *f = fopen(nome_ficheiro, "r");
    if (!f) {
        printf("Erro ao abrir o ficheiro\n");
        exit(1);
    }

    fscanf(f, "%d", n_moedas); // Número de moedas
    fscanf(f, "%f", valor_objetivo); // Valor objetivo

    // Lê os valores das moedas
    float *valores_moedas = malloc(sizeof(float) * (*n_moedas));
    if (!valores_moedas) {
        printf("Erro ao alocar memória para valores das moedas\n");
        exit(1);
    }

    for (int i = 0; i < *n_moedas; i++) {
        fscanf(f, "%f", &valores_moedas[i]);
    }

    fclose(f);
    return valores_moedas;
}

// Inicializa o gerador de números aleatórios
void init_rand() {
    srand((unsigned)time(NULL) ^ (unsigned)_getpid());
}

// Gera um número aleatório entre min e max (inclusive)
int random_l_h(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Gera um número real aleatório entre 0 e 1
float rand_01() {
    return ((float)rand()) / RAND_MAX;
}

// Substitui o conteúdo de um vetor por outro
void substitui(int a[], int b[], int n) {
    for (int i = 0; i < n; i++) {
        a[i] = b[i];
    }
}

// Gera a solução inicial (para o Trepa-Colinas)
void gera_sol_inicial(int *sol, int n_moedas, float *valores_moedas) {
    // Preenche a solução inicial com valores aleatórios para as moedas
    for (int i = 0; i < n_moedas; i++) {
        sol[i] = random_l_h(0, 10); // Gera entre 0 e 10 moedas de cada tipo
    }
}
