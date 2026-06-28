
CC      = gcc
CFLAGS  = -I./headers -g -Wall
LDFLAGS = -lm

SRC     = main.c ./src/lista.c ./src/hash.c ./src/patricia.c \
          ./src/leitura_entrada.c ./src/tfidf.c

# Detecta o sistema operacional
ifeq ($(OS), Windows_NT)
    TARGET  = tp.exe
    RM      = del /f /q
    RUN     = $(TARGET)
else
    TARGET  = tp
    RM      = rm -f
    RUN     = ./$(TARGET)
endif

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(SRC) $(CFLAGS) $(LDFLAGS) -o $(TARGET)

run: all
	$(RUN)

clean:
	$(RM) tp tp.exe
