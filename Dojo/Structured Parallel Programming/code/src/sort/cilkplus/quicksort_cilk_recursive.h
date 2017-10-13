void parallel_quicksort( T* first, T* last ) {
    if( last-first<=QUICKSORT_CUTOFF ) {
        std::sort(first,last);
    } else {
        // Divide
        if( T* middle = divide(first,last) ) {
            // Conquer subproblems in parallel
            cilk_spawn parallel_quicksort( first, middle );
            parallel_quicksort( middle+1, last );
            // no cilk_sync needed here because of implicit one later
        }
    }
    // Implicit cilk_sync when function returns
}