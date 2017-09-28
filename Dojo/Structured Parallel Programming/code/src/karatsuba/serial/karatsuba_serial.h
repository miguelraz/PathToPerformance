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
        karatsuba( c, a, b, m );
        // Set c[2*m:n-1] = $t_2$
        karatsuba( c+2*m, a+m, b+m, n-m );
        temp_space<T> s(4*(n-m));
        T *a_=s.data(), *b_=a_+(n-m), *t=b_+(n-m); 
        for( size_t j=0; j<m; ++j ) {
            a_[j] = a[j]+a[m+j];
            b_[j] = b[j]+b[m+j];
        }
        if( n&1 ) {
            a_[m] = a[2*m];
            b_[m] = b[2*m];
        }
        // Set t = $t_1$
        karatsuba( t, a_, b_, n-m ); 
        
        // Set t = $t_1 - t_0 - t_2$
        for( size_t j=0; j<2*m-1; ++j )
            t[j] -= c[j] + c[2*m+j];
        // Add $(t_1 - t_0 - t_2) K$ into final product.
        c[2*m-1] = 0;
        for( size_t j=0; j<2*m-1; ++j )
            c[m+j] += t[j];
        if( n&1 ) 
            for( size_t j=0; j<2; ++j )
                c[3*m-1+j] += t[2*m-1+j] - c[4*m-1+j];
    }
}
