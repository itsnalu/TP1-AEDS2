#include "TAD_Patricia.h"
#include "Leitura_Arquivo_Patricia.h"

int main() {
    TipoArvore arvore = NULL;
    int qtd;
    /* 
    printf("DIGITE A QUANTIDADE DE PALAVRINHAS: ");
    scanf("%d",&qtd);
    Palavra palavrinha = (Palavra)malloc(100*sizeof(unsigned char));
    for(int i = 0; i < qtd; i++){
        printf("DIGITE A PALAVRINHA: ");
        scanf("%s", palavrinha+i);
        arvore = Insere(palavrinha, arvore);
    }
    */

    Palavra palavra1 = (Palavra)"casca";
    Palavra palavra2 = (Palavra)"casco";
    Palavra palavra3 = (Palavra)"cascalho";
    Palavra palavra4 = (Palavra)"cascavel";
    arvore = Insere(palavra1, arvore);
    arvore = Insere(palavra2, arvore);
    arvore = Insere(palavra3, arvore);
    arvore = Insere(palavra4, arvore);

    printf("Arvore sera impressa: \n");
    ImprimeArvore(arvore, 0, NULL);
    //ImprimeArvore_PreOrdem(arvore,0,NULL); // Começa da raiz por isso 0, direção null pq é a raiz
    //free(palavrinha);
    return 0;
}