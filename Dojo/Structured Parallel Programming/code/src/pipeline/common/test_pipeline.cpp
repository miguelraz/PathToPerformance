#include <cassert>

class BugWorkAround {
#if TBB_VERSION_MAJOR<4
    // Work around bug in parallel_pipeline that occurs when objects fit in one word.
    char bloat[8];
#endif
};

class U;

class T: BugWorkAround {
    int seqno;
    friend struct F;
    friend struct G;
    T( int i ) : seqno(i) {}
public:
    T() : seqno(-2) {}
    operator bool() const {
        assert( seqno>=-1 );
        return seqno>=0;
    }
};

class U: BugWorkAround {
    int seqno;
    explicit U( int i ) : seqno(i) {}
    friend struct G;
    friend struct H;
public:
    U() : seqno(-2) {}
};

static int InputCounter;
static int InputLimit;
static int OutputCounter;

struct F {
    T operator()() const {
        if( InputCounter<InputLimit )
            return T(InputCounter++);
        else
            return T(-1);
    }
};

F f;

struct G {
    U operator()( T t ) const {
        return U(t.seqno);
    }
};

G g;

struct H {
    void operator()( U u ) const {
        assert(u.seqno==OutputCounter);
        ++OutputCounter;
    }
};

H h;

struct HState {
};

void h_( HState*, U u ) {
    h(u);
}

#include "../serial/serial_pipeline.h"
#include "tbb/pipeline.h"
#include "../tbb/tbb_sps_pipeline.h"
#if HAVE_CILKPLUS
#include <cilk/cilk.h>
#include "../cilkplus/reducer_consume.h"
#include "../cilkplus/cilk_sps_pipeline.h"
#endif /* HAVE_CILIPLUS */
#include <cstdio>

int main() {
#if HAVE_CILKPLUS
    std::printf("Testing reducer_consume...\n");
    void test_reducer_consume();
    test_reducer_consume();
#endif

    std::printf("Testing tbb_sps_pipeline...\n");
    for( int k=0; k<2; ++k ) {
        InputLimit = 1000;
        InputCounter = 0;
        OutputCounter = 0;
        if( k==0 ) tbb_sps_pipeline( 8 );
#if HAVE_CILKPLUS
        else cilk_sps_pipeline();
#endif 
    }
}
