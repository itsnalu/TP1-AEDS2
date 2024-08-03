#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <ctype.h> // biblioteca para tolower
#define N 46
//Utilizando a formula para calcular o M = alpha/N, sendo alpha 3 e N 46
// O resultado deu ~15,333 e foi arredondado para 17 (o número primo mais próximo)
#define M 17
#define TAMALFABETO 256



/* typedef unsigned int  TipoPesos[n]; */
typedef char* Palavra;

typedef struct Indice_Invertido
{
    int qtde;
    int idDoc;
    struct Indice_Invertido* proxInd;
} Indice_Invertido;

typedef struct Tipo_Celula* Apontador_Prox;

typedef struct Tipo_Celula
{
    Palavra Ingrediente;
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



void FIndice_Invertido(Indice_Invertido *Lista);
void InsereIndice_Invertido(int qtde, int idDoc, Indice_Invertido **Lista);
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

