#include <stdlib.h>
#include <sys/time.h>
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
        } NInterno; \\
        Palavra Chave;
    } NO;
} TipoPatNo;

typedef struct Indice_Invertido
{
    int qtde;
    int idDoc;
    Apontador_Ind proxInd;
} Indice_Invertido;

typedef struct Indice_Invertido* Apontador_Ind;
typedef struct Tipo_Celula* Apontador_Prox;
