template<typename T, typename Pred> 
size_t serial_pack( const T a[], size_t n, T b[], Pred p ) {
    size_t j=0;
    for( size_t i=0; i<n; ++i )
        if( p(a[i]) )
            b[j++] = a[i];
    return j;
}
