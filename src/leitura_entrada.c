#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/leitura_entrada.h"


// Funcao pra tirar pontuacao e botar tudo minusculo, porque o TF-IDF é sensivel e a professora pediu
void limparPalavra(char* palavra) {
    int i = 0, j = 0;
    char limpa[100];

    while (palavra[i] != '\0') {
        if (isalpha(palavra[i])) { // Se for letra, passa pra minuscula
            limpa[j] = tolower(palavra[i]);
            j++;
        }
        i++;
    }
    limpa[j] = '\0'; // Finaliza a string pro C nao imprimir lixo de memoria na tela
    strcpy(palavra, limpa);
}

// Funcao que verifica se a palavra ta na lista de stop words
int ehStopWord(char* palavra, char stopWords[][50], int numStopWords) {
    for(int i = 0; i < numStopWords; i++) {
        if(strcmp(palavra, stopWords[i]) == 0) {
            return 1; // Achei a maldita, ignora ela
        }
    }
    return 0; // Palavra limpa, pode seguir pro indice
}

// Funcao pra carregar as stop words que a professora mandou no txt
void carregarStopWords(const char* nomeArquivo, char stopWords[][50], int* numStopWords) {
    FILE* f = fopen(nomeArquivo, "r");
    if (f == NULL) {
        printf("Arquivo %s não existe\n", nomeArquivo);
        *numStopWords = 0;
        return;
    }

    *numStopWords = 0;
    // O fscanf ja ignora os 'enters' do Stopwords.txt automaticamente
    while (fscanf(f, "%s", stopWords[*numStopWords]) != EOF && *numStopWords < 500) {
        limparPalavra(stopWords[*numStopWords]);
        (*numStopWords)++;
    }
    fclose(f);

    // Print de seguranca pra gente saber que o arquivo leu certo
    printf(" %d Stopwords carregadas com sucesso!\n", *numStopWords);
}

// Abre a fabula especifica, le palavra por palavra e joga pros TADs
void processarFabula(const char* nomeFabula, int idDoc, char stopWords[][50], int numStopWords, tipoHash* hash) {
    FILE* f = fopen(nomeFabula, "r");
    if (f == NULL) {
        printf("Deu ruim: Nao achei a fabula %s!\n", nomeFabula);
        return;
    }

    char palavra[100];

    while (fscanf(f, "%s", palavra) != EOF) {
        limparPalavra(palavra);

        if (strlen(palavra) > 0 && !ehStopWord(palavra, stopWords, numStopWords)) {

            // Inserindo na Hash!
            // A gente passa o endereco da hash, a palavra limpa e o ID do documento
            insereHash(hash, palavra, idDoc);

            // Quando a Patricia estiver pronta, vai entrar algo como:
            // inserePatricia(&arvorePatricia, palavra, idDoc);
        }
    }
    fclose(f);
}

// Funcao chefe que faz o meio de campo. A main (do menu) so precisa chamar essa aqui.
void lerEntradaPrincipal(const char* arquivoEntradaPrincipal, const char* arquivoStopWords) {
    char stopWords[500][50]; // Cabem ate 500 palavras de ate 50 letras
    int numStopWords = 0;

    // 1. Carrega as stop words primeiro
    carregarStopWords(arquivoStopWords, stopWords, &numStopWords);

    // 2. Abre o entrada.txt
    FILE* f = fopen(arquivoEntradaPrincipal, "r");
    if (f == NULL) {
        printf("Erro fatal: Arquivo %s nao encontrado.\n", arquivoEntradaPrincipal);
        return;
    }

    int n;
    if(fscanf(f, "%d", &n) != 1) { // Puxa o numero total de fabulas da primeira linha
        printf("Erro: Arquivo vazio ou sem o N na primeira linha.\n");
        fclose(f);
        return;
    }

    // Alocacao dinamica pra guardar o idDoc e o nome em memoria como manda o PDF
    Documento* docs = (Documento*) malloc(n * sizeof(Documento));
    if (docs == NULL) {
        printf("Faltou memoria, malloc falhou.\n");
        fclose(f);
        return;
    }

    printf("[OK] Lendo %d fabulas...\n", n);

    // Le o nome de cada arquivo, cria o ID e ja manda processar
    for (int i = 0; i < n; i++) {
        fscanf(f, "%s", docs[i].nomeArquivo);
        docs[i].idDoc = i + 1;

        processarFabula(docs[i].nomeArquivo, docs[i].idDoc, stopWords, numStopWords);
    }

    // Libera a memoria pro Valgrind nao chorar
    free(docs);
    fclose(f);
    printf("[OK] Leitura das fabulas finalizada com sucesso!\n");
}
