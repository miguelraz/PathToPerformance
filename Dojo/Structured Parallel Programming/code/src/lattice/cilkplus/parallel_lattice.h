template<typename T, typename F>
void recursive_diamond( T* a, T* b, size_t w, int s, size_t n, const F& f ) {
    if( w<=CUT_OFF ) {
        base_diamond( a, b, w, s, n, f );
    } else {
        size_t h = w/2;
        recursive_diamond( a, b, h, s, n, f );
        if( h<n ) {
            cilk_spawn recursive_diamond( a+h, b, h, 0, n-h, f );
            recursive_diamond( a, b-h, h, 0, n-h, f );
            if( w<n ) {
                cilk_sync;
                recursive_diamond( a+h, b-h, h, 0, n-2*h, f );
            }
        }
    }
}

template<typename T, typename F>
void parallel_lattice( T* a, size_t n, F f ) {
    T* b = new T[n];
    std::reverse_copy( a, a+n, b );
    size_t w=1;
    while( w<n ) w*=2;
    recursive_diamond( a, b+n-1, w, 1, n, f );
    delete[] b;
}
