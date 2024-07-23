#include <stdio.h>
#include <string.h>
#include "Leitura_Arquivo.h"

int Contar_Ocorrencias(const char *string, const char *substring) {
    int count = 0;
    const char *temp = string;
    
    while ((temp = strstr(temp, substring)) != NULL) {
        count++;
        temp += strlen(substring); //Próxima contagem vai começar a partir de onde achou a primeira ocorrência :p
    }
    
    return count;
}


void RemoveEspacos(char *str) {
    if (str[0] == ' ') {
        memmove(str, str + 1, strlen(str));
    }
}

// Lista de stop words em inglês
const char *stopWords[] = {
    "a", "an", "and", "are", "as", "at", "be", "by", "for", "from", "has", 
    "he", "in", "is", "it", "its", "of", "on", "that", "the", "to", "was", 
    "were", "will", "with"
};
const int num_stopWords = sizeof(stopWords) / sizeof(stopWords[0]);

// Função para verificar se uma palavra é uma stop word
int isStopWord(const char *word) {
    for (int i = 0; i < num_stopWords; i++) {
        if (strcmp(word, stopWords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Função para remover stop words de um texto
char* removeStopWords(const char *text) {
    // Fazer uma cópia do texto para trabalhar
    char *textCopy = strdup(text);
    char *token;
    char *result = (char*)malloc(strlen(text) + 1);
    result[0] = '\0';

    // Tokenizar o texto e remover as stop words
    token = strtok(textCopy, " ");
    while (token != NULL) {
        if (!isStopWord(token)) {
            strcat(result, token);
            strcat(result, " ");
        }
        token = strtok(NULL, " ");
    }

    // Remover o espaço extra no final
    if (strlen(result) > 0 && result[strlen(result) - 1] == ' ') {
        result[strlen(result) - 1] = '\0';
    }

    free(textCopy);
    return result;
}