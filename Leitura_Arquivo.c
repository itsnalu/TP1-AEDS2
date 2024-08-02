#include "Leitura_Arquivo.h"

void To_Lower_Case(char *str)
{
    while (*str)
    {
        *str = tolower(*str);
        str++;
    }
}

void Inicializa_Campo(Campos_Arquivo Campo)
{
    Campo.ingredientes = NULL;
    Campo.receita = NULL;
    Campo.nIngredientes = 0;
}

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

void remover_espacos_fim(char *str) {
    int i = strlen(str) - 1;
    while (i >= 0 && str[i] == ' ') {
        str[i] = '\0';
        i--;
    }
}

// int Contar_Ocorrencias(const char *string, const char *substring)
// {
//     int count = 0;
//     const char *temp = string;

//     while ((temp = strstr(temp, substring)) != NULL)
//     {
//         count++;
//         temp += strlen(substring); // Próxima contagem vai começar a partir de onde achou a primeira ocorrência :p
//     }

//     return count;
// }


int Contar_Ingrediente(char* string,int tamanho){
    int count = 0;
    for (int i = 0; i < tamanho; i++)
    {
        if (string[i] == ';')   
        {
            count++;
        }
        
    }
    count++;
    return count;
}


int Compara_Caractere(const FILE *arq, const char *str)
{
    int count = 0;
    int tamanhoString = strlen(str);
    int ContadorCorrespondencia = 0;
    int caractere;

    FILE *arqCopy = (FILE *)arq;
    // Loop para ler o arquivo caractere por caractere
    while ((caractere = fgetc(arqCopy)) != EOF)
    {
        if (caractere == str[ContadorCorrespondencia])
        {
            // Se o caractere corresponde ao da string, incrementa o contador de correspondência
            ContadorCorrespondencia++;
            if (ContadorCorrespondencia == tamanhoString)
            {
                // Se todos os caracteres da string foram encontrados, incrementa o contador de ocorrências
                count++;
                ContadorCorrespondencia = 0; // Reinicia o contador de correspondência para procurar novas ocorrências
            }
        }
        else
        {
            // Se o caractere não corresponde, reinicia o contador de correspondência
            ContadorCorrespondencia = 0;
        }
    }

    return count;
}


int Contar_Ocorrencias(char *texto, char *ingrediente)
{
    int count = 0;
    int tamanhoIngrediente = strlen(ingrediente);
    char *posicao = texto;

    // Loop para ler o arquivo caractere por caractere
    while ((posicao = strstr(posicao, ingrediente)) != NULL)
    {
        // verifica se nas extremidades da string tem um espaço ou se é o final da string
        if ((posicao == texto || *(posicao - 1) == ' ') && (*(posicao + tamanhoIngrediente) == ' ' || *(posicao + tamanhoIngrediente) == '\0'))
        {
            count++;
        }
        posicao += tamanhoIngrediente;
    }

    return count;
}


char *Le_arquivo_inteiro(char *arquivo, int *tamanho)
{
    char *buffer = NULL;
    FILE *arq;

    arq = fopen(arquivo, "rb");
    if (arq == NULL)
    {
        printf("Não foi possível abrir o arquivo");
        return NULL;
    }
    fseek(arq, 0, SEEK_END);
    *tamanho = ftell(arq);
    fseek(arq, 0, SEEK_SET);

    buffer = (char *)malloc(*tamanho + 1);
    if (buffer == NULL)
    {
        printf("Não foi possível alocar memória");
        fclose(arq);
        return NULL;
    }

    fread(buffer, 1, *tamanho, arq);
    buffer[*tamanho] = '\0';

    fclose(arq);

    return buffer;
}

