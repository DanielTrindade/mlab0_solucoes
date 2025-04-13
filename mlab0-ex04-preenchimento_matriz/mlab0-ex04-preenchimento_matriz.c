#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
// Exercicio 04 - Preenchimento Matriz
// Descrição: Aloca uma matriz N x M dinamicamente e preenche as linhas com múltiplas threads.

typedef struct {
    long long **matrix;
    long long row_start;
    long long row_end;
    long long columns;
} ThreadArgs;

void* thread_func(void* arg) {
    ThreadArgs *args = arg;
    srand(time(NULL) + args->row_start);
    for(int i = args->row_start; i < args->row_end; ++i) {
        for(int j = 0; j < args->columns; ++j) {
            args->matrix[i][j] = rand() % (args->row_end * args->columns);
        }
    }
    pthread_exit(NULL);
}
long long **allocate_matrix(long long rows, long long columns) {
    long long **matrix = malloc(rows * sizeof(long long*));
    for (long long i = 0; i < rows; ++i) {
        matrix[i] = malloc(columns * sizeof(long long));
    }
    return matrix;
}

void free_matrix(long long **matrix, long long rows, long long columns) {
    for (long long i = 0; i < rows; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}

void print_matrix(long long **matrix, long long rows, long long columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%lld ", matrix[i][j]);
        }
        putchar('\n');
    }
    
}

int main(int argc, char* argv[]) {
    long long rows = 1000, columns = 1000;
    long long NUM_THREADS = 5;
    if (argc >= 2) {
        rows = atoll(argv[1]);
        if(rows <= 0) {
            //usando o valor padrão de 1000
            rows = 1000;
        }
    }
    if(argc >= 3) {
        columns = atoll(argv[2]);
        if(columns <= 0) {
            //usando o valor padrão de 1000
            columns = 1000;
        }
    }

    if(argc >= 4) {
        NUM_THREADS = atoll(argv[3]);
        if(NUM_THREADS <= 0) {
            //usando o valor padrão de threads 5
            NUM_THREADS = 5;
        }
    }

    printf("Executando preenchimento_matriz...\n");
    printf("Dimensões: %lld x %lld com %lld threads\n", rows, columns, NUM_THREADS);
    //alocando a matriz
    long long **matrix = allocate_matrix(rows, columns);
    //criando as threads
    pthread_t *threads = malloc(NUM_THREADS * sizeof(pthread_t)); // Corrigido: alocando apenas NUM_THREADS
    ThreadArgs *thread_data = malloc(NUM_THREADS * sizeof(ThreadArgs));
    long long block_size = rows / NUM_THREADS;
    for(int i = 0; i < NUM_THREADS; ++i) {
        thread_data[i].matrix = matrix;
        thread_data[i].columns = columns;
        thread_data[i].row_start = i * block_size;
        thread_data[i].row_end = (i == NUM_THREADS - 1) ? rows : (i + 1) * block_size;
        pthread_create(&threads[i], NULL, thread_func, (void *)&thread_data[i]);
    }

    for(int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    if (rows <= 20 && columns <= 20) {
        printf("Matriz preenchida:\n");
        print_matrix(matrix, rows, columns);
    } else {
        printf("Matriz muito grande para impressão. Dimensões: %lld x %lld\n", rows, columns);
    }

    //liberando a memória alocada para a matriz
    free_matrix(matrix, rows, columns);
    free(threads);
    free(thread_data);
    return 0;
}
