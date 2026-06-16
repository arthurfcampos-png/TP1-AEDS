#include "headers/hash.h"
#include "headers/leitura_entrada.h"
#include "headers/lista.h"
#include "headers/patricia.h"


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
