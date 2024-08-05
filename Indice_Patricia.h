/*
Alexia Karoline Augusta Germano Silva [EF05373] 
Ana Luisa Moreira Rodrigues [EF05389] 
Dalmo Nolasco Dantas Rainer [EF05361] 
Lucas da Costa Moreira [EF05377]
*/

#ifndef INDICE_PATRICIA_H
#define INDICE_PATRICIA_H
#include <stdio.h>
#include <stdlib.h>
//#include "Leitura_Arquivo_Patricia.h"

typedef struct Item_Indice_Invertido_Patricia
{
    int qtde; // Quantidade de repeticoes
    int idDoc; // identificador do documento
} Item_Indice_Invertido_Patricia;

typedef struct Celula_Indice_Invertido_Patricia *Ponteiro_ind;
typedef struct Celula_Indice_Invertido_Patricia
{
    Item_Indice_Invertido_Patricia item;
    Ponteiro_ind prox;
} Celula_Indice_Invertido_Patricia;

typedef struct Lista_encadeada_Indice_Invertido_Patricia
{
    Ponteiro_ind primeiro, ultimo;
} Lista_encadeada;


//int Contar_Ocorrencias_Patricia(char *texto, char *ingrediente);
void FLVazia(Lista_encadeada *Lista);
int Vazia(Lista_encadeada Lista);
void InsereIndice(int quantidade, int idDoc, Lista_encadeada *Lista);
void Imprime_Lista(Lista_encadeada *Lista);
int Arquivo_Existe(Lista_encadeada *Lista, int idDoc);
int Busca_Repeticoes_Palavra(Lista_encadeada *Lista);

//void Ocorrencias_Patricia(char *texto, char *nome, char *ingrediente, int j, TipoArvore patricia);

#endif