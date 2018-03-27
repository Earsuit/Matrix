  Matrix.h - A free library for matrix calculation. Invalid dimension for calculation
  will lead to empty matrix, therefore, one should check whether the matrix is
  empty after calculation.

  This library is easy to use, I have overloaded operators, one can use +,*,/,-,
  =,==,!= as they want, but there is no definition for matrix division (like A/B).
  One should use the inverse function inv() instead.

  The transpose() and inv() functions are static functions, which should use
  Matrix<Type>::transpose() and Matrix<Type>::inv() format to call, Type is the
  type you used to create the matrix.

  Feedback and contribution is welcome!

  Version 1.1
  * Improved the processing speed

  ----------------
  Version 1.0

  Created by Yudi Ren, Jan 05, 2018.
  renyudicn@outlook.com
