  Matrix.h - Library for matrix calculation. Invalid dimension for calculation
  will lead to empty matrix, therefore, one should check whether the matrix is
  empty after calculation.
  
  This library is easy to use, I have overloaded operators, one can use +,*,/,-,
  =,==,!= as they want, but there is no definition for matrix division (like A/B).
  One should use the inverse function .inv() instead.
  
  To get a better performance, it's recommended to use /=, *=, -= and += if you
  have A = A*B, A = A+B or A = A/b (b is a scalar). If you have A = B*C,
  the times(const Matrix & B,const Matrix & C) function gives faster performance.
  
  However, using this library to do matrix calculation is not very
  efficient, if you have a time-critical sketch, it would be better to write your
  own code which is optimised for your project.
  
  If you want to use the .show() function, you have to initialise the Serial 
  communication.
  
  Created by Yudi Ren, Jan 05, 2018.
  renyudicn@outlook.com
  Version 0.1
