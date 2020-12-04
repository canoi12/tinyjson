CC = gcc
SOURCE = main.c src/tinyjson.c
OUT = tjson
CFLAGS = -Wall -std=c99

hello:
	$(CC) $(SOURCE) -o $(OUT) $(CFLAGS)