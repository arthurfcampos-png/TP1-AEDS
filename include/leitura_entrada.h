#ifndef LEITURA_ENTRADA_H
#define LEITURA_ENTRADA_H

#include "../include/hash.h"
#include <stdio.h>

// Struct pra guardar o nome do arquivo e o ID dele em memoria, senao a gente se perde na hora de listar
typedef struct {
    int idDoc;
    char nomeArquivo[100];
} Documento;

// Assinaturas das funcoes (o que o pessoal do utils vai usar na main)
void limparPalavra(char* palavra);
int ehStopWord(char* palavra, char stopWords[][50], int numStopWords);
void carregarStopWords(const char* nomeArquivo, char stopWords[][50], int* numStopWords);
void processarFabula(const char* nomeFabula, int idDoc, char stopWords[][50], int numStopWords, tipoHash* hash);
void lerEntradaPrincipal(const char* arquivoEntradaPrincipal, const char* arquivoStopWords);

#endif
