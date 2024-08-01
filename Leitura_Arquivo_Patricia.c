#include "Leitura_Arquivo_Patricia.h"

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

void lerEProcessarArquivo_Patricia(const char *nomeArquivo, TipoArvore Patricia) {
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
    //printf("Modo de Preparo: %s\n", modoPreparo);


    for (int k= 0; k < 46; k++)
    {
        //Não temos certeza se estamos armazenando corretamente no vetor ingredientes (quando tentatmos printar assim não funciona)
        //Executar o código para ver o problema.
        Remove_Espaco(ingredientes[k]);
        Remove_Pontuacao(ingredientes[k]);
        printf("PRINTANDO INGREDIENTE: numero %d - %s\n", k,ingredientes[k]);
        Insere(ingredientes[k], Patricia);

    }
    
}
