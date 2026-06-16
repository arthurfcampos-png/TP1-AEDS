#include "patricia.h" 
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Retorna o caractere da palavra em uma posição específica */
static inline char char_em(const char *str, int pos) {
    int i = 0;
    while (i < pos && str[i] != '\0') {
        i++;
    }
    return str[i];
}

/* Cria um nó folha, onde a palavra realmente fica armazenada */
static PatriciaNode *novo_no_folha(const char *palavra, void *dado) {
    PatriciaNode *n = malloc(sizeof(PatriciaNode));
    if (!n) return NULL;
    n->pos    = -1;
    n->ch     = '\0';
    n->esq    = NULL;
    n->dir    = NULL;
    n->palavra = strdup(palavra);
    n->dado   = dado;
    patricia_memoria_bytes += sizeof(PatriciaNode) + strlen(palavra) + 1;
    return n;
}

/* Cria um nó interno, usado apenas para decidir o caminho da busca */
static PatriciaNode *novo_no_interno(int pos, char ch) {
    PatriciaNode *n = malloc(sizeof(PatriciaNode));
    if (!n) return NULL;
    n->pos    = pos;
    n->ch     = ch;
    n->esq    = NULL;
    n->dir    = NULL;
    n->palavra = NULL;
    n->dado   = NULL;
    patricia_memoria_bytes += sizeof(PatriciaNode);
    return n;
}

/* Procura a primeira posição em que as duas palavras são diferentes */
static int primeira_diferenca(const char *a, const char *b) {
    int i = 0;
    while (a[i] == b[i] && a[i] != '\0') i++;
    return i;
}

/* Cria uma raiz vazia para iniciar a árvore */
PatriciaNode *patricia_criar(void) {
    PatriciaNode *raiz = malloc(sizeof(PatriciaNode));
    if (!raiz) return NULL;
    raiz->pos    = -1;
    raiz->ch     = '\0';
    raiz->esq    = NULL;
    raiz->dir    = NULL;
    raiz->palavra = NULL;
    raiz->dado   = NULL;
    patricia_memoria_bytes += sizeof(PatriciaNode);
    return raiz;
}

PatriciaNode *patricia_buscar(PatriciaNode *raiz, const char *palavra) {
    if (!raiz) return NULL;
    if (!raiz->palavra && raiz->pos < 0) return NULL;

    PatriciaNode *atual = raiz;

    /* Percorre a árvore até chegar em uma folha */
    while (atual->pos >= 0) {
        patricia_comparacoes_busca++;
        if (char_em(palavra, atual->pos) < atual->ch)
            atual = atual->esq;
        else
            atual = atual->dir;
    }
    /* Depois de chegar na folha, compara a palavra inteira para confirmar a busca */
     if (atual->palavra) { 
        int i = 0;
        while (atual->palavra[i] != '\0' || palavra[i] != '\0') {
            patricia_comparacoes_busca++;
            if (atual->palavra[i] != palavra[i]) return NULL;
            i++;
        }
        return atual;
    }
    return NULL;
}

