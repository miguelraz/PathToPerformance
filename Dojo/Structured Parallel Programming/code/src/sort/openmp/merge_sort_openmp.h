// sorts [xs,xe).  zs[0:xe-xs) is temporary buffer supplied by caller.
// result is in [xs,xe) if inplace==true, otherwise in zs[0:xe-xs).
void parallel_merge_sort( T* xs, T* xe, T* zs, bool inplace ) {
    const size_t SORT_CUT_OFF = 500;
    if( xe-xs<=SORT_CUT_OFF ) {
       std::stable_sort( xs, xe );
       if( !inplace ) 
           std::move( xs, xe, zs );
   } else {
       T* xm = xs + (xe-xs)/2;
       T* zm = zs + (xm-xs);
       T* ze = zs + (xe-xs);
#pragma omp task
       parallel_merge_sort( xs, xm, zs, !inplace );
       parallel_merge_sort( xm, xe, zm, !inplace );
#pragma omp taskwait  
       if( inplace )
           parallel_merge( zs, zm, zm, ze, xs );
       else
           parallel_merge( xs, xm, xm, xe, zs );
   }
}

// OpenMP tasks do not run in parallel unless launched inside a thread team.
// This outer wrapper shows how to create the thread team and run the top-level call.
void do_parallel_merge_sort( T* xs, T* xe, T* zs, bool inplace ) {
    // Create a thread team.
#pragma omp parallel
    // Make only one thread do the top-level call.  
    // Other threads in team pick up spawned tasks.   
#pragma omp single 
    {
        parallel_merge_sort( xs, xe, zs, true );
    }
}
