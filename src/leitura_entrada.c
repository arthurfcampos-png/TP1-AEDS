#include "../headers/leitura_entrada.h"


//funcao pra colocar todos os caracteres minusculos
void limparPalavra(char* palavra) {
    int i = 0, j = 0;
    char limpa[MAX_PALAVRA];

    while (palavra[i] != '\0') {
        if (isalpha(palavra[i])) {
            limpa[j] = tolower(palavra[i]);
            j++;
        }
        i++;
    }
    limpa[j] = '\0';
    strcpy(palavra, limpa);
}

//funcao que verifica se a palavra esta na lista de stopwords
int ehStopWord(char* palavra, char stopWords[][MAX_PALAVRA], int numStopWords) {
    for(int i = 0; i < numStopWords; i++) {
        if(strcmp(palavra, stopWords[i]) == 0) {
            return 1;
        }
    }
    return 0; //palavra limpa
}

//funcao para carregar as stopwords
void carregarStopWords(const char* nomeArquivo, char stopWords[][MAX_PALAVRA], int* numStopWords) {
    FILE* f = fopen(nomeArquivo, "r");
    if (f == NULL) {
        printf("Arquivo %s não existe\n", nomeArquivo);
        *numStopWords = 0;
        return;
    }

    *numStopWords = 0;

    while (fscanf(f, "%s", stopWords[*numStopWords]) != EOF && *numStopWords < 500) {
        limparPalavra(stopWords[*numStopWords]);
        (*numStopWords)++;
    }
    fclose(f);
}

//abre a fabula especifica, le palavra por palavra e joga pros TADs
int processarFabula(const char* nomeFabula, int idDoc, char stopWords[][MAX_PALAVRA], int numStopWords, tipoHash* hash, tipoNoPatricia** patricia, double* tempo_total_hash, double* tempo_total_patricia) {
    char caminho_completo[100];

    clock_t i_hash, f_hash, i_patricia, f_patricia;

    snprintf(caminho_completo, sizeof(caminho_completo), "entradas/%s", nomeFabula);

    FILE* f = fopen(caminho_completo, "r");
    if (f == NULL) {
        printf("erro: fabula %s nao encontrada\n", nomeFabula);
        return 0;
    }

    char palavra[MAX_PALAVRA];
    int nTermos = 0;

    while (fscanf(f, "%s", palavra) != EOF) {
        limparPalavra(palavra);

        if (strlen(palavra) > 0 && !ehStopWord(palavra, stopWords, numStopWords)){

            i_hash = clock();
            nTermos += insereHash(hash, palavra, idDoc);
            f_hash = clock();
            
            *tempo_total_hash += ((double)(f_hash - i_hash) / CLOCKS_PER_SEC) * 1000.0;

            i_patricia = clock();
            inserePatricia(patricia, palavra, idDoc);
            f_patricia = clock();

        *tempo_total_patricia += ((double)(f_patricia - i_patricia) / CLOCKS_PER_SEC) * 1000.0;
        }
    }

    fclose(f);

    return nTermos;
}


//função pra ler a entrada principa que retorna um ponteiro pro array de documentos, pra podermos calcular o tfidf corretamente
Documento* lerEntradaPrincipal(const char* arquivoEntradaPrincipal, const char* arquivoStopWords, tipoHash* hash, tipoNoPatricia** patricia, int* nDocs){
    char stopWords[500][MAX_PALAVRA]; //cabe 500 palavras com o tamanho de MAX_PALAVRA
    int numStopWords = 0;

    carregarStopWords(arquivoStopWords, stopWords, &numStopWords);

    //abre o arquivo de entrada
    FILE* f = fopen(arquivoEntradaPrincipal, "r");
    if (f == NULL) {
        printf("erro: arquivo %s nao encontrado.\n", arquivoEntradaPrincipal);
        return NULL;
    }

    int n;
    if(fscanf(f, "%d", &n) != 1) { //pega o numero total de fabulas da primeira linha
        printf("erro: arquivo vazio ou sem o N na primeira linha.\n");
        fclose(f);
        return NULL;
    }

    //alocacao dinamica pra guardar o idDoc e o nome em memoria
    Documento* docs = (Documento*) malloc(n * sizeof(Documento));
    if (docs == NULL) {
        printf("erro: falta de memoria. malloc falhou.\n");
        fclose(f);
        return NULL;
    }

    printf("Lendo %d fabulas...\n", n);

    double tempo_insercao_hash = 0.0;
    double tempo_insercao_patricia = 0.0;

    //lê o nome de cada arquivo, cria o idDoc, processa e atualiza o nTermos no docs 
    for (int i = 0; i < n; i++) {
        fscanf(f, "%s", docs[i].nomeArquivo);        
        docs[i].idDoc = i + 1;
        docs[i].nTermos = processarFabula(docs[i].nomeArquivo, docs[i].idDoc, stopWords, numStopWords, hash, patricia, &tempo_insercao_hash, &tempo_insercao_patricia);
    }

    *nDocs = n;
   
    fclose(f);

    printf("\nTempo total de insercao na Hash: %f ms\n", tempo_insercao_hash);
    printf("Tempo total de insercao na Patricia: %f ms\n", tempo_insercao_patricia);

    return docs;
}