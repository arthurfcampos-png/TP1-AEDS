#include "utils.h"

#include <stdio.h>
#include <sys/stat.h>

/* Definição das variáveis globais declaradas em utils.h */
long long patricia_comparacoes_insercao = 0;
long long patricia_comparacoes_busca    = 0;
long long hash_comparacoes_insercao     = 0;
long long hash_comparacoes_busca        = 0;

size_t patricia_memoria_bytes = 0;
size_t hash_memoria_bytes     = 0;

/* Reinicia todas as métricas para uma nova execução */
void analise_zerar(void) {
    patricia_comparacoes_insercao = 0;
    patricia_comparacoes_busca    = 0;
    hash_comparacoes_insercao     = 0;
    hash_comparacoes_busca        = 0;
    patricia_memoria_bytes        = 0;
    hash_memoria_bytes            = 0;
}

/* Exibe os resultados das comparações e memória usada */
void analise_imprimir(void) {
    printf("\n=== Analise Comparativa ===\n");
    printf("%-35s %lld\n", "PATRICIA - comparacoes insercao:",  patricia_comparacoes_insercao);
    printf("%-35s %lld\n", "PATRICIA - comparacoes busca:",     patricia_comparacoes_busca);
    printf("%-35s %zu bytes\n", "PATRICIA - memoria estimada:",  patricia_memoria_bytes);
    printf("%-35s %lld\n", "HASH     - comparacoes insercao:",  hash_comparacoes_insercao);
    printf("%-35s %lld\n", "HASH     - comparacoes busca:",     hash_comparacoes_busca);
    printf("%-35s %zu bytes\n", "HASH     - memoria estimada:",  hash_memoria_bytes);
}

void analise_exportar_csv(const char *arquivo) {
    /* Verifica se o arquivo já existe para saber se precisa criar o cabeçalho */
    struct stat st;
    int novo = (stat(arquivo, &st) != 0);

    FILE *f = fopen(arquivo, "a");
    if (!f) {
        perror("analise_exportar_csv: fopen");
        return;
    }

    if (novo) {
        /* Se o arquivo for novo, escreve o cabeçalho do CSV */
        fprintf(f,
            "patricia_cmp_insercao,patricia_cmp_busca,patricia_mem_bytes,"
            "hash_cmp_insercao,hash_cmp_busca,hash_mem_bytes\n");
    }
    /* Escreve os valores coletados nesta execução */
    fprintf(f, "%lld,%lld,%zu,%lld,%lld,%zu\n",
        patricia_comparacoes_insercao,
        patricia_comparacoes_busca,
        patricia_memoria_bytes,
        hash_comparacoes_insercao,
        hash_comparacoes_busca,
        hash_memoria_bytes);

    fclose(f);
}