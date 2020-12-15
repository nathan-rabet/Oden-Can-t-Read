#Makefile
CC=gcc

CPPFLAGS= -MMD
CFLAGS = -Wall -Wextra  -std=c99 `pkg-config --cflags gtk+-3.0` -ldl -MMD -rdynamic
CFLAGS += $(shell pkg-config --cflags json-c) # json-c flags
LDLIBS = -lm `pkg-config --libs gtk+-3.0` `sdl2-config --cflags --libs` -lSDL2_image -lpthread
LDLIBS += $(shell pkg-config --libs json-c) #json-c libs
LDFLAGS = $(PTHREAD) $(GTKLIB) -export-dynamic

SRC = OCR_project.c
SRC += src/matrix/matrix.c 
SRC += src/image/image.c 
SRC += src/image/binarization.c 
SRC += src/ml/struct/network.c
SRC += src/ml/struct/layer.c 
SRC += src/ml/struct/neurone.c
SRC += src/math/sortalgo.c
SRC += src/rotate/rotate.c
SRC += src/math/analysis.c
SRC += src/math/random.c
SRC += src/ml/train/backpropagation.c
SRC += src/segmentation/segmentation.c
SRC += src/ml/struct/networks.c
OBJ= ${SRC:.c=.o}
DEP= ${SRC:.c=.d}


all: ${SRC} ${SRC}
	${CC} ${SRC} ${LDLIBS} ${CFLAGS} -g -o OCR_project

interface: ${OBJ}

clean:
	${RM} ${OBJ} ${DEP} *~ OCR_project

-include ${DEP}

#END