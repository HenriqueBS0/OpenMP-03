#include <iostream>
#include <vector>
#include <omp.h>

int main() {
    const int N = 100;  // Tamanho do vetor
    std::vector<int> vetor(N);

    // Inicializa o vetor com valores aleatórios entre 0 e 99
    for (int i = 0; i < N; ++i) {
        vetor[i] = rand() % 100;
    }

    int pares = 0;
    int impares = 0;

    // Contagem paralela de pares e ímpares utilizando OpenMP
    #pragma omp parallel for
    for (int i = 0; i < N; ++i) {
        if (vetor[i] % 2 == 0) {
            #pragma omp atomic
            pares++;
        } else {
            #pragma omp atomic
            impares++;
        }
    }

    // Exibe os resultados
    std::cout << "Número de elementos pares: " << pares << "\n";
    std::cout << "Número de elementos ímpares: " << impares << "\n";

    return 0;
}
