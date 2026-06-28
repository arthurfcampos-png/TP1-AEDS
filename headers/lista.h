#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>


//Struct da celula
typedef struct tipoNo{
    int qtde, idDoc;
    struct tipoNo* prox;
} tipoNo;

//Struct da lista encadeada
typedef struct tipoLista{
    tipoNo *primeiro, *ultimo;
} tipoLista;


// Funções

void inicializaLista(tipoLista* lista);

int insereLista(int idDoc, tipoLista* lista);

void imprimeLista(tipoLista* lista);


//Get

// Retorna quantidade de ocorrências de uma célula
int getQtde(tipoNo* No);

// Retorna o ID do documento de uma célula
int getIdDoc(tipoNo* No);

// Retorna o ponteiro para a próxima célula
tipoNo* getProx(tipoNo* No);

// Retorna o primeiro elemento da lista (Célula cabeça)
tipoNo* getPrimeiro(tipoLista* lista);

// Retorna o último elemento da lista
tipoNo* getUltimo(tipoLista* lista);


//Sets

// Altera a quantidade de ocorrências de uma célula
void setQtde(tipoNo* No, int qtde);

// Altera o ID do documento de uma célula
void setIdDoc(tipoNo* No, int idDoc);

// Altera o ponteiro para a próxima célula
void setProx(tipoNo* No, tipoNo* prox);


#endif