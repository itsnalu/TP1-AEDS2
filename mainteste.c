#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Indice_Hash.h"
//#include "Indice_Patricia.h"
#define SUBPASTA "arquivos/"

int main() {
    int numArquivos;
    char nomeArquivo[MAX_FILENAME_LENGTH];
    
    //TipoArvore arvore = NULL;
    int totalIngredientes;
    int totalDocs;
    Vetor Tabela;
    TipoPesos p;
    InicializaVetor(Tabela);
    Inicializa(Tabela);
    GeraPesos(p);


    // Abrir o arquivo entrada.txt
    FILE *entrada = fopen("entrada.txt", "r");
    if (entrada == NULL) {
        perror("Erro ao abrir o arquivo entrada.txt");
        return 1;
    }

    // Ler o número de arquivos
    if (fscanf(entrada, "%d", &numArquivos) != 1) {
        perror("Erro ao ler o número de arquivos");
        fclose(entrada);
        return 1;
    }


    int TermosporArquivo[numArquivos];  
    totalDocs = numArquivos;
    totalIngredientes = 46;
    
    // Loop para ler e abrir cada arquivo especificado
    for (int i = 0; i < numArquivos; i++) {
        // Ler o nome do arquivo do arquivo entrada.txt
        if (fscanf(entrada, "%s", nomeArquivo) != 1) {
            perror("Erro ao ler o nome do arquivo");
            fclose(entrada);
            return 1;
        }


        char caminhoCompleto[MAX_FILENAME_LENGTH];

        snprintf(caminhoCompleto, sizeof(caminhoCompleto), "%s%s", SUBPASTA, nomeArquivo);


        // Abrir o arquivo
        FILE *arquivo = fopen(caminhoCompleto, "r");
        if (arquivo == NULL) {
            
            perror("Erro ao abrir o arquivo");
            continue; // Pula para a próxima iteração do loop
        }

        // Chamar a função Armazenar
        printf("%s\n", caminhoCompleto);
        Armazenar(caminhoCompleto, p, Tabela, (i+1), TermosporArquivo);
        //Armazenar_Patricia(nomeArquivo, &arvore, (i+1));
        
        
        // printf("%d\n", i);
        // Fechar o arquivo
        fclose(arquivo);
    }

    Imprime(Tabela);


    // char *Ingrediente;
    // Ingrediente = (char*) malloc(100 * sizeof(char));
    // do
    // {
    //     printf("Digite o ingrediente (Digite 0 para voltar ao menu): ");
    //     if (fgets(Ingrediente, 100, stdin) != NULL) {
    //         size_t len = strlen(Ingrediente);
    //         if (len > 0 && Ingrediente[len - 1] == '\n') {
    //             Ingrediente[len - 1] = '\0';  // Remove o caractere de nova linha
    //         }
    //     }
    //     Imprimir_IndiceInvertido_Hash(Ingrediente, p, Tabela);
    //     //memset(Ingrediente, '\0', sizeof(Ingrediente));

    // } while (Ingrediente[0] != '0');
    
    // imprimirIngredientes(Tabela, totalDocs);
    printf("\n");
    calcularTFIDFParaTodos(Tabela, totalDocs, TermosporArquivo);


    // char *Ingrediente;
    // Ingrediente = (char*) malloc(100 * sizeof(char));
    // if (fgets(Ingrediente, 100, stdin) != NULL) {
    //     size_t len = strlen(Ingrediente);
    //     if (len > 0 && Ingrediente[len - 1] == '\n') {
    //         Ingrediente[len - 1] = '\0';  // Remove o caractere de nova linha
    //     }
    // }
    // Imprimir_IndiceInvertido_Hash(Ingrediente, p, Tabela);

    // int lala = ArvoreVazia(arvore);
    // printf("%d\n", lala);

    // ImprimeEmOrdem(arvore);
    // ImprimeEmOrdemComInternos(arvore);

    // printf("Digite a palavra para pesquisar: \n");
    /* char *Ingrediente;
    Ingrediente = (char*) malloc(100 * sizeof(char));
    if (fgets(Ingrediente, 100, stdin) != NULL) {
        size_t len = strlen(Ingrediente);
        if (len > 0 && Ingrediente[len - 1] == '\n') {
            Ingrediente[len - 1] = '\0';  // Remove o caractere de nova linha
        }
    } */
    // Pesquisa(Ingrediente,arvore);

    // Libera(arvore);
    fclose(entrada); // Fechar o arquivo entrada.txt
}

