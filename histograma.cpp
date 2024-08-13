#include <iostream>
#include <vector>
#include <omp.h>

int main() {
    const int N = 100;  // Tamanho do vetor original
    const int RANGE = 10; // Intervalo dos valores (0 a RANGE-1)
    std::vector<int> vetor(N);
    std::vector<int> histograma(RANGE, 0);

    // Inicializa o vetor com valores aleatórios entre 0 e RANGE-1
    for (int i = 0; i < N; ++i) {
        vetor[i] = rand() % RANGE;
    }

    // Calcula o histograma utilizando OpenMP
    #pragma omp parallel for
    for (int i = 0; i < N; ++i) {
        int valor = vetor[i];
        
        #pragma omp critical
        {
            histograma[valor]++;
        }
    }

    // Exibe o histograma
    std::cout << "Histograma:\n";
    for (int i = 0; i < RANGE; ++i) {
        std::cout << i << ": " << histograma[i] << "\n";
    }

    return 0;
}
