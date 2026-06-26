all:
	gcc ./src/*.c main.c -I./headers -g -Wall -lm -o tp

run: all
	./tp

clean:
	rm -f tp tp.exe