#ifndef STRUCT_INFO_H
#define STRUCT_INFO_H

// Definir a estrutura de um cromossomo
typedef struct {
    int *p;         // Vetor de genes (representação binária)
    int fitness;    // Fitness da solução
    int valido;     // Se a solução é válida ou não
} chrom;

typedef chrom* pchrom;  // Ponteiro para cromossomo

// A estrutura info será usada para armazenar os parâmetros do problema
struct info {
    int popsize;      // Tamanho da população
    float pm;         // Probabilidade de mutação
    float pr;         // Probabilidade de recombinação
    int tsize;        // Tamanho do torneio
    int numGenerations; // Número de gerações
    int numGenes;     // Número de genes no cromossomo
    int capacity;     // Capacidade da mochila (se aplicável)
    float ro;         // Alguma outra variável de controle (se aplicável)
};

#endif
