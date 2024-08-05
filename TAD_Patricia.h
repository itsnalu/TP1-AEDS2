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
    struct Lista_encadeada_Indice_Invertido_Patricia *Lista_ind;
} TipoPatNo;




TipoArvore CriaNoExterno(Palavra chave, int idDoc);
TipoArvore CriaNoInterno(TipoIndexAmp index, TipoArvore *Esq, TipoArvore *Dir, unsigned char caractere);
TipoArvore InsereEntre(Palavra k, TipoArvore *t, int i, unsigned char caractere, int idDoc);
TipoArvore Insere(Palavra k, TipoArvore *t, int idDoc);
TipoArvore Pesquisa(Palavra chave, TipoArvore t);
void Libera(TipoArvore t);

void ImprimeEmOrdemAux(TipoArvore t);
void ImprimeEmOrdem(TipoArvore t);

void ImprimeEmOrdemAuxComInternos(TipoArvore t);
void ImprimeEmOrdemComInternos(TipoArvore t);

void Busca_Palavra_Indice(Palavra palavra, TipoArvore p);

#endif
