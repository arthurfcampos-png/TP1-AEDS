#include "headers/hash.h"
#include "headers/leitura_entrada.h"
#include "headers/lista.h"


int main(){
    tipoHash hash;
    tipoNoPatricia* patricia;

    inicializaHash(&hash, TAM_HASH);
    inicializaPatricia(&patricia);

    char nome_entrada[50], caminho_entrada[100];
    int nDocs = 0;

    printf("Iniciando!\n");

    printf("Digite o nome do arquivo de entrada principal:\n");
    scanf("%s", nome_entrada);
    snprintf(caminho_entrada, sizeof(caminho_entrada), "./entradas/%s", nome_entrada);

    Documento* documentos = lerEntradaPrincipal(caminho_entrada, "stopwords.txt", &hash, &patricia, &nDocs);

    printf("imprimindo a hash:\n");
    imprimeHash(&hash);

    printf("imprimindo a patricia:\n");
    imprimePatricia(patricia);

    return 0;
}
