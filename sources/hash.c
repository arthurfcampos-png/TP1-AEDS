#include "../headers/hash.h"

void inicializaHash(tipoHash* hash, int tamanho) {
    hash->tamanho = tamanho;
    
    hash->tabela = (tipoNoHash**) malloc(tamanho * sizeof(tipoNoHash*));
    if (hash->tabela == NULL) {
        printf("Erro: Falha ao alocar memoria para a Tabela Hash.\n");
        exit(1);
    }
    
    for (int i = 0; i < tamanho; i++) {
        hash->tabela[i] = NULL;
    }

    struct timeval semente;
    // Utiliza o tempo exato em microssegundos para gerar uma semente muito aleatória
    gettimeofday(&semente, NULL); 
    srand((int)(semente.tv_sec + 1000000 * semente.tv_usec));

    // Preenche a matriz de pesos
    for (int i = 0; i < MAX_PALAVRA; i++) {
        for (int j = 0; j < TAM_ALFABETO; j++) {
            hash->pesos[i][j] = 1 + (int)(10000.0 * rand() / (RAND_MAX + 1.0));
        }
    }
}

int calculaHash(tipoHash* hash, char* palavra) {
    unsigned int soma = 0; 
    int comp = strlen(palavra);
    
    for (int i = 0; i < comp; i++) {
        // Pega o peso sorteado para a posição 'i' e a letra 'palavra[i]'
        soma += hash->pesos[i][(unsigned int)palavra[i]];
    }
    
    return (soma % hash->tamanho);
}

void insereHash (tipoHash* hash, char* palavra, int idDoc){

    // Calcula o índice matemático
    int indice = calculaHash(palavra, hash->tamanho);

    // Verifica a lista de colisões nesse índice
    tipoNoHash* atual = hash->tabela[indice];

    while (atual != NULL) {
        if (strcmp(atual->palavra, palavra) == 0) {
            insereLista (idDoc, &(atual->ocorrencias));
            return;
        }
        atual = atual->prox;
    }

    // Caso a palavra seja nova
    tipoNoHash* novoNO = (tipoNoHash*) malloc (sizeof(tipoNoHash));
    strcpy (novoNO->palavra, palavra);

    // Prepara a lista encadeada dentro do novo slot da hash
    inicializaLista (&(novoNO->ocorrencias));
    insereLista (idDoc, &(novoNO->ocorrencias));

    
    novoNO->prox = hash->tabela[indice]; // novoNo entra e se liga como primeiro da lista encadeada
    hash->tabela[indice] = novoNO; // Tabela reconhece o novoNo como o primeiro
}

// Função auxiliar para o qsort comparar as strings em ordem alfabética 
int comparaNos(const void* a, const void* b) {
    // Convertendo os ponteiros genéricos do qsort para os nossos nós
    tipoNoHash* noA = *(tipoNoHash**)a;
    tipoNoHash* noB = *(tipoNoHash**)b;
    
    // O strcmp já faz a comparação alfabética perfeita para nós!
    return strcmp(noA->palavra, noB->palavra);
}

// Imprime o índice invertido em ordem alfabética
void imprimeHash(tipoHash* hash) {
    
    // Contar o total de palavras armazenadas
    int totalPalavras = 0;
    for (int i = 0; i < hash->tamanho; i++) {
        tipoNoHash* atual = hash->tabela[i];
        while (atual != NULL) {
            totalPalavras++;
            atual = atual->prox;
        }
    }

    if (totalPalavras == 0) {
        printf("A Tabela Hash esta vazia.\n");
        return;
    }

    // Alocar um vetor dinâmico de ponteiros temporário
    tipoNoHash** vetorTemp = (tipoNoHash**) malloc(totalPalavras * sizeof(tipoNoHash*));
    
    // Preencher o vetor com os endereços de todos os nós
    int pos = 0;
    for (int i = 0; i < hash->tamanho; i++) {
        tipoNoHash* atual = hash->tabela[i];
        while (atual != NULL) {
            vetorTemp[pos] = atual; // Guarda o nó no vetor
            pos++;
            atual = atual->prox;
        }
    }

    // Ordenar o vetor usando o QuickSort (qsort) nativo do C
    qsort(vetorTemp, totalPalavras, sizeof(tipoNoHash*), comparaNos);

    // Imprimir os nós já em ordem alfabética
    for (int i = 0; i < totalPalavras; i++) {
        // Imprime a palavra
        printf("%s ", vetorTemp[i]->palavra);
        
        // Imprime a lista de ocorrências 
        imprimeLista(&(vetorTemp[i]->ocorrencias)); 
    }

    // Liberar a memória do vetor temporário
    free(vetorTemp);
}