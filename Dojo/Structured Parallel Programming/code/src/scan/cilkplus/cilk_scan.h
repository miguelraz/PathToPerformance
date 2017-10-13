#include "split.h"
#include "upsweep.h"
#include "downsweep.h"

template<typename T, typename R, typename C, typename S>
void cilk_scan( size_t n, T initial, size_t tilesize, R reduce, C combine, S scan ) {
    if( n>0 ) {
        size_t m = (n-1)/tilesize;
        temp_space<T> r(m+1);
        upsweep(0, m+1, tilesize, r.data(), 
                n-m*tilesize, reduce, combine);
        downsweep(0, m+1, tilesize, r.data(), 
                n-m*tilesize, initial, combine, scan);
    }
}
