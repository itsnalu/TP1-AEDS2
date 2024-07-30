#include "TAD_Tabela_Hash.h"

void To_Lower_Case(char *str)
{
    while (*str)
    {
        *str = tolower(*str);
        str++;
    }
}

void FL_Vazia(Tabela_Hash *Lista)
{
    Lista->Primeiro = (Tipo_Celula *)malloc(sizeof(Tipo_Celula));
    Lista->Ultimo = Lista->Primeiro;
    Lista->Primeiro->Prox = NULL;
    Lista->Primeiro->Ingrediente = NULL;
    Lista->Primeiro->Indices = NULL;
}

short Vazia(Tabela_Hash Lista)
{
    return (Lista.Primeiro == Lista.Ultimo);
}

void Ins(Palavra x, Tabela_Hash *Lista)
{
    Lista->Ultimo->Prox = (Apontador_Prox)malloc(sizeof(Tipo_Celula));
    Lista->Ultimo = Lista->Ultimo->Prox;
    Lista->Ultimo->Ingrediente = strdup(x); // Usar strdup para alocar memória e copiar a string
    Lista->Ultimo->Prox = NULL;
    Lista->Ultimo->Indices = NULL;
}

void Ret(Apontador_Prox p, Tabela_Hash *Lista, Palavra *Ingrediente)
{
    Apontador_Prox q;
    if (Vazia(*Lista) || p == NULL || p->Prox == NULL)
    {
        printf(" Erro Lista vazia ou posicao nao existe\n");
        return;
    }
    q = p->Prox;
    *Ingrediente = strdup(q->Ingrediente); // Usar strdup para alocar memória e copiar a string
    p->Prox = q->Prox;
    if (p->Prox == NULL)
        Lista->Ultimo = p;
    free(q->Ingrediente); // Liberar a memória alocada para a string
    free(q);
}

void GeraPesos(TipoPesos p)
{
    int i, j;
    struct timeval semente;
    gettimeofday(&semente, NULL);
    srand((int)(semente.tv_sec + 1000000 * semente.tv_usec));

    // srand(NULL);
    for (i = 0; i < N; i++)
        for (j = 0; j < TAMALFABETO; j++)
            p[i][j] = 1 + (int)(10000.0 * rand() / (RAND_MAX + 1.0));
}

TipoIndice h(Palavra Chave, TipoPesos p)
{
    int i;
    unsigned int Soma = 0;
    int comp = strlen(Chave);
    for (i = 0; i < comp; i++)
        Soma += p[i][(unsigned int)Chave[i]];
    return (Soma % M);
}

void Inicializa(Vetor T)
{
    int i;
    for (i = 0; i < M; i++)
        FL_Vazia(&T[i]);
}

Apontador_Prox Pesquisa(Palavra Ch, TipoPesos p, Vetor T)
{
    TipoIndice i;
    Apontador_Prox Ap;
    i = h(Ch, p);
    if (Vazia(T[i]))
        return NULL;
    else
    {
        Ap = T[i].Primeiro;
        while (Ap->Prox->Prox != NULL && strcmp(Ch, Ap->Prox->Ingrediente))
            Ap = Ap->Prox;
        if (!strcmp(Ch, Ap->Prox->Ingrediente))
            return Ap;
        else
            return NULL;
    }
}

void Insere(Palavra x, TipoPesos p, Vetor T)
{
    if (Pesquisa(x, p, T) == NULL)
        Ins(x, &T[h(x, p)]);
    else
        printf(" Registro ja  esta  presente\n");
}

void Retira(Palavra x, TipoPesos p, Vetor T)
{
    Apontador_Prox Ap;
    Ap = Pesquisa(x, p, T);
    if (Ap == NULL)
        printf(" Registro nao esta  presente\n");
    else
        Ret(Ap, &T[h(x, p)], &x);
}

void Imp(Tabela_Hash Lista)
{
    Apontador_Prox Aux;
    Aux = Lista.Primeiro->Prox;
    while (Aux != NULL)
    {
        printf("%s ", Aux->Ingrediente);
        Aux = Aux->Prox;
    }
}

void Imprime(Vetor Tabela)
{
    int i;
    for (i = 0; i < M; i++)
    {
        
        printf("%d: ", i);
        if (!Vazia(Tabela[i]))
            Imp(Tabela[i]);
        putchar('\n');
        
        
        
        
    }
}

/*
void GeraPesos(TipoPesos p)
{ int i;
  struct timeval semente;
  gettimeofday(&semente, NULL);
  srand((int)(semente.tv_sec + 1000000*semente.tv_usec));
  for (i = 0; i < n; i++)
     p[i] =  1+(int) (10000.0*rand()/(RAND_MAX+1.0));
}

TipoIndice h(Palavra Chave, TipoPesos p)
{ int i;
  unsigned int Soma = 0;
  int comp = strlen(Chave);
  for (i = 0; i < comp; i++) Soma += (unsigned int)Chave[i] * p[i];
  return (Soma % M);
}
*/
