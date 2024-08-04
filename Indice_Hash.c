/*
Alexia Karoline Augusta Germano Silva [EF05373] 
Ana Luisa Moreira Rodrigues [EF05389] 
Dalmo Nolasco Dantas Rainer [EF05361] 
Lucas da Costa Moreira [EF05377]
*/
#include "Indice_Hash.h"

void Imprimir_IndiceInvertido_Hash(char *ingrediente, TipoPesos p, Tabela_Hash *T)
{
    Apontador_Prox ap;
    To_Lower_Case(ingrediente);
    ap = Pesquisa_Hash(ingrediente, p, T);

    if (ap == NULL)
    {
        printf("O ingrediente não foi encontrado\n");
        return;
    }else
    {
        while (ap->Indices != NULL)
        {
            printf("<%d, %d> ", ap->Indices->qtde, ap->Indices->idDoc);
            ap->Indices = ap->Indices->proxInd;
        }
        printf("\n");   
    }
    
    //printf("Qtd,idDoc\n");
    //printf("%s: ", ingrediente);
}


