#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <omp.h>

int main() {
    const int num_threads = 6;
    const int num_pontos = 1000000;  // Número total de pontos gerados
    int pontos_dentro_do_circulo = 0;

    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    #pragma omp parallel num_threads(num_threads)
    {
        unsigned int seed = rand();  // Inicializa a semente aleatória para cada thread
        int contagem_local = 0;

        #pragma omp for
        for (int i = 0; i < num_pontos; ++i) {
            double x = (double)rand_r(&seed) / RAND_MAX;  // Gera ponto x
            double y = (double)rand_r(&seed) / RAND_MAX;  // Gera ponto y

            if (x * x + y * y <= 1.0) {
                ++contagem_local;
            }
        }

        // Sincroniza as threads antes de atualizar a contagem global
        #pragma omp barrier

        #pragma omp atomic
        pontos_dentro_do_circulo += contagem_local;
    }

    // Calcula o valor de PI
    double pi = 4.0 * pontos_dentro_do_circulo / num_pontos;
    printf("Estimativa de PI: %f\n", pi);

    return 0;
}
