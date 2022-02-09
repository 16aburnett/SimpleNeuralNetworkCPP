// Matrix Math Library 
// Author: Amy Burnett
// Date:   January 30 2022
//========================================================================

#include "matrix.hpp"

//========================================================================

// default ctor 
Matrix::Matrix ()
{
    m_rows = 0;
    m_cols = 0; 
    m_data = nullptr; 
}

//========================================================================

// Ctor 
// Constructs a blank (zero-valued) matrix 
// with given dimensions
Matrix::Matrix (size_t rows, size_t cols) 
{

    m_rows = rows;
    m_cols = cols;
    m_data = (float*) malloc (rows * cols * sizeof(float));

    // initialize matrix data
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            m_data[i*m_cols+j] = 0.0f;
        }
    }

}

// DATA 
// ================================================================

void Matrix::setData (float* data) 
{
    if (!data || sizeof(data)==0) {
        printf ("error: data entered is not a 2 dimensional array\n");
        return;
    }

    m_data = data;

}

// Randomly generates data 
void Matrix::randomize()
{
    for(size_t i = 0; i < m_rows; i++){
        for(size_t j = 0; j < m_cols; j++){
            // generates a number between -1 and 1 
            m_data[i*m_cols+j] = ((float(rand()) / float(RAND_MAX)) * (1.0 - -1.0)) + -1.0;
        }
    }
}

// Returns a copy of this matrix 
Matrix Matrix::copy()
{
    // Creates new matrix 
    Matrix newMatrix (m_rows, m_cols);

    // Copy data to new matrix 
    for(size_t i = 0; i < m_rows; i++){
        for(size_t j = 0; j < m_cols; j++){
            newMatrix.m_data[i*m_cols+j] = m_data[i*m_cols+j];
        }
    }

    return newMatrix;

}

// Returns this matrix transposed
// -Rows become columns 
// -Columns become rows
Matrix Matrix::transpose(){
    
    // Create new transposed matrix
    Matrix transposedMatrix (m_cols, m_rows);

    // Transpose Data
    for(size_t i = 0; i < m_rows; i++){
        for(size_t j = 0; j < m_cols; j++){
            transposedMatrix.m_data[j*m_rows+i] = m_data[i*m_cols+j];
        }
    }

    return transposedMatrix;

}

// Converts this matrix to an array if there is only one column or one row
float* Matrix::toArray()
{

    // Ensure matrix can be simplified down to an array
    // - only one column or one row
    if(m_rows != 1 && m_cols != 1){
        printf("this matrix cannot be converted to an array\n");
        printf("must have 1 row or 1 column only\n");
        return nullptr;
    }

    // Convert to array 
    // 1 row || 1 column (stored the same either way, no data transfer)
    float* arr = (float*) malloc (m_rows*m_cols*sizeof(float));
    memcpy (arr, m_data, m_rows*m_cols*sizeof(float));
    return arr;

}

// Creates a matrix from an array 
// the array is converted from a single row to a single column by default
// use Const SINGLE_ROW/SINGLE_COLUMN
Matrix Matrix::fromArray(float* arr, int n, int type)
{
    // Single Column Format 
    if(type == SINGLE_COLUMN) {
        // Create matrix 
        Matrix matrix (n, 1);

        // Add data to matrix 
        for(size_t i = 0; i < matrix.m_rows; i++){
            matrix.m_data[i] = arr[i];
        }

        return matrix;
    } 
    
    // Single Row Format
    else {
        // Create matrix 
        Matrix matrix (1, n);

        // Add data to matrix 
        for(size_t i = 0; i < matrix.m_cols; i++){
            matrix.m_data[i] = arr[i];
        }

        return matrix;
    }

}


// // MATRIX MATH 
// // ================================================================

// Adds a scalar or another matrix to this matrix 
// Note: this matrix is affected while the other is not
void Matrix::add(float n){
    for(size_t i = 0; i < m_rows; i++){
        for(size_t j = 0; j < m_cols; j++){
            m_data[i*m_cols+j] += n;
        }
    }
}
void Matrix::add(Matrix n){
    // Ensure matrices have the same dimensions
    if(n.m_rows != m_rows || n.m_cols != m_cols){
        printf("error: matrices must have the same dimensions\n");
        printf("to preform elementwise operation\n");
        printf("this: %lux%lu\n", m_rows, m_cols);
        printf("addend: %lux%lu\n", n.m_rows, n.m_cols);
        return;
    }

    // Add cooresponding elements to this matrix
    for(size_t i = 0; i < m_rows; i++){
        for(size_t j = 0; j < m_cols; j++){
            m_data[i*m_cols+j] += n.m_data[i*n.m_cols+j];
        }
    }
}

