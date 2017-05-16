// Data structures that simulate Fortran arrays

#include <cassert>
#include <cmath>
#include <cstring>
#include <iostream>
#include <iomanip>

// Template class for simulating Fortran 1D array of type T.  Indexing starts at 1.
template<typename T>
class FortranVector {
    T* my_array;
    int my_size;
public:
    FortranVector() : my_array(NULL), my_size(0) {}
    FortranVector( int n ) : my_array(new T[n]), my_size(n) {}
    ~FortranVector() {
        delete[] my_array;
    }
    int size() const {return my_size;}
    T& operator()( int i ) {
        assert( 0<i && i<=my_size );
        return my_array[i-1];
    };
    T operator()( int i ) const {
        return const_cast<FortranVector*>(this)->operator()(i);
    } 
    void resize( int size ) {
        if( size!=my_size ) {
            delete[] my_array;
            my_size = 0;
            my_array = new T[size];
            my_size = size;
        }
    }
    FortranVector( const FortranVector& x ) : my_array(NULL), my_size(0) {
        *this = x;
    }
    void operator=( const FortranVector& x ) {
        delete[] my_array;
        my_size = x.my_size;
        my_array = new T[my_size];
        memcpy( my_array, x.my_array, my_size*sizeof(T) );
    }

    void operator=( T value ) {
        T* array = my_array;
        int n = size();
        for( int i=0; i<n; ++i ) 
            array[i] = value;
    }
};

template<typename T>
std::ostream& operator<<( std::ostream& o, const FortranVector<T>& a ) {
    for( int i=1; i<=a.size(); ++i ) {
        o << "\t";
        o << a(i);
    }
    return o;
}

template<typename T>
T max_diff( const FortranVector<T>& a, const FortranVector<T>& b ) {
   assert(a.size()==b.size());
    T worse = 0;
    for( int i=1; i<=a.size(); ++i ) {
        T diff = a(i)-b(i);
        if( diff<0 ) diff=-diff;
        worse = std::max(worse, diff);
    }
    return worse;
}

// Template class for simulating Fortran 2D array of type T.  Indexing starts at 1.
template<typename T>
class FortranMatrix {
    T* my_array;
    int my_rows;
    int my_cols;
public:
    FortranMatrix() : my_array(NULL), my_rows(0), my_cols(0) {}
    FortranMatrix( int m, int n ) : my_array(new T[m*n]), my_rows(m), my_cols(n) {
    }
    ~FortranMatrix() {
        delete[] my_array;
    }
    int rows() const {return my_rows;}
    int cols() const {return my_cols;}
    T& operator()( int i, int j ) {
        assert( 0<i && i<=my_rows );
        assert( 0<j && j<=my_cols );
        return my_array[(j-1)*my_rows+(i-1)];
    };
    T operator()( int i, int j ) const {
        return const_cast<FortranMatrix*>(this)->operator()(i,j);
    } 
    FortranMatrix( const FortranMatrix& x ) : my_array(NULL), my_rows(0), my_cols(0) {
        *this = x;
    }
    void resize( int rows, int cols ) {
        if( my_rows*my_cols!=rows*cols ) {
            delete[] my_array;
            my_array = NULL;
            my_rows = 0;
            my_cols = 0;
            my_array = new T[rows*cols];
        }
        my_rows = rows;
        my_cols = cols;
    }

    void operator=( const FortranMatrix& x ) {
        resize( x.rows(), x.cols() );
        memcpy( my_array, x.my_array, my_rows*my_cols*sizeof(T) );
    }

    //! Fill matrix with value
    void operator=( T value ) {
        int size = rows()*cols();
        T* array = my_array;
        for( int k=0; k<size; ++k )
            array[k] = value; 
    }

    //! Assign from C array
    template<size_t N>
    void operator=( T rhs[][N] ) {
        assert( cols()==N );
        for( int i=1; i<=rows(); ++i )
            for( int j=1; j<=cols(); ++j )
                (*this)(i,j) = rhs[i-1][j-1];
    }

    //! Fill matrix with i*ifactor+j*jfactor
    void fill_rectangle( T ifactor, T jfactor ) {
        for( int j=1; j<=cols(); ++j )
            for( int i=1; i<=rows(); ++i )
                 (*this)(i,j) = i*ifactor+j*jfactor;
    }


    //! Fill upper triangle (including diagonal) with i*ifactor+j*jfactor.
    void fill_upper_triangle( T ifactor, T jfactor ) {
        for( int i=1; i<=rows(); ++i )
            for( int j=i; j<=cols(); ++j )
                (*this)(i,j) = i*ifactor+j*jfactor;
    }

    //! Fill diagonal with a value.
    void fill_diagonal( T value=1 ) {
        int n = std::min(rows(),cols());
        for( int k=1; k<=n; ++k )
            (*this)(k,k) = T(1);
    }

};

template<typename T>
std::ostream& operator<<( std::ostream& o, const FortranMatrix<T>& a ) {
    for( int i=1; i<=a.rows(); ++i ) {
        for( int j=1; j<=a.cols(); ++j ) {
            o << "\t" << std::setprecision(4) <<  a(i,j);
        }
        o << std::endl;
    }
    return o;
}

template<typename T>
FortranMatrix<T> operator-( const FortranMatrix<T>& a, const FortranMatrix<T>& b ) {
    FortranMatrix<T> c(a.rows(),a.cols());
    for( int i=1; i<=a.rows(); ++i )
        for( int j=1; j<=a.cols(); ++j )
            c(i,j) = a(i,j)-b(i,j);
    return c;
}

template<typename T>
T max_diff( const FortranMatrix<T>& a, const FortranMatrix<T>& b ) {
    assert(a.rows()==b.rows());
    assert(a.cols()==b.cols());
    T worse = 0;
    for( int j=1; j<=a.cols(); ++j ) 
        for( int i=1; i<=a.rows(); ++i ) 
            worse = std::max(worse, T(fabs(a(i,j)-b(i,j))));
    return worse;
}

template<typename T>
T max_diff_lower_triangle( const FortranMatrix<T>& a, const FortranMatrix<T>& b ) {
    assert(a.rows()==b.rows());
    assert(a.cols()==b.cols());
    T worse = 0;
    for( int i=1; i<=a.rows(); ++i )
        for( int j=1; j<=i; ++j )
            worse = std::max(worse, T(fabs(a(i,j)-b(i,j))));
    return worse;
}