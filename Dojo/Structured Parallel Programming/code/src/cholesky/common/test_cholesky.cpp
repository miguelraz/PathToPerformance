#define NOMINMAX
#include "FortranArray.h"
#include <algorithm>
#include <math.h>
#include <tbb/tick_count.h>

#include "blas_leaf.h"

#if HAVE_CILKPLUS
#include "cilkplus/blas_cilk.h"
#endif

typedef float T;

FortranMatrix<T> A;
FortranMatrix<T> L;

void InitializeMatrices(int n) {
    // Fill L with lower-triangular matrix.  Diagonal elements must be nonzero.
    L.resize(n,n);
    L = 0;
    for( int i=1; i<=L.rows(); ++i )
        for( int j=1; j<=i; ++j ) 
            L(i,j) = i*23 + j*29;
    A.resize(n,n);
    A = 0;
    // Set A == L*L
    leaf_gemm( n, n, n, &L(1,1), L.rows(), &L(1,1), L.rows(), &A(1,1), A.rows(), 'N', 'T', T(1), 0 );
}

typedef void (*PotrfRoutine)( int n, T a[], int lda );

void TimeOnePotrf( PotrfRoutine r, const char* what ) {
    // Create local copy of A
    FortranMatrix<T> a(A);
    size_t n = a.cols();
    assert( n==a.rows() );
    tbb::tick_count t0 = tbb::tick_count::now();
    (*r)(n,&a(1,1),a.rows());
    tbb::tick_count t1 = tbb::tick_count::now();
    T error = max_diff_lower_triangle(a,L);
    // Error is expected to grow quadratically in n.
    if( error>=n*n*0.0002 ) {
        std::cout << "TimeOnePotrf FAILED with error = " << error << std::endl;
        if( n<=16 ) {
            std::cout << "a = \n" << a << std::endl;
            std::cout << "L = \n" << L << std::endl;
        }
    } else {
        std::cout << what << " " << (t1-t0).seconds() << std::endl;
    }
}

void serial_potrf( int n, T a[], int lda ) {
    int info = -1;
    leaf_potrf( n, a, lda, &info );
}

int main( int argc, char* argv[] ) {
    int n = argc>1 ? strtol(argv[1],0,0) : 4000;
    InitializeMatrices(n);
    std::cout <<                  "       Routine Seconds" << std::endl;
    for( int trial=0; trial<3; ++trial ) {
        TimeOnePotrf( serial_potrf,   "  serial_potrf" );
#if HAVE_CILKPLUS
        TimeOnePotrf( parallel_potrf, "parallel_potrf" );
#endif
    }
    return 0;
}
