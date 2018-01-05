/*
  Matrix.h - Library for matrix calculation. Invalid dimension for calculation
  will lead to empty matrix, therefore, one should check whether the matrix is
  empty after calculation.

  This library is easy to use, I have overloaded operators, one can use +,*,/,-
  as they want, but there is no definition for matrix division (like A/B).
  One should use the inverse function inv() instead. 

  To get a better performance, it's recommended to use /=, *=, -= and += if you
  have A = A*B, A = A+B or A = A/b (b is a scalar). If you have A = B*C,
  the times(const Matrix & B,const Matrix & C) function gives faster performance.

  However, using this library to do matrix calculation is not very
  efficient, if you have a time-critical sketch, it would be better to write your
  own code which is optimised for your project.

  Created by Yudi Ren, Jan 05, 2018.
  renyudicn@outlook.com
  Version 0.1
*/

#ifndef MATRIX_H
#define MATRIX_H

template <class Any>
class Matrix
{
    public:
        int _row;
        int _column;
        Any** _entity;
        Matrix();
        //ini stands for the initial value of all elements, r is row, c is column
        Matrix(int r,int c, int ini=0);
        //copy constructor, one can directly use the "=" operator like A=B
        Matrix(const Matrix & m);
        //for a 2d array, you need to cast it to (Any*) type, see example for
        //more information
        Matrix(int r,int c,Any* m);
        /*
            'I': create an identity matrix when r==c, otherwise it's empty
        */
        Matrix(int r,int c, char type);
        ~Matrix();
        Matrix operator*(const Matrix & A);
        Matrix & operator*=(const Matrix & A);
        Matrix operator*(Any a);
        Matrix & operator*=(Any a);
        template <class T, class G>
        friend Matrix<T> operator*(G a, const Matrix<T> & A);
        void times(const Matrix & A,const Matrix & B);
        Matrix operator/(Any a);
        Matrix & operator/=(Any a);
        Matrix operator+(const Matrix & A);
        Matrix & operator+=(const Matrix & A);
        Matrix operator-(const Matrix & A);
        Matrix & operator-=(const Matrix & A);
        Matrix transpose();
        Matrix & operator=(const Matrix & A);
        bool operator!=(const Matrix & A);
        bool operator==(const Matrix & A);
        //The inverse function uses the Gauss-Jordan Elimination
        Matrix inv();
        //i: the row needs to be swaped, j: the position the row i goes to
        void swapRow(int i, int j);
        //decimal: the numbers of decimal place
        void show(int decimal = 0);
        //check if it's an empty matrix.
        bool notEmpty();
};

template <class Any>
Matrix<Any>::Matrix(){
    _row = 0;
    _column = 0;
    _entity = NULL;
}

template <class Any>
Matrix<Any>::Matrix(int r,int c, int ini){
    _row = r;
    _column = c;
    _entity = new Any*[_row];
    for(int i=0;i<_row;i++)
        _entity[i] = new Any[_column];

    for(int i=0;i<_row;i++)
        for(int j=0;j<_column;j++)
            _entity[i][j] = ini;
}

template <class Any>
Matrix<Any>::Matrix(const Matrix<Any> & m){
    _row = m._row;
    _column = m._column;

    _entity = new Any*[_row];
    for(int i=0;i<_row;i++)
        _entity[i] = new Any[_column];

    for(int i=0;i<_row;i++)
        for(int j=0;j<_column;j++)
            _entity[i][j] = m._entity[i][j];
}

template <class Any>
Matrix<Any>::Matrix(int r,int c, Any* m){
    _row = r;
    _column = c;

    _entity = new Any*[_row];
    for(int i=0;i<r;i++)
        _entity[i] = new Any[_column];

    for(int i=0;i<_row;i++)
        for(int j=0;j<_column;j++){
            _entity[i][j] = *((m+i*_column)+j);
        }
}

template <class Any>
Matrix<Any>::Matrix(int r,int c,char type){
    _row = r;
    _column = c;

    _entity = new Any*[_row];
    for(int i=0;i<r;i++)
        _entity[i] = new Any[_column];

    switch(type){
        case 'I':  //identity matrix
            if(r == c){
                for(int i=0;i<_row;i++)
                    for(int j=0;j<_column;j++)
                        _entity[i][j] = (i==j?1:0);
            }else{
                for(int i=0;i<_row;i++)
                    delete [] _entity[i];
                delete [] _entity;
            }
            break;
        default:
            for(int i=0;i<_row;i++)
                for(int j=0;j<_column;j++)
                    _entity[i][j] = 0;
    }
}

template <class Any>
Matrix<Any>::~Matrix(){
    for(int i=0;i<_row;i++)
        delete [] _entity[i];
    delete [] _entity;
}

