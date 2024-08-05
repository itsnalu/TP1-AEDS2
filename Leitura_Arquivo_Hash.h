/*
Alexia Karoline Augusta Germano Silva [EF05373] 
Ana Luisa Moreira Rodrigues [EF05389] 
Dalmo Nolasco Dantas Rainer [EF05361] 
Lucas da Costa Moreira [EF05377]
*/

#ifndef LEITURA_ARQUIVO_HASH_H
#define LEITURA_ARQUIVO_HASH_H

#include "TAD_Tabela_Hash.h"

#define typeof(var) _Generic( (var),\
char: "Char",\
int: "Integer",\
float: "Float",\
char *: "String",\
void *: "Pointer",\
default: "Undefined")


#define MAX_FILENAME_LENGTH 100
#define MAX_CONTENT_LENGTH 1000
#define MAX_INGREDIENTS 48
#define MAX_INGREDIENT_LENGTH 100

typedef struct Campos_Arquivo
{

    /* Não sabemos se isso vai valer a pena,
    mas a struct vai ter todos os ingredientes e um campo de quantidade pra cada um deles
    usar função que conta os ingredientes de cada ingrediente na linha 
    */
    char *receita;
    char **ingredientes;
    int nIngredientes;
    
} Campos_Arquivo;



char* Le_arquivo_inteiro(char *arquivo, int *tamanho);
int contarCaracteresSegundaLinha(const char *nomeArquivo);
void Inicializa_Campo(Campos_Arquivo Campo);
int Contar_Ocorrencias(char *texto, char *ingrediente);
int Contar_Ingrediente(char* string,int tamanho);
void Armazenar(char *nomeArquivo, TipoPesos p, Tabela_Hash *T, int j, int *termos_por_doc);  
void Remove_Espaco(char *str);
void Remove_Pontuacao(char *str);
void To_Lower_Case(char *str);
void Ocorrencias_Hash(char *texto, char *ingrediente, int j, TipoPesos p, Tabela_Hash *Tabela);


double calcularPesoTermo(int frequencia, int totalDocs, int numDocsComTermo) ;
double calcularRelevanciaDocumento(Tipo_Celula *celulaAtual, int totalDocs, int *totalTermosPorDoc);
void calcularTFIDFParaTodos(Tabela_Hash *tabela, int totalDocs, int *totalTermosPorDoc);
// double calcularTFIDF(int qtdeTermo, int totalTermos, int totalDocs, int docsComTermo);
// void calcularTFIDFParaTodos(Tabela_Hash *tabela, int totalDocs, int *totalTermosPorDoc);

#endif