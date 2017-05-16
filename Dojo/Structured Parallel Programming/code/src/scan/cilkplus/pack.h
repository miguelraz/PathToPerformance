template<typename T, typename Pred> 
size_t pack( const T a[], size_t n, T b[], Pred p ) {
    size_t result;
    cilk_scan( n, size_t(0), 10000,
        [&]( size_t i, size_t m ) -> T {
            size_t sum=0;
            for( size_t j=i; j<i+m; ++j )
                if( p(a[j]) )
                    sum++;
                return sum;
        },
        std::plus<T>(),
        [&]( size_t i, size_t m, T sum ) {
            for( size_t j=i; j<i+m; ++j ) 
                if( p(a[j]) ) 
                    b[sum++] = a[j];
            if( i+m==n )
                // Save result from last tile
                result = sum;
        }
    );
    return result;
}