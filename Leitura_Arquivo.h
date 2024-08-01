#include "TAD_Tabela_Hash.h"

#define MAX_FILENAME_LENGTH 100
#define MAX_CONTENT_LENGTH 1000
#define MAX_INGREDIENTS 48
#define MAX_INGREDIENT_LENGTH 100

struct Campos_Arquivo
{
    /* Não sabemos se isso vai valer a pena,
    mas a struct vai ter todos os ingredientes e um campo de quantidade pra cada um deles
    usar função que conta os ingredientes de cada ingrediente na linha 
    */
    //char nome[MAX_INGREDIENT_LENGTH];
    //char ingredientes[MAX_INGREDIENTS][MAX_INGREDIENT_LENGTH];
    //int nIngredientes;
};


int Contar_Ocorrencias(const char *string, const char *substring);
void lerEProcessarArquivo(const char *nomeArquivo, TipoPesos p, Tabela_Hash* T);
void Remove_Espaco(char *str);
void Remove_Pontuacao(char *str);