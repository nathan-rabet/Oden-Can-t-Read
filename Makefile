CC = gcc

CFLAGS = -Wall -Wextra -std=c99 -O0 -lm -ldl
CFLAGS += $(shell pkg-config --cflags json-c) # json-c flags


CLIBS = `sdl2-config --cflags --libs` -lSDL2_image
CLIBS += $(shell pkg-config --libs json-c) #json-c libs

#SRC = main.c
SRC =  src/matrix/matrix.c 
SRC += src/image/image.c 
SRC += src/image/binarization.c 
SRC += src/ml/struct/network.c
SRC += src/ml/struct/layer.c 
SRC += src/ml/struct/neurone.c
SRC += src/math/sortalgo.c
SRC += src/rotate/rotate.c
SRC += src/math/analysis.c
SRC += src/ml/train/generate.c
SRC += src/math/random.c
SRC += src/ml/train/backpropagation.c


OUT = ocr
DEBUG_OUT = a.out


all: ${SRC} ${SRC}
	${CC} main.c ${SRC} ${CLIBS} ${CFLAGS} -g -o main

xor : ${SRC} ${SRC}
	${CC} mainXOR.c ${SRC} ${CLIBS} ${CFLAGS} -g -o mainXOR

binarization : ${SRC} ${SRC}
	${CC} mainBINARIZATION.c ${SRC} ${CLIBS} ${CFLAGS} -g -o mainBINARIZATION

rotation : ${SRC} ${SRC}
	${CC} mainROTATION.c ${SRC} ${CLIBS} ${CFLAGS} -g -o mainROTATION

test : ${SRC} ${SRC}
	${CC} maintest.c ${SRC} ${CLIBS} ${CFLAGS} -g -o maintest
