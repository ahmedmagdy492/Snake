CC=gcc

all:
	$(CC) ./src/main.c -o ./build/main -ggdb -std=c99 -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
clear:
	rm -rf ./build/* ./build/core.*
