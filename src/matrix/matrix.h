#ifndef MATRIX
#define MATRIX

/**
 * @brief Matrix of int
 * 
 */
struct MatrixINT {

/**
 * @struct MatrixINT 
 * matrix composed by integers.
 */

  /**
   * @brief The height coordinate.
   * 
   */
  int rows;

  /**
   * @brief The width coordinate.
   * 
   */
  int columns;

  /* The pointer of the matrix
   */

  /**
   * @brief Cells of the matrix.
   * 
   * @see The data structure is like so :\n
   * E.g :\n
   | a | aa |\n
   | b | bb |\n
   | c | cc |
   * 
   * Is stored in the memory like :\n
   * 
   | a* | aa | b | bb | c | cc |\n
   * 
   * with * correspond to the pointer\n
   * And the allocated size in the memory must be "sizeof(TYPE) × rows × columns".
   * 
   */
  int* cells;
};

/**
 * @brief Matrix of double
 * 
 */
struct MatrixDOUBLE {
/**
 * @struct MatrixDOUBLE 
 * matrix composed by doubles.
 */

  /**
   * @brief The height coordinate.
   * 
   */
  int rows;

  /**
   * @brief The width coordinate.
   * 
   */
  int columns;

  /**
   * @copydoc MatrixINT::cells
   */
  double* cells;
};

/**
 * @brief Matrix of unsigned characters
 * 
 */
struct MatrixUCHAR {
/**
 * @struct MatrixUCHAR 
 * matrix composed by unsigned characters.
 */

  /**
   * @brief The height coordinate.
   * 
   */
  int rows;

  /**
   * @brief The width coordinate.
   * 
   */
  int columns;

  /**
   * @copydoc MatrixINT::cells
   */
  unsigned char* cells;
};

/**
 * @brief Create a MatrixINT object.
 * 
 * @param x The number of rows.
 * @param y The number of columns.
 * @return struct MatrixINT.
 */
struct MatrixINT createMatrixINT(int x, int y);

/**
 * @brief Create a MatrixDOUBLE object.
 * 
 * @param x The number of rows.
 * @param y The number of columns.
 * @return struct MatrixDOUBLE.
 */
struct MatrixDOUBLE createMatrixDOUBLE(int x, int y);

/**
 * @brief Create a MatrixUCHAR object.
 * 
 * @param x The number of rows.
 * @param y The number of columns.
 * @return struct MatrixUCHAR.
 */
struct MatrixUCHAR createMatrixUCHAR(int x, int y);

/**
 * @brief Check if integers 
 * composed matrix pointer is not NULL.
 * 
 * @param matrix The matrix to check.
 * @return 0 if False, ℕ* if true.
 */
int checkMatrixINTValidity(struct MatrixINT matrix);

/**
 * @brief Check if double 
 * composed matrix pointer is not NULL.
 * 
 * @param matrix The matrix to check.
 * @return 0 if False, ℕ* if true.
 */
int checkMatrixDOUBLEValidity(struct MatrixDOUBLE matrix);

/**
 * @brief Check if usigned characters 
 * composed matrix pointer is not NULL.
 * 
 * @param matrix The matrix to check.
 * @return 0 if False, ℕ* if true.
 */
int checkMatrixUCHARValidity(struct MatrixUCHAR matrix);

/**
 * @brief Check if the coordinates x & y 
 * are in an integers composed matrix.
 * 
 * @param matrix The matrix to check.
 * @param x The rows coordinate.
 * @param y The columns coordinate.
 * @return 0 if False, ℕ* if true.
 */
int checkMatrixINTCoord(struct MatrixINT matrix, int x, int y);

/**
 * @brief Check if the coordinates x & y 
 * are in a double composed matrix.
 * 
 * @param matrix The matrix to check.
 * @param x The rows coordinate.
 * @param y The columns coordinate.
 * @return 0 if False, ℕ* if true.
 */
int checkMatrixDOUBLECoord(struct MatrixDOUBLE matrix, int x, int y);

/**
 * @brief Check if the coordinates x & y 
 * are in an unsigned characters composed matrix.
 * 
 * @param matrix The matrix to check.
 * @param x The rows coordinate.
 * @param y The columns coordinate.
 * @return 0 if False, ℕ* if true.
 */
int checkMatrixUCHARCoord(struct MatrixUCHAR matrix, int x, int y);

/**
 * @brief Print an error about the matrix.
 * 
 * @deprecated This function will be deleted for the next defence. 
 * 
 * @param error The error code
 */
void printMatrixERROR(int error);

/**
 * @brief Put a unsigned character into a matrix at the (x,y) coordonates.
 * 
 * @param matrix The matrix to work with.
 * @param x The rows coordinate.
 * @param y The columns coordinate.
 * @param value The UCHAR value to include in the matrix.
 */
void matrixSetUCHAR(struct MatrixUCHAR matrix, int x, int y, unsigned char value);

/**
 * @brief Put a double into a matrix at the (x,y) coordonates.
 * 
 * @param matrix The matrix to work with.
 * @param x The rows coordinate.
 * @param y The columns coordinate.
 * @param value The DOUBLE value to include in the matrix.
 */
void matrixSetDOUBLE(struct MatrixDOUBLE matrix, int x, int y, double value);

/**
 * @brief Put a integer into a matrix at the (x,y) coordonates.
 * 
 * @param matrix The matrix to work with.
 * @param x The rows coordinate.
 * @param y The columns coordinate.
 * @param value The INT value to include in the matrix.
 */
void matrixSetINT(struct MatrixINT matrix, int x, int y, int value);

/**
 * @brief Return the (x,y) unsigned charater in a matrix.
 * 
 * @param matrix The matrix to work with.
 * @param x The rows coordinate.
 * @param y The columns coordinate.
 * @return The corresponding unsigned character.
 */
unsigned char matrixGetUCHAR(struct MatrixUCHAR matrix, int x, int y);

/**
 * @brief Return the (x,y) double in a matrix.
 * 
 * @param matrix The matrix to work with.
 * @param x The rows coordinate.
 * @param y The columns coordinate.
 * @return The corresponding double.
 */
double matrixGetDOUBLE(struct MatrixDOUBLE matrix, int x, int y);

/**
 * @brief Return the (x,y) integer in a matrix.
 * 
 * @param matrix The matrix to work with.
 * @param x The rows coordinate.
 * @param y The columns coordinate.
 * @return The corresponding integer.
 */
int matrixGetINT(struct MatrixINT matrix, int x, int y);

/**
 * @brief Print a unsigned characters composed matrix.
 * 
 * @param matrix The matrix to work with.
 */
void printMatrixUCHAR(struct MatrixUCHAR matrix);

/**
 * @brief Print a double composed matrix.
 * 
 * @param matrix The matrix to work with.
 */
void printMatrixDOUBLE(struct MatrixDOUBLE matrix);
#endif