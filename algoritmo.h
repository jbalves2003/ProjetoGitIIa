#ifndef ALGORITMO_H
#define ALGORITMO_H

#include "utils.h"

// Funções de Trepa-Colinas
void executa_trepa_colinas(int runs, float *valores_moedas, int n_moedas, float valor_objetivo);
int trepa_colinas(int sol[], float *valores_moedas, int n_moedas, float valor_objetivo, int num_iter);
void gera_vizinho(int a[], int b[], int n);
void substitui(int a[], int b[], int n);  // Declaração de substitui

// Funções do Algoritmo Evolutivo
void executa_evolutivo(struct info d, float *valores_moedas, float *pesos, float valor_objetivo, float capacidade);
void genetic_operators(pchrom parents, struct info d, pchrom offspring);
void crossover(pchrom parents, struct info d, pchrom offspring);
void mutation(pchrom offspring, struct info d);
void tournament(pchrom pop, struct info d, pchrom parents);

// Funções de Inicialização e Avaliação (necessárias para o Algoritmo Evolutivo)
pchrom init_pop(struct info d);           // Função de criação da população inicial
void evaluate(pchrom pop, struct info d, float *valores_moedas, float *pesos, float valor_objetivo, float capacidade);
chrom get_best(pchrom pop, struct info d, chrom best);
void write_best(chrom x, struct info d); // melhor solução


#endif
