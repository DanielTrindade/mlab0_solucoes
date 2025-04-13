#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
// Exercicio 03 - Soma Vetor
// Descrição: Soma os elementos de um vetor de forma paralela, dividindo entre múltiplas threads.

typedef struct {
    int thread_id;
    int *array;
    int start_index;
    int end_index;
    long sum;
} ThreadArgs;

void* partial_sum(void* arg) {
    ThreadArgs *args = arg;
    args->sum = 0;
    for(int i = args->start_index; i < args->end_index; ++i) {
        args->sum += args->array[i];
    }
    printf("Thread: %d calculou a soma no intervalo %d a %d igual a %ld\n", 
    args->thread_id, args->start_index, args->end_index, args->sum);
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    int ARR_SIZE = 1000; // valores padrão
    int NUM_THREADS = 5;

    if (argc >= 2) {
        ARR_SIZE = atoi(argv[1]);
        if(ARR_SIZE <= 0) {
            printf("Tamanho do vetor inválido. Usando o valor padrão (1000).\n");
            ARR_SIZE = 1000;
        }
    }

    if(argc >= 3) {
        NUM_THREADS = atoi(argv[2]);
        if(NUM_THREADS <= 0) {
            printf("Números de threads inválido. Usando o valor padrão de (5).\n");
            NUM_THREADS = 5;
        }
    }

    printf("Executando com o vetor de tamanho %d e %d threads\n", ARR_SIZE, NUM_THREADS);


    //criar o array e preencher com os valores
    int *array = malloc(ARR_SIZE * sizeof(int));
    long long total_sum = 0;
    for (int i = 0; i < ARR_SIZE; ++i) {
        array[i] = i + 1; 
    }
    pthread_t threads[NUM_THREADS];
    ThreadArgs thread_data[NUM_THREADS];

    int block_size = ARR_SIZE / NUM_THREADS;
    for(int i = 0; i < NUM_THREADS; ++i) {
        //inicializa os dados que serão passados para as threads
        thread_data[i].thread_id = i;
        thread_data[i].array = array;
        thread_data[i].start_index = i * block_size;
        thread_data[i].end_index = (i == NUM_THREADS - 1) ? ARR_SIZE: (i + 1) * block_size;
        // inicia as threads e manda os dados
        int isSFailedThread = pthread_create(&threads[i], NULL, partial_sum, (void *)&thread_data[i]);
        if(isSFailedThread) {
            printf("ERRO na criação da thread %d", thread_data[i].thread_id);
            exit(-1);
        }
    }

    //Aguarda as threads acabarem 
    for(int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }
    //calcular a soma total na thread principal
    for(int i = 0; i < NUM_THREADS; i++) {
        total_sum += thread_data[i].sum;
    }
    printf("A soma total calculada pelas threads é: %lld\n", total_sum);
    long long resultado_esperado = (long long)ARR_SIZE * (ARR_SIZE + 1) / 2;
    printf("Resultado esperado: %lld\n", resultado_esperado);
    
    // Libera a memória
    free(array);

    return 0;
}
