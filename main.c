#include "headers/tfidf.h"


int main(){
    tipoHash hash;
    tipoNoPatricia* patricia;

    inicializaHash(&hash, TAM_HASH);
    inicializaPatricia(&patricia);

    int nDocs = 0;
    Documento* documentos = NULL;

    char nome_entrada[50], caminho_entrada[100], termo_busca[100];

    char stopWords[500][MAX_PALAVRA];
    int numStopWords = 0;
    carregarStopWords("stopwords.txt", stopWords, &numStopWords);

    int v_true = 1;

    printf("\n");
    printf("Bem Vindo(a)! Iniciando o programa...\n");

    while (v_true == 1){
        printf("\n=============================================================\n");
        printf("Digite o numero correspondente a acao que deseja executar:\n");
        printf("=============================================================\n");
        printf("1. Inserir dados nos indices invertidos\n");
        printf("2. Imprimir indices invertidos\n");
        printf("3. Buscar termos na Hash\n");
        printf("4. Buscar termos na PATRICIA\n");
        printf("5. Encerrar o programa\n");

        int v_prog;
        scanf("%d", &v_prog);

        switch (v_prog){
    
            case 1:
                printf("Digite o nome do arquivo de entrada principal:\n");
                scanf("%s", nome_entrada);
                snprintf(caminho_entrada, sizeof(caminho_entrada), "./entradas/%s", nome_entrada);

                if (documentos != NULL){
                    free(documentos);
                }

                documentos = lerEntradaPrincipal(caminho_entrada, "stopwords.txt", &hash, &patricia, &nDocs);

                if (documentos != NULL){
                    printf("Dados inseridos com sucesso!\n");
                }

                break;
            
            case 2:
                if (documentos == NULL) {
                    printf("Erro: Leia os arquivos de entrada (opcao 1) antes de imprimir os indices.\n");
                    break;
                }

                printf("\nImprimindo a estrutura Hash:\n");
                imprimeHash(&hash);

                printf("\nImprimindo a estrutura Arvore PATRICIA:\n");
                imprimePatricia(patricia);

                break;
            
            case 3:
                if (documentos == NULL) {
                    printf("Erro: Leia os arquivos de entrada (opcao 1) antes de fazer buscas.\n");
                    break;
                }
                
                printf("Digite o(s) termo(s) de busca: ");
                while (getchar() != '\n');
                fgets(termo_busca, sizeof(termo_busca), stdin);
                termo_busca[strcspn(termo_busca, "\n")] = '\0';

                realizarBusca(termo_busca, &hash, patricia, documentos, nDocs, stopWords, numStopWords, 1);


                break;
            
            case 4:
                if (documentos == NULL) {
                    printf("Erro: Leia os arquivos de entrada (opcao 1) antes de fazer buscas.\n");
                    break;
                }
                
                printf("Digite o(s) termo(s) de busca: ");
                while (getchar() != '\n');
                fgets(termo_busca, sizeof(termo_busca), stdin);
                termo_busca[strcspn(termo_busca, "\n")] = '\0';

                realizarBusca(termo_busca, &hash, patricia, documentos, nDocs, stopWords, numStopWords, 2);

                break;
            
            case 5:
                if (documentos != NULL) {
                    free(documentos);
                }

                //liberaHash(&hash);
                //limpa patricia

                v_true = 0;
                break;
            
            default:
                printf("Opcao invalida.\n");
                break;
            }
    }

    return 0;
}
