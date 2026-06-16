#include "include/hash.h"
#include "include/leitura_entrada.h"
#include "include/lista.h"
#include "include/patricia.h"
#include "include/tfidf_hash.h"
#include "include/tfidf_patricia.h"
#include "include/utils.h"

int main(){
    tipoHash hash;
    inicializaHash(&hash, TAM_HASH);

    //char arquivo[50];

    printf("iniciando\n");

    //scanf("%s", arquivo);

    lerEntradaPrincipal("./entradas/entrada.txt", "stopwords.txt", &hash);

    imprimeHash(&hash);
    return 0;
}
