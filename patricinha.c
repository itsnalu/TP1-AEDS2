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
    
    /* Palavra palavra1 = (Palavra)"casca";
    Palavra palavra2 = (Palavra)"casco";
    Palavra palavra3 = (Palavra)"cascalho";
    Palavra palavra4 = (Palavra)"cascavel";
    arvore = Insere(palavra1, &arvore);
    arvore = Insere(palavra2, &arvore);
    arvore = Insere(palavra3, &arvore);
    arvore = Insere(palavra4, &arvore);

    printf("Arvore sera impressa: \n");
    ImprimeEmOrdem(arvore);
    ImprimeEmOrdemComInternos(arvore); */

    Palavra palavra1 = (Palavra)"casa";
    Palavra palavra2 = (Palavra)"caso";
    Palavra palavra3 = (Palavra)"casu";
    Palavra palavra4 = (Palavra)"case";
    Palavra palavra5 = (Palavra)"casi"; 
    Palavra palavra6 = (Palavra)"casu"; 
    Palavra palavra7 = (Palavra)"casulo";
    Palavra palavra8 = (Palavra)"casulaine";
    Palavra palavra9 = (Palavra)"casule";
    Palavra palavra10 = (Palavra)"cas";

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

    //ImprimeEmOrdemComDirecao(arvore);
    //O imprime em ordem com direcao primeiro imprime a raiz e depois em ordem.(isso pode deixar confuso).


    //free(palavrinha);
    return 0;
    
}