
This program makes matrices. It does that by the class Matrix the program is build on. Each matrix being build by the number of rows * number of columns
the user put as an input, and also has a type the user input. Each matrix the user makes is initialized to be zeroes matrix at the start.The matrix type
can be 1 of 3 types actually: "Arrowhead", "Toeplitz" or "any". Each one of the types is different, and has certain rules that the matrix has to handle.
There are several methods which can be performed on the matrices, and they are programmed to check that every change which is being performed on the matrix
does not break it's type. If a method break the matrix type, the program will not change the matrix by it. Those methods are basic methods which can be done
on matrices, like shifting rows, shifting columns, sum matrices (the add method) etc. There are also some private methods which were made to helps the
public methods do the work.

As I said at the start, the user construct the matrix he wants by making a matrix from the class Matrix, and calling the constructor that gets
3 varaiables (rows, cols, matType). The rows and cols (columns) are integers (cannot be a negative number ofcourse) and the matType (matrix type)
is a string (one of the 3 types). That way the user makes his matrix and can activate the matrix methods on it, in condition the method does not
break the matrix type, which in that case the change will not happen. 

Program matrix:
Contains class matrix (in matrix.h) that has in it the constructor, and the signatures of the public and the private methods.
The are 4 varaiables of calss Matrix: _array- the pointer to the start of the matrix (2-dimentional array), rows- the matrix number of rows,
cols- the matrix number of columns, matType- the type of the wanted matrix.

Functions:
public:
1. setElement =  set the input 'data' to be in the [i,j] place of the matrix, in case it's not ruin the matrix 'matType.
2. getElement = returns the 'data' in the [i,j] place of the matrix.
3. add = sum 2 matrices.
4. isA = checks if a matrix is from the matType it gets as an input.
5. rowShift = shift the rows of the matrix "shiftsize" times. 
6. colShift = shift the cols of the matrix "shiftsize" times.
7. print = print the matrix on the screen.
8. ~Matrix = destructor of the matrix made by the constructor.
private:
9. isArrowHead = check if the matrix is 'Arrowhead' type.
10. is_diagonal_equal =  gets the start indexes of a diagonal in the matrix, and checks if the 'data' in it is equal.
11. isToepplitz = check if the matrix is 'Toeplitz' type.
12. mat_before_change = make a copy of the matrix.
13. print_mat = print the matrix. Is called by the original method "print".

Program files:
matrix.cpp- the file contains all the implementations of the function of the class Matrix.
matrix.h- an header file ,contain the class Matrix with the constructor and declerations of functions.

Input:
1. Call the constructor with 3 varaiables (rows, cols, matType)
2. activate a method on the matrix the user construct ( for example, the user construct Matrix mat(3,3,"Arrowhead"),
can activate print method by doing mat.print()).

Output:
For print(): the matrix itself.
For isA(matType): true\false .
For getElement: the 'data' in the wanted index of the matrix.
For invalid matType: NA: Undefined matType, please enter valid type of matrix.
For not square matrix to construct "Arrowhead" matrix: Invalid input: Arrowhead matrix must have equal rows and cols.
For indexes of the matrix out of bounds: NA.
For trying activate a method on not initialized matrix: NA - The matrix should be initialized first.
For trying put 'data' in not available index (out of bounds): NA.
For triying to add 2 matrices with different sizes: NA.
