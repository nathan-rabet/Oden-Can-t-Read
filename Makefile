CC = gcc

FLAGS = -Wall -Wextra -std=c99 -O2
LIBS = `sdl2-config --cflags --libs` -lSDL2_image
SRC = main.c
SRC2 = src/matrix/matrix.c src/image/image.c

OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}
RM = rm

OUT = ocr
DEBUG_OUT = a.out

debug: ${SRC} ${SRC2}
	${CC} ${SRC} ${SRC2} ${LIBS} ${FLAGS} -g -o a.out

release: ${SRC} ${SRC2}
	${CC} ${SRC} ${SRC2} ${LIBS} ${FLAGS} -o ocr

.PHONY: clean
clean:
	rm ${OBJ}   # remove object files
	rm ${DEP}   # remove dependency files
	rm OUT DEBUG_OUT     # remove main program

-include ${DEP}