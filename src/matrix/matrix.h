#ifndef MATRIX
#define MATRIX

struct MatrixINT {
  // These corresponds to the height & width of the matrix
  int rows;
  int columns;

  // The pointer of the matrix
  // The data structure is like so :
  //  E.g :
  //        
  //   rows=3       a aa                   0 1  2 3  4 5
  //   columns=2    b bb -> IN MEMORY : | |a|aa|b|bb|c|cc|...  
  //                c cc                   ^
  //                                    Pointer
  // And the allocated size in the memory must be "sizeof(TYPE) × rows × columns"
  int* cells;
};

struct MatrixDOUBLE {
  int rows;
  int columns;
  double* cells;
};

struct MatrixUCHAR {
  int rows;
  int columns;
  unsigned char* cells;
};

// Integers composed matrix creation
struct MatrixINT createMatrixINT(int x, int y);

// Floating numbers composed matrix creation
struct MatrixDOUBLE createMatrixDOUBLE(int x, int y);

// Unsigned characters composed matrix creation
struct MatrixUCHAR createMatrixUCHAR(int x, int y);

// Check if integers composed matrix pointer is not NULL
int checkMatrixINTValidity(struct MatrixINT matrix);

// Check if doubleing numbers composed matrix pointer is not NULL
int checkMatrixDOUBLEValidity(struct MatrixDOUBLE matrix);

// Check if integers composed matrix pointer is not NULL
int checkMatrixUCHARValidity(struct MatrixUCHAR matrix);

// Check if the coordinates x & y are in a integers composed matrix
int checkMatrixINTCoord(struct MatrixINT matrix, int x, int y);

// Check if the coordinates x & y are in a doubleing numbers composed matrix
int checkMatrixDOUBLECoord(struct MatrixDOUBLE matrix, int x, int y);

// Check if the coordinates x & y are in a unisgned characters composed matrix
int checkMatrixUCHARCoord(struct MatrixUCHAR matrix, int x, int y);

// Print an error about the matrix
void printMatrixERROR(int error);

// Put a unsigned character into a matrix at the (x,y) coordonates
void matrixSetUCHAR(struct MatrixUCHAR matrix, int x, int y, unsigned char value);

// Put a double into a matrix at the (x,y) coordonates
void matrixSetDOUBLE(struct MatrixDOUBLE matrix, int x, int y, double value);

// Put a float into a matrix at the (x,y) coordonates
void matrixSetINT(struct MatrixINT matrix, int x, int y, int value);

// Return the (x,y) charater in a matrix
unsigned char matrixGetUCHAR(struct MatrixUCHAR matrix, int x, int y);

// Return the (x,y) double in a matrix
double matrixGetDOUBLE(struct MatrixDOUBLE matrix, int x, int y);

// Return the (x,y) int in a matrix
int matrixGetINT(struct MatrixINT matrix, int x, int y);

// Print a unsigned characters composed matrix
void printMatrixUCHAR(struct MatrixUCHAR matrix);

// Print a double composed matrix
void printMatrixDOUBLE(struct MatrixDOUBLE matrix);
#endif