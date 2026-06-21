#ifndef PATRICIA_H
#define PATRICIA_H

#include "../headers/lista.h"
#include <sys/stat.h>

typedef struct tipoNoPatricia {
    int  pos;               
    char ch;                
    struct tipoNoPatricia* esq;   
    struct tipoNoPatricia* dir;   
    char* palavra;          
    tipoLista ocorrencias;             
} tipoNoPatricia;

//variaveis para analise de desempenho
extern long long patricia_comparacoes_insercao;
extern long long patricia_comparacoes_busca;
extern size_t patricia_memoria_bytes;

void inicializaPatricia(tipoNoPatricia** raiz);

//insere a palavra na árvore (retorna 1 se for palavra nova, 0 se repetida)
int inserePatricia(tipoNoPatricia** raiz, char* palavra, int idDoc);

//busca uma palavra na árvore e retorna o ponteiro para a lista de ocorrências
tipoLista* buscaPatricia(tipoNoPatricia* raiz, char* palavra);

//imprime em ordem alfabética
void imprimePatricia(tipoNoPatricia* raiz);

//libera toda a memória da árvore
void liberaPatricia(tipoNoPatricia* raiz);

#endif