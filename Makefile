CC = gcc
SRC = tinyjson.c
NAME = tjson

OUT = $(NAME)
RELEASE ?= 0

LIBNAME = lib$(NAME)
SLIBNAME = $(LIBNAME).a

OBJ = $(SRC:%.c=%.o)

CFLAGS = -Wall -std=c99

ifeq ($(RELEASE),1)
	CFLAGS += -O2
else
	CFLAGS += -g
endif

$(OUT): main.c $(SLIBNAME)
	$(CC) main.c -o $(OUT) -L. -l$(NAME) $(CFLAGS)

$(SLIBNAME): $(OBJ)
	ar rcs $@ $(OBJ)

%.o: %.c %.h
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(OBJ)
	rm -f $(OUT)
	rm -f $(SLIBNAME)