// Subtracts a scalar or another matrix to this matrix 
// Note: this matrix is affected while the other is not
void Matrix::subtract(float n){
    for(size_t i = 0; i < m_rows; i++){
        for(size_t j = 0; j < m_cols; j++){
            m_data[i*m_cols+j] -= n;
        }
    }
}
void Matrix::subtract(Matrix n){
    // Ensure matrices have the same dimensions
    if(n.m_rows != m_rows || n.m_cols != m_cols){
        printf("error: matrices must have the same dimensions\n");
        printf("to preform elementwise operation\n");
        printf("this: %lux%lu\n", m_rows, m_cols);
        printf("addend: %lux%lu\n", n.m_rows, n.m_cols);
        return;
    }

    // Add cooresponding elements to this matrix
    for(size_t i = 0; i < m_rows; i++){
        for(size_t j = 0; j < m_cols; j++){
            m_data[i*m_cols+j] -= n.m_data[i*n.m_cols+j];
        }
    }
}

// Multiplies this matrix by a scalar value or another matrix
void Matrix::multiply(float n){
    for(size_t i = 0; i < m_rows; i++){
        for(size_t j = 0; j < m_cols; j++){
            m_data[i*m_cols+j] *= n;
        }
    }
}
void Matrix::multiply(Matrix n){
    // Ensure matrices have the same dimensions
    if(n.m_rows != m_rows || n.m_cols != m_cols){
        printf("error: matrices must have the same dimensions\n");
        printf("to preform elementwise operation\n");
        printf("this: %lux%lu\n", m_rows, m_cols);
        printf("addend: %lux%lu\n", n.m_rows, n.m_cols);
        return;
    }

    // Add cooresponding elements to this matrix
    for(size_t i = 0; i < m_rows; i++){
        for(size_t j = 0; j < m_cols; j++){
            m_data[i*m_cols+j] *= n.m_data[i*n.m_cols+j];
        }
    }
}


// Tests if a given matrix equals this matrix
bool Matrix::equals(Matrix m){
    // Ensure that given matrix matches the dimensions of this matrix 
    if(m.m_rows != m_rows || m.m_cols != m_cols){
        return false;
    }

    // Ensure data matches 
    for(size_t i = 0; i < m_rows; i++){
        for(size_t j = 0; j < m_cols; j++){
            // Returns false if elements are not equal
            if(m_data[i*m_cols+j] != m.m_data[i*m.m_cols+j]){
                return false;
            }
        }
    }
    return true;
}

// Applies a given function to each element of this matrix
void Matrix::map(float (*f)(float)){
    for(size_t i = 0; i < m_rows; i++) {
        for(size_t j = 0; j < m_cols; j++){
            // pass through function
            m_data[i*m_cols+j] = f(m_data[i*m_cols+j]);
        }
    }
}

// // STATIC METHODS: MATH 
// // ================================================================

// Adds a scalar to a matrix or adds two matrices together elementwise
// note: none of the matrices are altered 
// the result is return as a new matrix
Matrix Matrix::add (float a, Matrix b){
    Matrix c (b.m_rows, b.m_cols);
    for(size_t i = 0; i < b.m_rows; i++){
        for(size_t j = 0; j < b.m_cols; j++){
            c.m_data[i*c.m_cols+j] = b.m_data[i*b.m_cols+j] + a;
        }
    } 
    return c;
}
Matrix Matrix::add (Matrix a, float b){
    Matrix c (a.m_rows, a.m_cols);
    for(size_t i = 0; i < a.m_rows; i++){
        for(size_t j = 0; j < a.m_cols; j++){
            c.m_data[i*c.m_cols+j] = a.m_data[i*a.m_cols+j] + b;
        }
    }
    return c; 
}
Matrix Matrix::add (Matrix a, Matrix b){
    // Ensure matrices have the same dimensions
    if(b.m_rows != a.m_rows || b.m_cols != a.m_cols){
        printf ("matrices must have the same dimensions\n");
        printf ("to preform elementwise operation\n");
        printf ("a: %lux%lu\n", a.m_rows, a.m_cols);
        printf ("b: %lux%lu\n", b.m_rows, b.m_cols);
        return Matrix();
    }

    Matrix c (a.m_rows, a.m_cols);
    // Add cooresponding elements to this matrix
    for(size_t i = 0; i < a.m_rows; i++){
        for(size_t j = 0; j < a.m_cols; j++){
            c.m_data[i*c.m_cols+j] = a.m_data[i*a.m_cols+j] + b.m_data[i*b.m_cols+j];
        }
    }
    return c; 
}

