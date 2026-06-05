CC=gcc
CFLAGS=-Iheaders -Wall -Wextra -std=c99
SRCS=main.c sources/hash.c sources/leitura_entrada.c sources/lista.c sources/patricia.c sources/tfidf_hash.c sources/tfidf_patricia.c sources/utils.c
OBJS=$(SRCS:.c=.o)
TARGET=tp1

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)
