struct Matrix {
  // These corresponds to the height & width of the matrix
  int rows;
  int columns;

  // The pointer of the matrix
  // The data structure is like so :
  //  E.g :
  //        a aa 
  //        b bb -> IN MEMORY : | |a|aa|b|bb|c|cc|...  
  //        c cc                   ^
  //                            Pointer
  // And the allocated size in the memory must be "sizeof(TYPE) × x × y"
  int* pointer;
};

// Matrix creation
struct Matrix CreateMatrix(int x, int y,int sizeof_type);

// Check if matrix pointer is not NULL
int CheckMatrixValidity(struct Matrix matrix);

// Check if the coordinates x & y are in a matrix
int CheckMatrixCoord(struct Matrix matrix, int x, int y);

// Print an error about the matrix
void PrintMatrixERROR(int error);

// Put a unsigned character into a matrix at the (x,y) coordonates
void MatrixSetUCHAR(struct Matrix matrix, int x, int y, unsigned char value);

// Put a float into a matrix at the (x,y) coordonates
void MatrixSetFLOAT(struct Matrix matrix, int x, int y, float value);

// Return the (x,y) charater in a matrix
unsigned char MatrixGetUCHAR(struct Matrix matrix, int x, int y);

// Return the (x,y) float in a matrix
float MatrixGetFLOAT(struct Matrix matrix, int x, int y);

// Print a unsigned characters composed matrix
void PrintMatrixUCHAR(struct Matrix matrix);

// Print a float composed matrix
void PrintMatrixFLOAT(struct Matrix matrix);