// Subtract a scalar to a matrix or Subtracts two matrices together elementwise
// note: none of the matrices are altered 
// the result is return as a new matrix
// first param should be the matrix 
Matrix Matrix::subtract (float a, Matrix b){
    Matrix c (b.m_rows, b.m_cols);
    for(size_t i = 0; i < b.m_rows; i++){
        for(size_t j = 0; j < b.m_cols; j++){
            c.m_data[i*c.m_cols+j] = b.m_data[i*b.m_cols+j] - a;
        }
    } 
    return c;
}
Matrix Matrix::subtract (Matrix a, float b){
    Matrix c (a.m_rows, a.m_cols);
    for(size_t i = 0; i < a.m_rows; i++){
        for(size_t j = 0; j < a.m_cols; j++){
            c.m_data[i*c.m_cols+j] = a.m_data[i*a.m_cols+j] - b;
        }
    }
    return c; 
}
Matrix Matrix::subtract (Matrix a, Matrix b){
    // Ensure matrices have the same dimensions
    if(b.m_rows != a.m_rows || b.m_cols != a.m_cols){
        printf ("matrices must have the same dimensions\n");
        printf ("to preform elementwise operation\n");
        printf ("a: %lux%lu\n", a.m_rows, a.m_cols);
        printf ("b: %lux%lu\n", b.m_rows, b.m_cols);
        return Matrix();
    }

    Matrix c (a.m_rows, a.m_cols);
    // Add cooresponding elements to this matrix
    for(size_t i = 0; i < a.m_rows; i++){
        for(size_t j = 0; j < a.m_cols; j++){
            c.m_data[i*c.m_cols+j] = a.m_data[i*a.m_cols+j] - b.m_data[i*b.m_cols+j];
        }
    }
    return c; 
}

// Multiplies a matrix by a scalar value or another matrix
// uses hadamard product 
// returns the new matrix 
Matrix Matrix::multiply (float a, Matrix b){
    Matrix c (b.m_rows, b.m_cols);
    for(size_t i = 0; i < b.m_rows; i++){
        for(size_t j = 0; j < b.m_cols; j++){
            c.m_data[i*c.m_cols+j] = b.m_data[i*b.m_cols+j] * a;
        }
    } 
    return c;
}
Matrix Matrix::multiply (Matrix a, float b){
    Matrix c (a.m_rows, a.m_cols);
    for(size_t i = 0; i < a.m_rows; i++){
        for(size_t j = 0; j < a.m_cols; j++){
            c.m_data[i*c.m_cols+j] = a.m_data[i*a.m_cols+j] * b;
        }
    }
    return c; 
}
Matrix Matrix::multiply (Matrix a, Matrix b){
    // Ensure matrices have the same dimensions
    if(b.m_rows != a.m_rows || b.m_cols != a.m_cols){
        printf ("matrices must have the same dimensions\n");
        printf ("to preform elementwise operation\n");
        printf ("a: %lux%lu\n", a.m_rows, a.m_cols);
        printf ("b: %lux%lu\n", b.m_rows, b.m_cols);
        return Matrix();
    }

    Matrix c (a.m_rows, a.m_cols);
    // Add cooresponding elements to this matrix
    for(size_t i = 0; i < a.m_rows; i++){
        for(size_t j = 0; j < a.m_cols; j++){
            c.m_data[i*c.m_cols+j] = a.m_data[i*a.m_cols+j] * b.m_data[i*b.m_cols+j];
        }
    }
    return c; 
}

// Multiplies two given matrices together 
// Using the matrix product method
Matrix Matrix::product (Matrix a, Matrix b){

    // Ensure Matrix Multiplication can be applied
    // - Columns of 'a' must equal rows of 'b'
    if(a.m_cols == b.m_rows){

        // Create Product matrix
        // - with rows of 'a' and columns of 'b'
        Matrix product (a.m_rows, b.m_cols);

        // Each row of 'a' multiplied by each column of 'b'
        for (size_t i = 0; i < a.m_rows; i++){
            for (size_t j = 0; j < b.m_cols; j++){

                // dot-product
                // each elem in 'a's row are
                // multiplied by cooresponding elements in 'b's column
                // and added together 
                for (size_t elem = 0; elem < a.m_cols; elem++){
                    product.m_data[i*product.m_cols+j] += a.m_data[i*a.m_cols+elem] * b.m_data[elem*b.m_cols+j]; 
                }

            }
        }

        return product;

    }
}

