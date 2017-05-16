// Polynomial multiplication C=A*B that takes quadratic time.
// A = a[0:n]
// B = b[0:n]
// C = c[0:2*n-1]
// This routine is used for the "small n" basecase in Karatsuba multiplication.
void simple_mul( T c[], const T a[], const T b[], size_t n ) {
    c[0:2*n-1] = 0;
    for (size_t i=0; i<n; ++i) 
        c[i:n] += a[i]*b[0:n];
}