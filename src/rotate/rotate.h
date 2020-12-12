#ifndef ROTATE_H                                                             
#define ROTATE_H
#include "../matrix/matrix.h"


/**
 * @brief Estimates the length of the diagonal
 * of the matrix via Pythagore Theorem and returns it.
 * 
 * @param matrix The matrix of the image we want to rotate.
 * @return int The length of the diagonal of the Matrix.
 */
int diagMatrixSizeINT(struct MatrixINT matrix);

int diagMatrixSizeDOUBLE(struct MatrixDOUBLE matrix);

/**
 * @brief Estimates the length of the diagonal 
 * of the matrix via Pythagore Theorem and returns it.
 * 
 * @param matrix The matrix of the image we want to rotate.
 * @return int The length of the diagonal of the Matrix.
 */
int diagMatrixSizeUCHAR(struct MatrixUCHAR matrix);


/**
 * @brief Rotates the Matrix by the given angle and returns a new Matrix of size diagMatrix(m).
 * 
 * @param m The Matrix we want to rotate.
 * @param angle The angle of rotation in degrees (positive).
 * @return struct MatrixINT.
 */
struct MatrixINT rotateINT(struct MatrixINT m, int angle);

struct MatrixDOUBLE rotateDOUBLE(struct MatrixDOUBLE m, int angle);

/**
 * @brief Rotates the Matrix by the given angle and returns a new Matrix of size diagMatrix(m).
 * 
 * @param m The Matrix we want to rotate.
 * @param angle The angle of rotation in degrees (positive).
 * @return struct MatrixUCHAR. 
 */
struct MatrixUCHAR rotateUCHAR(struct MatrixUCHAR m, int angle);

/**
 * @brief Trims the Matric of its unuseful values.
 * 
 * @param m The Matrix needed to be trimmed.
 * @return struct MatrixUCHAR.
 */
struct MatrixUCHAR TrimUCHAR(struct MatrixUCHAR m);

struct MatrixDOUBLE TrimDOUBLE(struct MatrixDOUBLE m);

#endif

