#include "TAD_Patricia.h"

#define MAX_FILENAME_LENGTH 100
#define MAX_CONTENT_LENGTH 1000
#define MAX_INGREDIENTS 48
#define MAX_INGREDIENT_LENGTH 100



void Remove_Espaco_Patricia(char *str);
void Remove_Pontuacao_Patricia(char *str);
void Armazenar_Patricia(char *nomeArquivo, TipoArvore *patricia, int j);
int Contar_Ocorrencias_Patricia(char *texto, char *ingrediente);
int Contar_Ingrediente_Patricia(char* string,int tamanho);
void To_Lower_Case_Patricia(char *str);