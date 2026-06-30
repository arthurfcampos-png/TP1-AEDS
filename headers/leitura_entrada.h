/*******************************************************************************
 * Arquivo: leitura_entrada.h
 * Autores: Robson Gaspar da Fonseca Junior [6573], Arthur Felipe Campos [6559], Álvaro de Oliveira Neto [6567], Tadeu Miller [6601]
 *******************************************************************************/

#ifndef LEITURA_ENTRADA_H
#define LEITURA_ENTRADA_H

#include "../headers/hash.h"
#include "../headers/patricia.h"
#include <ctype.h>
#include <time.h>


// Struct pra guardar o nome do arquivo e o ID dele em memoria
typedef struct {
    char nomeArquivo[100];
    int idDoc;
    int nTermos;
} Documento;

void limparPalavra(char* palavra);

int ehStopWord(char* palavra, char stopWords[][MAX_PALAVRA], int numStopWords);

void carregarStopWords(const char* nomeArquivo, char stopWords[][MAX_PALAVRA], int* numStopWords);

int processarFabula(const char* nomeFabula, int idDoc, char stopWords[][MAX_PALAVRA], int numStopWords, tipoHash* hash, tipoNoPatricia** patricia, double* tempo_total_hash, double* tempo_total_patricia);

Documento* lerEntradaPrincipal(const char* arquivoEntradaPrincipal, const char* arquivoStopWords, tipoHash* hash, tipoNoPatricia** patricia, int* nDocs);

#endif
