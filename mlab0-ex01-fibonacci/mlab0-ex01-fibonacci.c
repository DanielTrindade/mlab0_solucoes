#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define MAX_FIB 100

typedef struct {
    unsigned long long n;     
    unsigned long long result;
} ThreadArgs;

unsigned long long memo[MAX_FIB];
pthread_mutex_t memo_mutex = PTHREAD_MUTEX_INITIALIZER;

unsigned long long fibonacci_memoized(unsigned long long n) {
    if (n <= 1) {
        return n;
    }

    pthread_mutex_lock(&memo_mutex);
    if (memo[n] != 0) {
        unsigned long long result = memo[n];
        pthread_mutex_unlock(&memo_mutex);
        return result;
    }
    pthread_mutex_unlock(&memo_mutex);

    unsigned long long result = fibonacci_memoized(n - 1) + fibonacci_memoized(n - 2);
    
    pthread_mutex_lock(&memo_mutex);
    memo[n] = result;
    pthread_mutex_unlock(&memo_mutex);
    
    return result;
}

void* thread_fibonacci_memoized(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;
    args->result = fibonacci_memoized(args->n);
    pthread_exit(NULL);
}

unsigned long long parallel_fibonacci_memoized(unsigned long long n, int num_threads) {
    for (int i = 0; i < MAX_FIB; i++) {
        memo[i] = 0;
    }
    
    // Para números pequenos, calculamos diretamente
    if (n < 30) {
        return fibonacci_memoized(n);
    }
    
    pthread_t* threads = malloc(num_threads * sizeof(pthread_t));
    ThreadArgs* thread_args = malloc(num_threads * sizeof(ThreadArgs));
    
    thread_args[0].n = n - 1;
    pthread_create(&threads[0], NULL, thread_fibonacci_memoized, &thread_args[0]);
    
    thread_args[1].n = n - 2;
    pthread_create(&threads[1], NULL, thread_fibonacci_memoized, &thread_args[1]);
    
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    
    unsigned long long result = thread_args[0].result + thread_args[1].result;
    
    free(threads);
    free(thread_args);
    
    return result;
}


long long timespec_diff_ns(struct timespec start, struct timespec end) {
    long long sec_diff = end.tv_sec - start.tv_sec;
    long long nsec_diff = end.tv_nsec - start.tv_nsec;
    
    if (nsec_diff < 0) {
        nsec_diff += 1000000000;
        sec_diff -= 1;
    }
    
    return sec_diff * 1000000000LL + nsec_diff;
}


int main(int argc, char* argv[]) {
    unsigned long long n = 40; 
    int num_threads = 2;   
    
    if (argc >= 2) {
        n = strtoull(argv[1], NULL, 10);
    }
    
    if (argc >= 3) {
        num_threads = atoi(argv[2]);
        if (num_threads < 2) num_threads = 2;
    }

    
    printf("Calculando Fibonacci(%llu) usando %d threads...\n", n, num_threads);
    
    // Mede o tempo de execução
    struct timespec start_time, end_time;
    unsigned long long result;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    result = parallel_fibonacci_memoized(n, num_threads);
    
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    
    // Calcula a diferença de tempo em nanosegundos
    long long elapsed_ns = timespec_diff_ns(start_time, end_time);

    printf("Fibonacci(%llu) = %llu\n", n, result);
    printf("Tempo de execução: %lld nanosegundos\n", elapsed_ns);
    printf("                  = %.9f segundos\n", elapsed_ns / 1000000000.0);
    
    return 0;
}