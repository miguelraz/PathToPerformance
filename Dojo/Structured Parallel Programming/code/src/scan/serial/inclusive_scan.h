template<typename T, typename C>
void inclusive_scan(
    size_t n,    // number of elements
    const T a[], // input collection
    T A[],       // output collection
    C combine,   // combiner functor
    T initial    // initial value 
) {
    for (size_t i=0; i<n; ++i) {
        initial = combine(initial,a[i]);     
        A[i] = initial;
    }
}
