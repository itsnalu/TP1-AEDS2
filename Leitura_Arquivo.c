#include "Leitura_Arquivo.h"

void Remove_Pontuacao(char *str) {
    char *end = str + strlen(str) - 1;
    if (end >= str && (*end == '.')) {
        *end = '\0';
    }
}

void Remove_Espaco(char *str) {
    if (str[0] == ' ') {
        memmove(str, str + 1, strlen(str));
    }
}

int Contar_Ocorrencias(const char *string, const char *substring) {
    int count = 0;
    const char *temp = string;
    
    while ((temp = strstr(temp, substring)) != NULL) {
        count++;
        temp += strlen(substring); //Próxima contagem vai começar a partir de onde achou a primeira ocorrência :p
    }
    
    return count;
}

void lerEProcessarArquivo(const char *nomeArquivo, TipoPesos p, Tabela_Hash* T) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo especificado");
        return;
    }

    char nomeReceita[MAX_CONTENT_LENGTH];
    char ingredientes[MAX_INGREDIENTS][MAX_INGREDIENT_LENGTH];
    char modoPreparo[MAX_CONTENT_LENGTH];

    // char *nomeReceita;
    // char *ingredientes;
    // char *modoPreparo;

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


    for (int k= 0; k < 46; k++)
    {
        //Não temos certeza se estamos armazenando corretamente no vetor ingredientes (quando tentatmos printar assim não funciona)
        //Executar o código para ver o problema.
        Remove_Espaco(ingredientes[k]);
        Remove_Pontuacao(ingredientes[k]);
        printf("%s\n", ingredientes[k]);
        //Insere(ingredientes[k], p, T);
        //printf("-%d\n", k);
    }
    
}


void lerEProcessarArquivo(const char *nomeArquivo, TipoPesos p, Tabela_Hash* T) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo especificado");
        return;
    }


    char *nomeReceita = (char *)malloc(MAX_CONTENT_LENGTH * sizeof(char));
    if (nomeReceita == NULL) {
        perror("Erro ao alocar memória para nomeReceita");
        fclose(arquivo);
        return;
    }

    char **ingredientes = (char **)malloc(MAX_INGREDIENTS * sizeof(char *));
    for (int i = 0; i < MAX_INGREDIENTS; i++) {
        ingredientes[i] = (char *)malloc(MAX_INGREDIENT_LENGTH * sizeof(char));
        if (ingredientes[i] == NULL) {
            perror("Erro ao alocar memória para ingredientes");
            for (int j = 0; j < i; j++) {
                free(ingredientes[j]);
            }
            free(ingredientes);
            free(nomeReceita);
            fclose(arquivo);
            return;
        }
    }

    char *modoPreparo = (char *)malloc(MAX_CONTENT_LENGTH * sizeof(char));
    if (modoPreparo == NULL) {
        perror("Erro ao alocar memória para modoPreparo");
        for (int i = 0; i < MAX_INGREDIENTS; i++) {
            free(ingredientes[i]);
        }
        free(ingredientes);
        free(nomeReceita);
        fclose(arquivo);
        return;
    }

    // Ler a primeira linha e armazenar em nomeReceita
    if (fgets(nomeReceita, MAX_CONTENT_LENGTH, arquivo) == NULL) {
        perror("Erro ao ler o nome da receita");
        for (int i = 0; i < MAX_INGREDIENTS; i++) {
            free(ingredientes[i]);
        }
        free(ingredientes);
        free(nomeReceita);
        free(modoPreparo);
        fclose(arquivo);
        return;
    }
    nomeReceita[strcspn(nomeReceita, "\n")] = 0; // Remover nova linha

    // Ler a segunda linha e separar os ingredientes por ponto e vírgula
    char linhaIngredientes[MAX_CONTENT_LENGTH];
    if (fgets(linhaIngredientes, sizeof(linhaIngredientes), arquivo) == NULL) {
        perror("Erro ao ler os ingredientes");
        for (int i = 0; i < MAX_INGREDIENTS; i++) {
            free(ingredientes[i]);
        }
        free(ingredientes);
        free(nomeReceita);
        free(modoPreparo);
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
    if (fgets(modoPreparo, MAX_CONTENT_LENGTH, arquivo) == NULL) {
        perror("Erro ao ler o modo de preparo");
        for (int i = 0; i < MAX_INGREDIENTS; i++) {
            free(ingredientes[i]);
        }
        free(ingredientes);
        free(nomeReceita);
        free(modoPreparo);
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

    // Liberar a memória alocada
    free(nomeReceita);
    for (int i = 0; i < MAX_INGREDIENTS; i++) {
        free(ingredientes[i]);
    }
    free(ingredientes);
    free(modoPreparo);
}
/* int contar_Elementos_Na_Linha(char* linha){
    int count = 0;
    char *token = strtok(linha, ";");
    while (token != NULL) {
        count++;
        token = strtok(NULL, ";");
    }
    return count;
};


int contar_Tamanho_Do_Ingrediente(char* linha, int qualIngrediente){
    int count = 0;
    char *token = strtok(linha, ";");
    while (token != NULL) {
        if (count == qualIngrediente){
            return strlen(token);
        }
        count++;
        token = strtok(NULL, ";");
    }
    return -1;
};

int contar_Tamanho_Do_ModoPreparo(char* linha){
    int count = 0;
    char *token = strtok(linha, "\0");
    while (token != NULL) {
        return strlen(token);
    }
    return -1;
};
 */
