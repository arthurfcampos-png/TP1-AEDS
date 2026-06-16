#comandos recorrentemente executados
EXEC = ./bin/tp
CC = gcc
INCLUDE = -I./include

#e importante declarar essas variaveis com os nomes das pastas para que se mudarmos o nome seja mais facil muda-las no arquivo
SRC = ./src
OBJ = ./obj
TP = ./

#condicional com os comandos respectivos do sistema operacional
ifeq ($(OS),Windows_NT)
    RM = del /Q
    EXEC := $(EXEC).exe
	OBJCLEAN = .\obj\
	BINCLEAN = .\bin\*.exe
else
	EXEC = ./bin/tp
    RM = rm -f
	OBJCLEAN = ./obj/*
	BINCLEAN = ./bin/*
endif

#target de compilacao (comando pra compilar no windows -> mingw32-make || comando pra compilar no linux -> make)
all:
#faco a compilacao dos arquivos do src (.c) e transformo-os em objetos
	$(CC) -c $(SRC)/hash.c $(INCLUDE) -o $(OBJ)/hash.o
	$(CC) -c $(SRC)/leitura_entrada.c $(INCLUDE) -o $(OBJ)/leitura_entrada.o
	$(CC) -c $(SRC)/lista.c $(INCLUDE) -o $(OBJ)/lista.o
	$(CC) -c $(SRC)/patricia.c $(INCLUDE) -o $(OBJ)/patricia.o
	$(CC) -c $(SRC)/tfidf_hash.c $(INCLUDE) -o $(OBJ)/tfidf_hash.o
	$(CC) -c $(SRC)/tfidf_patricia.c $(INCLUDE) -o $(OBJ)/tfidf_patricia.o
	$(CC) -c $(SRC)/utils.c $(INCLUDE) -o $(OBJ)/utils.o

#faco a compilacao do main tranformando-o em um executavel
	$(CC) $(TP)/main.c $(OBJ)/*.o $(INCLUDE) -o $(EXEC)

#target de execucao (comando pra compilar no windows -> mingw32-make executar || comando pra compilar no linux -> make executar)
executar:
	$(EXEC)

#target que limpeza (comando pra compilar no windows -> mingw32-make limpar || comando pra compilar no linux -> make limpar)
limpar:
	$(RM) $(OBJCLEAN) $(BINCLEAN)
