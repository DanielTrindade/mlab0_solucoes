Mini-Laboratório 0 — Exercício 04: Preenchimento Matriz

Arquivo fonte: mlab0-ex04-preenchimento_matriz.c

Compilação:
  make

Execução:
  ./mlab0-ex04-preenchimento_matriz <linhas> <colunas> <num_threads>

Descrição:
  Aloca uma matriz N x M dinamicamente e preenche as linhas com múltiplas threads.

Observações:
  - Use struct para passar argumentos para as threads.
  - Sincronize corretamente usando pthread_join.
