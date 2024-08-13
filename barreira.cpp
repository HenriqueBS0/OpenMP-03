#include <cstdio>
#include <omp.h>

int main() {
    const int num_threads = 4;

    #pragma omp parallel num_threads(num_threads)
    {
        int thread_id = omp_get_thread_num();

        // Primeira Etapa: Cada thread realiza uma operação
        std::printf("Thread %d está realizando a primeira etapa.\n", thread_id);
        
        // Sincronização das threads
        #pragma omp barrier

        // Segunda Etapa: Cada thread realiza outra operação após a sincronização
        std::printf("Thread %d está realizando a segunda etapa.\n", thread_id);
    }

    return 0;
}
