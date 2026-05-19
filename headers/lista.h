#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define tam_char 70

typedef struct TipoCelula* TipoApontador;

typedef struct TipoCelula{
    char palavra[tam_char];
    TipoApontador prox;
} TipoCelula;

typedef struct TipoLista{
    TipoCelula *Primeiro, *Ultimo;
} TipoLista;

void InicializaLista(TipoLista* lista);

void InsereLista(char palavra, TipoLista* lista);

void RemoveLista(char palavra, TipoLista* lista, TipoApontador ptr);

//colocar gets e sets aqui
