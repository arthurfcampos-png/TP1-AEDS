#ifndef LEITURA_ENTRADA_H
#define LEITURA_ENTRADA_H

#include "../headers/hash.h"
#include <stdio.h>

// Struct pra guardar o nome do arquivo e o ID dele em memoria
typedef struct {
    char nomeArquivo[100];
    int idDoc;
    int nTermos;
} Documento;

void limparPalavra(char* palavra);

int ehStopWord(char* palavra, char stopWords[][MAX_PALAVRA], int numStopWords);

void carregarStopWords(const char* nomeArquivo, char stopWords[][MAX_PALAVRA], int* numStopWords);

int processarFabula(const char* nomeFabula, int idDoc, char stopWords[][MAX_PALAVRA], int numStopWords, tipoHash* hash);

Documento* lerEntradaPrincipal(const char* arquivoEntradaPrincipal, const char* arquivoStopWords, tipoHash* hash, int* nDocs);

#endif
