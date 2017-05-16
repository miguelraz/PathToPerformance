template<typename T, typename C, typename S>
void downsweep( size_t i, size_t m, size_t tilesize, const T r[], size_t lastsize, T initial, C combine, S scan ) {
    if( m==1 ) {
        scan(i*tilesize, lastsize, initial);
    } else {
        size_t k = split(m);
        cilk_spawn downsweep(i, k, tilesize, r, tilesize, initial, combine, scan);
        initial = combine(initial, r[k-1]);
        downsweep(i+k, m-k, tilesize, r+k, lastsize, initial, combine, scan);
        // implicit cilk_sync;
    }
}