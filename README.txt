Matrix.h - Library for matrix calculation. Invalid dimension for calculation
will lead to empty matrix, therefore, one should check whether the matrix is
empty after calculation.

To get a better performance, it's recommended to use /=, *=, -= and += if you
have A = A*B, A = A+B or A = A/b (b is a scalar). If you have A = B*C,
the times(const Matrix & B,const Matrix & C) function gives faster performance.

However, using this library to do matrix calculation is not very
efficient, if you have a time-critical sketch, it would be better to write your
own code which is optimised for your project.

Created by Yudi Ren, Jan 05, 2018.
renyudicn@outlook.com
Version 0.1