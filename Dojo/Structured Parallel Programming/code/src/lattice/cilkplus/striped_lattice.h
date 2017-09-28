template<typename T, typename F>
void striped_lattice( T* a, size_t n, F f ) {
    T* b = new T[n];
    std::reverse_copy( a, a+n, b );
    size_t w=CUT_OFF;
    for( size_t i=0; i<n; i+=w )
        cilk_for( size_t j=0; j<=i; j+=w )
            base_diamond( a+j, b+n-1-(i-j), w, i?0:1, n-i, f );
    delete[] b;
}