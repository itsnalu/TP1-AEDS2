/*
Alexia Karoline Augusta Germano Silva [EF05373] 
Ana Luisa Moreira Rodrigues [EF05389] 
Dalmo Nolasco Dantas Rainer [EF05361] 
Lucas da Costa Moreira [EF05377]
*/

#include "TAD_Tabela_Hash.h"
#include "Indice_Hash.h"
#include "TAD_Patricia.h"
#include "Leitura_Arquivo_Patricia.h"

#define SUBPASTA "arquivos/"



#define MAX_FILENAME_LENGTH 100
#define MAX_CONTENT_LENGTH 1000

int main() {
    

    int numArquivos;
    char nomeArquivo[MAX_FILENAME_LENGTH];
    char nomeArquivoALer[MAX_FILENAME_LENGTH];
    char *Ingrediente;
    TipoArvore arvore = NULL;

    Vetor Tabela;
    TipoPesos p;
    Inicializa(Tabela);
    GeraPesos(p);

    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1. Receber o arquivo de entrada com os textos a serem indexados\n");
        printf("2. Construir os indices invertidos, a partir dos textos de entrada, usando os TADs PATRICIA e HASH\n");
        printf("3. Imprimir os indices invertidos, contendo as palavras em ordem alfabetica, uma por linha, com suas respectivas listas de ocorrencias\n");
        printf("4. Realizar buscas por um ou mais termo(s) de busca, nos indices construidos, individualmente, apresentando os arquivos ordenados por relevancia, tambem individualmente para cada TAD\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:

                scanf("%s", nomeArquivoALer);
                printf("arquivo a ler: %s\n", nomeArquivoALer);
                // Abrir o arquivo entrada.txt
                FILE* entrada = fopen(nomeArquivoALer, "r");
                if (entrada == NULL) {
                    perror("Erro ao abrir o arquivo");
                    return 1;
                }

                // Ler o número de arquivos
                if (fscanf(entrada, "%d", &numArquivos) != 1) {
                    perror("Erro ao ler o numero de arquivos");
                    fclose(entrada);
                    return 1;
                }


                int *TermosporArquivo = (int *) malloc(numArquivos * sizeof(int));
                if (TermosporArquivo == NULL) {
                    perror("Erro ao alocar memoria para TermosporArquivo");
                    fclose(entrada);
                    return 1;
                } 
                int totalDocs = numArquivos;
                int totalIngredientes = 46;

                // Loop para ler e abrir cada arquivo especificado
                for (int i = 0; i < numArquivos; i++) {
                    // Ler o nome do arquivo

                    if (fscanf(entrada, "%s", nomeArquivo) != 1) {
                        perror("Erro ao ler o nome do arquivo");
                        fclose(entrada);
                        return 1;
                    }

                    // char caminhoCompleto[MAX_FILENAME_LENGTH];

                    // snprintf(caminhoCompleto, sizeof(caminhoCompleto), "%s%s", SUBPASTA, nomeArquivo);


                    // +Abrir o arquivo
                    FILE *arquivo = fopen(nomeArquivo, "r");
                    if (arquivo == NULL) {
            
                        perror("Erro ao abrir o arquivo");
                        continue; // Pula para a próxima iteração do loop
                    }

                

                    Armazenar_Patricia(nomeArquivo, &arvore, (i+1));
                
                    //printf("%s\n", caminhoCompleto);

                    Armazenar(nomeArquivo, p, Tabela, i+1, TermosporArquivo); 
                    fclose(arquivo);   
                }

                break;
            case 2:
                //
                printf("Devido ao processo do desenvolvimento do projeto, este passo ja foi feito durante o recebimento do arquivo de entrada\n");
                break;
            case 3:
                
                Ingrediente = (char*) malloc(100 * sizeof(char));
                fgets(Ingrediente, 100, stdin);
                printf("Indice invertido da tabela Hash:\n");
                do
                {
                    printf("Digite o ingrediente (Digite 0 para voltar ao menu): ");
                    if (fgets(Ingrediente, 100, stdin) != NULL) {
                        size_t len = strlen(Ingrediente);
                        if (len > 0 && Ingrediente[len - 1] == '\n') {
                            Ingrediente[len - 1] = '\0';  // Remove o caractere de nova linha
                        }
                    }
                    Imprimir_IndiceInvertido_Hash(Ingrediente, p, Tabela);
                    fflush(stdin);
                    //memset(Ingrediente, '\0', sizeof(Ingrediente)); //Iria limpar o vetor atribuindo fim de string no vetor inteiro, mas causou problemas com o Ingrediente[0]
                } while (Ingrediente[0] != '0');

                break;
            case 4:
                calcularTFIDFParaTodos_Pat(arvore, totalDocs, TermosporArquivo);
                calcularTFIDFParaTodos(Tabela, totalDocs, TermosporArquivo);
                break;
            case 0:
                //
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
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
// // Abrir o arquivo entrada.txt
//     FILE *entrada = fopen("entrada.txt", "r");
//     if (entrada == NULL) {
//         perror("Erro ao abrir o arquivo entrada.txt");
//         return 1;
//     }

//     // Ler o número de arquivos
//     if (fscanf(entrada, "%d", &numArquivos) != 1) {
//         perror("Erro ao ler o número de arquivos");
//         fclose(entrada);
//         return 1;
//     }

//     int TermosporArquivo[numArquivos];  
//     totalDocs = numArquivos;
//     totalIngredientes = 46;
    
//     // Loop para ler e abrir cada arquivo especificado
//     for (int i = 0; i < numArquivos; i++) {
//         // Ler o nome do arquivo do arquivo entrada.txt
//         if (fscanf(entrada, "%s", nomeArquivo) != 1) {
//             perror("Erro ao ler o nome do arquivo");
//             fclose(entrada);
//             return 1;
//         }

        
//         // Abrir o arquivo
//         FILE *arquivo = fopen(nomeArquivo, "r");
//         if (arquivo == NULL) {
//             perror("Erro ao abrir o arquivo");
//             continue; // Pula para a próxima iteração do loop
//         }

//         // Chamar a função Armazenar
//         Armazenar_Patricia(nomeArquivo, &arvore, (i+1));
        
        
//         // printf("%d\n", i);
//         // Fechar o arquivo
//         fclose(arquivo);
//     }

    
    


    