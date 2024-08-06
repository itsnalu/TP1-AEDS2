/*
Alexia Karoline Augusta Germano Silva [EF05373] 
Ana Luisa Moreira Rodrigues [EF05389] 
Dalmo Nolasco Dantas Rainer [EF05361] 
Lucas da Costa Moreira [EF05377]
*/

#ifndef INDICE_HASH_H
#define INDICE_HASH_H

#include "Leitura_Arquivo_Hash.h"


void Imprimir_IndiceInvertido_Hash(char *ingrediente, TipoPesos p, Tabela_Hash *T);
int contarDocsComTermo(Indice_Invertido *indiceAtual);
void imprimirIngredientes(Tabela_Hash *tabela, int totalDocs);
//char **fCaminhoArquivos(char **arquivos, int qtd);

#endif // INDICE_HASH_H
