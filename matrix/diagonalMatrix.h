#pragma  once


#ifndef _diagonalMatrix_H_
#define _diagonalMatrix_H_

// ∂‘Ω«æÿ’Û

template<class T>
class diagonalMatrix
{
public:
	diagonalMatrix(int theN = 10);
	~diagonalMatrix() { delete[] element; }
	T get(int, int) const;
	void set(int, int, const T&);
private:
	int n;       // matrix dimension
	T *element;  // 1D array for diagonal elements
};

template<class T>
diagonalMatrix<T>::diagonalMatrix(int theN)
{// Constructor.
   // validate theN
	if (theN < 1)
		return;

	n = theN;
	element = new T[n];
}

template <class T>
T diagonalMatrix<T>::get(int i, int j) const
{// Return (i,j)th element of matrix.
   // validate i and j
	if (i < 1 || j < 1 || i > n || j > n)
		return;
	if (i == j)
		return element[i - 1];   // diagonal element
	else
		return 0;              // nondiagonal element
}

template<class T>
void diagonalMatrix<T>::set(int i, int j, const T& newValue)
{// Store newValue as (i,j)th element.
   // validate i and j
	if (i < 1 || j < 1 || i > n || j > n)
		return;

	if (i == j)
		// save the diagonal value
		element[i - 1] = newValue;
	else
		// nondiagonal value, newValue must be zero
		if (newValue != 0)
			return;
}

#endif
