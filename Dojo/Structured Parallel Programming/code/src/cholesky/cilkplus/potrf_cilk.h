template<typename T>
void parallel_potrf( int n, T a[], int lda ) {
    if( double(n)*n*n<=CUT ) {
        // Leaf case - solve with serial LAPACK
        leaf_potf2( n, a, lda );
    } else {
        int n2=n/2;
        // Solve $A_{00} = L_{00} L_{00}^T$ for $L_{00}$ and set $A_{00}=L_{00}$.
        parallel_potrf( n2, a, lda );
        // Solve $A_{10} = L_{10} L_{00}^T$ for $L_{10}$ and set $A_{10}=L_{10}$.
        parallel_trsm( n-n2, n2, a, lda, a+n2, lda );
        // Set $A_{11} = A_{11} - L_{10}\times L_{10}^T$.
        parallel_syrk( n-n2, n2, a+n2, lda, a+n2+n2*lda, lda ); 
        // Solve $A_{11}^T = L_{11} L_{11}^T$ for $L_{11}$.
        parallel_potrf( n-n2, a+n2+n2*lda, lda );
    }
}