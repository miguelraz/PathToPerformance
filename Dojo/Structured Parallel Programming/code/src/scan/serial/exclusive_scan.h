template<typename T, typename C>
void exclusive_scan(
    size_t n,    // number of elements
    const T a[], // input collection
    T A[],       // output collection
    C combine,   // combiner functor
    T initial    // initial value 
) {
    if( n>0 ) {
        for (size_t i=0; i<n-1; ++i) {
            A[i] = initial;
            initial = combine(initial,a[i]);     
        }
        A[n-1] = initial;
    }
}