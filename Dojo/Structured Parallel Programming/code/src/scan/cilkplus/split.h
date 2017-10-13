#include <cstddef>

// Return greatest power of 2 less than m
size_t split( size_t m ) {
    size_t k=1; 
    while( 2*k<m ) k*=2;
    return k;   
}
