/*
Alexia Karoline Augusta Germano Silva [EF05373] 
Ana Luisa Moreira Rodrigues [EF05389] 
Dalmo Nolasco Dantas Rainer [EF05361] 
Lucas da Costa Moreira [EF05377]
*/

#include "Indice_Patricia.h"

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

void Ocorrencias_Patricia(char *texto, char *nome, char *ingrediente, int j, TipoArvore patricia){
    int count = 1; //Inicializado com 1, já que todo ingrediente já vai estar no arquivo pelo menos uma vez (na lista de ingredientes)
    int Doc_id;
    TipoArvore ap;
    Doc_id = j;
    count += Contar_Ocorrencias_Patricia(texto, ingrediente);

    // precisa alterar a funçao pesquisa para retornar o nó
    // ap =  Pesquisa(ingrediente, patricia);

    // InsereIndice_Invertido(count, Doc_id, &(ap->Indices));

    printf("O ingrediente %s aparece %d vezes na receita %d\n", ingrediente, count, Doc_id);

} 


// void Imprimir_IndiceInvertido_Patricia(char *ingrediente, TipoPesos p, Tabela_Hash *T)
// {
//     // Apontador_Prox ap;
//     // ap = Pesquisa(ingrediente, p, T);

//     // if (ap == NULL)
//     // {
//     //     printf("O ingrediente %s não foi encontrado\n", ingrediente);
//     //     return;
//     // }
//     // printf("Qtd,idDoc\n");
//     // printf("%s: ", ingrediente);
//     // while (ap->Indices != NULL)
//     // {
//     //     printf("<%d, %d> ", ap->Indices->qtde, ap->Indices->idDoc);
//     //     ap->Indices = ap->Indices->proxInd;
//     // }
//     // printf("\n");
// }