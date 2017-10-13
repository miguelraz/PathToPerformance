// Set bindex[0..n) to the bin index of each key in x[0..n), using the given implicit binary tree with m-1 entries. 
void map_keys_to_bins( const T x[], size_t n, const T tree[], size_t m, bindex_type bindex[], size_t freq[] ) {
    size_t d = floor_lg2(m);
    std::fill_n(freq,m,0);
    for( size_t i=0; i<n; ++i ) {
        size_t k = 0;
        for( size_t j=0; j<d; ++j )
            k = 2*k+2 - (x[i] < tree[k]);
        ++freq[bindex[i] = k-(m-1)];
    }
}
