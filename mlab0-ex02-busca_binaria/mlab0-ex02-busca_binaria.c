#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
// Exercicio 02 - Busca Binaria
// Descrição: Executa busca binária paralela em um vetor ordenado, utilizando duas threads.

typedef struct {
    long long *arr;
    long long key;
    long long start_index;
    long long end_index;
    long long founded_index;
} ThreadArgs;

long long binary_search(long long *vet, long long start_index, long long end_index, long long key) {
    while(start_index <= end_index) {
        long long middle_index = start_index + (end_index - start_index) / 2;
        long long arr_value = vet[middle_index];
        if(arr_value == key) {
            return middle_index;
        } else if (arr_value < key) {
            start_index = middle_index + 1;
        } else {
            end_index = middle_index - 1;
        }
    }
    return -1;
}

void fill_sorted_array(long long *arr, long long size, long long max_step, long long start_value) {
    if (arr == NULL || size <= 0 || max_step <= 0)
        return;
    srand(time(NULL));
    arr[0] = start_value;
    for (long long i = 1; i < size; ++i) {
        long long increment = 1 + rand() % max_step;
        arr[i] = arr[i - 1] + increment;
    }
}

void* thread_func(void* arg) {
    ThreadArgs *args = arg;
    args->founded_index = binary_search(args->arr, args->start_index, args->end_index, args->key);
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    long long ARR_SIZE = 150000;

    long long *array = malloc(ARR_SIZE * sizeof(long long));
    if (array == NULL) {
        printf("Erro: Falha na alocação de memória\n");
        return 1;
    }
    
    fill_sorted_array(array, ARR_SIZE, 20, 1);
    long long random_index = rand() % ARR_SIZE;
    long long key = array[random_index];
    if (argc >= 2) {
        key = atoll(argv[1]);
        if(key <= 0) {
            printf("Chave para pesquisa inválida. Usando uma chave para pesquisa aleatória.\n");
            key = rand() % 150000;
        }
    }

    printf("Executando busca_binaria...\n");
    //criando as threads
    pthread_t thread1, thread2;
    ThreadArgs thread_data1, thread_data2;
    thread_data1.arr = array;
    thread_data1.start_index = 0;
    thread_data1.end_index = ARR_SIZE / 2 - 1;
    thread_data1.key = key;
    thread_data1.founded_index = -1;
    pthread_create(&thread1, NULL, thread_func, (void *)&thread_data1);
    thread_data2.arr = array;
    thread_data2.start_index = ARR_SIZE / 2;
    thread_data2.end_index = ARR_SIZE - 1;
    thread_data2.key = key;
    thread_data2.founded_index = -1;
    pthread_create(&thread2, NULL, thread_func, (void *)&thread_data2);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    //verificando se as threads encontraram a key no vetor
    if(thread_data1.founded_index != -1) {
        printf("Chave %lld encontrada na posição %lld\n", key, thread_data1.founded_index);
    } else if(thread_data2.founded_index != -1) {
        printf("Chave %lld encontrada na posição %lld\n", key, thread_data2.founded_index);
        
    } else {
        printf("A chave %lld não foi encontrada\n", key);
    }
    free(array);
    return 0;
}
