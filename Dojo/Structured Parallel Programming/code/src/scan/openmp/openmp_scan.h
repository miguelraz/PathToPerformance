#include <omp.h>

template<typename T, typename R, typename C, typename S>
void openmp_scan( 
    size_t n, 
    T initial, 
    size_t tilesize, 
    R reduce, 
    C combine, 
    S scan 
) {
    if (n > 0) {
        // Set t to the number of tiles that might be used, at most one tile
        // per thread with no tile smaller than the requested tilesize.
        size_t t = std::min( size_t(omp_get_max_threads()), (n-1)/tilesize+1 );
        // Allocate space to hold the reduction value of each tile.
        temp_space<T> r(t);
        // Request one thread per tile. 
#pragma omp parallel num_threads(t)
        {
            // Find out how threads were actually delivered, which may be 
            // fewer than the requested number.
            size_t p = omp_get_num_threads();
            // Recompute tilesize so there is one tile per actual thread.
            tilesize = (n+p-1)/p;
            // Set m to index of last tile
            size_t m = p-1;
#pragma omp for
            // Set r[i] to reduction of the ith tile
            for ( size_t i = 0; i <= m; ++i )
                r[i] = reduce(i*tilesize, i==m ? n-m*tilesize : tilesize);
#pragma omp single
            // Use single thread to do in-place exclusive scan on r.
            for ( size_t i = 0; i <= m; ++i ) {
                T tmp = r[i];
                r[i] = initial;
                initial = combine(initial,tmp);
            }
#pragma omp for
            // Do scan over each tile, using r[i] as initial value.
            for ( size_t i = 0; i <= m; ++i )
                scan(i*tilesize, i==m ? n-m*tilesize : tilesize, r[i]);
        }
    }
}
