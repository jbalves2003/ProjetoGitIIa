#include "funcao.h"
#include <math.h>

int calcula_fit(int *sol, float *valores_moedas, int n_moedas, float valor_objetivo) {
    float soma = 0.0;
    int total_moedas = 0;

    for (int i = 0; i < n_moedas; i++) {
        soma += sol[i] * valores_moedas[i];
        total_moedas += sol[i];
    }

    if (fabs(soma - valor_objetivo) < 0.001) {
        return total_moedas;
    } else {
        float penalizacao = 10000 * fabs(soma - valor_objetivo);
        return total_moedas + (int)penalizacao;
    }

}


 float calcula_fit_mochila(int *sol, float *valores_moedas, float *pesos, int n_moedas, float capacidade) {
    float soma_valores = 0;
    float soma_pesos = 0;

    for (int i = 0; i < n_moedas; i++) {
        if (sol[i] == 1) { // Se o item está na solução
            soma_valores += valores_moedas[i];
            soma_pesos += pesos[i];
        }
    }

    // Penalização se a capacidade for excedida
    if (soma_pesos > capacidade) {
        return -1; // Retorna um valor negativo se exceder a capacidade
    }

    return soma_valores; // Retorna o valor total
}