// Returns given matrix transposed
// -Rows become columns 
// -Columns become rows
Matrix Matrix::transpose(Matrix m){
    
    // Create new transposed matrix
    Matrix transposedMatrix (m.m_cols, m.m_rows);

    // Transpose Data
    for(size_t i = 0; i < m.m_rows; i++){
        for(size_t j = 0; j < m.m_cols; j++){
            transposedMatrix.m_data[j*m.m_rows+i] = m.m_data[i*m.m_cols+j];
        }
    }

    return transposedMatrix;

}

// Applies a given function to elements of a given matrix
// returns a new matrix of the application
// Note: original matrix is unnaffected
Matrix Matrix::map (Matrix m, float (*fn)(float)){

    Matrix matrix (m.m_rows, m.m_cols);

    for(size_t i = 0; i < m.m_rows; i++) {
        for(size_t j = 0; j < m.m_cols; j++){
            // pass through function
            matrix.m_data[i*matrix.m_cols+j] = fn(m.m_data[i*m.m_cols+j]);
        }
    }

    return matrix;

}

// PRINTING 
// ================================================================

// Prints the matrix in a row/column format
void Matrix::print() 
{
    for (size_t i = 0; i < m_rows; i++) {
        for (size_t j = 0; j < m_cols; j++) {
            printf ("% 8.2f ", m_data[i*m_cols+j]);
        }
        printf ("\n");
    }
}

// ================================================================


/*
 Matrix m (3, 5);
    m.print(); 
    printf ("\n");

    m.setData (new float [3*5] {
        0.25, 0.45, 0.30, 0.22, 0.47,
        0.43, 0.87, 0.65, 2.34, 0.45,
        0.23, 0.21, 0.67, 1.00, 0.43
    });
    m.print(); 
    printf ("\n");

    m.randomize ();
    m.print ();
    printf ("\n");

    printf ("Copy\n");
    Matrix a = m.copy ();
    m.randomize ();
    printf ("A:\n");
    a.print ();
    printf ("B:\n");
    m.print ();
    printf ("\n");

    printf ("Transposed\n");
    a = a.transpose ();
    printf ("A:\n");
    a.print ();
    printf ("\n");

    printf ("toArray\n");
    Matrix b (5, 1);
    b.setData (new float[5] {0.12, 0.34, 0.2, 3.14, 0.53});
    b.print();
    printf ("\n");
    float* arr = b.toArray ();
    for (int i = 0; i < 5; ++i)
        printf ("%f ", arr[i]);
    printf ("\n");
    printf ("\n");

    printf ("fromArray\n");
    Matrix c = Matrix::fromArray (arr, 5, SINGLE_ROW);
    c.print ();
    printf ("\n");

    printf ("A+5\n");
    a = Matrix (2, 3);
    a.setData (new float[6] {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0
    });
    a.print();
    a.subtract (5);
    a.print();

    b = Matrix (2, 3);
    b.setData (new float[6] {
        6.0, 5.0, 4.0,
        3.0, 2.0, 1.0
    });
    a.subtract (b);
    a.print();

    b = a.copy ();
    printf ("a == b -> %d\n", a.equals(b));
    printf ("a == c -> %d\n", a.equals(c));

    auto func = [] (float a) {return a>0.0 ? 1.0f : -1.0f;};
    a.randomize ();
    a.print();
    b = Matrix::map (a, func);
    b.print ();
    printf("\n");

    c = Matrix::add(a, 7);
    a.print();
    c.print();
    Matrix d = Matrix::add(7, a);
    printf ("%d\n", c.equals(d));

    c = Matrix::add(a, c);
    c.print();

    printf ("DotProduct\n");
    a = Matrix (2, 3);
    a.setData (new float[6] {
        1, 2, 3,
        4, 5, 6
    });
    b = Matrix (3, 2);
    b.setData (new float[6] {
        7, 8, 
        9, 10,
        11, 12
    });
    a.print();
    printf("\n");
    b.print();
    printf("\n");
    c = Matrix::product (a, b);
    c.print();
    printf("\n");
    c = Matrix::transpose (c);
    c.print();
    printf("\n");


*/