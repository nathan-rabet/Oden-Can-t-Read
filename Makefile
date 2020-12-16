CC = gcc

# Train
CFLAGS = -Wall -Wextra -std=c99 -O0 -lm -ldl -std=gnu99
CFLAGS += $(shell pkg-config --cflags json-c) # json-c flags

CLIBS = `sdl2-config --cflags --libs` -lSDL2_image -lpthread
CLIBS += $(shell pkg-config --libs json-c) #json-c libs

# GTK
CFLAGS_GTK = -Wall -Wextra  -std=c99 `pkg-config --cflags gtk+-3.0` -ldl -MMD -rdynamic -std=gnu99
CFLAGS_GTK += $(shell pkg-config --cflags json-c) # json-c flags
LDLIBS_GTK = -lm `pkg-config --libs gtk+-3.0` `sdl2-config --cflags --libs` -lSDL2_image -lpthread
LDLIBS_GTK += $(shell pkg-config --libs json-c) #json-c libs
LDFLAGS_GTK = $(PTHREAD) $(GTKLIB) -export-dynamic



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
SRC += src/math/random.c
SRC += src/ml/train/backpropagation.c
SRC += src/segmentation/segmentation.c
SRC += src/ml/struct/networks.c
SRC += src/ml/train/lib/backpropagMISC.c
SRC += src/miscellaneous/CHARS.c

OBJ= ${SRC:.c=.o} mainINTERFACE.o mainTRAIN.o
DEP= ${SRC:.c=.d} mainINTERFACE.d mainTRAIN.d


OUT = ocr
DEBUG_OUT = a.out

interface: ${SRC} ${SRC}
	${CC} mainINTERFACE.c ${SRC} ${LDLIBS_GTK} ${CFLAGS_GTK} -g -o mainINTERFACE.o

train : ${SRC} ${SRC}
	${CC} mainTRAIN.c ${SRC} ${CLIBS} ${CFLAGS} -g -o mainTRAIN.o

clean:
	${RM} ${OBJ} ${DEP}

-include ${DEP}
