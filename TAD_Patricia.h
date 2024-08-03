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
    } NO;
} TipoPatNo;

typedef struct Indice_Invertido* Apontador_Ind;
//typedef struct Tipo_Celula* Apontador_Prox;

typedef struct Indice_Invertido
{
    int qtde;
    int idDoc;
    Apontador_Ind proxInd;
} Indice_Invertido;

TipoArvore CriaNoExterno(Palavra chave);
TipoArvore CriaNoInterno(TipoIndexAmp index, TipoArvore *Esq, TipoArvore *Dir, unsigned char caractere);
TipoArvore InsereEntre(Palavra k, TipoArvore *t, int i, unsigned char caractere);
TipoArvore Insere(Palavra k, TipoArvore *t);
int Pesquisa(Palavra chave, TipoArvore t);
void Libera(TipoArvore t);
void ImprimeEmOrdemAux(TipoArvore t);
void ImprimeEmOrdem(TipoArvore t);

void ImprimeEmOrdemAuxComDirecao(TipoArvore t, const char* direcao);
void ImprimeEmOrdemComDirecao(TipoArvore t);

void ImprimeEmOrdemAuxComInternos(TipoArvore t);
void ImprimeEmOrdemComInternos(TipoArvore t);

#endif