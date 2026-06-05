#include "../headers/lista.h"

// --- FUNÇÕES GERAIS --- 

// Função para inicializar a lista encadeada
void inicializaLista(tipoLista* lista){
    lista->primeiro = (tipoNo*) malloc(sizeof(tipoNo));
    lista->ultimo = lista->primeiro;
    lista->primeiro->prox = NULL;
}

// Função para inserção na lista encadeada
void insereLista(int idDoc , tipoLista* lista){
    tipoApontador aux = lista->primeiro->prox; // Ponteiro auxiliar para percorrer a lista
    
    while (aux != NULL){  // Loop para percursão 
        if (aux->idDoc == idDoc){  // Verifica se o ID do documento já consta na lista
            aux->qtde++; // Caso consta na lista encadeada, apenas aumenta em 1 a ocorrência
            return;
        }
        aux = aux->prox;
    }

    // Caso o documento da ocorrência não for encontrado na lista, cria um nó.
    lista->ultimo->prox = (tipoApontador) malloc(sizeof(tipoNo));
    lista->ultimo = lista->ultimo->prox;

    lista->ultimo->idDoc = idDoc;
    lista->ultimo->qtde = 1;
    lista->ultimo->prox = NULL;
}

// Função para imprimir a lista
void imprimeLista(tipoLista* lista){
    tipoApontador aux;
    aux = lista->primeiro->prox;
    while (aux != NULL){
        // Formato exigido no trabalho: <qtde, idDoc>
        printf("<%d, %d> ", aux->qtde, aux->idDoc);
        aux = aux->prox;
    }
    printf("\n");
}


// --- IMPLEMENTAÇÃO DOS GETTERS --- 

int getQtde(tipoApontador no) {
    if (no != NULL) {
        return no->qtde;
    }
    return 0; 
}

int getIdDoc(tipoApontador no) {
    if (no != NULL) {
        return no->idDoc;
    }
    return -1; // Retorno de segurança para indicar erro/vazio
}

tipoApontador getProx(tipoApontador no) {
    if (no != NULL) {
        return no->prox;
    }
    return NULL;
}

tipoApontador getPrimeiro(tipoLista* lista) {
    if (lista != NULL) {
        return lista->primeiro;
    }
    return NULL;
}

tipoApontador getUltimo(tipoLista* lista) {
    if (lista != NULL) {
        return lista->ultimo;
    }
    return NULL;
}


// --- IMPLEMENTAÇÃO DOS SETTERS --- 

void setQtde(tipoApontador no, int qtde) {
    if (no != NULL) {
        no->qtde = qtde;
    }
}

void setIdDoc(tipoApontador no, int idDoc) {
    if (no != NULL) {
        no->idDoc = idDoc;
    }
}

void setProx(tipoApontador no, tipoApontador prox) {
    if (no != NULL) {
        no->prox = prox;
    }
}