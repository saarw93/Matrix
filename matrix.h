/*Name: Saar Weitzman
  ID: 204175137    */

#ifndef _MATRIX_H
using namespace std;
#define ARROW_HEAD "Arrowhead"
#define TOEPLITZ "Toeplitz"
#define ANY "any"


class Matrix
{
private:
	double** _array;
	int rows, cols;
	string matType;

	bool isArrowHead();
	bool is_diagonal_equal(int i, int j);
	bool isToeplitz();
	Matrix* mat_before_change();
	void print_mat(double** ptr, int rows, int cols);

public:
	/*construct a rows*cols matrix from a certain matType*/
	Matrix(int rows, int cols, string matType)
	{
		if (rows < 0 || cols < 0)
		{
			cout << "NA" << endl;
			return;
		}
		else
		{
			
			if (matType.compare(ANY) && matType.compare(ARROW_HEAD) && matType.compare(TOEPLITZ))   //if(matType != ANY && matType != ARROWHEAD && matType != TOEPLITZ)
			{
				cout << "NA: Undefined matType, please enter valid type of matrix" << endl;
				this->~Matrix();
				return;
			}
			if (!matType.compare(ARROW_HEAD) && rows != cols)  // ArrowHead can be only row=col
			{
				cout << "Invalid input: Arrowhead matrix must have equal rows and cols" << endl;
				this->~Matrix();
				return;
			}
			this->rows = rows;      //saves rows in the Matrix class' variable
			this->cols = cols;     //saves cols in the Matrix class' variable
			this->matType = matType;   //saves the matType (matrix type) in the Matrix class' variable

			double **ptr = new double*[rows];
			assert(ptr != NULL);
			this->_array = ptr;    //saves the pointer to the array in the Matrix class' variable

            /*initialize the matrix - put zeroes in it*/
			for (int k = 0; k < rows; k++)
			{
				ptr[k] = new double[cols];
				assert(ptr[k] != NULL);
			}

			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < cols; j++)
					ptr[i][j] = 0;
			}
		}
	}

	void setElement(int i, int j, double data);
	double getElement(int i, int j);
	void add(Matrix& other, Matrix& result);
	bool isA(string matType);
	void rowShift(const int shiftSize);
	void colShift(const int shiftSize);
	void print();
	~Matrix();
};
#endif //	_MATRIX_H

