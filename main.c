#include <stdio.h>
#include <stdlib.h>
#include "TAD_Tabela_Hash.h"
#include "Leitura_Arquivo.h"
#define MAX_FILENAME_LENGTH 100
#define MAX_CONTENT_LENGTH 1000

int main() {
    
    FILE *entrada;
    int numArquivos;
    char nomeArquivo[MAX_FILENAME_LENGTH];
    
    // Abrir o arquivo entrada.txt
    entrada = fopen("entrada.txt", "r");
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

    // Loop para ler e abrir cada arquivo especificado
    for (int i = 0; i < numArquivos; i++) {
        // Ler o nome do arquivo
        if (fscanf(entrada, "%s", nomeArquivo) != 1) {
            perror("Erro ao ler o nome do arquivo");
            fclose(entrada);
            return 1;
        }

        // Abrir o arquivo especificado
        FILE *arquivo = fopen(nomeArquivo, "r");
        if (arquivo == NULL) {
            perror("Erro ao abrir o arquivo especificado");
            continue;
        }

        // Ler o conteúdo do arquivo e armazenar em uma string (ou outra estrutura, conforme necessidade)
        char conteudo[MAX_CONTENT_LENGTH];
        while (fgets(conteudo, sizeof(conteudo), arquivo) != NULL) {
            // Aqui você pode processar o conteúdo do arquivo conforme necessário
            printf("Conteúdo do arquivo %s:\n%s\n", nomeArquivo, conteudo);
        }

        // Fechar o arquivo após a leitura
        fclose(arquivo);
    }

    // Fechar o arquivo entrada.txt
    fclose(entrada);

    return 0;
}