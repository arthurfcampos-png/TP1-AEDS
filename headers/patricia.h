/*******************************************************************************
 * Arquivo: patricia.h
 * Autores: Robson Gaspar da Fonseca Junior [6573], Arthur Felipe Campos [6559], Álvaro de Oliveira Neto [6567], Tadeu Miller [6601]
 *******************************************************************************/

#ifndef PATRICIA_H
#define PATRICIA_H

#include "../headers/lista.h"

typedef struct tipoNoPatricia {
    int  pos;
    char ch;
    struct tipoNoPatricia* esq;
    struct tipoNoPatricia* dir;
    char* palavra;
    tipoLista ocorrencias;
} tipoNoPatricia;

//variaveis para analise de memoria da patricia
extern size_t patricia_memoria_bytes;

//insere a palavra na arvore (retorna 1 se for palavra nova, 0 se repetida)
int inserePatricia(tipoNoPatricia** raiz, char* palavra, int idDoc);

//busca uma palavra na árvore e retorna o ponteiro para a lista de ocorrencias
tipoLista* buscaPatricia(tipoNoPatricia* raiz, char* palavra);

//imprime em ordem alfabetica
void imprimePatricia(tipoNoPatricia* raiz);

//libera toda a memoria da arvore
void liberaPatricia(tipoNoPatricia* raiz);

#endif
