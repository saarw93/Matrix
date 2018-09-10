/*Name: Saar Weitzman
ID: 204175137    */

#include <iostream>
#include <string>
#include <assert.h>
#include "matrix.h"
using namespace std;

#define ARROW_HEAD "Arrowhead"
#define TOEPLITZ "Toeplitz"
#define ANY "any"

/*private method to check if the matrix is 'Arrowhead' type*/
bool Matrix:: isArrowHead()
{
	if (this->rows != this->cols)       //'ArrowHead' must be a square matrix
		return false;
	int i;

	/*the loops check if there if there are other numbers than zeroes, in indexes that should be only zeroes*/
	for (i = 1; i < this->rows; i++)
	{
		for (int j = 1; j < this->cols; j++)
		{
				if (this->_array[i][j] != 0)
					if(j != 0 && i != 0 && i != j)
						return false;
		}
	}
	return true;
}

/*private method to check if the matrix is 'Toeplitz' type*/
bool Matrix:: isToeplitz()
{
	int i, j;
	for (i = 0, j = 0; i < rows; i++)   //checks the central diagonal and the lower ones
	{
		if (is_diagonal_equal(i, j) == false)
			return false;
	}
	for (i = 0, j = 1; j < cols; j++)    //checks the upper diagonals from the central one
	{
		if (is_diagonal_equal(i, j) == false)
			return false;
	}
	return true;
}

/*private method that gets the start indexes of a diagonal in the matrix, and checks if the 'data' in it is equal*/
bool Matrix::is_diagonal_equal(int iRow, int jCol)
{
	int i,j;
	double data = _array[iRow][jCol];
	for (i = iRow+1, j = jCol+1; i < this->rows && j < this->cols; i++, j++)
		if (data != _array[i][j])
			return false;
	return true;
}

/*checks if a matrix is from the matType it gets as an input*/
bool Matrix:: isA(string matType)
{
	std::cout.setf(std::ios::boolalpha);
	if (this->_array == NULL) // check if the matrix is initialized
	{
		cout << "NA - The matrix should be initialized first" << endl;
		return false;
	}

	if (!matType.compare(ARROW_HEAD))
		return isArrowHead();
	else if (!matType.compare(TOEPLITZ))
		return isToeplitz();
	else if (!matType.compare(ANY))
		return true;
	else
	{
		cout << "ERROR: The input matrix type is undefined" << endl;
		return false;
	}
}

/*set the input 'data' to be in the [i,j] place of the matrix, in case it's not ruin the matrix 'matType'*/
void Matrix:: setElement(int i, int j, double data)
{
	if (this->_array == NULL) // check if the matrix is initialized
	{
		cout << "NA - The matrix should be initialized first" << endl;
		return;
	}

	if (i < 0 || i >= this->rows || j < 0 || j >= this->cols)   //indexes out of bounds of the matrix
		cout << "NA" << endl;
	else
	{
		double temp = this->_array[i][j];      //saves the value of the index before the set, in case the matrix matType will be broken by the set
		this->_array[i][j] = data;
		if (isA(this->matType) == true)        //the set did not break the matType, so it can be done
			return;
		else
		{
			this->_array[i][j] = temp;         //the set did break the matType, so it cancel the set by putting back the original value back
			cout << "NA" << endl;
		}
	}
}

/*returns the 'data' in the [i,j] place of the matrix*/
double Matrix::getElement(int i, int j)
{
	if (this->_array == NULL) // check if the matrix is initialized
	{
		cout << "NA - The matrix should be initialized first" << endl;
		exit(-1);
	}

	if (i < 0 || i >= this->rows || j < 0 || j >= this->cols)   //indexes out of bounds of the matrix
	{
		cout << "NA" << endl;
		exit(-1);
	}
	else
		return this->_array[i][j];
}

/*add 'this' to 'other' and put the result in 'result' matrix*/
void Matrix:: add(Matrix& other, Matrix& result)
{
	if (this->_array == NULL) // check if the matrix is initialized
	{
		cout << "NA - The matrix should be initialized first" << endl;
		return;
	}

	if (other.rows != this->rows || other.cols != this->cols)     //the matrices have different size, so the add function cannot be done
	{
		cout << "NA" << endl;
		return;
	}

	if (other.matType != this->matType)        //cannot add to matrices from different 'matType'
	{
		cout << "NA" << endl;
		return;
	}
	if (!isA(other.matType))        //the 'other' matrix is not really from the matType it says it is.
	{
		cout << "NA" << endl;
		return;
	}
		
	int i;
	for (i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			double data = other.getElement(i, j) + this->getElement(i, j);
			result.setElement(i, j, data);
		}
	}
}

