/*******************************************************************************
 * Arquivo: patricia.c
 * Autores: Robson Gaspar da Fonseca Junior [6573], Arthur Felipe Campos [6559], Álvaro de Oliveira Neto [6567], Tadeu Miller [6601]
 *******************************************************************************/

#include "../headers/patricia.h"


//variaveis para analise de desempenho
size_t patricia_memoria_bytes = 0;

//retorna o caractere da palavra em uma posicao especifica
char char_em(const char* str, int pos) {
    int i = 0;
    while (i < pos && str[i] != '\0') {
        i++;
    }
    return str[i];
}

//procura a primeira posicao em que as duas palavras são diferentes
int primeira_diferenca(const char* a, const char* b) {
    int i = 0;
    while (a[i] == b[i] && a[i] != '\0') i++;
    return i;
}

//cria um no folha contendo a palavra e inicializando a lista de ocorrências
tipoNoPatricia* novo_no_folha(const char* palavra, int idDoc) {
    tipoNoPatricia* n = (tipoNoPatricia*) malloc(sizeof(tipoNoPatricia));
    if (!n) return NULL;

    n->pos = -1;
    n->ch = '\0';
    n->esq = NULL;
    n->dir = NULL;
    n->palavra = strdup(palavra);

    inicializaLista(&(n->ocorrencias));
    insereLista(idDoc, &(n->ocorrencias));

    patricia_memoria_bytes += sizeof(tipoNoPatricia) + strlen(palavra) + 1;
    return n;
}

//cria um no interno
tipoNoPatricia* novo_no_interno(int pos, char ch) {
    tipoNoPatricia* n = (tipoNoPatricia*) malloc(sizeof(tipoNoPatricia));
    if (!n) return NULL;

    n->pos = pos;
    n->ch = ch;
    n->esq = NULL;
    n->dir = NULL;
    n->palavra = NULL;

    patricia_memoria_bytes += sizeof(tipoNoPatricia);
    return n;
}


//busca na arvore
tipoLista* buscaPatricia(tipoNoPatricia* raiz, char* palavra) {
    if (!raiz) return NULL;
    if (!raiz->palavra && raiz->pos < 0) return NULL;

    tipoNoPatricia* atual = raiz;

    //percorre a arvore usando o bit de discriminacao
    while (atual->pos >= 0) {
        if (char_em(palavra, atual->pos) < atual->ch)
            atual = atual->esq;
        else
            atual = atual->dir;
    }

    if (atual->palavra) {
        if (strcmp(atual->palavra, palavra) == 0) {
            return &(atual->ocorrencias);
        }
    }
    return NULL;
}

//funcao para inserir na patricia
int inserePatricia(tipoNoPatricia** raiz_ptr, char* palavra, int idDoc) {
    tipoNoPatricia* raiz = *raiz_ptr;

    //arvore completamente vazia
    if (!raiz) {
        *raiz_ptr = novo_no_folha(palavra, idDoc);
        return 1; // Termo novo
    }

    //busca o local onde a palavra deveria estar
    tipoNoPatricia* folha_atual = raiz;
    while (folha_atual->pos >= 0) {
        if (char_em(palavra, folha_atual->pos) < folha_atual->ch)
            folha_atual = folha_atual->esq;
        else
            folha_atual = folha_atual->dir;
    }

    //compara a palavra nova com a palavra encontrada na folha
    int dif = primeira_diferenca(palavra, folha_atual->palavra);

    //palavra já existe na árvore
    if (folha_atual->palavra[dif] == '\0' && palavra[dif] == '\0') {
        return insereLista(idDoc, &(folha_atual->ocorrencias));
    }

    //palavra é nova e precisa ser inserida
    char ch_nova = char_em(palavra, dif);
    char ch_folha = char_em(folha_atual->palavra, dif);
    char ch_disc = (ch_nova < ch_folha) ? ch_folha : ch_nova;

    tipoNoPatricia* novo_interno = novo_no_interno(dif, ch_disc);
    tipoNoPatricia* novo_folha = novo_no_folha(palavra, idDoc);

    if (!novo_interno || !novo_folha) {
        free(novo_interno);
        free(novo_folha);
        return 0;
    }

    tipoNoPatricia** link = raiz_ptr;
    tipoNoPatricia* cur = raiz;

    //encontra o ponto de inserção do novo no interno na hierarquia
    while (cur->pos >= 0 && cur->pos <= dif) {
        if (char_em(palavra, cur->pos) < cur->ch) {
            link = &(cur->esq);
            cur = cur->esq;
        } else {
            link = &(cur->dir);
            cur = cur->dir;
        }
    }

    //ponteiros do novo no interno
    if (ch_nova < ch_disc) {
        novo_interno->esq = novo_folha;
        novo_interno->dir = cur;
    } else {
        novo_interno->esq = cur;
        novo_interno->dir = novo_folha;
    }

    *link = novo_interno;

    return 1;
}

//funcao para imprimir a patricia
void imprimePatricia(tipoNoPatricia* raiz) {
    if (!raiz) return;

    if (raiz->pos < 0) {
        if (raiz->palavra) {
            printf("%s ", raiz->palavra);
            imprimeLista(&(raiz->ocorrencias));
        }
        return;
    }

    imprimePatricia(raiz->esq);
    imprimePatricia(raiz->dir);
}

//funcao para liberar a memoria usada pela patricia
void liberaPatricia(tipoNoPatricia* raiz) {
    if (!raiz) return;

    liberaPatricia(raiz->esq);
    liberaPatricia(raiz->dir);

    if (raiz->palavra) {
        free(raiz->palavra);
        
        //libera a lista de ocorrencias
        liberaLista(&(raiz->ocorrencias));
    }
    free(raiz);
}
