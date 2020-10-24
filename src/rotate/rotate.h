#ifndef ROTATE_H                                                             
#define ROTATE_H
#include "../matrix/matrix.h"


//Calculates the diagonal of the matrix
int diagMatrixSizeINT(struct MatrixINT matrix);

int diagMatrixSizeUCHAR(struct MatrixUCHAR matrix);


//Rotate the matrix with a given angle in degrees
struct MatrixINT rotateINT(struct MatrixINT m, int angle);

struct MatrixUCHAR rotateUCHAR(struct MatrixUCHAR m, int angle);

#endif

