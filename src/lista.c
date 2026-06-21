#include "../headers/lista.h"


// Função para inicializar a lista encadeada
void inicializaLista(tipoLista* lista){
    lista->primeiro = (tipoNo*) malloc(sizeof(tipoNo));
    lista->ultimo = lista->primeiro;
    lista->primeiro->prox = NULL;
}

// Função para inserção na lista encadeada
int insereLista(int idDoc , tipoLista* lista){
    tipoNo* aux = lista->primeiro; //ponteiro auxiliar para percorrer a lista

    while ((aux->prox != NULL) && (aux->prox->idDoc <= idDoc)){
        if (aux->prox->idDoc == idDoc){  //verifica se esse idDoc já está na lista
            aux->prox->qtde++; //se já estiver na lista apenas incrementa a qtde
            return 0;
        }
        aux = aux->prox;
    }

    //criamos o novoNo alocando memória para ele e depois definimos o idDoc e qtde
    tipoNo* novoNo = (tipoNo*) malloc(sizeof(tipoNo));
    novoNo->idDoc = idDoc;
    novoNo->qtde = 1;

    //fazemos o novoNo se ligar ao nó que estava logo após o aux->prox e depois religamos os ponteiros
    novoNo->prox = aux->prox;
    aux->prox = novoNo;

    //se o novoNo->prox for NULL, inserimos exatamente no final da lista. Sendo assim, atualizamos o lista->ultimo
    if(novoNo->prox == NULL){
        lista->ultimo = novoNo;
    }

    return 1;
}

// Função para imprimir a lista
void imprimeLista(tipoLista* lista){
    tipoNo* aux;
    aux = lista->primeiro->prox;
    while (aux != NULL){
        //<qtde, idDoc>
        printf("<%d, %d> ", aux->qtde, aux->idDoc);
        aux = aux->prox;
    }
    printf("\n");
}


//Gets

int getQtde(tipoNo* no) {
    if (no != NULL) {
        return no->qtde;
    }
    return 0;
}

int getIdDoc(tipoNo* no) {
    if (no != NULL) {
        return no->idDoc;
    }
    return -1;
}

tipoNo* getProx(tipoNo* no) {
    if (no != NULL) {
        return no->prox;
    }
    return NULL;
}

tipoNo* getPrimeiro(tipoLista* lista) {
    if (lista != NULL) {
        return lista->primeiro;
    }
    return NULL;
}

tipoNo* getUltimo(tipoLista* lista) {
    if (lista != NULL) {
        return lista->ultimo;
    }
    return NULL;
}


// Sets

void setQtde(tipoNo* no, int qtde) {
    if (no != NULL) {
        no->qtde = qtde;
    }
}

void setIdDoc(tipoNo* no, int idDoc) {
    if (no != NULL) {
        no->idDoc = idDoc;
    }
}

void setProx(tipoNo* no, tipoNo* prox) {
    if (no != NULL) {
        no->prox = prox;
    }
}
