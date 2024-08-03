#include "TAD_Patricia.h"

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
    Palavra palavra5 = (Palavra)"casce"; 
    Palavra palavra6 = (Palavra)"canalha"; 
    Palavra palavra7 = (Palavra)"alesia";
    Palavra palavra8 = (Palavra)"alexia";
    Palavra palavra9 = (Palavra)"aa";
    Palavra palavra10 = (Palavra)"a";

    arvore = Insere(palavra1, &arvore);
    arvore = Insere(palavra2, &arvore);
    arvore = Insere(palavra3, &arvore);
    arvore = Insere(palavra4, &arvore);
    arvore = Insere(palavra5, &arvore); 
    arvore = Insere(palavra6, &arvore); 
    arvore = Insere(palavra7, &arvore);
    arvore = Insere(palavra8, &arvore);
    arvore = Insere(palavra9, &arvore);
    arvore = Insere(palavra10, &arvore);

    printf("Arvore sera impressa em ordem sem internos: \n");
    ImprimeEmOrdem(arvore);
    printf("Arvore sera impressa em ordem com internos: \n");
    ImprimeEmOrdemComInternos(arvore);
    printf("Arvore sera impressa em pre ordem com internos: \n");
    ImprimePreOrdem(arvore);



    //free(palavrinha);
    return 0;
    
}