/*
Alexia Karoline Augusta Germano Silva [EF05373] 
Ana Luisa Moreira Rodrigues [EF05389] 
Dalmo Nolasco Dantas Rainer [EF05361] 
Lucas da Costa Moreira [EF05377]
*/

#ifndef TAD_TABELA_HASH_H
#define TAD_TABELA_HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <ctype.h> // biblioteca para tolower
#include <math.h> // biblioteca para pow

//#include "Indice_Hash.h"

#define N 46
//Utilizando a formula para calcular o M = alpha/N, sendo alpha 3 e N 46
// O resultado deu ~15,333 e foi arredondado para 17 (o número primo mais próximo)
#define M 17
#define TAMALFABETO 256



/* typedef unsigned int  TipoPesos[n]; */
typedef char* Palavra_Hash;

typedef struct Indice_Invertido
{
    int qtde;
    int idDoc;
    struct Indice_Invertido* proxInd;
} Indice_Invertido;

typedef struct Tipo_Celula* Apontador_Prox;

typedef struct Tipo_Celula
{
    Palavra_Hash Ingrediente;
    struct Tipo_Celula *Prox;
    struct Indice_Invertido* Indices;
} Tipo_Celula;

typedef struct Tabela_Hash
{
    Tipo_Celula *Primeiro, *Ultimo;
} Tabela_Hash;

typedef unsigned TipoPesos[N][TAMALFABETO];
typedef unsigned int Tipo_Indice;
typedef Tipo_Celula* Apontador_Prox;
typedef Tabela_Hash Vetor[M];

typedef unsigned int TipoIndice;


void InicializaVetor(Vetor T);
void FIndice_Invertido(Indice_Invertido *Lista);
void InsereIndice_Invertido(int qtde, int idDoc, Indice_Invertido **Lista);
void FL_Vazia(Tabela_Hash *Lista);
short Vazia(Tabela_Hash Lista);
void Ins(Palavra_Hash x, Tabela_Hash *Lista);
void Ret(Apontador_Prox p, Tabela_Hash *Lista, Palavra_Hash *Ingrediente);
void GeraPesos(TipoPesos p);
TipoIndice h(Palavra_Hash Chave, TipoPesos p);
void Inicializa(Vetor T);
Apontador_Prox Pesquisa_Hash(Palavra_Hash Ch, TipoPesos p, Vetor T);
//Tipo_Celula Busca_Hash(Palavra_Hash Ch, TipoPesos p, Vetor T);
void Insere_Hash(Palavra_Hash x, TipoPesos p, Vetor T);
void Retira(Palavra_Hash x, TipoPesos p, Vetor T);
void Imp(Tabela_Hash Lista);
void Imprime(Vetor Tabela);

#endif