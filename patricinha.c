#include "TAD_Patricia.h"
#include "Leitura_Arquivo_Patricia.h"

int main() {
    TipoArvore arvore = NULL;
    Palavra palavrinha = (Palavra)malloc(100*sizeof(unsigned char));
    int qtd;
    printf("DIGITE A QUANTIDADE DE PALAVRINHAS: ");
    scanf("%d",&qtd);
    for(int i = 0; i < qtd; i++){
        printf("DIGITE A PALAVRINHA: ");
        scanf("%s", palavrinha);
        arvore = Insere(palavrinha, arvore);
    }
    printf("Arvore sera impressa: \n");
    ImprimeArvore(arvore, 0, NULL);
    free(palavrinha);
    return 0;
}