PatriciaNode *patricia_inserir(PatriciaNode *raiz, const char *palavra, void *dado) {
    if (!raiz) return NULL;

    /* Caso a árvore esteja vazia, a primeira palavra fica na própria raiz */
    if (!raiz->palavra && raiz->pos < 0 && !raiz->esq && !raiz->dir) { 
        raiz->palavra = strdup(palavra);
        raiz->dado   = dado;
        patricia_memoria_bytes += strlen(palavra) + 1;
        return raiz;
    }

    /* Desce até uma folha para encontrar onde a nova palavra deve ser comparada */
    PatriciaNode *folha_atual = raiz;
    while (folha_atual->pos >= 0) {
        patricia_comparacoes_insercao++;
        if (char_em(palavra, folha_atual->pos) < folha_atual->ch)
            folha_atual = folha_atual->esq;
        else
            folha_atual = folha_atual->dir;
    }

    /* Procura a primeira posição onde as palavras se diferenciam */
    int dif = primeira_diferenca(palavra, folha_atual->palavra);

    /* Se não existe diferença, a palavra já está na árvore */
    if (folha_atual->palavra[dif] == '\0' && palavra[dif] == '\0') {
        folha_atual->dado = dado;
        return folha_atual;
    }
    /* Usa o maior caractere como separador. Assim, caracteres menores ficam à esquerda e iguais ou maiores ficam à direita. */
    char ch_nova   = char_em(palavra,             dif);
    char ch_folha  = char_em(folha_atual->palavra, dif);
    char ch_disc   = (ch_nova < ch_folha) ? ch_folha : ch_nova;

    /* Cria o novo nó interno e a nova folha da palavra inserida */
    PatriciaNode *novo_interno = novo_no_interno(dif, ch_disc);
    PatriciaNode *novo_folha   = novo_no_folha(palavra, dado);
    if (!novo_interno || !novo_folha) {
        free(novo_interno);
        free(novo_folha);
        return NULL;
    }

    /*encontra onde inserir o nó interno*/
    PatriciaNode **link = NULL; 
    PatriciaNode  *pai  = NULL;
    PatriciaNode  *cur  = raiz;

    /* Caso a nova diferença venha antes da raiz atual, a raiz precisa virar nó interno */
    if (cur->pos < 0 || cur->pos >= dif) {
        PatriciaNode *copia = malloc(sizeof(PatriciaNode));
        if (!copia) { free(novo_interno); free(novo_folha); return NULL; }
        *copia = *raiz; /* Copia a raiz antiga para manter a subárvore que já existia */
        patricia_memoria_bytes += sizeof(PatriciaNode);

        raiz->pos     = dif;
        raiz->ch      = ch_disc;
        raiz->palavra = NULL; /*raiz vira nó interno*/
        raiz->dado    = NULL;
        
        /* Liga a nova folha e a árvore antiga nos lados corretos do novo nó */
        if (ch_nova < ch_disc) {
            raiz->esq = novo_folha;
            raiz->dir = copia;
        } else {
            raiz->esq = copia;
            raiz->dir = novo_folha;
        }
        free(novo_interno);
        patricia_memoria_bytes -= sizeof(PatriciaNode); 
        return novo_folha;
    }

    /* Procura o ponto correto para encaixar o novo nó interno */
    while (cur->pos >= 0 && cur->pos < dif) {
        patricia_comparacoes_insercao++;
        pai  = cur;
        if (char_em(palavra, cur->pos) < cur->ch) {
            link = &cur->esq;
            cur  = cur->esq;
        } else {
            link = &cur->dir;
            cur  = cur->dir;
        }
    }

    /* O nó atual passa a ser filho do novo nó interno */
    novo_interno->pos = dif;
    novo_interno->ch  = ch_disc;
    if (ch_nova < ch_disc) {
        novo_interno->esq = novo_folha;
        novo_interno->dir = cur;
    } else {
        novo_interno->esq = cur;
        novo_interno->dir = novo_folha;
    }

    if (link) *link = novo_interno;
    (void)pai; 

    return novo_folha;
}

/* Percorre a árvore em ordem e chama a função para cada palavra armazenada */
void patricia_inorder(PatriciaNode *raiz,
                      void (*callback)(const char *palavra, void *dado, void *ctx),
                      void *ctx) {
    if (!raiz) return;

    if (raiz->pos < 0) {
        if (raiz->palavra)
            callback(raiz->palavra, raiz->dado, ctx);
        return;
    }

    patricia_inorder(raiz->esq, callback, ctx);
    patricia_inorder(raiz->dir, callback, ctx);
}

/* Libera todos os nós da árvore da memória */
static void destruir_rec(PatriciaNode *no) {
    if (!no) return;
    destruir_rec(no->esq);
    destruir_rec(no->dir);
    free(no->palavra);
    free(no);
}

void patricia_destruir(PatriciaNode *raiz) {
    destruir_rec(raiz);
}