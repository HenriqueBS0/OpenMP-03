#include <cstdio>
#include <omp.h>

int main() {
    int dado = 0;  // Variável compartilhada
    bool pronto = false;  // Flag para indicar que o dado foi produzido

    #pragma omp parallel num_threads(4)
    {
        int thread_id = omp_get_thread_num();

        if (thread_id == 0) {  // Thread produtora
            dado = 15;  // Produz o dado
            printf("Dados produzido %d\n", dado);
            #pragma omp flush(dado)  // Garante que o dado seja visível para outras threads
            pronto = true;
            #pragma omp flush(pronto)  // Garante que a flag 'pronto' seja visível
        } else {  // Threads consumidoras
            while (!pronto) {
                #pragma omp flush(pronto)  // Atualiza a flag 'pronto'
            }
            #pragma omp flush(dado)  // Atualiza a variável 'dado'
            printf("Thread %d consumiu o dado: %d\n", thread_id, dado);
        }
    }

    return 0;
}
