all: main.c Leitura_Arquivo_Hash.c TAD_Tabela_Hash.c Leitura_Arquivo_Patricia.c TAD_Patricia.c Indice_Hash.c Indice_Patricia.c
	gcc main.c -o programa Leitura_Arquivo_Hash.c TAD_Tabela_Hash.c Leitura_Arquivo_Patricia.c TAD_Patricia.c Indice_Hash.c Indice_Patricia.c 

run: ./programa