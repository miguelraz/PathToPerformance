// Functionality shared by all implementations of sample sort.

// Max number of bins.  Must not exceed 256.
const size_t M_MAX = 32; 

const size_t SAMPLE_SORT_CUT_OFF = 2000;

size_t floor_lg2( size_t n ) {
    size_t k = 0;
    for( ; n>1; n>>=1 ) 
        ++k;
    return k;
}

#include "choose_number_of_bins.h"

typedef unsigned char bindex_type;

// Assumes that m is a power of 2
void build_sample_tree( const T* xs, const T* xe, T tree[], size_t m ) {
    // Compute oversampling coefficient o as approximately log(xe-xs)
    assert(m<=M_MAX);
    size_t o = floor_lg2(xe-xs);
    const size_t O_MAX = 8*(sizeof(size_t));
    size_t n_sample = o*m-1;
    T tmp[O_MAX*M_MAX-1];
    size_t r = (xe-xs-1)/(n_sample-1);
    // Generate oversampling
    for( size_t i=0; i<n_sample; ++i )
        tmp[i] = xs[i*r];
    // Sort the samples
    std::sort( tmp, tmp+n_sample );
    // Select samples and put them into the tree
    size_t step = n_sample+1;
    for( size_t level=1; level<m; level*=2 ) {
        for( size_t k=0; k<level; ++k )
            tree[level-1+k] = tmp[step/2-1+k*step];
        step /= 2;
    }
}
