/*
Alexia Karoline Augusta Germano Silva [EF05373] 
Ana Luisa Moreira Rodrigues [EF05389] 
Dalmo Nolasco Dantas Rainer [EF05361] 
Lucas da Costa Moreira [EF05377]
*/

#include "Leitura_Arquivo_Patricia.h"

#include <math.h>


void To_Lower_Case_Patricia(char *str)
{
    while (*str)
    {
        *str = tolower(*str);
        str++;
    }
}
void Remove_Pontuacao_Patricia(char *str) {
    char *end = str + strlen(str) - 1;
    if (end >= str && (*end == '.')) {
        *end = '\0';
    }
}

void Remove_Espaco_Patricia(char *str) {
    if (str[0] == ' ') {
        memmove(str, str + 1, strlen(str));
    }
}

int Contar_Ingrediente_Patricia(char* string,int tamanho){
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




char *Le_arquivo_inteiro_Patricia(char *arquivo, int *tamanho)
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

void Armazenar_Patricia(char *nomeArquivo, TipoArvore *patricia, int j)
{
    int tamanho, indice, count[3] = {1, 1, 1};
    char *vetor = Le_arquivo_inteiro_Patricia(nomeArquivo, &tamanho);
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
    /* printf("Nome:%s\n", nome);
    printf("Ingredientes:%s\n", ingredientes);
    printf("Instrucoes:%s\n", instrucoes); */

    To_Lower_Case_Patricia(instrucoes);
    To_Lower_Case_Patricia(nome);
    
    int qtdIngrediente = Contar_Ingrediente_Patricia(ingredientes, count[1]);


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
        //printf("Ingrediente:%s\n", ingrediente_individual);
        To_Lower_Case_Patricia(ingrediente_individual);
        Remove_Pontuacao_Patricia(ingrediente_individual);
        //printf("Ingrediente tratado: %s\n", ingrediente_individual);
        *(patricia) = Insere(ingrediente_individual, patricia, j);
    
        Ocorrencias_Patricia(instrucoes, ingrediente_individual, j, *(patricia));


        // Obter o próximo ingrediente
        ingrediente_individual = strtok(NULL, ";");
    }

}

int Contar_Ocorrencias_Patricia(char *texto, char *ingrediente)
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

void Ocorrencias_Patricia(char *texto, char *ingrediente, int j, TipoArvore patricia){
    int count = 0; //Inicializado com 1, já que todo ingrediente já vai estar no arquivo pelo menos uma vez (na lista de ingredientes)
    int Doc_id;
    TipoArvore ap;
    Doc_id = j;
    count += Contar_Ocorrencias_Patricia(texto, ingrediente);

    // precisa alterar a funçao pesquisa para retornar o nó
    ap =  Pesquisa(ingrediente, patricia);

    // InsereIndice_Invertido(count, Doc_id, &(ap->Indices));
    if (ap != NULL) { // Verifica se o ingrediente foi encontrado
        Adiciona_Indice(count, Doc_id, ap->Lista_ind);
    } else {
        // printf("O ingrediente %s não foi encontrado\n", ingrediente);
        return;
    }
    // printf("O ingrediente %s aparece %d vezes na receita %d\n", ingrediente, count, Doc_id);



    // printf("O ingrediente %s aparece %d vezes na receita %d\n", ingrediente, count, Doc_id);

} 


double calcularPesoTermo_Pat(int frequencia, int totalDocs, int numDocsComTermo) {
    return frequencia * log10((double)totalDocs / (double)numDocsComTermo);
}


// Função para calcular a relevância do documento (r(i))
double calcularRelevanciaDocumento_Pat(TipoArvore patricia, int totalDocs, int *totalTermosPorDoc) {
    double somaPesos = 0.0;
    Celula_Indice_Invertido_Patricia *indiceAtual = patricia->Lista_ind->primeiro->prox;

    while (indiceAtual != NULL) {
        int f_ji = indiceAtual->item.qtde;
        int idDoc = indiceAtual->item.idDoc;
        int totalTermosDistintos = totalTermosPorDoc[idDoc - 1]; // Utiliza o vetor totalTermosPorDoc
        int docsComTermo = contarDocsComTermo_Pat(indiceAtual);

        double pesoTermo = calcularPesoTermo_Pat(f_ji, totalDocs, docsComTermo);
        somaPesos += pesoTermo;
        indiceAtual = indiceAtual->prox;
    }

    return somaPesos;
}


void calcularTFIDFParaTodos_Pat(TipoArvore patricia, int totalDocs, int *totalTermosPorDoc) {
    if (patricia == NULL) {
        return;
    }
    
    // Verifica se o nó é interno
    if (patricia->nt == Interno) {
        // Chamada recursiva para subárvores esquerda e direita
        calcularTFIDFParaTodos_Pat(patricia->NO.NInterno.Esq, totalDocs, totalTermosPorDoc);
        calcularTFIDFParaTodos_Pat(patricia->NO.NInterno.Dir, totalDocs, totalTermosPorDoc);
    } else { // Nó é externo
        printf("Palavra: %s\n", patricia->NO.Chave);
        
        // Inicializa a lista encadeada de índices invertidos
        Ponteiro_ind indiceAtual = patricia->Lista_ind->primeiro->prox;

        while (indiceAtual != NULL) {
            printf("Ingrediente %s Documento %d: %d\n", patricia->NO.Chave, indiceAtual->item.idDoc, indiceAtual->item.qtde);
            indiceAtual = indiceAtual->prox;
        }

        // Calcula a relevância do documento
        double relevanciaDocumento = calcularRelevanciaDocumento_Pat(patricia, totalDocs, totalTermosPorDoc);
        printf("Relevancia do documento para a palavra '%s': %lf\n", patricia->NO.Chave, relevanciaDocumento);
    }
}
