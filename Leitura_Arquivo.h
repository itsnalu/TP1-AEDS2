#include "TAD_Tabela_Hash.h"

#define MAX_FILENAME_LENGTH 100
#define MAX_CONTENT_LENGTH 1000
#define MAX_INGREDIENTS 48
#define MAX_INGREDIENT_LENGTH 100

int Contar_Ocorrencias(const char *string, const char *substring);
void lerEProcessarArquivo(const char *nomeArquivo, TipoPesos p, Tabela_Hash* T);
void Remove_Espaco(char *str);
void Remove_Pontuacao(char *str);