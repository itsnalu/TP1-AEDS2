/*
Alexia Karoline Augusta Germano Silva [EF05373] 
Ana Luisa Moreira Rodrigues [EF05389] 
Dalmo Nolasco Dantas Rainer [EF05361] 
Lucas da Costa Moreira [EF05377]
*/

#ifndef LEITURA_ARQUIVO_PATRICIA_H
#define LEITURA_ARQUIVO_PATRICIA_H

#include "TAD_Patricia.h"
#include "Indice_Patricia.h"

#define MAX_FILENAME_LENGTH 100
#define MAX_CONTENT_LENGTH 1000
#define MAX_INGREDIENTS 48
#define MAX_INGREDIENT_LENGTH 100



void Remove_Espaco_Patricia(char *str);
void Remove_Pontuacao_Patricia(char *str);
void Armazenar_Patricia(char *nomeArquivo, TipoArvore *patricia, int j);
void To_Lower_Case_Patricia(char *str);
int Contar_Ingrediente_Patricia(char* string,int tamanho);
void Ocorrencias_Patricia(char *texto, char *nome, char *ingrediente, int j, TipoArvore patricia);
int Contar_Ocorrencias_Patricia(char *texto, char *ingrediente);

#endif