#include <functional>

template<typename T, typename Pred> 
size_t pack( const T a[], size_t n, T b[], Pred p ) {
    size_t_ result;
    parallel_scan( n, size_t(0), 128,
        [&]( size_t i, size_t m ) -> T {
            size_t initial=0;
            for( size_t j=i; j<i+m; ++j )
                if( p(a[j]) )
                    ++initial;
                return initial;
        },
        std::plus<T>,
        [&]( size_t i, size_t m, T initial ) {
            for( size_t j=i; j<i+m; ++j ) {
                b[initial] = a[j];
                if( p(a[i]) )
                    ++initial;
            }
            if( i+m==n )
                // Save result from last block
                result = sum;
        }
    );
    return result;
}