#ifndef TFIDF_H
#define TFIDF_H

#include "../headers/leitura_entrada.h"
#include <math.h>

typedef struct {
    int idDoc;
    double score;
} Relevancia;

//calcula o tamanho de uma lista encadeada
int tamanhoLista(tipoLista* lista);

//funcao central que executa a busca, calcula o tfidf e imprime o ranking ordenado
void realizarBusca(char* consulta, tipoHash* hash, tipoNoPatricia* patricia, Documento* docs, int nDocs, char stopWords[][MAX_PALAVRA], int numStopWords, int tipoIndice);

#endif