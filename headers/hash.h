#ifndef HASH_H
#define HASH_H

#include "../headers/lista.h"

#define MAX_PALAVRA 80
#define TAM_ALFABETO 256
#define TAM_HASH 2003


typedef struct tipoNoHash {
    char palavra [MAX_PALAVRA];
    tipoLista ocorrencias;
    struct tipoNoHash* prox;
} tipoNoHash;

typedef struct tipoHash {
    tipoNoHash** tabela;
    int tamanho;
    unsigned int pesos[MAX_PALAVRA];
} tipoHash;

//variaveis para analise de memoria da hash
extern size_t hash_memoria_bytes;

// Inicializa a tabela Hash
void inicializaHash (tipoHash* hash, int tamanhoTabela);

// Calcula o índice do vetor que a palavra a ser inserida ocupará
int calculaHash (tipoHash* hash, char* palavra);

// Insere a palavra na tabela (IdDoc também)
int insereHash (tipoHash* hash, char* palavra, int idDoc);

// Procura uma palavra na Hash
tipoLista* buscaHash (tipoHash* hash, char* palavra);

// Libera a memória da hash em questão
void liberaHash(tipoHash* hash);

// Imprime o índice invertido
void imprimeHash (tipoHash* hash);


#endif