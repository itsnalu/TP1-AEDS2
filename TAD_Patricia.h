/*
Alexia Karoline Augusta Germano Silva [EF05373] 
Ana Luisa Moreira Rodrigues [EF05389] 
Dalmo Nolasco Dantas Rainer [EF05361] 
Lucas da Costa Moreira [EF05377]
*/

#ifndef TAD_PATRICIA_H
#define TAD_PATRICIA_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <ctype.h> // biblioteca para tolower
#define D 8 /* depende de TipoChave */


typedef unsigned char* Palavra; /* a definir, dependendo da aplicacao */
typedef unsigned char TipoIndexAmp;
typedef unsigned char TipoDib;
typedef enum
{
    Interno,
    Externo
} TipoNo;
typedef struct TipoPatNo *TipoArvore;
typedef struct TipoPatNo
{
    TipoNo nt;
    union
    {
        struct
        {
            TipoIndexAmp Index;
            TipoArvore Esq, Dir;
            unsigned char Caractere;
        } NInterno;
        Palavra Chave;
        // struct Indice_Invertido_Patricia *Indices;
    } NO;
    
} TipoPatNo;

typedef struct Indice_Invertido* Apontador_Ind;
//typedef struct Tipo_Celula* Apontador_Prox;

typedef struct Indice_Invertido_Patricia
{
    int qtde; //Quantidade de repeticoes
    int idDoc; //identificador do document
    Apontador_Ind *proxInd;
} Indice_Invertido_Patricia;

TipoArvore CriaNoExterno(Palavra chave);
TipoArvore CriaNoInterno(TipoIndexAmp index, TipoArvore *Esq, TipoArvore *Dir, unsigned char caractere);
TipoArvore InsereEntre(Palavra k, TipoArvore *t, int i, unsigned char caractere);
TipoArvore Insere(Palavra k, TipoArvore *t);
void Pesquisa(Palavra chave, TipoArvore t);
void Libera(TipoArvore t);

void ImprimeEmOrdemAux(TipoArvore t);
void ImprimeEmOrdem(TipoArvore t);

void ImprimeEmOrdemAuxComInternos(TipoArvore t);
void ImprimeEmOrdemComInternos(TipoArvore t);

int ArvoreVazia(TipoArvore t);

#endif