#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>

// --- ESTRUTURAS ---\\ 

// Definindo tipo apontador
typedef struct tipoNo* tipoApontador;

// Definindo a struct da celula
typedef struct tipoNo{
    int qtde, idDoc;
    tipoApontador prox;
} tipoNo;

// Definindo a struct da lista encadeada
typedef struct tipoLista{
    tipoNo *primeiro, *ultimo;
} tipoLista;

// --- FUNÇÕES GERAIS --- \\ 

void inicializaLista(tipoLista* lista);

void insereLista(int idDoc, tipoLista* lista);

void imprimeLista(tipoLista* lista);


// --- GETTERS --- \\ 

// Retorna quantidade de ocorrências de uma célula
int getQtde(tipoApontador No);

// Retorna o ID do documento de uma célula
int getIdDoc(tipoApontador No);

// Retorna o ponteiro para a próxima célula
tipoApontador getProx(tipoApontador No);

// Retorna o primeiro elemento da lista (Célula cabeça)
tipoApontador getPrimeiro(tipoLista* lista);

// Retorna o último elemento da lista
tipoApontador getUltimo(tipoLista* lista);


// --- SETTERS --- \\ 

// Altera a quantidade de ocorrências de uma célula
void setQtde(tipoApontador No, int qtde);

// Altera o ID do documento de uma célula
void setIdDoc(tipoApontador No, int idDoc);

// Altera o ponteiro para a próxima célula
void setProx(tipoApontador No, tipoApontador prox);


#endif