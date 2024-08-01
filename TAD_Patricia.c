#include "TAD_Patricia.h"
#include <string.h>

/* Função auxiliar para criar um nó externo */
TipoArvore CriaNoExterno(Palavra chave) {
    TipoArvore p = (TipoArvore)malloc(sizeof(TipoPatNo));
    p->nt = Externo;
    p->NO.Chave = (Palavra)malloc(strlen((char*)chave) + 1);
    strcpy((char*)p->NO.Chave, (char*)chave);
    return p;
}

/* Função auxiliar para criar um nó interno */
TipoArvore CriaNoInterno(TipoIndexAmp index, unsigned char caractere, TipoArvore Esq, TipoArvore Dir) {
    TipoArvore p = (TipoArvore)malloc(sizeof(TipoPatNo));
    p->nt = Interno;
    p->NO.NInterno.Index = index;
    p->NO.NInterno.Caractere = caractere;
    p->NO.NInterno.Esq = Esq;
    p->NO.NInterno.Dir = Dir;
    return p;
}

/* Função para inserir uma palavra na árvore */
TipoArvore InsereEntre(Palavra chave, TipoArvore t, TipoIndexAmp index, unsigned char caractere) {
    TipoArvore novo = CriaNoExterno(chave);

    if ((unsigned char)chave[index] <= caractere)
        return CriaNoInterno(index, caractere, novo, t);
    else
        return CriaNoInterno(index, caractere, t, novo);
}

TipoArvore Insere(Palavra chave, TipoArvore t) {
    if (t == NULL) return CriaNoExterno(chave);
    
    TipoArvore p = t;
    while (p->nt == Interno) {
        if ((unsigned char)chave[p->NO.NInterno.Index] <= p->NO.NInterno.Caractere)
            p = p->NO.NInterno.Esq;
        else
            p = p->NO.NInterno.Dir;
    }

    /* Encontramos um nó externo, verificar se a chave já existe */
    int i = 0;
    while (chave[i] == p->NO.Chave[i] && chave[i] != '\0') i++;

    if (chave[i] == p->NO.Chave[i]) {
        /* Chave já existe, não faz nada */
        return t;
    }

    /* Inserir entre os dois nós */
    return InsereEntre(chave, t, i, chave[i]);
}

/* Função para buscar uma palavra na árvore */
int Pesquisa(Palavra chave, TipoArvore t) {
    if (t == NULL) return 0;

    TipoArvore p = t;
    while (p->nt == Interno) {
        if ((unsigned char)chave[p->NO.NInterno.Index] <= p->NO.NInterno.Caractere)
            p = p->NO.NInterno.Esq;
        else
            p = p->NO.NInterno.Dir;
    }

    return (strcmp((char*)chave, (char*)p->NO.Chave) == 0);
}

/* Função para liberar a memória da árvore */
void Libera(TipoArvore t) {
    if (t == NULL) return;

    if (t->nt == Interno) {
        Libera(t->NO.NInterno.Esq);
        Libera(t->NO.NInterno.Dir);
    } else {
        free(t->NO.Chave);
    }
    free(t);
}
/*
void ImprimeArvore(TipoArvore t, int nivel) {
    if (t == NULL) return;

    for (int i = 0; i < nivel; i++) {
        printf("  ");
    }

    if (t->nt == Interno) {
        printf("Interno (Index: %d, Caractere: '%c' %p %p)\n", t->NO.NInterno.Index, t->NO.NInterno.Caractere,t->NO.NInterno.Dir,t->NO.NInterno.Esq);
        ImprimeArvore(t->NO.NInterno.Esq, nivel + 1);
        ImprimeArvore(t->NO.NInterno.Dir, nivel + 1);
    } else {
        printf("Externo (Chave: %s %p %p)\n", t->NO.Chave,t->NO.NInterno.Dir,t->NO.NInterno.Esq);
    }
}
*/

void ImprimeArvore(TipoArvore t, int nivel, const char* direcao) {
    if (t == NULL) return;

    // Imprimir a indentação para o nível
    for (int i = 0; i < nivel; i++) {
        printf("  ");
    }

    // Imprimir a direção do nó
    if (direcao != NULL) {
        printf("%s -> ", direcao);
    }

    // Imprimir o tipo de nó e suas informações
    if (t->nt == Interno) {
        printf("Interno (Index: %d, Caractere: '%c')\n", t->NO.NInterno.Index, t->NO.NInterno.Caractere);
        // Imprimir subárvore esquerda
        ImprimeArvore(t->NO.NInterno.Esq, nivel + 1, "Esquerda");
        // Imprimir subárvore direita
        ImprimeArvore(t->NO.NInterno.Dir, nivel + 1, "Direita");
    } else {
        printf("Externo (Chave: %s)\n", t->NO.Chave);
    }
}
