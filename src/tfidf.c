#include "../headers/tfidf.h"

int comparaRelevancia(const void* a, const void* b) {
    Relevancia* r1 = (Relevancia*)a;
    Relevancia* r2 = (Relevancia*)b;

    if (r1->score < r2->score) return 1;
    if (r1->score > r2->score) return -1;

    return 0;
}

int tamanhoLista(tipoLista* lista){
    int tamanho = 0;
    tipoNo* aux = lista->primeiro->prox;

    while (aux != NULL){ // <-- Alteração feita aqui
        tamanho++;
        aux = aux->prox;
    }

    return tamanho;
}


void realizarBusca(char* consulta, tipoHash* hash, tipoNoPatricia* patricia, Documento* docs, int nDocs, char stopWords[][MAX_PALAVRA], int numStopWords, int tipoIndice){
    Relevancia* ranking = (Relevancia*) malloc(nDocs * sizeof(Relevancia));
        for (int i = 0; i < nDocs; i++) {
            ranking[i].idDoc = docs[i].idDoc;
            ranking[i].score = 0.0;
        }

        char consultaCopia[500];
        strcpy(consultaCopia, consulta);

        char* palavra = strtok(consultaCopia, " ");

        while (palavra != NULL) {
            limparPalavra(palavra);

            if (strlen(palavra) > 0 && !ehStopWord(palavra, stopWords, numStopWords)) {
                tipoLista* ocorrencias = NULL;

                //define qual estrutura realizar a pesquisa atraves do parametro
                if (tipoIndice == 1) {
                    ocorrencias = buscaHash(hash, palavra);
                } else if (tipoIndice == 2) {
                    ocorrencias = buscaPatricia(patricia, palavra);
                }

                if (ocorrencias != NULL) {
                    int dj = tamanhoLista(ocorrencias);

                    double idf = log2((double)nDocs) / (double)dj;

                    tipoNo* aux = ocorrencias->primeiro->prox;
                    while (aux != NULL) {
                        int fji = aux->qtde;

                        double wji = (double)fji * idf;

                        for (int i = 0; i < nDocs; i++) {
                            if (ranking[i].idDoc == aux->idDoc) {
                                ranking[i].score += wji;
                                break;
                            }
                        }
                        aux = aux->prox;
                    }
                }
            }
            palavra = strtok(NULL, " ");
        }

        for (int i = 0; i < nDocs; i++) {
            if (ranking[i].score > 0) {
                int indiceDoc = ranking[i].idDoc - 1;
                ranking[i].score = ranking[i].score / (double)docs[indiceDoc].nTermos;
            }
        }

        qsort(ranking, nDocs, sizeof(Relevancia), comparaRelevancia);

        printf("\nRESULTADO DA BUSCA\n");
        int encontrou = 0;
        for (int i = 0; i < nDocs; i++) {
            if (ranking[i].score > 0) {
                int indiceDoc = ranking[i].idDoc - 1;
                printf("Relevancia: %f | Arquivo: %s\n", ranking[i].score, docs[indiceDoc].nomeArquivo);
                encontrou = 1;
            }
        }

        if (!encontrou) {
            printf("Nenhum documento relevante encontrado para a busca.\n");
        }

        free(ranking);
    }
