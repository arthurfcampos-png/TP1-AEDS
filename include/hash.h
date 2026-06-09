#ifndef HASH_H
#define HASH_H

#include "../include/lista.h"
#include <string.h>
#define MAX_PALAVRA 46

// --- ESTRUTURAS -- \\

typedef struct tipoNoHash {
    char palavra [MAX_PALAVRA];
    tipoLista ocorrencias;
    struct tipoNoHash* prox;
} tipoNoHash;

typedef struct tipoHash {
    tipoNoHash** tabela;
    int tamanho;
} tipoHash;

// --- FUNÇÕES GERAIS --- \\

// Inicializa a tabela Hash
void inicializaHash (tipoHash* hash, int tamanhoTabela);

// Calcula o índice do vetor que a palavra a ser inserida ocupará
int calculaHash (char* palavra, int tamanhoTabela);

// Insere a palavra na tabela (IdDoc também)
void insereHash (tipoHash* hash, char* palavra, int idDoc);

// Procura uma palavra na Hash
tipoLista* buscaHash (tipoHash* hash, char* palavra);

// Imprime o índice invertido
void imprimeHash (tipoHash* hash);


#endif
