// utils.h
#ifndef UTILS_H
#define UTILS_H

#define MAX_GENES 100
#define MAX_POP 100

// Estrutura para informações do problema
struct info {
    int numGenes;           // moedas
    int popsize;            // Tamanho da população
    float pm;               // Probabilidade de mutação
    float pr;               // Probabilidade de recombinação
    int numGenerations;     // Número de gerações
};

typedef struct chrom {
    int *p;       // Solução (indivíduo)
    float fitness;          // Valor de fitness
    int valido;             // Se a solução é válida
} chrom, *pchrom;

// Funções de Inicialização e Avaliação (necessárias para o Algoritmo Evolutivo)
void gera_sol_inicial(int *sol, int n_moedas, float *valores_moedas); // Declaração da função gera_sol_inicial
pchrom init_pop(struct info d);           // Função de criação da população inicial
void evaluate(pchrom pop, struct info d, float *valores_moedas, float *pesos, float valor_objetivo, float capacidade);
chrom get_best(pchrom pop, struct info d, chrom best); // Função para obter a melhor solução
void write_best(chrom x, struct info d); // Função para escrever a melhor solução
void ler_pesos(char *nome_ficheiro, float *pesos, int n_moedas);

void escreve_sol(int *sol, int n_moedas, float *valores_moedas, const char* titulo);
float* ler_moedas(char *nome_ficheiro, int *n_moedas, float *valor_objetivo);
void init_rand();
int random_l_h(int min, int max);
float rand_01();

#endif
