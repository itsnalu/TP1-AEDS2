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
    //Verifica se o nó atual é um nó externo ou se o índice i é menor que o índice do nó interno atual
    if (EExterno(*t) || i < (*t)->NO.NInterno.Index)
    {
        //Cria um novo nó externo com a chave a ser inserida
        p = CriaNoExterno(k);
        //Compara o caractere da palavra k na posição i com o caractere do nó interno atual.
        if (k[i] >= caractere){
            //Se o caractere da palavra for maior, cria um novo nó interno com o nó externo p como filho direito
            return CriaNoInterno(i, t, &p, caractere); // Cria nó interno com k[i] > caractere do nó interno
        }            
        else{
            //Se o caractere da palavra for menor ou igual, cria um novo nó interno com o nó externo p como filho esquerdo
            return CriaNoInterno(i, &p, t, caractere); // Cria nó interno com k[i] <= caractere do nó interno
        }            
    }
    else
    {
        //Se o nó não é externo e o índice i não é menor que o índice do nó interno atual
        //Compara o caractere da palavra k na posição do índice do nó interno atual com o caractere do nó interno atual
        if (k[(*t)->NO.NInterno.Index] > (*t)->NO.NInterno.Caractere){
            (*t)->NO.NInterno.Dir = InsereEntre(k, &(*t)->NO.NInterno.Dir, i,caractere);
        }         
        else{
            (*t)->NO.NInterno.Esq = InsereEntre(k, &(*t)->NO.NInterno.Esq, i,caractere);
        }           
        //Retorna o nó atual, que pode ter sido atualizado com novos filhos internos ou externos.
        return (*t);
    }
}




TipoArvore Insere(Palavra k, TipoArvore *t)
{
    TipoArvore p;
    int i;
    unsigned char letra_dif; //Armazena a letra que difere entre as palavras comparadas

    if (*t == NULL)
    {
        return CriaNoExterno(k); //Arvore vazia, cria nó externo com a chave k
    }
    else
    {
        p = *t;
        while (!EExterno(p)) //Enquanto o nó for interno, vai percorrendo a arvore ate encontrar um nó externo
        {
            if (k[p->NO.NInterno.Index] > p->NO.NInterno.Caractere)
                p = p->NO.NInterno.Dir;
            else
                p = p->NO.NInterno.Esq;
        }
        //Acha o primeiro caractere diferente entre as duas palavras comparadas
        i = 0;
        while (k[i] != '\0' && p->NO.Chave[i] != '\0' && tolower(k[i]) == tolower(p->NO.Chave[i]))
            i++;

        if(strlen(k) < strlen(p->NO.Chave) || k[i] <= p->NO.Chave[i]){
            letra_dif = p->NO.Chave[i];
        }
        else{
                letra_dif = k[i]; //se k[i] > p->NO.Chave[i]
        }

        if (k[i] == '\0' && p->NO.Chave[i] == '\0')
        {
            printf("Erro: chave ja esta na arvore\n");
            return (*t); //Chave já existente na arvore, portanto nao insere. retorna a arvore original
        }
        else{
            return InsereEntre(k, t, i, letra_dif);
        }
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







#include "TAD_Patricia.h"
#include <stdio.h>

/* Função auxiliar para imprimir a árvore em ordem com a direção dos nós */
void ImprimeEmOrdemAuxComInternos(TipoArvore t) {
    if (t != NULL) {
        if (!EExterno(t)) {
            // Primeiro, visite o filho esquerdo
            ImprimeEmOrdemAuxComInternos(t->NO.NInterno.Esq);
        }

        // Depois, visite o nó atual
        if (EExterno(t)) {
            printf("Externo: %s\n", t->NO.Chave);
        } else {
            printf("Interno: Index = %d, Caractere = %c\n", t->NO.NInterno.Index, t->NO.NInterno.Caractere);
        }

        if (!EExterno(t)) {
            // Finalmente, visite o filho direito
            ImprimeEmOrdemAuxComInternos(t->NO.NInterno.Dir);
        }
    }
}

/* Função para iniciar a impressão da árvore em ordem */
void ImprimeEmOrdemComInternos(TipoArvore t) {
    ImprimeEmOrdemAuxComInternos(t);
}


void ImprimePreOrdemAux(TipoArvore t, int nivel)
{
    if (t == NULL)
        return;

    // Imprime o nível do nó atual
    for (int j = 0; j < nivel; j++)
        printf("  ");  // Indenta os nós para representar a profundidade

    // Imprime informações sobre o nó atual
    if (EExterno(t))
    {
        // Se o nó é externo, imprime a chave e que é um nó externo
        printf("No Externo: %s\n", t->NO.Chave);
    }
    else
    {
        // Se o nó é interno, imprime o índice, o caractere e que é um nó interno
        printf("No Interno: indice %d, Caractere %c\n", t->NO.NInterno.Index, t->NO.NInterno.Caractere);

        // Imprime a direção dos filhos
        if (t->NO.NInterno.Esq != NULL || t->NO.NInterno.Dir != NULL)
        {
            printf("  Filho Esquerdo: ");
            ImprimePreOrdemAux(t->NO.NInterno.Esq, nivel + 1); // Recurssão para o filho esquerdo
            printf("  Filho Direito: ");
            ImprimePreOrdemAux(t->NO.NInterno.Dir, nivel + 1);  // Recurssão para o filho direito
        }
    }
}

/* Função para iniciar a impressão da árvore em pré-ordem */
void ImprimePreOrdem(TipoArvore t)
{
    ImprimePreOrdemAux(t, 0);  // Inicia com o nível 0
}