#include <stdio.h>
#include <stdlib.h>
//#include "TAD_Tabela_Hash.h"
#include "Leitura_Arquivo_Hash.h"
//#include "TAD_Patricia.h"
#include "Leitura_Arquivo_Patricia.h"

#define MAX_FILENAME_LENGTH 100
#define MAX_CONTENT_LENGTH 1000

int main() {
    
    FILE *entrada;
    int numArquivos;
    char nomeArquivo[MAX_FILENAME_LENGTH];
    char nomeArquivoALer[MAX_FILENAME_LENGTH];
    
    TipoArvore arvore = NULL;

    Vetor Tabela;
    TipoPesos p;
    Inicializa(Tabela);
    GeraPesos(p);

    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1. Receber o arquivo de entrada com os textos a serem indexados\n");
        printf("2. Construir os índices invertidos, a partir dos textos de entrada, usando os TADs PATRICIA e HASH\n");
        printf("3. Imprimir os índices invertidos, contendo as palavras em ordem alfabética, uma por linha, com suas respectivas listas de ocorrências\n");
        printf("4. Realizar buscas por um ou mais termo(s) de busca, nos índices construídos, individualmente, apresentando os arquivos ordenados por relevância, também individualmente para cada TAD\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:

                scanf("%s", nomeArquivoALer);
                printf("arquivo a ler: %s\n", nomeArquivoALer);
                // Abrir o arquivo entrada.txt
                entrada = fopen(nomeArquivoALer, "r");
                if (entrada == NULL) {
                    perror("Erro ao abrir o arquivo");
                    return 1;
                }

                // Ler o número de arquivos
                if (fscanf(entrada, "%d", &numArquivos) != 1) {
                    perror("Erro ao ler o número de arquivos");
                    fclose(entrada);
                    return 1;
                }

                // Loop para ler e abrir cada arquivo especificado
                for (int i = 0; i < numArquivos; i++) {
                    // Ler o nome do arquivo
                    if (fscanf(entrada, "%s", nomeArquivo) != 1) {
                        perror("Erro ao ler o nome do arquivo");
                        fclose(entrada);
                        return 1;
                        Armazenar_Patricia(nomeArquivo, &arvore, (i+1));    
                    }

                // Abrir o arquivo
                FILE *arquivo = fopen(nomeArquivo, "r");
                if (arquivo == NULL) {
                    perror("Erro ao abrir o arquivo");
                    continue; // Pula para a próxima iteração do loop
                }
                }



                break;
            case 2:
                //
                printf("ohhh bobo, ja foi feito\n");
                break;
            case 3:
                //
                char *Ingrediente;
                do
                {
                    Ingrediente = (char*) malloc(100 * sizeof(char));
                    printf("Digite o ingrediente (Digite 0 para voltar ao menu): ");
                    if (fgets(Ingrediente, 100, stdin) != NULL) {
                        size_t len = strlen(Ingrediente);
                        if (len > 0 && Ingrediente[len - 1] == '\n') {
                            Ingrediente[len - 1] = '\0';  // Remove o caractere de nova linha
                        }
                    }
                    Imprimir_IndiceInvertido_Hash(Ingrediente, p, Tabela);
                } while (Ingrediente[0] != '0');

                break;
            case 4:
                //
                break;
            case 0:
                //
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);


    // // Abrir o arquivo entrada.txt
    // entrada = fopen("entrada.txt", "r");
    // if (entrada == NULL) {
    //     perror("Erro ao abrir o arquivo entrada.txt");
    //     return 1;
    // }

    // // Ler o número de arquivos
    // if (fscanf(entrada, "%d", &numArquivos) != 1) {
    //     perror("Erro ao ler o número de arquivos");
    //     fclose(entrada);
    //     return 1;
    // }

    // // Loop para ler e abrir cada arquivo especificado
    // for (int i = 0; i < numArquivos; i++) {
    //     // Ler o nome do arquivo
    //     if (fscanf(entrada, "%s", nomeArquivo) != 1) {
    //         perror("Erro ao ler o nome do arquivo");
    //         fclose(entrada);
    //         return 1;
    //     }

    //     // Abrir o arquivo especificado
    //     FILE *arquivo = fopen(nomeArquivo, "r");
    //     if (arquivo == NULL) {
    //         perror("Erro ao abrir o arquivo especificado");
    //         continue;
    //     }

    //     // Ler o conteúdo do arquivo e armazenar em uma string (ou outra estrutura, conforme necessidade)
    //     char conteudo[MAX_CONTENT_LENGTH];
    //     while (fgets(conteudo, sizeof(conteudo), arquivo) != NULL) {
    //         // Aqui você pode processar o conteúdo do arquivo conforme necessário
    //         printf("Conteúdo do arquivo %s:\n%s\n", nomeArquivo, conteudo);
    //     }

    //     // Fechar o arquivo após a leitura
    //     fclose(arquivo);
    // }

    // // Fechar o arquivo entrada.txt
    // fclose(entrada);

    return 0;
}