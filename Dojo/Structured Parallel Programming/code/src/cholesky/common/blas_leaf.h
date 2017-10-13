// leaf_... routines provide overload interface MKL routines so that templates can call them for both float and double.
// Default arguments generally follow the Fortran95 conventions

#ifndef leaf_blas_H
#define leaf_blas_H

#include "mkl.h"

inline void leaf_gemm( int m, int n, int k, const float a[], int lda, const float b[], int ldb, float c[], int ldc, char transa='N', char transb='N', float alpha=1, float beta=1 ) {
    sgemm( &transa, &transb, &m, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc );
}

inline void leaf_gemm( int m, int n, int k, const double a[], int lda, const double b[], int ldb, double c[], int ldc, char transa='N', char transb='N', double alpha=1, double beta=1  ) {
    dgemm( &transa, &transb, &m, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc );
}

inline void leaf_trsm(int m, int n, const float b[], int ldb, float a[], int lda, char side='L', char transa='N', char diag='N', float alpha=1  ) {
    strsm(&side, "Lower", &transa, &diag, &m, &n, &alpha, b, &ldb, a, &lda);
}

inline void leaf_trsm(int m, int n, const double b[], int ldb, double a[], int lda, char side='L', char transa='N', char diag='N', double alpha=1 ) {
    dtrsm(&side, "Lower", &transa, &diag, &m, &n, &alpha, b, &ldb, a, &lda);
}

inline void leaf_getrf( int m, int n, float a[], int lda, int ipiv[], int* info ) {
    sgetrf(&m,&n,a,&lda,ipiv,info);
}

inline void leaf_getrf( int m, int n, double a[], int lda, int ipiv[], int* info ) {
    dgetrf(&m,&n,a,&lda,ipiv,info);
}

inline void leaf_syrk( int n, int k, const float a[], int lda, float c[], int ldc, float alpha=-1, float beta=1 ) {
    ssyrk( "Lower", "No transpose", &n, &k, &alpha, a, &lda, &beta, c, &ldc );
}

inline void leaf_syrk( int n, int k, const double a[], int lda, double c[], int ldc, double alpha=-1, double beta=1 ) {
    dsyrk( "Lower", "No transpose", &n, &k, &alpha, a, &lda, &beta, c, &ldc );
}

inline void leaf_potf2( int n, float a[], int lda, int* info, char uplo='L' ) {
    spotf2( &uplo, &n, a, &lda, info );
}

inline void leaf_potf2( int n, double a[], int lda, int* info, char uplo='L' ) {
    dpotf2( &uplo, &n, a, &lda, info );
}

inline void leaf_potrf( int n, float a[], int lda, int* info, char uplo='L' ) {
    spotrf( &uplo, &n, a, &lda, info );
}

inline void leaf_potrf( int n, double a[], int lda, int* info, char uplo='L' ) {
    dpotrf( &uplo, &n, a, &lda, info );
}

template<typename T>
inline void leaf_potf2( int n, T a[], int lda ) { // Version without "info" argument.
    int tmp;
    leaf_potrf( n, a, lda, &tmp );
}

// Utility function for getting pointer to op(a)(i,j) where op is usual BLAS transa parameter for a.
template<typename T>
inline T* at( char transa, int i, int j, T a[], int lda ) {
    assert( transa=='N'||transa=='n'||transa=='T'||transa=='t' );
    return transa=='T'||transa=='t' ? a+j+i*lda : a+i+j*lda;
}

#endif /* leaf_blas_H */