void Armazenar(char *nomeArquivo, TipoPesos p, Tabela_Hash *T)
{
    int tamanho, indice, count[3] = {1, 1, 1};
    char *vetor = Le_arquivo_inteiro(nomeArquivo, &tamanho);
    if (vetor == NULL)
    {
        perror("Erro ao ler o arquivo");
        return;
    }

    // conta o tamanho de cada linha dentro do vetor com todas as linhas
    indice = 0;
    for (int i = 0; i < tamanho; i++)
    {
        if (vetor[i] == '\n')
        {
            indice += 1;
        }
        count[indice] += 1;
    }

    char *linha = strtok(vetor, "\n");
    int linhaAtual = 0;

    char nome[count[0]];
    char ingredientes[count[1]];
    char instrucoes[count[2]];

    while (linha != NULL)
    {
        if (linhaAtual == 0)
        {
            strncpy(nome, linha, sizeof(nome) - 1);
            nome[sizeof(nome) - 1] = '\0'; // garante a terminação nula
        }
        else if (linhaAtual == 1)
        {
            strncpy(ingredientes, linha, sizeof(ingredientes) - 1);
            ingredientes[sizeof(ingredientes) - 1] = '\0'; // garante a terminação nula
        }
        else
        {
            strncat(instrucoes, linha, sizeof(instrucoes) - strlen(instrucoes) - 1);
            strncat(instrucoes, "\n", sizeof(instrucoes) - strlen(instrucoes) - 1);
        }

        linha = strtok(NULL, "\n");
        linhaAtual++;
    }
    printf("Nome:%s\n", nome);
    printf("Ingredientes:%s\n", ingredientes);
    printf("Instrucoes:%s\n", instrucoes);

    
    int qtdIngrediente = Contar_Ingrediente(ingredientes, count[1]);


    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL)
    {
        perror("Erro ao abrir o arquivo especificado");
        return;
    }
    //tamanho delimitado para o ingrediente
    char ingrediente_individual[40];
    //char *Ingrediente_tratado;
    //fgets(ingrediente_individual, 1000, arquivo);
    
    // //Descarta a primeira linha
    // char buffer[1024];
    // if (fgets(buffer, sizeof(buffer), arquivo) == NULL) {
    //     perror("Erro ao ler a primeira linha");

    // }

    while ((fscanf(arquivo, "%[^.;]", ingrediente_individual)) == 1)
    {
        //Ingrediente_tratado = strdup(ingrediente_individual);
        //remover_espacos_fim(Ingrediente_tratado);
        //printf("tamanho do ingrediente_tratado: %d\n",(40 - strlen(ingrediente_individual) + 1));
        Remove_Espaco(ingrediente_individual);
        To_Lower_Case(ingrediente_individual);
        Insere(ingrediente_individual, p, T);
    }


/*     char *CadaIngrediente;
    char *tempString = strdup(ingredientes);
    for (int i = 0; i < qtdIngrediente; i++)
    {
        //tempString = strdup(ingredientes);
        CadaIngrediente = strtok(tempString, ";");
        printf("Ingrediente atual: %s\n", CadaIngrediente);
        if (CadaIngrediente != NULL)
        {
            //To_Lower_Case(CadaIngrediente);
            //Remove_Espaco(CadaIngrediente);
            //Remove_Pontuacao(CadaIngrediente);
            Campos.ingredientes[i] = strdup(CadaIngrediente);        
        }
        free(tempString);
    }

    for (int i = 0; i < qtdIngrediente; i++)
    {
        printf("Ingrediente %d: %s\n", i + 1, Campos.ingredientes[i]);
    } */


    
    
    // while (fscanf(nomeArquivo, "%[^.;]", ingrediente) == 1) {
    //     qtd_ingrediente = 0;
    //     Letra_Minuscula(ingrediente);
    //     qtd_ingrediente = Frequencia_Ingrediente(receita_str, ingrediente);
        //printf("Qtd do ingrediente %s no doc(%d): %d\n", ingrediente, id_do
    // }
    
    // Liberar a memória alocada
    free(vetor);
}




/*
void lerEProcessarArquivo(const char *nomeArquivo, TipoPesos p, Tabela_Hash* T) {
    FILE *arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo especificado");
        return;
    }

    char nomeReceita[MAX_CONTENT_tamanho];
    char ingredientes[MAX_INGREDIENTS][MAX_INGREDIENT_tamanho];
    char modoPreparo[MAX_CONTENT_tamanho];


    // Ler a primeira linha e armazenar em nomeReceita
    if (fgets(nomeReceita, sizeof(nomeReceita), arquivo) == NULL) {
        perror("Erro ao ler o nome da receita");
        fclose(arquivo);
        return;
    }
    nomeReceita[strcspn(nomeReceita, "\n")] = 0; // Remover nova linha

    // Ler a segunda linha e separar os ingredientes por ponto e vírgula
    char linhaIngredientes[MAX_CONTENT_tamanho];
    if (fgets(linhaIngredientes, sizeof(linhaIngredientes), arquivo) == NULL) {
        perror("Erro ao ler os ingredientes");
        fclose(arquivo);
        return;
    }



    linhaIngredientes[strcspn(linhaIngredientes, "\n")] = 0; // Remover nova linha

    int i = 0;
    char *token = strtok(linhaIngredientes, ";");
    while (token != NULL && i < MAX_INGREDIENTS) {
        strncpy(ingredientes[i], token, MAX_INGREDIENT_tamanho - 1);
        ingredientes[i][MAX_INGREDIENT_tamanho - 1] = 0; // Garantir terminação nula
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



  */

