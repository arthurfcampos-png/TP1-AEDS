#include "..\headers/lista.h"

void InicializaLista(TipoLista* lista){
    lista->Primeiro = (TipoCelula*)malloc(sizeof(TipoCelula));
    lista->Ultimo = lista->Primeiro;
    lista->Primeiro->prox = NULL;
}

void InsereLista(char palavra[], TipoLista* lista){
    lista->Ultimo->prox = (TipoApontador)malloc(sizeof(TipoCelula));
    lista->Ultimo = lista->Ultimo->prox;
    strcpy(lista->Ultimo->palavra, palavra);
    lista->Ultimo->prox = NULL;
}

void RemoveLista(char palavra[], TipoLista* lista, TipoApontador ptr){
    TipoApontador q;
    if ((lista->Primeiro == lista->Ultimo) || (ptr == NULL) || (ptr->prox == NULL)){
        printf("lista vazia");
        return;
    }

    q = ptr->prox;
    strcpy(palavra, q->palavra);
    ptr->prox = q->prox;
    if (ptr->prox == NULL){
        lista->Ultimo = ptr;
    }
    free(q);
}
