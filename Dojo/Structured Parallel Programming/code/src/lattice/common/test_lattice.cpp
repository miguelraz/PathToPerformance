#include <cassert>
#include <cstring>
#include <cmath>
#include <stdio.h>
#include <algorithm>
#if HAVE_CILKPLUS
#include <cilk/cilk.h>
#endif

const size_t MAX_WIDTH = 1<<16;
const size_t CUT_OFF = 1<<8;

typedef float T;

struct Plus {
    T operator()( T x, T y ) const {
        return (x+y)/2;
    }
};

#if HAVE_CILKPLUS
#include "cilkplus/base_diamond.h"
#include "cilkplus/parallel_lattice.h"
#include "cilkplus/striped_lattice.h"
#endif 

template<typename T, typename F>
void serial_lattice( T* a, size_t n, F f ) {
    for( int i=1; i<n; ++i ) {
        for( int j=i; j>0; --j )
            a[j] = f(a[j-1],a[j]);
        a[0] = f(T(0),a[0]);
    }
}

static T A[MAX_WIDTH];
static T B[MAX_WIDTH];

static const char* What = NULL;

static void check() {
    for( size_t k=0; k<MAX_WIDTH; ++k ) {
        T expected=A[0];
        T actual=A[1];
        T error = fabs(actual-expected);
        T tol = 0;
        if( error>tol ) {
            printf("Error for %s: A[%d]=%g != %g\n", What, int(k), actual, expected );
        }
    }
}

#include "tbb/tick_count.h"

int main() {
    printf("%12s %s\n","Version","Seconds");
    for( int t=0; t<12; ++t ) {
        switch( t%3 ) {
            case 0:  std::memset( A, 0, MAX_WIDTH*sizeof(A[0]) ); A[0]=1; break;
            default: std::memset( B, 0, MAX_WIDTH*sizeof(B[0]) ); B[0]=1; break;
        }
        tbb::tick_count t0 = tbb::tick_count::now();
        switch( t%3 ) {
            case 0: serial_lattice( A, MAX_WIDTH, Plus() ); What="serial"; break;
#if HAVE_CILKPLUS
            case 1: striped_lattice( B, MAX_WIDTH, Plus() ); What="striped"; break;
            case 2: parallel_lattice( B, MAX_WIDTH, Plus() ); What="parallel"; break;
#else
            default:
                continue;
#endif
        }
        tbb::tick_count t1 = tbb::tick_count::now();
        if( t%3 ) {
            check();
        }
        printf("%12s %g\n",What,(t1-t0).seconds());
    }
    return 0;
}
