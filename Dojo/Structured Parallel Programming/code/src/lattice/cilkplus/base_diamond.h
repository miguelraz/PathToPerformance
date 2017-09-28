template<typename T, typename F>
void base_diamond( T* a, T* b, size_t w, int s, size_t n, const F& f ) {
    size_t kfinish = std::min( 2*w-1, n );
    for( size_t k=s; k<kfinish; ++k ) {
        int m = std::min(k+1,2*w-1-k);
        T* as = a+std::max(w,k+1)-w;
        T* bs = b-std::min(k,w-1);
        as[0:m] = f( bs[0:m], as[0:m] );
        bs[0:m] = as[0:m];
    }
}