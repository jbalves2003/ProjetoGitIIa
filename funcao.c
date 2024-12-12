#include "funcao.h"
#include <math.h>

int calcula_fit(int *sol, float *valores_moedas, int n_moedas, float valor_objetivo) {
    float soma = 0.0;
    int total_moedas = 0;

    for (int i = 0; i < n_moedas; i++) {
        soma += sol[i] * valores_moedas[i];
        total_moedas += sol[i];
    }

    if (fabs(soma - valor_objetivo) < 0.0000001) { // Solução válida
        return total_moedas; // Retorna o número de moedas
    } else {
        float penalizacao = 10000 * fabs(soma - valor_objetivo); // Penalização mais forte
        return total_moedas + (int)penalizacao;
    }
}
