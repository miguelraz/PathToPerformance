// sorts [xs,xe).  zs[0:xe-xs) is temporary buffer supplied by caller.
// result is in [xs,xe) if inplace==true, otherwise in zs[0:xe-xs)
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
       tbb::parallel_invoke( [=]{parallel_merge_sort( xs, xm, zs, !inplace );},
                             [=]{parallel_merge_sort( xm, xe, zm, !inplace );} );
       if( inplace )
           parallel_merge( zs, zm, zm, ze, xs );
       else
           parallel_merge( xs, xm, xm, xe, zs );
   }
}

void call_parallel_merge_sort( T* xs, T* xe ) {
    T* zs = new T[xe-xs];
    parallel_merge_sort( xs, xe, zs, true );
    delete[] zs;
}