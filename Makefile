CC = gcc

CFLAGS = -Wall -Wextra -std=c99 -O0 -lm -ldl
CFLAGS += $(shell pkg-config --cflags json-c) # json-c flags


CLIBS = `sdl2-config --cflags --libs` -lSDL2_image
CLIBS += $(shell pkg-config --libs json-c) #json-c libs

#SRC = main.c
SRC = src/matrix/matrix.c 
SRC += src/image/image.c 
SRC += src/image/binarization.c 
SRC += src/ml/network.c
SRC += src/ml/layer.c 
SRC += src/ml/neurone.c
SRC += src/math/sortalgo.c
SRC += src/rotate/rotate.c
SRC += src/math/analysis.c


OUT = ocr
DEBUG_OUT = a.out


all: ${SRC} ${SRC}
	${CC} main.c ${SRC} ${CLIBS} ${CFLAGS} -g -o a.out

xor : ${SRC} ${SRC}
	${CC} mainXOR.c ${SRC} ${CLIBS} ${CFLAGS} -o xor.out

binarization : ${SRC} ${SRC}
	${CC} mainBINARIZATION.c ${SRC} ${CLIBS} ${CFLAGS} -o binarization.out

rotation : ${SRC} ${SRC}
	${CC} mainROTATION.c ${SRC} ${CLIBS} ${CFLAGS} -o rotation.out