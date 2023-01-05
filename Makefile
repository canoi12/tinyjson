CC = gcc
SRC = tinyjson.c
NAME = tjson

OUT = $(NAME)
RELEASE ?= 0

LIBNAME = lib$(NAME)
SLIBNAME = $(LIBNAME).a
DLIBNAME = $(LIBNAME).so

OBJ = $(SRC:%.c=%.o)
DOBJ = $(SRC:%.c=%.do)

CFLAGS = -Wall -std=c89

ifeq ($(RELEASE),1)
	CFLAGS += -O2
else
	CFLAGS += -g
endif

.PHONY: build all

build: $(OUT)

all: $(SLIBNAME) $(DLIBNAME)

$(OUT): main.c $(SLIBNAME)
	$(CC) main.c -o $(OUT) -L. -l$(NAME) $(CFLAGS)

$(SLIBNAME): $(OBJ)
	ar rcs $@ $(OBJ)

$(DLIBNAME): $(DOBJ)
	$(CC) -shared -o $@ $(DOBJ) $(CFLAGS)

%.o: %.c %.h
	$(CC) -c $< -o $@ $(CFLAGS)

%.do: %.c %.h
	$(CC) -fPIC -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(OBJ) $(DOBJ)
	rm -f $(OUT)
	rm -f $(SLIBNAME) $(DLIBNAME)