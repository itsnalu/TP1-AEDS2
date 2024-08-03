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
    
    // if (tamanhoTexto < tamanhoIngrediente)
    // {
    //     return 0;
    // }
    

    char *posicao = texto;

    // Loop para ler o arquivo caractere por caractere
    while ((posicao = strstr(posicao, ingrediente)) != NULL)
    {
        // verifica se nas extremidades da string tem um espaço ou se é o final da string
        if ((posicao == texto || *(posicao - 1) == ' ') && (*(posicao + tamanhoIngrediente) == ' ' || *(posicao + tamanhoIngrediente) == '\0' || *(posicao + tamanhoIngrediente) == ';'))
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

void Armazenar(char *nomeArquivo, TipoPesos p, Tabela_Hash *T, int j)
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

    To_Lower_Case(instrucoes);
    To_Lower_Case(nome);
    
    int qtdIngrediente = Contar_Ingrediente(ingredientes, count[1]);


    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL)
    {
        perror("Erro ao abrir o arquivo especificado");
        return;
    }

    
    
    
    //Descarta a primeira linha
    //count[1] é o tamanho da string ingredientes
    //subtrai 2 para não pegar o \n e o \0
    char tamanho_ingredientes[count[1] - 2];
    char *ingrediente_individual;
    if (fgets(tamanho_ingredientes, sizeof(tamanho_ingredientes), arquivo) == NULL) {
        perror("Erro ao ler a primeira linha");
    }
    


    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    printf("LAUALUA\n");
    // Leia o conteúdo inteiro do arquivo
    size_t tamanhos = fread(tamanho_ingredientes, 1, sizeof(tamanho_ingredientes) - 1, arquivo);
    tamanho_ingredientes[tamanhos] = '\0'; // Garantir que o buffer é uma string válida

    // Use strtok para separar os ingredientes pelo delimitador ';'
    memset(ingrediente_individual, '\0', 40);
    ingrediente_individual = strtok(tamanho_ingredientes, ";");
    while (ingrediente_individual != NULL) {
        // Remover espaços em branco iniciais e finais
        while (*ingrediente_individual == ' ') {
            ingrediente_individual++;
        }
        char *fim = ingrediente_individual + strlen(ingrediente_individual) - 1;
        while (fim > ingrediente_individual && *fim == ' ') {
            *fim = '\0';
            fim--;
        }
        
        // Processar o ingrediente individual
        printf("Ingrediente:%s\n", ingrediente_individual);
        To_Lower_Case(ingrediente_individual);
        Remove_Pontuacao(ingrediente_individual);
        printf("Ingrediente tratado: %s\n", ingrediente_individual);
        Insere(ingrediente_individual, p, T);
        printf("LAUALUA\n");
        Ocorrencias_Hash(instrucoes, nome, ingrediente_individual, j, p, T);
        printf("LAUALUA\n");

        // Obter o próximo ingrediente
        ingrediente_individual = strtok(NULL, ";");
    }

}

void Ocorrencias_Hash(char *texto, char *nome, char *ingrediente, int j, TipoPesos p, Tabela_Hash *Tabela){
    int count = 1; //Inicializado com 1, já que todo ingrediente já vai estar no arquivo pelo menos uma vez (na lista de ingredientes)
    int Doc_id;
    Apontador_Prox ap;
    Doc_id = j;
    count += Contar_Ocorrencias(texto, ingrediente);

    ap = Pesquisa(ingrediente, p, Tabela); 

    InsereIndice_Invertido(count, Doc_id, &(ap->Indices));

    printf("O ingrediente %s aparece %d vezes na receita %d\n", ingrediente, count, Doc_id);


}

    // memset(ingrediente_individual, '\0', 40);
    // printf("antes do scanf arquivo %s\n", nomeArquivo);
    // int contagem = 0;
    // while (contagem < qtdIngrediente)
    // {
    //     fscanf(arquivo, "%[^.;]", ingrediente_individual);
        
    //     //Ingrediente_tratado = strdup(ingrediente_individual);
    //     //remover_espacos_fim(Ingrediente_tratado);
    //     //printf("tamanho do ingrediente_tratado: %d\n",(40 - strlen(ingrediente_individual) + 1));
    //     printf("Ingrediente: %s\n", ingrediente_individual);
    //     Remove_Espaco(ingrediente_individual);
    //     To_Lower_Case(ingrediente_individual);
    //     printf("Ingrediente tratado: %s\n", ingrediente_individual);
    //     Insere(ingrediente_individual, p, T);
    //     memset(ingrediente_individual, '\0', 40);
    //     contagem++;
    // }