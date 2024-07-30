all: mainteste.c Leitura_Arquivo.c TAD_Tabela_Hash.c
	gcc mainteste.c -o programa Leitura_Arquivo.c TAD_Tabela_Hash.c

run: ./programa