#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Leitura_Arquivo.c"
#include "TAD_Tabela_Hash.c"



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

        // Chamar a função para ler e processar o arquivo
        lerEProcessarArquivo(nomeArquivo);
    }



    // Fechar o arquivo entrada.txt
    fclose(entrada);


    Vetor Tabela;
    TipoPesos p;
    Inicializa(Tabela);
    
    printf("lala\n");
    GeraPesos(p);

    
    printf("lala\n");

    char* palavras[] = {"banana", "abacaxi", "uva", "manga", "laranja", "melancia", "cereja", "pera", "maçã", "pêssego"};
    int n = sizeof(palavras) / sizeof(palavras[0]);

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
    Imprime(Tabela);


    return 0;
}

