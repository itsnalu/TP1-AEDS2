#include "TAD_Patricia.h"
#include <string.h>

/* Função auxiliar para criar um nó externo */
TipoArvore CriaNoExterno(Palavra chave) {
    TipoArvore p;
    p = (TipoArvore)malloc(sizeof(TipoPatNo));
    p->nt = Externo;
    p->NO.Chave = (Palavra)malloc(strlen(chave)*sizeof(unsigned char)+1);
    strcpy((char*)p->NO.Chave, (char*)chave);
    return p;
}

/* Função auxiliar para criar um nó interno */
TipoArvore CriaNoInterno(TipoIndexAmp index, TipoArvore *Esq, TipoArvore *Dir, unsigned char caractere) {
    TipoArvore p = (TipoArvore)malloc(sizeof(TipoPatNo));
    p->nt = Interno;
    p->NO.NInterno.Index = index;
    p->NO.NInterno.Caractere = caractere;
    p->NO.NInterno.Esq = *Esq;
    p->NO.NInterno.Dir = *Dir;
    return p;
}

short EExterno(TipoArvore p)
{ /* Verifica se p^ e nodo externo */
    return (p->nt == Externo);
}

TipoArvore InsereEntre(Palavra k, TipoArvore *t, int i, unsigned char caractere)
{
    TipoArvore p;

    if (EExterno(*t) || i < (*t)->NO.NInterno.Index)
    {
        /* Cria um novo nó externo */
        p = CriaNoExterno(k);
        if (k[i] > (*t)->NO.NInterno.Caractere)
            return CriaNoInterno(i, t, &p, caractere); // Cria nó interno com k[i] > caractere do nó interno
        else
            return CriaNoInterno(i, &p, t, caractere); // Cria nó interno com k[i] <= caractere do nó interno
    }
    else
    {
        if (k[(*t)->NO.NInterno.Index] > (*t)->NO.NInterno.Caractere)
            (*t)->NO.NInterno.Dir = InsereEntre(k, &(*t)->NO.NInterno.Dir, i,caractere);
        else
            (*t)->NO.NInterno.Esq = InsereEntre(k, &(*t)->NO.NInterno.Esq, i,caractere);
        return (*t);
    }
}



TipoArvore Insere(Palavra k, TipoArvore *t)
{
    TipoArvore p;
    int i;
    unsigned char letra_dif;

    if (*t == NULL)
    {
        return CriaNoExterno(k); // Supondo que essa função cria um nó externo com a chave k
    }
    else
    {
        p = *t;
        while (!EExterno(p))
        {
            if (k[p->NO.NInterno.Index] > p->NO.NInterno.Caractere)
                p = p->NO.NInterno.Dir;
            else
                p = p->NO.NInterno.Esq;
        }
        // Acha o primeiro caractere diferente
        i = 0;
        while (k[i] != '\0' && p->NO.Chave[i] != '\0' && tolower(k[i]) == tolower(p->NO.Chave[i]))
            i++;
        
        letra_dif=k[i];

        if (k[i] == '\0' && p->NO.Chave[i] == '\0')
        {
            printf("Erro: chave ja esta na arvore\n");
            return (*t);
        }
        else
            return InsereEntre(k, t, i, letra_dif); // Supondo que essa função insere entre os nós
    }
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

void ImprimeEmOrdemAux(TipoArvore t) {
    if (t != NULL) {
        if (EExterno(t)) {
            printf("%s\n", t->NO.Chave);  // Supondo que a chave é do tipo Palavra
        } else {
            ImprimeEmOrdemAux(t->NO.NInterno.Esq);
            ImprimeEmOrdemAux(t->NO.NInterno.Dir);
        }
    }
}

void ImprimeEmOrdem(TipoArvore t) {
    ImprimeEmOrdemAux(t);
}





void ImprimeEmOrdemAuxComDirecao(TipoArvore t, const char* direcao) {
    if (t != NULL) {
        if (EExterno(t)) {
            printf("Externo: %s (%s)\n", t->NO.Chave, direcao);
        } else {
            printf("Interno: Index = %d, Caractere = %c (%s)\n", t->NO.NInterno.Index, t->NO.NInterno.Caractere, direcao);
            ImprimeEmOrdemAuxComDirecao(t->NO.NInterno.Esq, "Esq");
            ImprimeEmOrdemAuxComDirecao(t->NO.NInterno.Dir, "Dir");
        }
    }
}

void ImprimeEmOrdemComDirecao(TipoArvore t) {
    ImprimeEmOrdemAuxComDirecao(t, "Raiz");
}

void ImprimeEmOrdemAuxComInternos(TipoArvore t) {
    if (t != NULL) {
        if (EExterno(t)) {
            printf("Externo: %s\n", t->NO.Chave);
        } else {
            printf("Interno: Index = %d, Caractere = %c\n", t->NO.NInterno.Index, t->NO.NInterno.Caractere);
            ImprimeEmOrdemAuxComInternos(t->NO.NInterno.Esq);
            ImprimeEmOrdemAuxComInternos(t->NO.NInterno.Dir);
        }
    }
}

void ImprimeEmOrdemComInternos(TipoArvore t) {
    ImprimeEmOrdemAuxComInternos(t);
}