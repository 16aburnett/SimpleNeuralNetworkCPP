// Matrix Math Library 
// Author: Amy Burnett
// Date:   January 30 2022
//========================================================================

#ifndef MATRIX_HPP
#define MATRIX_HPP

//========================================================================

#include <stdlib.h>
#include <stdio.h>
#include <cstring> // memcpy 

//========================================================================

const int SINGLE_ROW = 1;
const int SINGLE_COLUMN = 0;

//========================================================================

class Matrix 
{

public:
    // Members
    float* m_data;
    size_t m_rows;
    size_t m_cols; 


    // ================================================================

    Matrix ();
    // Ctor 
    // Constructs a blank (zero-valued) matrix 
    // with given dimensions
    Matrix (size_t rows, size_t cols);

    // DATA 
    // ================================================================

    // data should contain rows*cols # of data 
    void setData(float* data);

    // Randomly generates data 
    void randomize();

    // Returns a copy of this matrix 
    Matrix copy();

    // Returns this matrix transposed
    // -Rows become columns 
    // -Columns become rows
    Matrix transpose();

    // Converts this matrix to an array if there is only one column or one row
    float* toArray();

    // Converts and returns an array into a matrix 
    // the array is converted from a single row to a single column by default
    // use Const SINGLE_ROW/SINGLE_COLUMN
    static Matrix fromArray(float* arr, int n, int type);

    // MATRIX MATH 
    // ================================================================

    // Adds a scalar or another matrix to this matrix 
    // Note: this matrix is affected while the other is not
    void add(float n);
    void add(Matrix n);

    // Subtracts a scalar or another matrix to this matrix 
    // Note: this matrix is affected while the other is not
    void subtract(float n);
    void subtract(Matrix n);

    // Multiplies this matrix by a scalar value or another matrixv
    void multiply(float n);
    void multiply(Matrix n);

    // Tests if a given matrix equals this matrix
    bool equals(Matrix m);

    // Applies a given function to each element of this matrix
    void map(float (*f)(float));

    // STATIC METHODS: MATH 
    // ================================================================

    // Adds a scalar to a matrix or adds two matrices together elementwise
    // note: none of the matrices are altered 
    // the result is return as a new matrix
    static Matrix add(float a, Matrix b);
    static Matrix add(Matrix a, float b);
    static Matrix add(Matrix a, Matrix b);

    // Subtract a scalar to a matrix or Subtracts two matrices together elementwise
    // note: none of the matrices are altered 
    // the result is return as a new matrix
    static Matrix subtract(float a, Matrix b);
    static Matrix subtract(Matrix a, float b);
    static Matrix subtract(Matrix a, Matrix b);

    // Multiplies a matrix by a scalar value or another matrix
    // uses hadamard product (element-wise)
    // returns the new matrix 
    static Matrix multiply(float a, Matrix b);
    static Matrix multiply(Matrix a, float b);
    static Matrix multiply(Matrix a, Matrix b);

    // Multiplies two given matrices together 
    // Using the matrix product method
    static Matrix product(Matrix a, Matrix b);

    // Returns given matrix transposed
    // -Rows become columns 
    // -Columns become rows
    static Matrix transpose(Matrix m);

    // Applies a given function to elements of a given matrix
    // returns a new matrix of the application
    // Note: original matrix is unnaffected
    static Matrix map(Matrix m, float (*fn)(float));

    // PRINTING 
    // ================================================================

    // Prints the matrix in a row/column format
    void print();


};


//========================================================================

#endif 