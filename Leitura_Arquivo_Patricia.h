#include "TAD_Patricia.h"

#define MAX_FILENAME_LENGTH 100
#define MAX_CONTENT_LENGTH 1000
#define MAX_INGREDIENTS 48
#define MAX_INGREDIENT_LENGTH 100


void Remove_Espaco(char *str);
void Remove_Pontuacao(char *str);
void lerEProcessarArquivo_Patricia(const char *nomeArquivo, TipoArvore Patricia);