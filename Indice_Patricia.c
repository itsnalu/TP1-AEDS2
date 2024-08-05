/*
Alexia Karoline Augusta Germano Silva [EF05373] 
Ana Luisa Moreira Rodrigues [EF05389] 
Dalmo Nolasco Dantas Rainer [EF05361] 
Lucas da Costa Moreira [EF05377]
*/

#include "Indice_Patricia.h"


// Inicia lista encadeada
void FLVazia(Lista_encadeada *Lista)
{
    Lista->primeiro = (Ponteiro_ind)malloc(sizeof(Celula_Indice_Invertido_Patricia));
    Lista->ultimo = Lista->primeiro;
    Lista->primeiro->prox = NULL;
}

int Vazia(Lista_encadeada Lista)
{
    return (Lista.primeiro == Lista.ultimo);
}

void InsereIndice(int quantidade, int idDoc, Lista_encadeada *Lista)
{
    Lista->ultimo->prox = (Ponteiro_ind)malloc(sizeof(Celula_Indice_Invertido_Patricia));
    Lista->ultimo = Lista->ultimo->prox;
    Lista->ultimo->item.idDoc = idDoc;
    Lista->ultimo->item.qtde = quantidade;
    Lista->ultimo->prox = NULL;
}

void Imprime_Lista(Lista_encadeada *Lista)
{
    Ponteiro_ind Aux;
    Aux = Lista->primeiro->prox;
    while (Aux != NULL)
    {
        printf("Documento ID: %d, Quantidade: %d\n", Aux->item.idDoc, Aux->item.qtde);
        Aux = Aux->prox;
    }
}

int Arquivo_Existe(Lista_encadeada *Lista, int idDoc){
    Ponteiro_ind Aux;
    Aux = Lista->primeiro->prox;
    while (Aux != NULL)
    {
        if(Aux->item.idDoc == idDoc){
            Aux->item.qtde++; //Palavra repete no mesmo documento
            return 1;
        }
        Aux = Aux->prox;
    }
    return 0;
}

int Busca_Repeticoes_Palavra(Lista_encadeada *Lista){

    Ponteiro_ind Aux;
    Aux = Lista->primeiro->prox;
    while (Aux != NULL)
    {
        printf("<Documento ID: %d, Quantidade: %d> ", Aux->item.idDoc, Aux->item.qtde);
        Aux = Aux->prox;
    }
    return 0;

}
