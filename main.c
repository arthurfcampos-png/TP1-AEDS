#include "headers/hash.h"
#include "headers/leitura_entrada.h"
#include "headers/lista.h"


int main(){
    tipoHash hash;
    inicializaHash(&hash, TAM_HASH);

    char nome_entrada[50], caminho_entrada[100];
    int nDocs = 0;

    printf("Iniciando!\n");

    printf("Digite o nome do arquivo de entrada principal:\n");
    scanf("%s", nome_entrada);
    snprintf(caminho_entrada, sizeof(caminho_entrada), "./entradas/%s", nome_entrada);

    Documento* documentos = lerEntradaPrincipal(caminho_entrada, "stopwords.txt", &hash, &nDocs);

    imprimeHash(&hash);

    return 0;
}
