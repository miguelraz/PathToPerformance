const size_t CutOff = 128; 

// Polynomial multiplication C=A*B.
// A = a[0:n]
// B = b[0:n]
// C = c[0:2*n-1]
void karatsuba( T c[], const T a[], const T b[], size_t n ) {
    if( n<=CutOff ) {
        simple_mul( c, a, b, n );
    } else { 
        size_t m = n/2;
        // Set c[0:n-1] = $t_0$
        cilk_spawn karatsuba( c, a, b, m );
        // Set c[2*m:n-1] = $t_2$
        cilk_spawn karatsuba( c+2*m, a+m, b+m, n-m );
        temp_space<T> s(4*(n-m));
        T *a_=s.data(), *b_=a_+(n-m), *t=b_+(n-m); 
        a_[0:m] = a[0:m]+a[m:m];
        b_[0:m] = b[0:m]+b[m:m];
        if( n&1 ) {
            a_[m] = a[2*m];
            b_[m] = b[2*m];
        }
        // Set t = $t_1$
        karatsuba( t, a_, b_, n-m ); 
        cilk_sync;
        // Set t = $t_1 - t_0 - t_2$
        t[0:2*m-1] -= c[0:2*m-1] + c[2*m:2*m-1];
        // Add $(t_1 - t_0 - t_2) K$ into final product.
        c[2*m-1] = 0;
        c[m:2*m-1] += t[0:2*m-1];
        if( n&1 ) 
            c[3*m-1:2] += t[2*m-1:2] - c[4*m-1:2];
    }
}
