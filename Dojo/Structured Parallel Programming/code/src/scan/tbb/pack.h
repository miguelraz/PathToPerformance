#include "tbb/tbb.h"

// The "body" object to pass to tbb::parallel_scan
template<typename T, typename Pred> 
struct scanner {
    const T* a;
    T* b;
    Pred p;
    size_t sum;
    template<typename Tag>
    void operator()( const tbb::blocked_range<size_t>& r, Tag ) {
        size_t r_end = r.end();
        size_t j = sum;
        for( size_t i=r.begin(); i!=r_end; ++i ) 
            if( p(a[i]) )
                if( Tag::is_final_scan() )
                    b[j++] = a[i];
                else
                    j++;
        sum = j; 
    }     
    scanner( const T a_[], T b_[], Pred p_ ) : a(a_), b(b_), p(p_) {}
    scanner( scanner& y, tbb::split ) : a(y.a), b(y.b), p(y.p), sum(0) {}
    void reverse_join( scanner& x ) {sum += x.sum;}
    void assign( scanner& b ) {sum = b.sum;}
};

template<typename T, typename Pred> 
size_t tbb_pack( const T a[], size_t n, T b[], Pred p ) {
    scanner<T,Pred> z(a,b,p);
    size_t grainsize = 10000;
    tbb::parallel_scan( tbb::blocked_range<size_t>(0,n,grainsize), z );
    return z.sum;
}
