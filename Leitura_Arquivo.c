#include <stdio.h>
#include <string.h>
#include "Leitura_Arquivo.h"


#define MAX_FILENAME_LENGTH 100
#define MAX_CONTENT_LENGTH 1000
#define MAX_INGREDIENTS 48
#define MAX_INGREDIENT_LENGTH 100

int Contar_Ocorrencias(const char *string, const char *substring) {
    int count = 0;
    const char *temp = string;
    
    while ((temp = strstr(temp, substring)) != NULL) {
        count++;
        temp += strlen(substring); //Próxima contagem vai começar a partir de onde achou a primeira ocorrência :p
    }
    
    return count;
}

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

    // Ler a terceira linha e armazenar em modoPreparo
    if (fgets(modoPreparo, sizeof(modoPreparo), arquivo) == NULL) {
        perror("Erro ao ler o modo de preparo");
        fclose(arquivo);
        return;
    }
    modoPreparo[strcspn(modoPreparo, "\n")] = 0; // Remover nova linha

    // Fechar o arquivo após a leitura
    fclose(arquivo);

    // Exibir os resultados
    printf("Nome da Receita: %s\n", nomeReceita);

    for (int j = 0; j < i; j++) {
        printf("-%s\n", ingredientes[j]);
    }
    printf("Modo de Preparo: %s\n", modoPreparo);
    printf("testestestestes");
}
