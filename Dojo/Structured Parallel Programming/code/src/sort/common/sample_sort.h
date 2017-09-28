void parallel_sample_sort( T* xs, T* xe ) {
    if( xe-xs<=SAMPLE_SORT_CUT_OFF ) {
        parallel_quicksort(xs,xe);
    } else {
        size_t m = choose_number_of_bins(xe-xs);
        size_t tally[M_MAX][M_MAX];
        T* y = new T[xe-xs];
        bin(xs, xe, m, y, tally);
        repack_and_subsort(xs, xe, m, y, tally);
        delete[] y;
    }
}
