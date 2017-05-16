//! Cilk implementation of BLAS ?gemm
template<typename T>
void parallel_gemm( int m, int n, int k, const T a[], int lda, const T b[], int ldb, T c[], int ldc, char transa='N', char transb='N', T alpha=1, T beta=1 ) {
    assert(1<=m);
    assert(1<=n);
    assert(1<=k);
    assert(transa=='N'||transa=='n'||transa=='T'||transa=='t');
    assert(transb=='N'||transb=='n'||transb=='T'||transb=='t');
    if( double(m)*n*k<=CUT ) {
        leaf_gemm( m, n, k, a, lda, b, ldb, c, ldc, transa, transb, alpha, beta );
    } else if( n>=m && n>=k ) {
        int n2=n/2;
        cilk_spawn parallel_gemm( m, n2, k, a, lda, b, ldb, c, ldc, transa, transb, alpha, beta );
        parallel_gemm( m, n-n2, k, a, lda, at(transb,0,n2,b,ldb), ldb, c+n2*ldc, ldc, transa, transb, alpha, beta );  
    } else if( m>=k ) {
        int m2=m/2;
        cilk_spawn parallel_gemm( m2, n, k, a, lda, b, ldb, c, ldc, transa, transb, alpha, beta );
        parallel_gemm( m-m2, n, k, at(transa,m2,0,a,lda), lda, b, ldb, c+m2, ldc, transa, transb, alpha, beta );  
    } else {
        int k2=k/2;
        parallel_gemm( m, n, k2, a, lda, b , ldb, c, ldc, transa, transb, alpha, beta );
        // Note: using default beta=1 is intentional
        parallel_gemm( m, n, k-k2, at(transa,0,k2,a,lda), lda, at(transb,k2,0,b,ldb), ldb, c, ldc, transa, transb, alpha ); 
    }
}
