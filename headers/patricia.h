#ifndef PATRICIA_H
#define PATRICIA_H

typedef struct PatriciaNode {
    int  pos;               
    char ch;                
    struct PatriciaNode *esq;   
    struct PatriciaNode *dir;   
    char *palavra;          
    void *dado;             
} PatriciaNode;

PatriciaNode *patricia_criar(void);

PatriciaNode *patricia_inserir(PatriciaNode *raiz, const char *palavra, void *dado);

PatriciaNode *patricia_buscar(PatriciaNode *raiz, const char *palavra);

void patricia_inorder(PatriciaNode *raiz,
    void (*callback)(const char *palavra, void *dado, void *ctx),
    void *ctx);

void patricia_destruir(PatriciaNode *raiz);

#endif