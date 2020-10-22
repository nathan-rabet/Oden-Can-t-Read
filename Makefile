CC = gcc

CFLAGS = -Wall -Wextra -std=c99 -O0 -lm -ldl
CFLAGS += $(shell pkg-config --cflags json-c) # json-c flags


CLIBS = `sdl2-config --cflags --libs` -lSDL2_image
CLIBS += $(shell pkg-config --libs json-c) #json-c libs

SRC = main.c
SRC2 = src/matrix/matrix.c src/image/image.c src/image/binarization.c src/ml/network.c src/ml/layer.c src/ml/neurone.c

OUT = ocr
DEBUG_OUT = a.out

all: ${SRC} ${SRC2}
	${CC} ${SRC} ${SRC2} ${CLIBS} ${CFLAGS} -g -o a.out

release: ${SRC} ${SRC2}
	${CC} ${SRC} ${SRC2} ${CLIBS} ${CFLAGS} -o ocr