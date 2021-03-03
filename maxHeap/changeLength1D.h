// change the length of an array

#ifndef changeLength1D_
#define changeLength1D_

#include <iostream>

template<class T>
void changeLength1D(T*& a, int oldLength, int newLength)
{
	if (newLength < 0)
	{
		std::cout << "New length must be >0" << std::endl;
		return 0;
	}

   T* temp = new T[newLength];              // new array
   int number = min(oldLength, newLength);  // number to copy
   copy(a, a + number, temp);
   delete [] a;                             // deallocate old memory
   a = temp;
}

#endif
