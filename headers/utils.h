#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

/* Variáveis que guardam a quantidade de comparações feitas */
extern long long patricia_comparacoes_insercao;
extern long long patricia_comparacoes_busca;
extern long long hash_comparacoes_insercao;
extern long long hash_comparacoes_busca;

/* Variáveis para estimar a memória usada por cada estrutura */
extern size_t patricia_memoria_bytes;
extern size_t hash_memoria_bytes;

/* Reinicia todos os contadores para começar uma nova análise */
void analise_zerar(void);

/* Mostra na tela os dados coletados durante a execução */
void analise_imprimir(void);

/* Salva os resultados em um arquivo CSV para análise posterior */
void analise_exportar_csv(const char *arquivo);

#endif 