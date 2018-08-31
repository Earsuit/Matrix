  Matrix.h - A free library for matrix calculation. Invalid dimension for calculation
  will lead to empty matrix, therefore, one should check whether the matrix is
  empty after calculation.

  This library is easy to use, I have overloaded operators, one can use +,*,/,-,
  =,==,!= as they want, but there is no definition for matrix division (like A/B).
  One should use the inverse function inv() instead.

  The transpose() and inv() functions are static functions, which should use
  Matrix<Type>::transpose() and Matrix<Type>::inv() format to call, Type is the
  type you used to create the matrix.

  The elements of the matrix are stored in a public member of the instance called "_entity",
  which is a 2D array. For example, we have a 2 by 1 vector called A, one could use 
  A._entity[1][0] to get the second element.

  Feedback and contribution is welcome!

  Version 1.2
  * Now it can perform mixed calculation with scalars.

  Version 1.1
  * Improved the processing speed, it becomes more efficient.

  ----------------
  Version 1.0

  Created by Yudi Ren, Jan 05, 2018.
  renyudicn@outlook.com
