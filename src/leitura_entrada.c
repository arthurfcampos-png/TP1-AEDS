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

    printf(" %d Stopwords carregadas com sucesso!\n", *numStopWords);
}

//abre a fabula especifica, le palavra por palavra e joga pros TADs
int processarFabula(const char* nomeFabula, int idDoc, char stopWords[][MAX_PALAVRA], int numStopWords, tipoHash* hash, tipoNoPatricia** patricia) {
    char caminho_completo[100];
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

        if (strlen(palavra) > 0 && !ehStopWord(palavra, stopWords, numStopWords)) {

            nTermos += insereHash(hash, palavra, idDoc);

            inserePatricia(patricia, palavra, idDoc);
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

    printf("[OK] Lendo %d fabulas...\n", n);

    //lê o nome de cada arquivo, cria o idDoc, processa e atualiza o nTermos no docs 
    for (int i = 0; i < n; i++) {
        fscanf(f, "%s", docs[i].nomeArquivo);        
        docs[i].idDoc = i + 1;
        docs[i].nTermos = processarFabula(docs[i].nomeArquivo, docs[i].idDoc, stopWords, numStopWords, hash, patricia);
    }

    *nDocs = n;
   
    fclose(f);
    printf("[OK] Leitura das fabulas finalizada com sucesso!\n");

    return docs;
}