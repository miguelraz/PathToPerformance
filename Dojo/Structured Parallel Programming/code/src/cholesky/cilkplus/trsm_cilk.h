/* Cilk implementation of BLAS ?trsm for case of solving  X*transpose(B)=A.
   It does not have the full generality of the standard BLAS routine, but 
   only the functionality required for the Cholesky solver.  Specifically, 
   in BLAS parlance, it assumes that UPLO='L', ALPHA=1, TRANSB='T', and 
   SIDE='R'.  The names of arguments a and b are swapped to make the 
   routine easier to understand as a callee of potrf. */ 
template<typename T>
void parallel_trsm( int m, int n, const T b[], int ldb, T a[], int lda ) {
    if( double(m)*m*n<=CUT ) {
        // Leaf case - solve with serial BLAS
        leaf_trsm(m, n, b, ldb, a, lda, 'R', 'T', 'N' );
     } else {
        if( m>=n ) {                             
            // Partition $A$ into $\left[ \begin{array}{c} \; A_0 \; \\ \hline A_1 \end{array}\right]$ 
            int m2=m/2;
            // Solve $X_0 \times B^T = A_0$, and set $A_0=X_0$.  
            cilk_spawn parallel_trsm( m2, n, b, ldb, a, lda );
            // Solve $X_1 \times B^T = A_1$, and set $A_1=X_1$. 
            parallel_trsm( m-m2, n, b, ldb, a+m2, lda );
        } else {
            // Partition $B$ into $\left[ \begin{array}{cc} B_{00}^T & B_{10}^T \\ 0 & B_{11}^T \end{array}\right]$ and $A$ into $\left[ \begin{array}{c|c} A_0 \cstrut & A_1 \end{array}\right]$         
            // where $B_{00}$ and $B_{11}$ are lower triangular matrices.
            int n2=n/2;
            // Solve $X_0 \times B_{00}^T=A_0$, and set $A_0=X_0$.  
            parallel_trsm( m, n2, b, ldb, a, lda );
            // Set $A_1 -= A_0*B_{10}^T$
            parallel_gemm( m, n-n2, n2, 
                           a, lda, b+n2, ldb, a+n2*lda, lda, 
                          'N', 'T', T(-1), T(1) );
            // Solve $X_1 \times B_{11}^T=A_1$, and set $A_1=X_1$.
            parallel_trsm( m, n-n2, b+n2+n2*ldb, ldb, a+n2*lda, lda );
        }
    }
    // implicit cilk_sync
}