template <class Any>
Matrix<Any> Matrix<Any>::operator*(const Matrix<Any> & A){
    if(_column != A._row)
        return Matrix();

    Matrix<Any> tmp(_row,A._column);

    for(int i=0;i<_row;i++)
        for(int j=0;j<A._column;j++){
            for(int k=0;k<_column;k++)
                tmp._entity[i][j] += _entity[i][k]*A._entity[k][j];
        }

    return Matrix(tmp);
}

template <class Any>
Matrix<Any> & Matrix<Any>::operator*=(const Matrix<Any> & A){
    //check if the dimension matches
    if(_column != A._row){
        for(int i=0;i<_row;i++)
            delete [] _entity[i];
        delete [] _entity;
        return *this;
    }

    Matrix<Any> tmp(*this);

    //the dimension of the result matrix does not match the calling matrix
    if(_column != A._column){
        for(int i=0;i<_row;i++)
            delete [] _entity[i];

        _column = A._column;

        for(int i=0;i<_row;i++)
            _entity[i] = new Any[_column];

        for(int i=0;i<_row;i++)
            for(int j=0;j<_column;j++){
                _entity[i][j] = 0;
                for(int k=0;k<tmp._column;k++)
                    _entity[i][j] += tmp._entity[i][k] * A._entity[k][j];
            }
    }else{ //the dimension of the result matrix matches the calling matrix
        for(int i=0;i<_row;i++)
            for(int j=0;j<_column;j++){
                _entity[i][j] = 0;
                for(int k=0;k<_column;k++)
                    _entity[i][j] += tmp._entity[i][k]*A._entity[k][j];
            }
    }

    return *this;
}

template <class Any>
Matrix<Any> Matrix<Any>::operator*(Any a){
    Matrix<Any> tmp(_row,_column);

    for(int i=0;i<_row;i++)
        for(int j=0;j<_column;j++){
            tmp._entity[i][j] = _entity[i][j]*a;
        }

    return Matrix(tmp);
}

template <class Any>
Matrix<Any> & Matrix<Any>::operator*=(Any a){
    for(int i=0;i<_row;i++)
        for(int j=0;j<_column;j++){
            _entity[i][j] *= a;
        }

    return *this;
}

template <class Any, class G>
Matrix<Any> operator*(G a, const Matrix<Any> & A){
    return A*a;
}

template <class Any>
void Matrix<Any>::times(const Matrix<Any> & A,const Matrix<Any> & B){
    if(A._column == B._row){
        if(A._row != _row || B._column != _column){
            for(int i=0;i<_row;i++)
                delete [] _entity[i];
            delete [] _entity;

            _row = A._row;
            _column = B._column;

            _entity = new Any*[_row];
            for(int i=0;i<_row;i++)
                _entity[i] = new Any[_column];
        }

        for(int i=0;i<A._row;i++)
            for(int j=0;j<B._column;j++){
                _entity[i][j] = 0;
                for(int k=0;k<A._column;k++)
                    _entity[i][j] += A._entity[i][k]*B._entity[k][j];
                }
    }else{
        for(int i=0;i<_row;i++)
            delete [] _entity[i];
        delete [] _entity;
    }
}

template <class Any>
Matrix<Any> Matrix<Any>::operator/(Any a){
    Matrix<Any> tmp(_row,_column);

    for(int i=0;i<_row;i++)
        for(int j=0;j<_column;j++){
            tmp._entity[i][j] = _entity[i][j]/a;
        }

    return Matrix(tmp);
}

template <class Any>
Matrix<Any> & Matrix<Any>::operator/=(Any a){
    for(int i=0;i<_row;i++)
        for(int j=0;j<_column;j++){
            _entity[i][j] /= a;
        }

    return *this;
}

template <class Any>
Matrix<Any> Matrix<Any>::operator+(const Matrix<Any> & A){
    if(_row != A._row || _column != A._column)
        return Matrix();

    Matrix<Any> tmp(_row,_column);

    for(int i=0;i<_row;i++)
        for(int j=0;j<_column;j++){
            tmp._entity[i][j] = _entity[i][j]+A._entity[i][j];
        }

    return Matrix(tmp);
}

template <class Any>
Matrix<Any> & Matrix<Any>::operator+=(const Matrix<Any> & A){
    if(_row != A._row || _column != A._column){
        for(int i=0;i<_row;i++)
            delete [] _entity[i];
        delete [] _entity;
        return *this;
    }

    for(int i=0;i<_row;i++)
        for(int j=0;j<_column;j++){
            _entity[i][j] = _entity[i][j] + A._entity[i][j];
        }

    return *this;
}

