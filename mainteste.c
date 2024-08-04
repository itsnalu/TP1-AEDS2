#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Indice_Hash.h"
//#include "Indice_Patricia.h"


int main() {
    int numArquivos;
    char nomeArquivo[MAX_FILENAME_LENGTH];
    
    //TipoArvore arvore = NULL;
    int totalIngredientes;
    int totalDocs;
    Vetor Tabela;
    TipoPesos p;
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

        
        // Abrir o arquivo
        FILE *arquivo = fopen(nomeArquivo, "r");
        if (arquivo == NULL) {
            perror("Erro ao abrir o arquivo");
            continue; // Pula para a próxima iteração do loop
        }

        // Chamar a função Armazenar
        Armazenar(nomeArquivo, p, Tabela, (i+1), TermosporArquivo);
        //Armazenar_Patricia(nomeArquivo, &arvore, (i+1));
        
        
        // printf("%d\n", i);
        // Fechar o arquivo
        fclose(arquivo);
    }

    Imprime(Tabela);


    char *Ingrediente;
    Ingrediente = (char*) malloc(100 * sizeof(char));
    do
    {
        printf("Digite o ingrediente (Digite 0 para voltar ao menu): ");
        if (fgets(Ingrediente, 100, stdin) != NULL) {
            size_t len = strlen(Ingrediente);
            if (len > 0 && Ingrediente[len - 1] == '\n') {
                Ingrediente[len - 1] = '\0';  // Remove o caractere de nova linha
            }
        }
        printf("%s: ", Ingrediente);   
        Imprimir_IndiceInvertido_Hash(Ingrediente, p, Tabela);
    } while (Ingrediente[0] != '0');
    

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



/* 
    char* palavras[] = {"banana", "abacaxi", "uva", "manga", "laranja", "melancia", "cereja", "pera", "maca", "cavalo", "cebola"};
    int n = sizeof(palavras) / sizeof(palavras[0]);

    printf("%d\n", n);
    printf("Inserindo palavras:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Inserindo %s\n", palavras[i]);
        Insere(palavras[i], p, Tabela);
    }

    

    printf("\nTabela Hash após inserções:\n");
    Imprime(Tabela);

    

    printf("\nPesquisando palavras:\n");
    for (int i = 0; i < n; i++)
    {
        if (Pesquisa(palavras[i], p, Tabela) != NULL)
            printf("Palavra %s encontrada.\n", palavras[i]);
        else
            printf("Palavra %s não encontrada.\n", palavras[i]);
    }

    printf("\nRemovendo algumas palavras:\n");
    for (int i = 0; i < n; i += 2)
    {
        printf("Removendo %s\n", palavras[i]);
        Retira(palavras[i], p, Tabela);
    }

    printf("\nTabela Hash após remoções:\n");
    Imprime(Tabela); */

