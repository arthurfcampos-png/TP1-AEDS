#ifndef HASH_H
#define HASH_H

#include "../headers/lista.h"
#include <string.h>
#define MAX_PALAVRA 70
#define TAM_ALFABETO 256 // Para cobrir toda a tabela ASCII (Padrão Ziviani)

// --- ESTRUTURAS -- \\ 

typedef struct tipoNoHash {
    char palavra [MAX_PALAVRA];
    tipoLista ocorrencias;
    struct tipoNoHash* prox;
} tipoNoHash;

typedef struct tipoHash {
    tipoNoHash** tabela;
    int tamanho;
    unsigned int pesos[MAX_PALAVRA][TAM_ALFABETO];
} tipoHash;

// --- FUNÇÕES GERAIS --- \\ 

// Inicializa a tabela Hash
void inicializaHash (tipoHash* hash, int tamanhoTabela);

// Calcula o índice do vetor que a palavra a ser inserida ocupará
int calculaHash (tipoHash* hash, char* palavra);

// Insere a palavra na tabela (IdDoc também)
void insereHash (tipoHash* hash, char* palavra, int idDoc);

// Procura uma palavra na Hash
tipoLista* buscaHash (tipoHash* hash, char* palavra);

// Imprime o índice invertido
void imprimeHash (tipoHash* hash);


#endif