/*
void lerEProcessarArquivo(const char *nomeArquivo, TipoPesos p, Tabela_Hash* T) {
    arq *arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo especificado");
        return;
    }


    char *nomeReceita = (char *)malloc(MAX_CONTENT_tamanho * sizeof(char));
    if (nomeReceita == NULL) {
        perror("Erro ao alocar memória para nomeReceita");
        fclose(arquivo);
        return;
    }

    // (fscanf(entrada, "%d", &numArquivos) != 1)

    char vetorIngrediente[MAX_INGREDIENTS][MAX_INGREDIENT_tamanho];
    char **ingredientes = (char **)malloc(MAX_INGREDIENTS * sizeof(char *));
    for (int i = 0; i < MAX_INGREDIENTS; i++) {
        ingredientes[i] = (char *)malloc(MAX_INGREDIENT_tamanho * sizeof(char));
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

    char *modoPreparo = (char *)malloc(MAX_CONTENT_tamanho * sizeof(char));
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
    if (fgets(nomeReceita, MAX_CONTENT_tamanho, arquivo) == NULL) {
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
    char linhaIngredientes[MAX_CONTENT_tamanho];
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
        strncpy(ingredientes[i], token, MAX_INGREDIENT_tamanho - 1);
        ingredientes[i][MAX_INGREDIENT_tamanho - 1] = 0; // Garantir terminação nula
        i++;
        token = strtok(NULL, ";");
    }

    // Ler a terceira linha e armazenar em modoPreparo
    if (fgets(modoPreparo, MAX_CONTENT_tamanho, arquivo) == NULL) {
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


/*

int contar_Elementos_Na_Linha(char* linha){
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

*/

/* void Remove_Pontuacao(char *str) {
    char *end = str + strlen(str) - 1;
    if (end >= str && (*end == '.')) {
        *end = '\0';
    }
}

int contar_Tamanho_Do_ModoPreparo(char* linha){
    int count = 0;
    char *token = strtok(linha, "\0");
    while (token != NULL) {
        return strlen(token);
    }
    return -1;
};


void Remove_Espaco(char *str) {
    if (str[0] == ' ') {
        memmove(str, str + 1, strlen(str));
    }
}
*/

/* void lerEProcessarArquivo(const char *nomeArquivo, TipoPesos p, Tabela_Hash* T) {
    arq *arquivo = fopen(nomeArquivo, "r");
    int tamanho_ingredientes;


    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo especificado");
        return;
    }

    printf("lalala2\n");
    // add mais 1 para contar o "/0" no final da string
    tamanho_ingredientes = (1 + contarCaracteresSegundaLinha(nomeArquivo));
    char ingredientes[tamanho_ingredientes];
    printf("lalala3\n");
    Campos_Arquivo campos;
    Inicializa_Campo(campos);
    printf("lalala4\n");
    if (tamanho_ingredientes == -1) {
        fclose(arquivo);
        return;
    }

    //char *ingredientes = (char *)malloc((tamanho_ingredientes + 1) * sizeof(char));
    if (ingredientes == NULL) {
        perror("Erro ao alocar memória para ingredientes");
        fclose(arquivo);
        return;
    }
    printf("lalala5\n");
    // Ler e descartar a primeira linha
    char linha[MAX_CONTENT_tamanho];
    if (fgets(linha, sizeof(linha), arquivo) == NULL) {
        perror("Erro ao ler a primeira linha");
        free(ingredientes);
        fclose(arquivo);
        return;
    }
    printf("lalala6\n");
    // Ler a segunda linha e armazenar em ingredientes
    if (fgets(ingredientes, tamanho_ingredientes + 1, arquivo) == NULL) {
        perror("Erro ao ler a segunda linha");
        free(ingredientes);
        fclose(arquivo);
        return;
    }

    fclose(arquivo);


    // Processar os ingredientes
    ingredientes[strcspn(ingredientes, "\n")] = '\0'; // Remover nova linha
    char *token = strtok(ingredientes, ";");
    printf("lala\n");
    while (token != NULL) {
        printf("tipado otario: %s\n", typeof(token));
        campos.nIngredientes++;
        printf("lalala8\n");
        campos.ingredientes = (char **)realloc(campos.ingredientes, campos.nIngredientes * sizeof(char *));
        printf("lalala9\n");
        campos.ingredientes[campos.nIngredientes - 1] = strdup(token);
        token = strtok(NULL, ";");
    }



    // Exibir os resultados
    printf("Nome da Receita: %s\n", campos.receita ? campos.receita : "Desconhecida");
    for (int i = 0; i < campos.nIngredientes; i++) {
        printf("Ingrediente %d: %s\n", i + 1, campos.ingredientes[i]);
        free(campos.ingredientes[i]); // Liberar a memória de cada ingrediente
    }
    free(campos.ingredientes); // Liberar a memória do vetor de ingredientes
    free(ingredientes); // Liberar a memória alocada para a linha de ingredientes

}
 */