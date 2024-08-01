
#include "TAD_Patricia.h"
#include "Leitura_Arquivo_Patricia.h"

int main() {
    TipoArvore arvore = NULL;
    FILE *entrada;
    int numArquivos;
    char nomeArquivo[MAX_FILENAME_LENGTH];
    
    //Vetor Inserir_na_Patricia;
    
    // Abrir o arquivo entrada.txt
    entrada = fopen("entrada.txt", "r");
    if (entrada == NULL) {
        perror("Erro ao abrir o arquivo entrada.txt");
        return 1;
    }

    // Ler o número de arquivos
    if (fscanf(entrada, "%d", &numArquivos) != 1) {
        perror("Erro ao ler o número de arquivos");
        fclose(entrada);
        return 1;
    }

    // Loop para ler e abrir cada arquivo especificado
    for (int i = 0; i < numArquivos; i++) {
        // Ler o nome do arquivo
        if (fscanf(entrada, "%s", nomeArquivo) != 1) {
            perror("Erro ao ler o nome do arquivo");
            fclose(entrada);
            return 1;
        }

        // Chamar a função para ler e processar o arquivo
        lerEProcessarArquivo_Patricia(nomeArquivo, arvore);
    }

    //ImprimeArvore(arvore,0);

    // Fechar o arquivo entrada.txt
    fclose(entrada);
    





    /*
    Palavra palavra1 = (Palavra)"teste";
    Palavra palavra2 = (Palavra)"palavra";
    Palavra palavra3 = (Palavra)"arvore";

    arvore = Insere(palavra1, arvore);
    arvore = Insere(palavra2, arvore);
    arvore = Insere(palavra3, arvore);

    printf("Pesquisa de 'teste': %d\n", Pesquisa(palavra1, arvore));
    printf("Pesquisa de 'palavra': %d\n", Pesquisa(palavra2, arvore));
    printf("Pesquisa de 'arvore': %d\n", Pesquisa(palavra3, arvore));
    printf("Pesquisa de 'inexistente': %d\n", Pesquisa((Palavra)"inexistente", arvore));

    Libera(arvore);

    return 0; 
    */
}