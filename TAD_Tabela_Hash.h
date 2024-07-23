#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#define M 7
#define N 7      
#define TAMALFABETO 256


/* typedef unsigned int  TipoPesos[n]; */
typedef char Palavra[50];

typedef struct Indice_Invertido
{
    int qtde;
    int idDoc;
    Apontador_Ind proxInd;
} Indice_Invertido;

typedef struct Indice_Invertido* Apontador_Ind;
typedef struct Tipo_Celula* Apontador_Prox;

typedef struct Tipo_Celula
{
    Palavra Ingrediente;
    struct Tipo_Celula *Prox;
    Apontador_Ind Indices;
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



Vetor Tabela;
Tipo_Celula Elemento;
TipoPesos p;
Apontador_Prox i;


void to_Lower_Case(char *str);
void FL_Vazia(Tabela_Hash *Lista);
short Vazia(Tabela_Hash Lista);
void Ins(Palavra x, Tabela_Hash *Lista);
void Ret(Apontador_Prox p, Tabela_Hash *Lista, Palavra *Ingrediente);
void GeraPesos(TipoPesos p);
TipoIndice h(Palavra Chave, TipoPesos p);
void Inicializa(Vetor T);
Apontador_Prox Pesquisa(Palavra Ch, TipoPesos p, Vetor T);
void Insere(Palavra x, TipoPesos p, Vetor T);
void Retira(Palavra x, TipoPesos p, Vetor T);
void Imp(Tabela_Hash Lista);
void Imprime(Vetor Tabela);

