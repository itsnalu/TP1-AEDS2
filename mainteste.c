#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Leitura_Arquivo.c"

#define MAX_FILENAME_LENGTH 100
#define MAX_CONTENT_LENGTH 1000
#define MAX_INGREDIENTS 100
#define MAX_INGREDIENT_LENGTH 100


void lerEProcessarArquivo(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo especificado");
        return;
    }

    char nomeReceita[MAX_CONTENT_LENGTH];
    char ingredientes[MAX_INGREDIENTS][MAX_INGREDIENT_LENGTH];
    char modoPreparo[MAX_CONTENT_LENGTH];

    // Ler a primeira linha e armazenar em nomeReceita
    if (fgets(nomeReceita, sizeof(nomeReceita), arquivo) == NULL) {
        perror("Erro ao ler o nome da receita");
        fclose(arquivo);
        return;
    }
    nomeReceita[strcspn(nomeReceita, "\n")] = 0; // Remover nova linha

    // Remover stop words do nome da receita
    char *nomeReceitaSemStopWords = removeStopWords(nomeReceita);

    // Ler a segunda linha e separar os ingredientes por ponto e vírgula
    char linhaIngredientes[MAX_CONTENT_LENGTH];
    if (fgets(linhaIngredientes, sizeof(linhaIngredientes), arquivo) == NULL) {
        perror("Erro ao ler os ingredientes");
        fclose(arquivo);
        return;
    }
    linhaIngredientes[strcspn(linhaIngredientes, "\n")] = 0; // Remover nova linha

    int i = 0;
    char *token = strtok(linhaIngredientes, ";");
    while (token != NULL && i < MAX_INGREDIENTS) {
        strncpy(ingredientes[i], token, MAX_INGREDIENT_LENGTH - 1);
        ingredientes[i][MAX_INGREDIENT_LENGTH - 1] = 0; // Garantir terminação nula
        i++;
        token = strtok(NULL, ";");
    }

    // Remover stop words de cada ingrediente
    for (int j = 0; j < i; j++) {
        char *ingredienteSemStopWords = removeStopWords(ingredientes[j]);
        strncpy(ingredientes[j], ingredienteSemStopWords, MAX_INGREDIENT_LENGTH - 1);
        ingredientes[j][MAX_INGREDIENT_LENGTH - 1] = '\0'; // Garantir terminação nula
        free(ingredienteSemStopWords);
    }

    // Ler a terceira linha e armazenar em modoPreparo
    if (fgets(modoPreparo, sizeof(modoPreparo), arquivo) == NULL) {
        perror("Erro ao ler o modo de preparo");
        fclose(arquivo);
        return;
    }
    modoPreparo[strcspn(modoPreparo, "\n")] = 0; // Remover nova linha

    // Remover stop words do modo de preparo
    char *modoPreparoSemStopWords = removeStopWords(modoPreparo);

    // Fechar o arquivo após a leitura
    fclose(arquivo);

    // Exibir os resultados
    printf("Nome da Receita: %s\n", nomeReceitaSemStopWords);

    for (int j = 0; j < i; j++) {
        printf("- %s\n", ingredientes[j]);
    }
    printf("Modo de Preparo: %s\n", modoPreparoSemStopWords);

    // Liberar a memória alocada
    free(nomeReceitaSemStopWords);
    free(modoPreparoSemStopWords);
}

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

    return 0;
}
