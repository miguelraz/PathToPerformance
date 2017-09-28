// Cilk implementation of BLAS ?syrk for symmetric rank update 
// A is an nxn matrix, C is a nxk matrix 
// Sets A -= C*trans(C).
template<typename T>
void parallel_syrk( int n, int k, const T c[], int ldc, T a[], int lda ) {
    if( double(n)*n*k<=CUT ) {
        leaf_syrk( n, k, c, ldc, a, lda );
    } else if( n>=k ) {
        int n2=n/2; 
        cilk_spawn parallel_syrk( n2, k, c, ldc, a, lda ); /*@\label{line:syrk:fork:begin}@*/
        cilk_spawn parallel_gemm( n-n2, n2, k, 
                                  c+n2, ldc, c, ldc, a+n2, lda, 
                                  'N', 'T', T(-1), T(1) );
        parallel_syrk( n-n2, k, c+n2, ldc, a+n2+n2*lda, lda ); /*@\label{line:syrk:fork:end}@*/
    } else {
        int k2=k/2;
        parallel_syrk( n, k2, c, ldc, a, lda );
        parallel_syrk( n, k-k2, c+k2*ldc, ldc, a, lda );
    }
    // implicit cilk_sync
}