/*
Alexia Karoline Augusta Germano Silva [EF05373] 
Ana Luisa Moreira Rodrigues [EF05389] 
Dalmo Nolasco Dantas Rainer [EF05361] 
Lucas da Costa Moreira [EF05377]
*/
#include "Indice_Hash.h"

void Imprimir_IndiceInvertido_Hash(char *ingrediente, TipoPesos p, Tabela_Hash *T)
{
    Apontador_Prox apAUX;
    To_Lower_Case(ingrediente);
    apAUX = Pesquisa_Hash(ingrediente, p, T);
    Apontador_Prox ap;

    if (ingrediente[0] == '0')
    {
        return;
    }
    
    if (apAUX == NULL)
    {
        printf("O ingrediente não foi encontrado\n");
        return;
    }
    
    memcpy(ap, apAUX, sizeof(Tipo_Celula));

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
    

}

int contarDocsComTermo(Indice_Invertido *indiceAtual) {
    int docsComTermo = 0;
    Indice_Invertido *aux = indiceAtual;
    while (aux != NULL) {
        if (aux->qtde > 0) {
            docsComTermo++;
        }
        aux = aux->proxInd;
    }
    return docsComTermo;
}


void imprimirIngredientes(Tabela_Hash *tabela, int totalDocs) {
    for (int i = 0; i < M; i++) {
        // Verifica se a posição da tabela não é nula
        if (tabela[i].Primeiro != NULL) {
            Tipo_Celula *celulaAtual = tabela[i].Primeiro->Prox;

            // Percorre a lista ligada de ingredientes
            while (celulaAtual != NULL) {
                printf("Celula atual: %s\n", celulaAtual->Ingrediente);

                Indice_Invertido *indiceAtual = celulaAtual->Indices;
                while (indiceAtual != NULL) {
                    printf("Ingrediente %s Documento %d: %d\n", celulaAtual->Ingrediente, indiceAtual->idDoc, indiceAtual->qtde);
                    indiceAtual = indiceAtual->proxInd;
                }

                celulaAtual = celulaAtual->Prox;
            }
        }
    }
}


    //printf("Qtd,idDoc\n");
    //printf("%s: ", ingrediente);


