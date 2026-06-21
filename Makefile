all:
	gcc ./src/*.c main.c -I./headers -g -Wall -o tp

run: all
	./tp

clean:
	rm -f tp tp.exe