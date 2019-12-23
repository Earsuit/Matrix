  Matrix.h - A free library for matrix calculation. Invalid dimension for calculation
  will lead to empty matrix, therefore, one should check whether the matrix is
  empty after calculation.

  This library is easy to use, I have overloaded operators, one can use +,*,/,-,
  =,==,!= as they want, but there is no definition for matrix division (like A/B).
  One should use the inverse function inv() instead.

  The transpose() and inv() functions are static functions, which should use
  Matrix<Type>::transpose() and Matrix<Type>::inv() format to call, Type is the
  type you used to create the matrix.

  The elements of the matrix are easy to access. For example, we have a 2 by 1 vector called A, one could use 
  A[1][0] to get the second element or A[1][0] to assign a value to it.

  The show(int decimal) function can be used to visulise the matrix, where decimal specifies the decimal numbers.

  Detailed description: https://playground.arduino.cc/Code/Matrix.

  Feedback and contribution is welcome!

  Version 1.3
  * Overloading operator [], so we can access the element by using A[][]. Because the internal data structure is a two 
    dimensional array, we have to use A[*][0] or A[0][*] to access the element in a column or row matrix.

  Version 1.2
  * Now it can perform mixed calculation with scalars. 
    But you need to ensure the dimension of the matrix is 1 for plus and minus.

  Version 1.1
  * Improved the processing speed, it becomes more efficient.

  ----------------
  Version 1.0

  Created by Yudi Ren, Jan 05, 2018.
  renyudicn@outlook.com
