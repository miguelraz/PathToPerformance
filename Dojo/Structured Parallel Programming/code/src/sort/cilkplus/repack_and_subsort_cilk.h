// Auxilary routine used by sample_sort.
void repack_and_subsort( T* xs, T* xe, size_t m, const T* y, const size_t tally[M_MAX][M_MAX] ) {
    // Compute column sums of tally, forming the running sum of bin sizes.
    size_t col_sum[M_MAX];
    col_sum[0:m] = 0;
    for( size_t i=0; i<m; ++i )
        col_sum[0:m] += tally[i][0:m];
    assert( col_sum[m-1]==xe-xs );

    // Copy buckets into their bins and do the subsorts
    size_t block_size = ((xe-xs)+m-1)/m;
    cilk_for( size_t j=0; j<m; ++j ) {
        T* x_bin = xs + (j==0 ? 0 : col_sum[j-1]);
        T* x = x_bin;
        for( size_t i=0; i<m; ++i ) {
            const T* src_row = y+i*block_size;
            x = std::move( src_row+(j==0?0:tally[i][j-1]), src_row+tally[i][j], x );
        }
        parallel_quicksort(x_bin,x);
    }
}