/*shift the rows of the matrix "shiftsize" times*/
void Matrix::rowShift(const int shiftSize)
{
	if (this->_array == NULL) // check if the matrix is initialized
	{
		cout << "NA - The matrix should be initialized first" << endl;
		return;
	}

	if (shiftSize == 0 || shiftSize%rows == 0 || (-1 * shiftSize)%rows == 0)     //in those cases the matrix shifts don't change the order of the rows
		return;

	Matrix* copy_mat = mat_before_change();   //make a copy of the mat before change, case the new mat is not in right matType
	double** temp_mat = new double*[this->rows];     //make the new mat, to change this._array afterwards to it
	assert(temp_mat != NULL);

	int i, j;
	for (i = 0; i < this->rows; i++)
	{
		if (shiftSize > 0)
		{
			int k = (i + shiftSize) % rows;
			temp_mat[k] = _array[i];
		}
		else       // (shiftSize < 0)
		{
			int k = (((rows - ((shiftSize*-1)%rows)) + i) % rows);
			temp_mat[k] = _array[i];
		}
	}

	i = 0;
	while (i < this->rows)    //change the pointing of copy_mat->_array to be the rowShifted mat (temp_mat)
	{
		this->_array[i] = temp_mat[i];
		i++;
	}
	if (isA(this->matType) == false)
	{
		cout << "NA" << endl;
		i = 0;
		while (i < this->rows)
		{
			this->_array[i] = copy_mat->_array[i];   //copy the pointers to be the original matrix before the shifts
			i++;
		}
	}
	delete copy_mat;
	delete[] temp_mat;
}

/*shift the cols of the matrix "shiftsize" times*/
void Matrix::colShift(const int shiftSize)
{
	if (this->_array == NULL) // check if the matrix is initialized
	{
		cout << "NA - The matrix should be initialized first" << endl;
		return;
	}

	if (shiftSize == 0 || shiftSize%cols == 0 || (-1 * shiftSize)%cols == 0)   //in those cases the matrix shifts don't change the order of the cols
		return;

	Matrix* copy_mat = mat_before_change();   //make a copy of the mat before change
	double** temp_mat = new double*[this->rows];  //make the new mat, to change this->_array afterwards to it
	assert(temp_mat != NULL);
	for (int j = 0; j < this->rows; j++)
	{
		temp_mat[j] = new double[this->cols];
		assert(temp_mat[j] != NULL);
	}
	int i, j;
	for (j = 0; j < this->rows; j++)
	{
		for (i = 0; i < this->cols; i++)
		{
			if (shiftSize > 0)
			{
				int k = (i + shiftSize)% cols;
				temp_mat[j][k] = _array[j][i];
			}
			else       //(shiftSize < 0)
			{
				int k = (((cols - ((shiftSize*-1)%cols)) + i) % cols);
				temp_mat[j][k] = _array[j][i];
			}
		}
	}

	i = 0;
	/*copy the new temp_mat to this->_array*/
	for (i=0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			this->_array[i][j] = temp_mat[i][j];
	}

	/*check if the new mat is from the same matType it was before the shift*/
	if (isA(this->matType) == false)
	{
		cout << "NA" << endl;
		i = 0;
		while (i < this->rows)  //change the matrix back to the original one
		{
			this->_array[i] = copy_mat->_array[i];
			i++;
		}
	}
	delete copy_mat;
	for (int i = 0; i < this->rows; i++)
		delete[] temp_mat[i];
	delete[] temp_mat;
}

/*private method to make a copy of the matrix*/
Matrix* Matrix:: mat_before_change()
{
	Matrix *copy_mat = new Matrix(this->rows, this->cols, this->matType);
	for (int i = 0 ; i < copy_mat->rows ; i++)
		for (int j = 0; j < copy_mat->cols; j++)
		{
			copy_mat->_array[i][j] = this->_array[i][j];
		}
	return copy_mat;
}

/*private method to print the matrix. Is called by the original method "print()"*/
void Matrix:: print_mat(double** ptr ,int rows, int cols)
{
	int i;
	for (i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (j + 1 == cols)
				cout << ptr[i][j] << endl;       // case of a new row in the matrix
			else
				cout << ptr[i][j] << ",";        // case of the same line in the matrix
		}
	}
}
/*print the matrix on the screen*/
void Matrix:: print()
{
	if (this->_array == NULL) // check if the matrix is initialized
	{
		cout << "NA - The matrix should be initialized first" << endl;
		return;
	}

	print_mat(_array, rows, cols);
}

/*destructor of the matrix*/
Matrix:: ~Matrix()
{
	for (int i = 0; i < rows; i++)
		delete[] _array[i];
	delete[] _array;
}