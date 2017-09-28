#define NOMINMAX /* Required on Windows to avoid breaking std::min */

#include <cassert>
#include <cstddef>

// Examples borrow class temp_space from the Karatsuba example
#include "../../karatsuba/common/temp_space.h"

#if HAVE_CILKPLUS
#include <cilk/cilk.h>
#include "cilkplus/cilk_scan.h"
#endif

template<typename Scanner>
void TestBlockedScan() {
    typedef typename Scanner::value_type T;
    const size_t max_n = 4096;
    T in[max_n], out[max_n];
    bool touched[max_n];
    for( size_t n=0; n<max_n; ++n ) {
        for( size_t i=0; i<n; ++i ) {
            in[i] = (i+1)*(i+2)/2;
            out[i] = T(-1);
            touched[i] = false;
        } 
        T initial = 1<<n;
        Scanner::template parallel_scan( n, initial, 128,
            [&]( size_t i, size_t n ) -> T {
                size_t sum=0;
                for( size_t j=i; j<i+n; ++j ) {
                    sum += in[j];
                    assert(!touched[j]);
                    touched[j] = true;
                }
                return sum;
            },
            []( T x, T y ) {return x+y;},
            [&]( size_t i, size_t n, T initial ) {
                for( size_t j=i; j<i+n; ++j ) {
                    initial += in[j];
                    out[j] = initial;
                }
            }
        );
        T sum=initial;
        for( size_t i=0; i<n; ++i ) {
            sum += in[i];
            assert(sum==out[i]);
            assert(touched[i]);
        }
    }
}

#include "serial/inclusive_scan.h"
#include "serial/exclusive_scan.h"
#include <functional>

template<typename T>
void TestSerialScan() {
    const size_t n_max = 20;
    T a[n_max+1], b[n_max+1], c[n_max+1];
    for( size_t n=0; n<n_max; ++n ) {
        for( size_t i=0; i<=n; ++i ) {
            a[i] = 1+i*i;
            b[i] = -1;
            c[i] = -1;
        }
        T initial = 42;
        inclusive_scan(n,a,b,std::plus<int>(),initial);
        exclusive_scan(n,a,c,std::plus<int>(),initial);
        if( n>0 ) {
            assert(b[0]==initial+a[0]);
            assert(c[0]==initial);
            for( size_t i=1; i<n; ++i ) {
                assert(b[i]==b[i-1]+a[i]);
                assert(c[i]==c[i-1]+a[i-1]);
            }
            // Check for writing too far
            assert(b[n]==-1);
            assert(c[n]==-1);
        }
    }
}

#include "cilkplus/pack.h"
#include "tbb/pack.h"
#include "tbb/tick_count.h"
#include "serial/serial_pack.h"

enum Kind {Serial,Cilk,TBB};

template<typename T>
void TimePack( Kind kind, const char* what ) {
    double min_time = 2;
    const size_t n = 2000000;
    static int trials = 0;
    bool first_time = trials==0;
    if( first_time ) {
        trials = 1;
    }
    static T a[n];
    static T b[n];
    for( size_t k=0; k<n; ++k )
        a[k] = (k%3)*10*k;
    size_t m;
    double t;
    for(;;) {
        tbb::tick_count t0;
        for( int i=-1; i<trials; ++i ) {
            if( i==0 ) t0 = tbb::tick_count::now();
            switch( kind ) {
                case Serial: 
                    m = serial_pack( a, n, b, []( T x ) {return x!=0;} );
                    break;
                case Cilk:
#if HAVE_CILKPLUS
                    m = pack( a, n, b, []( T x ) {return x!=0;} );
#else
                    m = 0;
#endif
                    break;
                case TBB:
                    m = tbb_pack( a, n, b, []( T x ) {return x!=0;} );
                    break;
            }
        }
        tbb::tick_count t1 = tbb::tick_count::now();
        t = (t1-t0).seconds();
        if( !first_time || t>=min_time ) break;
        trials *= 2;
    }
    if( first_time ) {
        printf("Timing %d packings of %d %s\n",trials,unsigned(n),what);
        printf("%10s %s\n","version","seconds");
    }
    printf("%10s %g\n",kind==Serial?"serial":kind==Cilk?"Cilk Plus":"TBB",t);
    size_t j=0;
    for( size_t k=0; k<n; ++k ) 
        if( a[k]!=0 ) {
            assert( b[j]==a[k] );
            ++j;
        }
}

// Alas C++ does not allow "template template function parameters".  
// So the function templates are wrapped in classes.

#if HAVE_CILKPLUS
struct CilkPlusScan {
    typedef int value_type;
    template<typename T, typename R, typename C, typename S>
    static void parallel_scan( size_t n, T initial, size_t tilesize, R reduce, C combine, S scan ) {
        cilk_scan(n,initial,tilesize,reduce,combine,scan);
    }
};
#endif 

#if HAVE_OPENMP
#include <algorithm>
#include "openmp/openmp_scan.h"

struct OpenMPScan {
    typedef int value_type;
    template<typename T, typename R, typename C, typename S>
    static void parallel_scan( size_t n, T initial, size_t tilesize, R reduce, C combine, S scan ) {
        openmp_scan(n,initial,tilesize,reduce,combine,scan);
    }
};
#endif /* HAVE_OPENMP */

int main() {
    // Test the scan algorithms
    printf("Testing serial scan...\n");
    TestSerialScan<int>();
#if HAVE_CILKPLUS
    printf("Testing Cilk Plus scan...\n");
    TestBlockedScan<CilkPlusScan>();
#endif
#if HAVE_OPENMP
    printf("Testing OpenMP scan...\n");
    TestBlockedScan<OpenMPScan>();
    printf("\n");
#endif 

    // Time and verify the pack algorithms
    TimePack<int>(Serial,"int");
#if HAVE_CILKPLUS
    TimePack<int>(Cilk,"int");
#endif
    TimePack<int>(TBB,"int");
    return 0;
}
