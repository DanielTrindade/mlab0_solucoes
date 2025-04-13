# Mini-Laboratório 0: Exercícios de Programação Paralela com Pthreads

Este repositório contém uma série de exercícios práticos sobre programação paralela utilizando a biblioteca POSIX Threads (pthreads) em C.

## Estrutura do Repositório

Cada exercício está em seu próprio diretório, contendo o código fonte e um Makefile para compilação.

## Exercícios

### Exercício 01: Fibonacci

**Arquivo fonte:** `mlab0-ex01-fibonacci.c`

**Compilação:**
```
make
```

**Execução:**
```
./mlab0-ex01-fibonacci <n>
```

**Descrição:**
Calcula o n-ésimo número da sequência de Fibonacci usando chamadas recursivas com threads.

**Observações:**
- Usa struct para passar argumentos para as threads
- Sincroniza corretamente usando pthread_join

### Exercício 02: Busca Binária

**Arquivo fonte:** `mlab0-ex02-busca_binaria.c`

**Compilação:**
```
make
```

**Execução:**
```
./mlab0-ex02-busca_binaria <valor>
```

**Descrição:**
Executa busca binária paralela em um vetor ordenado, utilizando duas threads.

**Observações:**
- Usa struct para passar argumentos para as threads
- Sincroniza corretamente usando pthread_join

### Exercício 03: Soma Vetor

**Arquivo fonte:** `mlab0-ex03-soma_vetor.c`

**Compilação:**
```
make
```

**Execução:**
```
./mlab0-ex03-soma_vetor <tamanho> <num_threads>
```

**Descrição:**
Soma os elementos de um vetor de forma paralela, dividindo entre múltiplas threads.

**Observações:**
- Usa struct para passar argumentos para as threads
- Sincroniza corretamente usando pthread_join

### Exercício 04: Preenchimento Matriz

**Arquivo fonte:** `mlab0-ex04-preenchimento_matriz.c`

**Compilação:**
```
make
```

**Execução:**
```
./mlab0-ex04-preenchimento_matriz <linhas> <colunas> <num_threads>
```

**Descrição:**
Aloca uma matriz N x M dinamicamente e preenche as linhas com múltiplas threads.

**Observações:**
- Usa struct para passar argumentos para as threads
- Sincroniza corretamente usando pthread_join

## Requisitos

- Compilador GCC
- Biblioteca POSIX Threads
- Make

## Como executar todos os exercícios

Você pode compilar e executar todos os exercícios com os seguintes comandos:

```bash
# Compilar todos os exercícios
for dir in */; do
    cd "$dir" && make && cd ..
done

# Limpar todos os executáveis
for dir in */; do
    cd "$dir" && make clean && cd ..
done
```

## Notas

Os exercícios são projetados para demonstrar conceitos fundamentais de programação paralela usando threads, incluindo:
- Divisão de trabalho entre threads
- Passagem de parâmetros para threads
- Sincronização de threads
- Compartilhamento de memória entre threads