template <class Any>
Matrix<Any> Matrix<Any>::operator-(const Matrix<Any> & A){
    if(_row != A._row || _column != A._column)
        return Matrix();

    Matrix<Any> tmp(_row,_column);

    for(int i=0;i<_row;i++)
        for(int j=0;j<_column;j++){
            tmp._entity[i][j] = _entity[i][j]-A._entity[i][j];
        }

    return Matrix(tmp);
}

template <class Any>
Matrix<Any> & Matrix<Any>::operator-=(const Matrix<Any> & A){
    if(_row != A._row || _column != A._column){
        for(int i=0;i<_row;i++)
            delete [] _entity[i];
        delete [] _entity;
        return *this;
    }

    for(int i=0;i<_row;i++)
        for(int j=0;j<_column;j++){
            _entity[i][j] = _entity[i][j] - A._entity[i][j];
        }

    return *this;
}

template <class Any>
Matrix<Any> Matrix<Any>::transpose(){
    Matrix<Any> tmp(_column,_row);

    for(int i=0;i<_row;i++)
        for(int j=0;j<_column;j++)
            tmp._entity[j][i] = _entity[i][j];

    return tmp;
}

template <class Any>
Matrix<Any>& Matrix<Any>::operator=(const Matrix<Any> & A){
    if(_entity != NULL){
        for(int i=0;i<_row;i++)
            delete [] _entity[i];
        delete [] _entity;
    }

    _row = A._row;
    _column = A._column;

    _entity = new Any*[_row];
    for(int i=0;i<_row;i++)
        _entity[i] = new Any[_column];

    for(int i=0;i<_row;i++)
        for(int j=0;j<_column;j++)
            _entity[i][j] = A._entity[i][j];

    return *this;
}

template <class Any>
bool Matrix<Any>::operator!=(const Matrix<Any> & A){
    if(_row!=A._row || _column != A._column)
        return true;

    for(int i=0;i<_row;i++)
        for(int j=0;j<_column;j++)
            if(_entity[i][j] != A._entity[i][j])
                return true;

    return false;
}

template <class Any>
bool Matrix<Any>::operator==(const Matrix<Any> & A){
    if(_row != A._row || _column != A._column)
        return false;

    for(int i=0;i<_row;i++)
        for(int j=0;j<_column;j++)
            if(_entity[i][j] != A._entity[i][j])
                return false;

    return true;
}

template <class Any>
Matrix<Any> Matrix<Any>::inv(){
    //has to be a square matrix
    if(_row != _column){
        return Matrix<Any>();
    }

    Matrix<Any> tmp(_row,_column,'I');
    Matrix<Any> copy(*this);

    //set the pivot to be the largest element in that column
    for(int i=0;i<_row-1;i++){
        Any pivot = copy._entity[i][i];
        int row = i;
        for(int j = i+1;j<_row;j++)
            if(copy._entity[j][i] > pivot){
                pivot = copy._entity[j][i];
                row = j;
            }

        if(pivot == 0){
            return Matrix<Any>();
        }else{
            copy.swapRow(i,row);
            tmp.swapRow(i,row);
        }
    }

    for(int i=0;i<_row;i++)
        for(int j=0;j<_row;j++)
            if(i!=j){
                Any backup = copy._entity[j][i];
                for(int k=0;k<_column;k++){
                    copy._entity[j][k] -= backup*copy._entity[i][k]/copy._entity[i][i];
                    tmp._entity[j][k] -= backup*tmp._entity[i][k]/copy._entity[i][i];
                }
            }

    for(int i=0;i<_row;i++)
        for(int j=0;j<_column;j++){
            tmp._entity[i][j] /= copy._entity[i][i];
        }

    return tmp;
}

template <class Any>
void Matrix<Any>::swapRow(int i,int j){
    if(i!=j && i<_row && j<_row && i>=0 && j>=0){
        Any tmp;
        for(int k=0;k<_column;k++){
            tmp = _entity[j][k];
            _entity[j][k] = _entity[i][k];
            _entity[i][k] = tmp;
        }
    }
}

template <class Any>
void Matrix<Any>::show(int decimal)
{
    if(decimal<0)
        decimal = 0;

	for(int i=0; i<_row; i++)
	{
	    Serial.print("[");
	    for(int j=0; j<_column; j++)
		{
			Serial.print("  ");
            Serial.print(_entity[i][j],decimal);
            Serial.print(" ");
		}
		Serial.println("]");
	}
    Serial.println();
}

template <class Any>
bool Matrix<Any>::notEmpty(){
    if(_entity == NULL)
        return false;
    return true;
}
#endif
