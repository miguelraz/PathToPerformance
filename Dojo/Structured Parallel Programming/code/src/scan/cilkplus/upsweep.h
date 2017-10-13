template<typename T, typename R, typename C>
void upsweep( size_t i, size_t m,  size_t tilesize, T r[], size_t lastsize, R reduce, C combine ) {
    if( m==1 ) {
        r[0] = reduce(i*tilesize, lastsize); 
    } else {
        size_t k = split(m);
        cilk_spawn upsweep(i, k, tilesize, r, tilesize, reduce, combine);
        upsweep(i+k, m-k, tilesize, r+k, lastsize, reduce, combine);
        cilk_sync;
        if( m==2*k )
            r[m-1] = combine(r[k-1], r[m-1]);
    }
}